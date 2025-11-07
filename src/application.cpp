#include "application.h"

#include "at32f435_437_board.h"
#include "at32f435_437_clock.h"
#include "at32f435_437_misc.h"
#include "beep.h"
#include "wifi.h"
#include "board.h"
#include "timer.h"
#include "config.h"
#include "custom.h"
#include "events_init.h"
#include "gui_guider.h"
#include "lcd.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_tick_custom.h"
#include "lvgl.h"
#include "key.h"
#include "oled.h"
#include "music.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define USING_EXT_FLASH 1

lv_ui guider_ui;

tmr_output_config_type tmr_oc_init_structure;

void PWM_init(void) {
    uint16_t ccr1_val = 333;
    uint16_t ccr2_val = 249;
    uint16_t ccr3_val = 166;
    uint16_t prescalervalue = 0;

    gpio_init_type gpio_init_struct;
    crm_periph_clock_enable(CRM_TMR3_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_pins = GPIO_PINS_6 | GPIO_PINS_7 | GPIO_PINS_8;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init(GPIOC, &gpio_init_struct);

    gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE6, GPIO_MUX_2);
    gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE7, GPIO_MUX_2);
    gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE8, GPIO_MUX_2);

    /* compute the prescaler value */

    prescalervalue = (uint16_t)((crm_clocks_freq_struct.apb1_freq * 2) / 24000000) - 1;

    /* tmr3 time base configuration */
    tmr_base_init(TMR3, 665, prescalervalue);
    tmr_cnt_dir_set(TMR3, TMR_COUNT_UP);
    tmr_clock_source_div_set(TMR3, TMR_CLOCK_DIV1);

    tmr_output_default_para_init(&tmr_oc_init_structure);
    tmr_oc_init_structure.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_A;
    tmr_oc_init_structure.oc_idle_state = FALSE;
    tmr_oc_init_structure.oc_polarity = TMR_OUTPUT_ACTIVE_HIGH;
    tmr_oc_init_structure.oc_output_state = TRUE;
    tmr_output_channel_config(TMR3, TMR_SELECT_CHANNEL_1, &tmr_oc_init_structure);
    tmr_channel_value_set(TMR3, TMR_SELECT_CHANNEL_1, 665);
    tmr_output_channel_buffer_enable(TMR3, TMR_SELECT_CHANNEL_1, TRUE);

    tmr_output_channel_config(TMR3, TMR_SELECT_CHANNEL_2, &tmr_oc_init_structure);
    tmr_channel_value_set(TMR3, TMR_SELECT_CHANNEL_2, 0);
    tmr_output_channel_buffer_enable(TMR3, TMR_SELECT_CHANNEL_2, TRUE);

    tmr_output_channel_config(TMR3, TMR_SELECT_CHANNEL_3, &tmr_oc_init_structure);
    tmr_channel_value_set(TMR3, TMR_SELECT_CHANNEL_3, 665);
    tmr_output_channel_buffer_enable(TMR3, TMR_SELECT_CHANNEL_3, TRUE);

    tmr_period_buffer_enable(TMR3, TRUE);

    /* tmr enable counter */
    tmr_counter_enable(TMR3, TRUE);
}

__IO uint32_t time_cnt = 0;

// 心跳包相关变量
uint32_t heartbeat_timer = 0;
uint8_t connection_status = 0; // 0: 未连接, 1: 已连接
uint32_t last_heartbeat_response_time = 0;
uint8_t heartbeat_sent = 0;                 // 标记是否已发送心跳包等待响应
uint32_t connection_lost_time = 0;          // 连接丢失时间
uint8_t consecutive_heartbeat_failures = 0; // 连续心跳失败次数
#define HEARTBEAT_INTERVAL 55000            // 55秒心跳间隔
#define HEARTBEAT_TIMEOUT 5000              // 5秒心跳响应超时
#define MAX_HEARTBEAT_FAILURES 3            // 最大连续心跳失败次数
#define CONNECTION_RETRY_INTERVAL 300000    // 5分钟重连间隔

// WiFi异步连接请求标志（由心跳或启动时触发）
volatile uint8_t wifi_reconnect_requested = 1;

// 心跳包发送函数
void send_heartbeat() {
    printf("\r\n发送心跳包: Q\r\n");
    comSendBuf(COM3, (uint8_t *)"Q", 1);
    heartbeat_sent = 1; // 标记已发送心跳包
    last_heartbeat_response_time = Timer_GetTickCount();
}

// 检查心跳包响应
// 添加设备状态变量
uint8_t lm75_temp = 0;       // lm75温度值
uint16_t adc_value = 0;      // adc值
uint8_t aircon_status = 0;   // 空调状态 (LED_GREEN)
uint8_t lighting_status = 0; // 照明状态 (LED_YELLOW)

// 命令解析缓冲区
char command_buffer[256];
uint8_t command_index = 0;
uint8_t command_ready = 0;

// 状态上报定时器
uint32_t send_timer = 0;

// LED控制函数
void control_aircon(uint8_t status) {
    aircon_status = status;
    if (status) {
        at32_led_on(LED_GREEN);
        printf("\r\n空调已开启 (LED_GREEN ON)\r\n");
    } else {
        at32_led_off(LED_GREEN);
        printf("\r\n空调已关闭 (LED_GREEN OFF)\r\n");
    }
}

void control_lighting(uint8_t status) {
    lighting_status = status;
    if (status) {
        at32_led_on(LED_Yellow);
        printf("\r\n照明已开启 (LED_YELLOW ON)\r\n");
    } else {
        at32_led_off(LED_Yellow);
        printf("\r\n照明已关闭 (LED_YELLOW OFF)\r\n");
    }
}

// 获取连接状态
uint8_t get_connection_status(void) {
    return connection_status;
}

// 发送状态上报
char TlinkCommandStr[20];
void send_status_report() {
    lm75_temp = lm75_read();  // 读取lm75温度值
    adc_value = analogRead(); // 读取ADC值
    sprintf(TlinkCommandStr, "#%d,%d,%d,%d#", lm75_temp, adc_value, aircon_status, lighting_status);

    printf("\r\n上报状态: %s\r\n", TlinkCommandStr);

    if (get_connection_status()) {
        comSendBuf(COM3, (uint8_t *)TlinkCommandStr, strlen(TlinkCommandStr));
    } else {
        printf("连接断开，状态未上报\r\n");
    }
}

// JSON解析
void parse_command(char *cmd) {
    printf("\r\n收到命令: %s\r\n", cmd);

    // 查找aircon_switch命令
    if (strstr(cmd, "aircon_switch") != NULL) {
        if (strstr(cmd, "\"switch\":1") != NULL) {
            control_aircon(1);
        } else if (strstr(cmd, "\"switch\":0") != NULL) {
            control_aircon(0);
        }
        send_timer = 25000;
    }

    // 查找lighting_switch命令
    if (strstr(cmd, "lighting_switch") != NULL) {
        if (strstr(cmd, "\"switch\":1") != NULL) {
            control_lighting(1);
        } else if (strstr(cmd, "\"switch\":0") != NULL) {
            control_lighting(0);
        }
        send_timer = 25000;
    }
}

// 处理接收到的数据
void process_received_data() {
    uint8_t received_data;

    while (comGetChar(COM3, &received_data)) {
        // 处理心跳响应
        if (heartbeat_sent && received_data == 'A') {
            printf("\r\n收到心跳响应: A\r\n");
            connection_status = 1;
            heartbeat_sent = 0;
            consecutive_heartbeat_failures = 0;
            last_heartbeat_response_time = Timer_GetTickCount();
            continue;
        }

        // 处理JSON命令
        if (received_data == '[') {
            // 开始接收命令
            command_index = 0;
            command_buffer[command_index++] = received_data;
            command_ready = 0;
        } else if (received_data == ']' && command_index > 0) {
            // 命令接收完成
            command_buffer[command_index++] = received_data;
            command_buffer[command_index] = '\0';
            command_ready = 1;
        } else if (command_index > 0 && command_index < sizeof(command_buffer) - 1) {
            // 继续接收命令内容
            command_buffer[command_index++] = received_data;
        }

        // 如果命令准备好了，解析它
        if (command_ready) {
            parse_command(command_buffer);
            command_ready = 0;
            command_index = 0;
        }
    }
}

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

void esp12_init_wifi(void) {
    char testStr[] = "9B0Y5S576WNBR380";
    comSendBuf(COM3, (uint8_t *)"+++", 3);
    // printf("\r\n 发送AT指令: AT\r\n");
    delay_ms1(1000);

    g_wifi.sendAT("AT");
    if (g_wifi.waitResponse("OK", 5000) != 1) {
        printf("\r\n AT fail!\r\n");
        delay_ms1(1000);
    }
    g_wifi.sendAT("ATE0");
    if (g_wifi.waitResponse("OK", 50) != 1) {
        printf("\r\n ATE0 fail\r\n");
    }

    if (g_wifi.setWiFiMode(1) != 1) {
        printf("\r\n CWMODE fail\r\n");
    }

    // 使用库函数进行AP连接，避免手动AT并统一处理应答
    if (g_wifi.joinAP(wifi_name, wifi_password, 15000) != 1) {
        printf("\r\n CWJAP fail\r\n");
        delay_ms1(1000);
    }
    g_wifi.sendAT("AT+CIPSTART=\"TCP\",\"tcp.tlink.io\",8647");
    if (g_wifi.waitResponse("OK", 5000) != 1) {
        printf("\r\n CIPSTART fail\r\n");
    }

    g_wifi.sendAT("AT+CIPMODE=1");
    if (g_wifi.waitResponse("OK", 1000) != 1) {
        printf("\r\n CIPMODE fail\r\n");
    }

    g_wifi.sendAT("AT+CIPSEND");
    if (g_wifi.waitResponse("OK", 1000) != 1) {
        printf("\r\n CIPSEND fail\r\n");
    }
    printf("\r\n 服务器已连接!\r\n");
    comSendBuf(COM3, (uint8_t *)testStr, strlen(testStr));
    delay_ms1(4000);
}

// 检测心跳包 函数
void check_heartbeat_response(void) {
    process_received_data();

    // 检查心跳响应超时
    if (heartbeat_sent && Timer_PassedDelay(last_heartbeat_response_time, HEARTBEAT_TIMEOUT)) {
        // printf("\r\n心跳响应超时 (失败次数: %d)\r\n", consecutive_heartbeat_failures + 1);
        heartbeat_sent = 0;
        consecutive_heartbeat_failures++;

        if (consecutive_heartbeat_failures >= MAX_HEARTBEAT_FAILURES) {
            if (connection_status == 1) {
                printf("\r\n连续%d次心跳失败，连接断开\r\n", MAX_HEARTBEAT_FAILURES);
                connection_status = 0;
                connection_lost_time = Timer_GetTickCount();
            }
        }
    }
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
        check_heartbeat_response();

        // 检查是否需要重连
        if (should_reconnect()) {
            printf("\r\n检测到连接断开超过5分钟，尝试重连...\r\n");
            wifi_reconnect_requested = 1;
        }

        // 定时发送心跳包
        if ((xTaskGetTickCount() - lastHeartbeatTick) >= pdMS_TO_TICKS(HEARTBEAT_INTERVAL)) {
            lastHeartbeatTick = xTaskGetTickCount();
            if (connection_status) {
                send_heartbeat();
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
        if (get_connection_status()) {
            send_status_report();
        } else {
            printf("连接断开，数据未发送\r\n");
        }

        vTaskDelay(pdMS_TO_TICKS(30000));
    }
}

static void TaskLED(void *pvParameters) {
    (void)pvParameters;
    for (;;) {
        at32_led_toggle(LED_Yellow);
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

static void TaskKeys(void *pvParameters) {
    (void)pvParameters;
    for (;;) {
        uint8_t keyvalue = Key::GetInstance().get();
        if (keyvalue == KEY_1_DOWN) {
            g_beep.keyTone();
            printf("KEY_1_DOWN - 切换空调状态\r\n");
            control_aircon(!aircon_status);
            send_status_report();
        }
        if (keyvalue == KEY_2_DOWN) {
            g_beep.keyTone();
            printf("KEY_2_DOWN - 切换照明状态\r\n");
            control_lighting(!lighting_status);
            send_status_report();
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
            printf("\r\n开始WiFi连接（异步）...\r\n");
            esp12_init_wifi();
            reset_connection_status();
            printf("\r\nWiFi连接完成，心跳机制启动\r\n");
            wifi_reconnect_requested = 0;
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

Application::Application() {}
Application::~Application() {}

void Application::Start() {
    uint16_t i;
    // bsp_Init();
    auto& board = Board::GetInstance();
    board.Init();

#if USING_EXT_FLASH
    ext_flash_init();
#endif

    g_wifi.sendAT("AT");
    if (g_wifi.waitResponse("OK", 50) == 1) {
        printf("\r\n ESP12 resp OK\r\n");
        delay_ms(1000);
    }

    // driver init
    tmr7_int_init(287, 999); // 1 micro second interrupt
    lcd_init(LCD_DISPLAY_HORIZONTAL_180);
    touch_init(TOUCH_SCAN_HORIZONTAL_180);

    // lvgl init
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();

    // ui init
    setup_ui(&guider_ui);
    events_init(&guider_ui);
    custom_init(&guider_ui);

    // 异步WiFi连接任务在后台进行连接，不阻塞UI

    // 初始化 ADC 值
    last_adc_value = (uint32_t)analogRead() * 3300 / 4095;
    update_adc_display(&guider_ui);

    // 创建FreeRTOS任务
    xTaskCreate(TaskLVGL, "lvgl", 1024, NULL, tskIDLE_PRIORITY + 2, NULL);
    xTaskCreate(TaskWiFi, "wifi", 1024, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(TaskHeartbeat, "heartbeat", 1024, NULL, tskIDLE_PRIORITY + 3, NULL);
    xTaskCreate(TaskADC, "adc", 512, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(TaskStatus, "status", 768, NULL, tskIDLE_PRIORITY + 1, NULL);
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