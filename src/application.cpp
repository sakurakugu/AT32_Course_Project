#include "application.h"

#include "IoT.hpp"
#include "at32f435_437_clock.h"
#include "at32f435_437_misc.h"
#include "beep.h"
#include "board.h"
#include "board/bsp_eep_lm75.h"
#include "board/led/led.h"
#include "color_led.h"
#include "config.h"
#include "custom.h"
#include "events_init.h"
#include "gui_guider.h"
#include "key.h"
#include "lcd.hpp"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_tick_custom.h"
#include "lvgl.h"
#include "music.h"
#include "oled.h"
#include "timer.h"
#include "touch.hpp"
#include "wifi.hpp"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define USING_EXT_FLASH 1

lv_ui guider_ui;

__IO uint32_t time_cnt = 0;

// 串口COM3接收保护：为避免HTTP响应被其他任务抢占
volatile uint8_t g_com3_guard = 0;

// 检查心跳包响应

// 获取连接状态字符串
const char *get_connection_status_string(void) {
    if (connection_status) {
        return "已连接";
    } else {
        if (consecutive_heartbeat_failures > 0) {
            return "连接不稳定";
        } else {
            return "未连接";
        }
    }
}

// 检查是否需要重连
uint8_t should_reconnect(void) {
    return (connection_status == 0 && connection_lost_time > 0 &&
            Timer_PassedDelay(connection_lost_time, CONNECTION_RETRY_INTERVAL));
}

// 重置连接状态
void reset_connection_status(void) {
    connection_status = 1;
    consecutive_heartbeat_failures = 0;
    connection_lost_time = 0;
    last_heartbeat_response_time = Timer_GetTickCount();
}

void tlink_init_wifi() {
    char testStr[] = "9B0Y5S576WNBR380";
    comSendBuf(COM3, (uint8_t *)"+++", 3);
    // printf("\r\n 发送AT指令: AT\r\n");
    delay_ms1(1000);

    auto &wifi = Wifi::GetInstance();

    wifi.sendAT("AT");
    if (wifi.waitResponse("OK", 5000) != 1) {
        printf("\r\n AT fail!\r\n");
        delay_ms1(1000);
    }
    wifi.sendAT("ATE0");
    if (wifi.waitResponse("OK", 50) != 1) {
        printf("\r\n ATE0 fail\r\n");
    }

    if (wifi.setWiFiMode(1) != 1) {
        printf("\r\n CWMODE fail\r\n");
    }

    // 使用库函数进行AP连接，避免手动AT并统一处理应答
    if (wifi.joinAP(wifi_ssid, wifi_password, 15000) != 1) {
        printf("\r\n CWJAP fail\r\n");
        delay_ms1(1000);
    }
    wifi.sendAT("AT+CIPSTART=\"TCP\",\"tcp.tlink.io\",8647");
    if (wifi.waitResponse("OK", 5000) != 1) {
        printf("\r\n CIPSTART fail\r\n");
    }

    wifi.sendAT("AT+CIPMODE=1");
    if (wifi.waitResponse("OK", 1000) != 1) {
        printf("\r\n CIPMODE fail\r\n");
    }

    wifi.sendAT("AT+CIPSEND");
    if (wifi.waitResponse("OK", 1000) != 1) {
        printf("\r\n CIPSEND fail\r\n");
    }
    printf("\r\n 服务器已连接!\r\n");
    comSendBuf(COM3, (uint8_t *)testStr, strlen(testStr));
    delay_ms1(4000);
}

static bool wifi_save_credentials_to_eeprom(const char *ssid, const char *pwd) {
    if (!ssid || !pwd)
        return false;
    size_t ssid_len = strlen(ssid);
    size_t pwd_len = strlen(pwd);
    if (ssid_len > 32 || pwd_len > 64)
        return false;

    uint8_t ssid_buf[33] = {0};
    uint8_t pwd_buf[65] = {0};
    memcpy(ssid_buf, ssid, ssid_len);
    memcpy(pwd_buf, pwd, pwd_len);

    eep_write(WIFI_EEP_ADDR_SSID, ssid_buf, sizeof(ssid_buf));
    eep_write(WIFI_EEP_ADDR_PASSWORD, pwd_buf, sizeof(pwd_buf));
    return true;
}

static bool wifi_load_credentials_from_eeprom(char *ssid_out, size_t ssid_out_size, char *pwd_out,
                                              size_t pwd_out_size) {
    if (!ssid_out || !pwd_out)
        return false;
    if (ssid_out_size < 33 || pwd_out_size < 65)
        return false;

    uint8_t ssid_buf[33] = {0};
    uint8_t pwd_buf[65] = {0};

    eep_read(WIFI_EEP_ADDR_SSID, ssid_buf, sizeof(ssid_buf));
    eep_read(WIFI_EEP_ADDR_PASSWORD, pwd_buf, sizeof(pwd_buf));

    // 简单校验：非空
    if (ssid_buf[0] == '\0')
        return false;

    memcpy(ssid_out, ssid_buf, 33);
    memcpy(pwd_out, pwd_buf, 65);
    return true;
}

static bool wifi_connect(const char *ssid, const char *pwd, uint16_t timeout_ms = 15000) {
    if (!ssid || !pwd)
        return false;
    auto &wifi = Wifi::GetInstance();

    wifi.sendAT("AT");
    wifi.waitResponse("OK", 1000);
    wifi.sendAT("ATE0");
    wifi.waitResponse("OK", 1000);

    if (wifi.setWiFiMode(1) != 1) {
        printf("\r\n CWMODE fail\r\n");
        return false;
    }

    if (wifi.joinAP(ssid, pwd, timeout_ms) != 1) {
        printf("\r\n CWJAP fail\r\n");
        return false;
    }
    return true;
}

// 在设置页面显示已连接的Wi‑Fi名称
static void update_wifi_name_label(lv_ui *ui, const char *ssid) {
    if (!ui || !ssid)
        return;
    char label_text[80];
    snprintf(label_text, sizeof(label_text), "Wifi名称: %s", ssid);
    lv_label_set_text(ui->setting_app_wifi_name_text, label_text);
}

/**
 * @brief  main function.
 * @param  none
 * @retval none
 */

// 添加全局变量用于 ADC 值变化检测
static uint32_t last_adc_value = 0;
static uint32_t adc_update_threshold = 10; // ADC 值变化阈值（毫伏）

/**
 * @brief 检查 ADC 值是否发生了显著变化
 * @param new_value 新的 ADC 值（毫伏）
 * @param old_value 旧的 ADC 值（毫伏）
 * @return true 如果值发生了显著变化，false 否则
 */
bool adc_value_changed(uint32_t new_value, uint32_t old_value) {
    uint32_t diff = (new_value > old_value) ? (new_value - old_value) : (old_value - new_value);
    return diff >= adc_update_threshold;
}

/**
 * @brief 更新 LVGL 界面中的 ADC 显示值
 * @param ui LVGL UI 结构体指针
 */
void update_adc_display(lv_ui *ui) {
    char adc_str[32];
    sprintf(adc_str, "%d mV", last_adc_value);
    // lv_label_set_text(ui->screen_counter, adc_str);
}

// FreeRTOS任务声明
static void TaskLVGL(void *pvParameters);
static void TaskHeartbeat(void *pvParameters);
static void TaskADC(void *pvParameters);
static void TaskStatus(void *pvParameters);
static void TaskLED(void *pvParameters);
static void TaskKeys(void *pvParameters);
static void TaskWiFi(void *pvParameters);

// FreeRTOS任务实现
static void TaskLVGL(void *pvParameters) {
    (void)pvParameters;
    for (;;) {
        lv_task_handler();
        vTaskDelay(pdMS_TO_TICKS(25));
    }
}

static void TaskHeartbeat(void *pvParameters) {
    (void)pvParameters;
    TickType_t lastHeartbeatTick = xTaskGetTickCount();
    for (;;) {
        // 处理心跳响应与命令
        IoT::GetInstance().Check_Heartbeat();

        // 检查是否需要重连
        if (should_reconnect()) {
            printf("\r\n检测到连接断开超过5分钟，尝试重连...\r\n");
            wifi_reconnect_requested = 1;
        }

        // 定时发送心跳包
        if ((xTaskGetTickCount() - lastHeartbeatTick) >= pdMS_TO_TICKS(HEARTBEAT_INTERVAL)) {
            lastHeartbeatTick = xTaskGetTickCount();
            if (connection_status) {
                IoT::GetInstance().Send_Heartbeat();
            }
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

static void TaskADC(void *pvParameters) {
    (void)pvParameters;
    for (;;) {
        uint32_t current_adc_value = (uint32_t)analogRead() * 3300 / 4095;
        if (adc_value_changed(current_adc_value, last_adc_value)) {
            last_adc_value = current_adc_value;
            update_adc_display(&guider_ui);
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

static void TaskStatus(void *pvParameters) {
    (void)pvParameters;
    for (;;) {
        // 显示连接状态
        printf(" [%s]", get_connection_status_string());

        // 打印上一轮的状态字符串（兼容原逻辑）
        printf("%s\r\n", TlinkCommandStr);

        // 连接状态下上报当前状态
        if (connection_status) {
            IoT::GetInstance().Send_Status_Report();
        } else {
            printf("连接断开，数据未发送\r\n");
        }

        vTaskDelay(pdMS_TO_TICKS(30000));
    }
}

static void TaskLED(void *pvParameters) {
    (void)pvParameters;
    for (;;) {
        LED::GetInstance().Toggle(LED_Yellow);
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

static void TaskKeys(void *pvParameters) {
    (void)pvParameters;
    for (;;) {
        uint8_t keyvalue = Key::GetInstance().get();
        if (keyvalue == KEY_1_DOWN) {
            g_beep.keyTone();
        }
        if (keyvalue == KEY_2_DOWN) {
            g_beep.keyTone();
            printf("KEY_2_DOWN - 切换照明状态\r\n");
            IoT::GetInstance().Control_Lighting(!lighting_status);
            IoT::GetInstance().Send_Status_Report();
        }
        if (keyvalue == KEY_3_DOWN) {
            g_beep.keyTone();
            if (!music_playing) {
                printf("KEY_3_DOWN - 开始播放音乐\r\n");
                music_start = 1;  /* 由音乐任务消费 */
                music_resume = 0; /* 确保处于播放状态 */
            } else {
                music_resume = !music_resume;
                printf("KEY_3_DOWN - %s播放\r\n", music_resume ? "暂停" : "继续");
                if (music_resume) {
                    g_beep.disableOutput(); /* 立即静音 */
                }
            }
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

// 异步WiFi连接任务：在后台执行连接过程，不阻塞UI
static void TaskWiFi(void *pvParameters) {
    (void)pvParameters;
    for (;;) {
        if (wifi_reconnect_requested) {
            printf("wifi名称：%s\r\n", wifi_ssid);
            printf("wifi密码：%s\r\n", wifi_password);
            printf("\r\n开始WiFi连接...\r\n");
            // 仅连接到路由器，不建立到Tlink的TCP
            bool ok = wifi_connect(wifi_ssid, wifi_password, 15000);
            if (ok) {
                printf("\r\nWiFi已连接: %s\r\n", wifi_ssid);
                update_wifi_name_label(&guider_ui, wifi_ssid);
                wifi_save_credentials_to_eeprom(wifi_ssid, wifi_password);
            } else {
                printf("\r\nWiFi连接失败\r\n");
            }
            wifi_reconnect_requested = 0;
            // // 原有路径：同时建立到Tlink服务器的连接
            // tlink_init_wifi();
            // reset_connection_status();
            // printf("\r\nWiFi+Tlink连接完成，心跳机制启动\r\n");
            // wifi_reconnect_requested = 0;
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

Application::Application() {}
Application::~Application() {}

void Application::Start() {
    uint16_t i;
    // bsp_Init();
    auto &board = Board::GetInstance();
    board.Init();

#if USING_EXT_FLASH
    ext_flash_init();
#endif

    auto &wifi = Wifi::GetInstance();
    wifi.sendAT("AT");
    if (wifi.waitResponse("OK", 50) == 1) {
        printf("\r\n ESP12 OK\r\n");
        delay_ms(1000);
    }

    // driver init
    tmr7_int_init(287, 999); // 1 micro second interrupt
    lcd_init(LCD_DISPLAY_HORIZONTAL_180);
    Touch::GetInstance().Init(TOUCH_SCAN_HORIZONTAL_180);

    // lvgl init
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();

    // ui init
    setup_ui(&guider_ui);
    events_init(&guider_ui);
    custom_init(&guider_ui);

    // 从EEPROM加载上次保存的Wi‑Fi凭据并自动连接
    if (wifi_load_credentials_from_eeprom(wifi_ssid, sizeof(wifi_ssid), wifi_password, sizeof(wifi_password))) {
        lv_textarea_set_text(guider_ui.setting_app_wifi_name_input, wifi_ssid);
        lv_textarea_set_text(guider_ui.setting_app_wifi_password_input, wifi_password);
        update_wifi_name_label(&guider_ui, wifi_ssid);
        wifi_reconnect_requested = 1; // 启动后台自动连接Wi‑Fi
    }

    // 异步WiFi连接任务在后台进行连接，不阻塞UI

    // 初始化 ADC 值
    last_adc_value = (uint32_t)analogRead() * 3300 / 4095;
    update_adc_display(&guider_ui);

    // 创建FreeRTOS任务
    // 增大 LVGL 任务栈深度，避免在显示键盘等复杂布局时栈溢出
    xTaskCreate(TaskLVGL, "lvgl", 2048, NULL, tskIDLE_PRIORITY + 2, NULL);
    xTaskCreate(TaskWiFi, "wifi", 1024, NULL, tskIDLE_PRIORITY + 1, NULL);
    // xTaskCreate(TaskHeartbeat, "heartbeat", 1024, NULL, tskIDLE_PRIORITY + 3, NULL);
    xTaskCreate(TaskADC, "adc", 512, NULL, tskIDLE_PRIORITY + 1, NULL);
    // xTaskCreate(TaskStatus, "status", 768, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(TaskLED, "led", 256, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(TaskKeys, "keys", 512, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(TaskMusic, "music", 512, NULL, tskIDLE_PRIORITY + 1, NULL);

    printf("FreeRTOS任务创建完成\r\n");
    // 启动调度器，不会返回
    vTaskStartScheduler();

    // 如果调度器返回（通常不会），进入安全死循环
    while (1) {}
}

/**
 * @brief 重启设备
 */
void Application::Reboot() {
    printf("正在重启...\r\n");
    nvic_system_reset();
}

// 统一定时任务处理：由 bsp_RunPer10ms 调用，每10ms一次
void Application::OnClockTimer() {}

// /**
//  * @brief 添加异步任务到主循环
//  * @param callback 要执行的回调函数
//  */
// void Application::Schedule(std::function<void()> callback) {
//     {
//         std::lock_guard<std::mutex> lock(mutex_); // 加锁
//         main_tasks_.push_back(std::move(callback)); // 添加任务到列表
//     }
//     xEventGroupSetBits(event_group_, SCHEDULE_EVENT); // 设置事件组
// }