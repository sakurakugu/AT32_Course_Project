#include "setting.hpp"
#include "../board/lcd/lcd.hpp"
#include "../network/wifi.hpp"
#include "logger.h"
#include "lvgl.h"
#include "../../gui/generated/gui_guider.h"
#include "../../gui/custom/custom.h"
#include "uart.h"
#include "beep.hpp"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// 来自应用的串口接收保护标志
extern volatile uint8_t g_com3_guard;

#ifdef __cplusplus
extern "C" {
#endif

bool Setting_SyncNetworkTime(bool sync) {
    return Setting::GetInstance().SyncNetworkTime(sync);
}
void Setting_BacklightSetPercent(uint8_t percent) {
    Setting::GetInstance().BacklightSetPercent(percent);
}

#ifdef __cplusplus
}
#endif

// 引用各屏幕的时钟全局变量（widgets_init.c 中以 extern 引用）
extern int g_time_hour_value;
extern int g_time_min_value;
extern int g_time_sec_value;

extern lv_obj_t *g_status_bar_date;
extern int clock_app_analog_clock_1_hour_value;
extern int clock_app_analog_clock_1_min_value;
extern int clock_app_analog_clock_1_sec_value;
extern lv_ui guider_ui;

bool Setting::SyncNetworkTime(bool sync) {
    auto &wifi = Wifi::GetInstance();

    LOGI("开始同步网络时间\n");

    // 保护COM3接收，避免IoT任务抢占HTTP响应
    g_com3_guard = 1;
    (void)tlink_disconnect_wifi();

    // 建立到 quan.suning.com 的 TCP 连接
    wifi.SendAT("AT+CIPSTART=\"TCP\",\"quan.suning.com\",80");
    if (wifi.WaitResponse("OK", 5000) != 1) {
        g_com3_guard = 0;
        wifi_set_time_sync_done(false);
        // 失败时保持同步开关为关闭
        if (lv_obj_is_valid(guider_ui.setting_app_sync_net_time_sw)) {
            lv_obj_clear_state(guider_ui.setting_app_sync_net_time_sw, LV_STATE_CHECKED);
        }
        return false;
    }

    // 构造 HTTP GET 请求：苏宁系统时间接口（增加常见头以避免403）
    const char *req = "GET /getSysTime.do HTTP/1.1\r\n"
                      "Host: quan.suning.com\r\n"
                      "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64)\r\n"
                      "Accept: application/json\r\n"
                      "Accept-Encoding: identity\r\n"
                      "Accept-Language: zh-CN,zh;q=0.9\r\n"
                      "Origin: http://quan.suning.com\r\n"
                      "Referer: http://quan.suning.com/\r\n"
                      "Cache-Control: no-cache\r\n"
                      "Connection: close\r\n\r\n";
    char cmd[32];
    sprintf(cmd, "AT+CIPSEND=%d", (int)strlen(req));
    wifi.SendAT(cmd);
    if (wifi.WaitResponse(">", 2000) != 1) {
        wifi.SendAT("AT+CIPCLOSE");
        wifi.WaitResponse("OK", 1000);
        g_com3_guard = 0;
        wifi_set_time_sync_done(false);
        if (lv_obj_is_valid(guider_ui.setting_app_sync_net_time_sw)) {
            lv_obj_clear_state(guider_ui.setting_app_sync_net_time_sw, LV_STATE_CHECKED);
        }
        return false;
    }
    // 发送 HTTP 请求正文
    comSendBuf(COM3, (uint8_t *)req, (uint32_t)strlen(req));
    // 不再等待 "SEND OK"，直接读取所有行直到连接关闭
    // 等待数据到来标记 "+IPD"，确认服务端已返回数据
    wifi.WaitResponse("+IPD", 8000);

    // 读取响应（按行叠加到缓冲区）
    char resp[2048] = {0};
    char line[512];
    int pos = 0;
    while (1) {
        uint16_t n = wifi.ReadLine(line, sizeof(line), 1500);
        if (n == 0)
            break;
        if (pos + n >= (int)sizeof(resp) - 1)
            break;
        memcpy(resp + pos, line, n);
        pos += n;
        resp[pos] = '\0';
        // 仅在连接关闭时结束读取，避免因 "HTTP/1.1 200 OK" 提前退出
        if (strstr(line, "CLOSED"))
            break;
    }

    // 在解析前先检查HTTP状态码
    if (strstr(resp, "HTTP/1.1 200") == NULL) {
        // 关闭连接并报告错误
        wifi.SendAT("AT+CIPCLOSE");
        wifi.WaitResponse("OK", 2000);
        LOGI("HTTP状态非200，响应前200字节: %.*s\n", 200, resp);
        g_com3_guard = 0;
        wifi_set_time_sync_done(false);
        if (lv_obj_is_valid(guider_ui.setting_app_sync_net_time_sw)) {
            lv_obj_clear_state(guider_ui.setting_app_sync_net_time_sw, LV_STATE_CHECKED);
        }
        return false;
    }

    // 解析时间字段
    int year = 0, month = 0, day = 0, hour = 0, min = 0, sec = 0;
    bool ok = ParseDatetimeISO8601(resp, &year, &month, &day, &hour, &min, &sec);

    // 关闭连接
    wifi.SendAT("AT+CIPCLOSE");
    wifi.WaitResponse("OK", 2000);

    if (!ok) {
        // 打印响应片段帮助定位问题
        LOGI("解析网络时间失败，响应前200字节: %.*s\n", 200, resp);
        g_com3_guard = 0;
        wifi_set_time_sync_done(false);
        if (lv_obj_is_valid(guider_ui.setting_app_sync_net_time_sw)) {
            lv_obj_clear_state(guider_ui.setting_app_sync_net_time_sw, LV_STATE_CHECKED);
        }
        return false;
    }

    // 应用到各屏幕的时间与日期标签
    ApplyTimeToAll(hour, min, sec);
    ApplyDateLabels(year, month, day);

    LOGI("同步网络时间成功：%04d-%02d-%02d %02d:%02d:%02d\n", year, month, day, hour, min, sec);
    wifi_set_time_sync_done(true);
    // 成功时将设置界面开关置为打开
    if (lv_obj_is_valid(guider_ui.setting_app_sync_net_time_sw)) {
        lv_obj_add_state(guider_ui.setting_app_sync_net_time_sw, LV_STATE_CHECKED);
    }
    g_com3_guard = 0;
    return true;
}

bool Setting::ParseDatetimeISO8601(const char *json, int *year, int *month, int *day, int *hour, int *min, int *sec) {
    // 统一定位到 HTTP Body（如果存在），避免头部干扰
    const char *body = strstr(json, "\r\n\r\n");
    if (body) {
        json = body + 4;
    }

    // 优先解析苏宁接口：sysTime1（形如 20251108204449）
    const char *p = strstr(json, "\"sysTime1\":\"");
    if (p) {
        p += strlen("\"sysTime1\":\"");
        int matched = sscanf(p, "%4d%2d%2d%2d%2d%2d", year, month, day, hour, min, sec);
        if (matched == 6) {
            return true;
        }
    }

    // 其次解析苏宁接口：sysTime2（形如 2025-11-08 20:44:49）
    p = strstr(json, "\"sysTime2\":\"");
    if (p) {
        p += strlen("\"sysTime2\":\"");
        int matched = sscanf(p, "%d-%d-%d %d:%d:%d", year, month, day, hour, min, sec);
        if (matched == 6) {
            return true;
        }
    }

    // 兼容旧的 worldtimeapi 响应："datetime":"YYYY-MM-DDThh:mm:ss[.sss][+offset]"
    const char *start = strstr(json, "\"datetime\":\"");
    if (!start) {
        return false;
    }
    start += strlen("\"datetime\":\"");
    int matched = sscanf(start, "%d-%d-%dT%d:%d:%d", year, month, day, hour, min, sec);
    if (matched == 6) {
        return true;
    }
    matched = sscanf(start, "%d-%d-%d%*c%d:%d:%d", year, month, day, hour, min, sec);
    return matched == 6;
}

void Setting::ApplyTimeToAll(int hour, int min, int sec) {
    // 更新全局时间变量
    g_time_hour_value = hour;
    g_time_min_value = min;
    g_time_sec_value = sec;
    // 更新时钟显示
    clock_app_analog_clock_1_hour_value = hour;
    clock_app_analog_clock_1_min_value = min;
    clock_app_analog_clock_1_sec_value = sec;
    if (lv_obj_is_valid(guider_ui.clock_app_analog_clock_1)) {
        lv_analogclock_set_time(guider_ui.clock_app_analog_clock_1, hour, min, sec);
    }
}

void Setting::ApplyDateLabels(int year, int month, int day) {
    char buf[20];
    snprintf(buf, sizeof(buf), "%d/%02d/%02d", year, month, day);
    if (lv_obj_is_valid(g_status_bar_date))
        lv_label_set_text(g_status_bar_date, buf);
}

void Setting::BacklightSetPercent(uint8_t percent) {
    LCD::GetInstance().BacklightSetPercent(percent);
}

#ifdef KEIL_COMPILE
// 点击“连接”按钮事件：读取输入->触发异步连接->成功后写EEPROM
void wifi_link_btn_event_handler(lv_event_t *e) {
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui)
        return;

    const char *ssid_text = lv_textarea_get_text(ui->setting_app_wifi_name_input);
    const char *pwd_text = lv_textarea_get_text(ui->setting_app_wifi_password_input);

    if (!ssid_text || !pwd_text)
        return;

    // 复制到运行时缓冲，并更新全局凭据指针
    strncpy(wifi_ssid, ssid_text, sizeof(wifi_ssid) - 1);
    strncpy(wifi_password, pwd_text, sizeof(wifi_password) - 1);
    wifi_ssid[sizeof(wifi_ssid) - 1] = '\0';
    wifi_password[sizeof(wifi_password) - 1] = '\0';

    // 由后台任务异步完成连接，避免阻塞UI
    wifi_reconnect_requested = 1;
}
#endif

#ifdef KEIL_COMPILE
// 亮度滑块事件：0 关闭背光；>0 打开背光（如需PWM可在 Setting_BacklightSetPercent 内扩展）
void setting_app_light_slider_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_VALUE_CHANGED)
        return;
    lv_obj_t *slider = lv_event_get_target(e);
    int32_t val = lv_slider_get_value(slider); // 0..100
    Setting_BacklightSetPercent((uint8_t)val);
}

// 同步网络时间开关：打开时立即触发一次与服务器的时间同步
void setting_app_sync_net_time_sw_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_VALUE_CHANGED)
        return;
    lv_obj_t *sw = lv_event_get_target(e);
    bool enabled = lv_obj_has_state(sw, LV_STATE_CHECKED);
    if (enabled) {
        bool ok = Setting_SyncNetworkTime(true);
        if (!ok) {
            lv_obj_clear_state(sw, LV_STATE_CHECKED);
        }
    }
}

// 声音开关：打开显示“声音开启”图标并允许蜂鸣器发声；关闭显示“静音”并禁止蜂鸣
void setting_app_sound_sw_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_VALUE_CHANGED)
        return;
    lv_obj_t *sw = lv_event_get_target(e);
    bool on = lv_obj_has_state(sw, LV_STATE_CHECKED);
    status_bar_update_sound(on);
    Beep_SetMute(on ? 0 : 1);
}
#endif