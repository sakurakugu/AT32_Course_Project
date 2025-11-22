#include "application.h"
#include "IoT.hpp"

#include "at32f435_437_clock.h"
#include "at32f435_437_misc.h"
#include "beep.hpp"
#include "board.h"
#include "delay.h"
#include "eeprom.h"
#include "lm75.h"
#include "mpu6050.h"
#include "board/led/led.h"
#include "color_led.hpp"
#include "config.h"
#include "custom.h"
#include "events_init.h"
#include "gui_guider.h"
#include "lcd.hpp"
#include "led.hpp"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_tick_custom.h"
#include "lvgl.h"
#include "music.hpp"
#include "oled.h"
#include "task/task_key.h"
#include "task/task_wifi.h"
#include "timer.h"
#include "touch.hpp"
#include "wifi.hpp"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define USING_EXT_FLASH 1

lv_ui guider_ui;

__IO uint32_t time_cnt = 0;
static volatile uint8_t g_temp_value = 0;
static volatile bool g_temp_dirty = false;
static volatile float g_acc_x = 0.0f;
static volatile float g_acc_y = 0.0f;
static volatile float g_acc_z = 0.0f;
static volatile float g_gyro_x = 0.0f;
static volatile float g_gyro_y = 0.0f;
static volatile float g_gyro_z = 0.0f;
static volatile float g_mpu_temp = 0.0f;
static volatile bool g_mpu_acc_dirty = false;
static volatile bool g_mpu_gyro_dirty = false;
static volatile bool g_mpu_temp_dirty = false;

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

void tlink_init_wifi() {
    char testStr[] = "9B0Y5S576WNBR380";
    comSendBuf(COM3, (uint8_t *)"+++", 3);
    // LOGI("\r\n 发送AT指令: AT\r\n");
    delay_ms(1000);

    auto &wifi = Wifi::GetInstance();

    wifi.SendAT("AT");
    if (wifi.WaitResponse("OK", 5000) != 1) {
        LOGE("\r\n AT fail!\r\n");
        delay_ms(1000);
    }
    wifi.SendAT("ATE0");
    if (wifi.WaitResponse("OK", 50) != 1) {
        LOGE("\r\n ATE0 fail\r\n");
    }

    if (wifi.SetWiFiMode(1) != 1) {
        LOGE("\r\n CWMODE fail\r\n");
    }

    // 使用库函数进行AP连接，避免手动AT并统一处理应答
    if (wifi.JoinAP(wifi_ssid, wifi_password, 15000) != 1) {
        LOGE("\r\n CWJAP fail\r\n");
        delay_ms(1000);
    }
    wifi.SendAT("AT+CIPSTART=\"TCP\",\"tcp.tlink.io\",8647");
    if (wifi.WaitResponse("OK", 5000) != 1) {
        LOGE("\r\n CIPSTART fail\r\n");
    }

    wifi.SendAT("AT+CIPMODE=1");
    if (wifi.WaitResponse("OK", 1000) != 1) {
        LOGE("\r\n CIPMODE fail\r\n");
    }

    wifi.SendAT("AT+CIPSEND");
    if (wifi.WaitResponse("OK", 1000) != 1) {
        LOGE("\r\n CIPSEND fail\r\n");
    }
    LOGI("\r\n 服务器已连接!\r\n");
    comSendBuf(COM3, (uint8_t *)testStr, strlen(testStr));
    delay_ms(4000);
}

static bool wifi_load_credentials_from_eeprom(char *ssid_out, size_t ssid_out_size, char *pwd_out,
                                              size_t pwd_out_size) {
    if (!ssid_out || !pwd_out)
        return false;
    if (ssid_out_size < 33 || pwd_out_size < 65)
        return false;

    uint8_t ssid_buf[33] = {0};
    uint8_t pwd_buf[65] = {0};

    EEP_Read(WIFI_EEP_ADDR_SSID, ssid_buf, sizeof(ssid_buf));
    EEP_Read(WIFI_EEP_ADDR_PASSWORD, pwd_buf, sizeof(pwd_buf));
    LOGD("ssid_buf: %s, pwd_buf: %s", ssid_buf, pwd_buf);

    // 简单校验：非空
    if (ssid_buf[0] == '\0')
        return false;

    memcpy(ssid_out, ssid_buf, 33);
    memcpy(pwd_out, pwd_buf, 65);
    return true;
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
    if (!ui)
        return;
    char adc_str[32];
    sprintf(adc_str, "%d mV", last_adc_value);
    // lv_label_set_text(ui->smart_home_app_ADC_num, adc_str);
}

// FreeRTOS任务声明
static void TaskLVGL(void *pvParameters);
static void TaskHeartbeat(void *pvParameters);
static void TaskADC(void *pvParameters);
// static void TaskLM75(void *pvParameters);
// static void TaskMPU6050(void *pvParameters);
static void TaskStatus(void *pvParameters);
static void TaskLED(void *pvParameters);

// FreeRTOS任务实现
static void TaskLVGL(void *pvParameters) {
    (void)pvParameters;
    portTASK_USES_FLOATING_POINT();
    for (;;) {
        if (g_temp_dirty) {
            uint8_t v = g_temp_value;
            g_temp_dirty = false;
            if (guider_ui.smart_home_app_temperature_num) {
                lv_label_set_text_fmt(guider_ui.smart_home_app_temperature_num, "%d°C", v);
            }
        }
        if (g_mpu_acc_dirty) {
            g_mpu_acc_dirty = false;
            if (guider_ui.smart_home_app_accelerated_speed_num_x) {
                lv_label_set_text_fmt(guider_ui.smart_home_app_accelerated_speed_num_x, "%.2f", g_acc_x);
            }
            if (guider_ui.smart_home_app_accelerated_speed_num_y) {
                lv_label_set_text_fmt(guider_ui.smart_home_app_accelerated_speed_num_y, "%.2f", g_acc_y);
            }
            if (guider_ui.smart_home_app_accelerated_speed_num_z) {
                lv_label_set_text_fmt(guider_ui.smart_home_app_accelerated_speed_num_z, "%.2f", g_acc_z);
            }
        }
        if (g_mpu_gyro_dirty) {
            g_mpu_gyro_dirty = false;
            if (guider_ui.smart_home_app_attitude_num_x) {
                lv_label_set_text_fmt(guider_ui.smart_home_app_attitude_num_x, "%.1f", g_gyro_x);
            }
            if (guider_ui.smart_home_app_attitude_num_y) {
                lv_label_set_text_fmt(guider_ui.smart_home_app_attitude_num_y, "%.1f", g_gyro_y);
            }
            if (guider_ui.smart_home_app_attitude_num_z) {
                lv_label_set_text_fmt(guider_ui.smart_home_app_attitude_num_z, "%.1f", g_gyro_z);
            }
        }
        if (g_mpu_temp_dirty) {
            g_mpu_temp_dirty = false;
            if (guider_ui.smart_home_app_mpu6050_teemp_num) {
                lv_label_set_text_fmt(guider_ui.smart_home_app_mpu6050_teemp_num, "%.1f°C", g_mpu_temp);
            }
        }
        // LOGI("TaskLVGL 栈的高水位标记: %d\r\n", uxTaskGetStackHighWaterMark(NULL));
        lv_task_handler();
        vTaskDelay(pdMS_TO_TICKS(25));
    }
}

static void TaskHeartbeat(void *pvParameters) {
    (void)pvParameters;
    TickType_t lastHeartbeatTick = xTaskGetTickCount();
    for (;;) {
        // 处理心跳响应与命令
        IoT::GetInstance().CheckHeartbeat();
        
        // 检查是否需要重连
        if (should_reconnect()) {
            LOGI("\r\n检测到连接断开超过5分钟，尝试重连...\r\n");
            wifi_reconnect_requested = 1;
        }

        // 定时发送心跳包
        if ((xTaskGetTickCount() - lastHeartbeatTick) >= pdMS_TO_TICKS(HEARTBEAT_INTERVAL)) {
            lastHeartbeatTick = xTaskGetTickCount();
            if (connection_status) {
                IoT::GetInstance().SendHeartbeat();
            }
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

static void TaskADC(void *pvParameters) {
    (void)pvParameters;
    for (;;) {
        uint32_t current_adc_value = (uint32_t)AnalogRead() * 3300 / 4095;
        if (adc_value_changed(current_adc_value, last_adc_value)) {
            last_adc_value = current_adc_value;
            update_adc_display(&guider_ui);
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

static void TaskLM75([[maybe_unused]] void *pvParameters) {
    for (;;) {
        uint8_t t = LM75::GetInstance().Read();
        g_temp_value = t;
        g_temp_dirty = true;
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

static void TaskMPU6050([[maybe_unused]] void *pvParameters) {
    portTASK_USES_FLOATING_POINT();
    bool inited = false;
    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(200));
        if (!inited) {
            uint8_t ret = MPU6050_Init();
            if (ret != 0) {
                LOGE("MPU6050 init failed\r\n");
                vTaskDelay(pdMS_TO_TICKS(500));
                continue;
            }
            inited = true;
        }
        int16_t ax_i, ay_i, az_i;
        if (MPU6050_GetAcc(&ax_i, &ay_i, &az_i) == 0) {
            g_acc_x = ax_i / 16384.0f;
            g_acc_y = ay_i / 16384.0f;
            g_acc_z = az_i / 16384.0f;
            g_mpu_acc_dirty = true;
        }
        int16_t gx_i, gy_i, gz_i;
        if (MPU6050_GetGyro(&gx_i, &gy_i, &gz_i) == 0) {
            g_gyro_x = gx_i / 16.4f;
            g_gyro_y = gy_i / 16.4f;
            g_gyro_z = gz_i / 16.4f;
            g_mpu_gyro_dirty = true;
        }
        short t100 = MPU6050_GetTemp();
        g_mpu_temp = t100 / 100.0f;
        g_mpu_temp_dirty = true;
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

static void TaskStatus(void *pvParameters) {
    (void)pvParameters;
    for (;;) {
        // 显示连接状态
        LOGI(" [%s]", get_connection_status_string());

        // 打印上一轮的状态字符串（兼容原逻辑）
        LOGI("%s\r\n", TlinkCommandStr);

        // 连接状态下上报当前状态
        if (connection_status) {
            IoT::GetInstance().SendStatusReport();
        } else {
            LOGI("连接断开，数据未发送\r\n");
        }

        vTaskDelay(pdMS_TO_TICKS(30000));
    }
}

static void TaskLED([[maybe_unused]] void *pvParameters) {
    for (;;) {
        LED::GetInstance().Toggle(LED_Yellow);
        vTaskDelay(pdMS_TO_TICKS(200));
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

    // 初始化 ESP12 的串口（USART3）与中断，确保后续 AT 指令有收发能力
    auto &wifi = Wifi::GetInstance();
    wifi.Init();

    wifi.SendAT("AT");
    if (wifi.WaitResponse("OK", 50) == 1) {
        LOGI("\r\n ESP12 OK\r\n");
        delay_ms(1000);
    }

    // driver init
    tmr7_int_init(287, 999); // 1 micro second interrupt
    LCD_Init(LCD_DISPLAY_HORIZONTAL_180);
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
    // if (wifi_load_credentials_from_eeprom(wifi_ssid, sizeof(wifi_ssid), wifi_password, sizeof(wifi_password))) {
    //     lv_textarea_set_text(guider_ui.setting_app_wifi_name_input, wifi_ssid);
    //     lv_textarea_set_text(guider_ui.setting_app_wifi_password_input, wifi_password);
    //     update_wifi_name_label(&guider_ui, wifi_ssid);
    //     wifi_reconnect_requested = 1; // 启动后台自动连接Wi‑Fi
    // }

    // 初始化 ADC 值
    last_adc_value = (uint32_t)AnalogRead() * 3300 / 4095;
    update_adc_display(&guider_ui);

    // 创建FreeRTOS任务
    // 增大 LVGL 任务栈深度，避免在显示键盘等复杂布局时栈溢出
    xTaskCreate(TaskLVGL, "lvgl", 8192, NULL, tskIDLE_PRIORITY + 2, NULL);
    xTaskCreate(TaskWiFi, "wifi", 1024+512, NULL, tskIDLE_PRIORITY + 1, NULL);
    // xTaskCreate(TaskHeartbeat, "heartbeat", 1024, NULL, tskIDLE_PRIORITY + 3, NULL);
    xTaskCreate(TaskADC, "adc", 256, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(TaskLM75, "lm75", 256, NULL, tskIDLE_PRIORITY + 1, NULL);
    // xTaskCreate(TaskMPU6050, "mpu6050", 1024, NULL, tskIDLE_PRIORITY + 1, NULL);
    // xTaskCreate(TaskStatus, "status", 768, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(TaskLED, "led",64+32, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(TaskKeys, "keys", 512+32, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(TaskMusic, "music", 256, NULL, tskIDLE_PRIORITY + 1, NULL);

    LOGI("FreeRTOS任务创建完成\r\n");
    // 启动调度器，不会返回
    vTaskStartScheduler();

    // 如果调度器返回（通常不会），进入安全死循环
    while (1) {}
}

/**
 * @brief 重启设备
 */
void Application::Reboot() {
    LOGI("正在重启...\r\n");
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
