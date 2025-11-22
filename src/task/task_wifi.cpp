#include "../app/setting/setting.h"
#include "eeprom.h"
#include "gui_guider.h"
#include "logger.h"
#include "timer.h"
#include "wifi.hpp"
#include <FreeRTOS.h>
#include <task.h>

volatile uint8_t wifi_reconnect_requested = 0; // 0: 未请求, 1: 请求重连
static uint32_t last_wifi_retry_time = 0;      // 最近一次失败后记录的时间戳（ms）
static bool time_sync_done = false;            // 成功同步过一次网络时间后置1
#define CONNECTION_RETRY_INTERVAL 300000       // 5分钟重连间隔
bool connection_status = 0;                    // 0: 未连接, 1: 已连接
uint32_t connection_lost_time = 0;             // 连接丢失时间
uint32_t last_heartbeat_response_time = 0;

// 检查是否需要重连
uint8_t should_reconnect(void) {
    return (connection_status == 0 && connection_lost_time > 0 &&
            Timer_PassedDelay(connection_lost_time, CONNECTION_RETRY_INTERVAL));
}

// 重置连接状态
void reset_connection_status(void) {
    connection_status = 1;
    // consecutive_heartbeat_failures = 0; // 重置心跳失败次数
    connection_lost_time = 0;
    last_heartbeat_response_time = Timer_GetTickCount();
}

static bool wifi_connect(const char *ssid, const char *pwd, uint16_t timeout_ms = 15000) {
    if (!ssid || !pwd)
        return false;
    auto &wifi = Wifi::GetInstance();

    wifi.SendAT("AT");
    wifi.WaitResponse("OK", 1000);
    wifi.SendAT("ATE0");
    wifi.WaitResponse("OK", 1000);

    if (wifi.SetWiFiMode(1) != 1) {
        LOGE("\r\n CWMODE fail\r\n");
        return false;
    }

    if (wifi.JoinAP(ssid, pwd, timeout_ms) != 1) {
        LOGE("\r\n CWJAP fail\r\n");
        return false;
    }
    return true;
}

// 在设置页面显示已连接的Wi‑Fi名称
void update_wifi_name_label(lv_ui *ui, const char *ssid) {
    if (!ui || !ssid)
        return;
    char label_text[80];
    snprintf(label_text, sizeof(label_text), "Wifi名称: %s", ssid);
    lv_label_set_text(ui->setting_app_wifi_name_text, label_text);
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

    EEP_Write(WIFI_EEP_ADDR_SSID, ssid_buf, sizeof(ssid_buf));
    EEP_Write(WIFI_EEP_ADDR_PASSWORD, pwd_buf, sizeof(pwd_buf));
    return true;
}

// 异步WiFi连接任务：在后台执行连接过程，不阻塞UI
void TaskWiFi([[maybe_unused]] void *pvParameters) {
    for (;;) {
        // LOGI("TaskWiFi 栈的高水位标记: %d\r\n", uxTaskGetStackHighWaterMark(NULL));
        if (wifi_reconnect_requested) {
            LOGD("wifi名称：%s\r\n", wifi_ssid);
            LOGD("wifi密码：%s\r\n", wifi_password);
            LOGI("\r\n开始WiFi连接...\r\n");
            // 仅连接到路由器，不建立到Tlink的TCP
            bool ok = wifi_connect(wifi_ssid, wifi_password, 15000);
            if (ok) {
                LOGI("WiFi已连接: %s\r\n", wifi_ssid);
                update_wifi_name_label(&guider_ui, wifi_ssid);
                wifi_save_credentials_to_eeprom(wifi_ssid, wifi_password);

                // 成功连接后，如果还未同步过时间，则执行一次网络时间同步
                if (!time_sync_done) {
                    bool ts_ok = Setting_SyncNetworkTime(true);
                    if (ts_ok) {
                        time_sync_done = true;
                        LOGI("网络时间已同步成功\r\n");
                    } else {
                        LOGI("网络时间同步失败\r\n");
                    }
                }

                // 成功后清除重试时间戳
                last_wifi_retry_time = 0;
            } else {
                LOGI("\r\nWiFi连接失败\r\n");
                // 记录失败时间，用于5分钟后自动重试
                last_wifi_retry_time = Timer_GetTickCount();
            }
            wifi_reconnect_requested = 0;
            // // 原有路径：同时建立到Tlink服务器的连接
            // tlink_init_wifi();
            // reset_connection_status();
            // LOGI("\r\nWiFi+Tlink连接完成，心跳机制启动\r\n");
            // wifi_reconnect_requested = 0;
        }

        // 如果上次连接失败，且已过重试间隔，则触发一次自动重试
        if (!wifi_reconnect_requested && last_wifi_retry_time != 0) {
            if (Timer_PassedDelay(last_wifi_retry_time, CONNECTION_RETRY_INTERVAL)) { // 5分钟
                LOGI("\r\n距离上次失败已过5分钟，自动重试连接Wi‑Fi\r\n");
                wifi_reconnect_requested = 1;
            }
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
