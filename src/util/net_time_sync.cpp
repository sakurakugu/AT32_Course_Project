/**
 * @brief 通过 HTTP 获取世界时间并同步到各界面（Asia/Shanghai）
 */
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "board/network/wifi.hpp"
#include "bsp_uart.h"
#include "gui_guider.h"
#include "lvgl.h"

// 引用各屏幕的时钟全局变量（widgets_init.c 中以 extern 引用）
extern int home_app1_time_hour_value; extern int home_app1_time_min_value; extern int home_app1_time_sec_value;
extern int home_app2_time_hour_value; extern int home_app2_time_min_value; extern int home_app2_time_sec_value;
extern int weather_app_time_hour_value; extern int weather_app_time_min_value; extern int weather_app_time_sec_value;
extern int music_app_time_hour_value; extern int music_app_time_min_value; extern int music_app_time_sec_value;
extern int smart_home_app_time_hour_value; extern int smart_home_app_time_min_value; extern int smart_home_app_time_sec_value;
extern int calculator_app_time_hour_value; extern int calculator_app_time_min_value; extern int calculator_app_time_sec_value;
extern int deepseek_app_time_hour_value; extern int deepseek_app_time_min_value; extern int deepseek_app_time_sec_value;
extern int setting_app_time_hour_value; extern int setting_app_time_min_value; extern int setting_app_time_sec_value;

extern lv_ui guider_ui;

static bool parse_datetime_iso8601(const char *json, int *year, int *month, int *day, int *hour, int *min, int *sec) {
    // 查找 "datetime":"YYYY-MM-DDThh:mm:ss"
    const char *p = strstr(json, "\"datetime\"");
    if (!p) return false;
    p = strchr(p, '"'); if (!p) return false; // 第一个引号
    p = strchr(p+1, '"'); if (!p) return false; // 第二个引号
    p = strchr(p+1, '"'); if (!p) return false; // 值开始引号
    const char *start = p + 1;
    // 期望格式：YYYY-MM-DDThh:mm:ss
    if (sscanf(start, "%d-%d-%dT%d:%d:%d", year, month, day, hour, min, sec) == 6) {
        return true;
    }
    return false;
}

static void apply_time_to_all(int hour, int min, int sec) {
    home_app1_time_hour_value = hour; home_app1_time_min_value = min; home_app1_time_sec_value = sec;
    home_app2_time_hour_value = hour; home_app2_time_min_value = min; home_app2_time_sec_value = sec;
    weather_app_time_hour_value = hour; weather_app_time_min_value = min; weather_app_time_sec_value = sec;
    music_app_time_hour_value = hour; music_app_time_min_value = min; music_app_time_sec_value = sec;
    smart_home_app_time_hour_value = hour; smart_home_app_time_min_value = min; smart_home_app_time_sec_value = sec;
    calculator_app_time_hour_value = hour; calculator_app_time_min_value = min; calculator_app_time_sec_value = sec;
    deepseek_app_time_hour_value = hour; deepseek_app_time_min_value = min; deepseek_app_time_sec_value = sec;
    setting_app_time_hour_value = hour; setting_app_time_min_value = min; setting_app_time_sec_value = sec;
}

static void apply_date_labels(int year, int month, int day) {
    char buf[20];
    snprintf(buf, sizeof(buf), "%d/%02d/%02d", year, month, day);
    if (lv_obj_is_valid(guider_ui.home_app1_date)) lv_label_set_text(guider_ui.home_app1_date, buf);
    if (lv_obj_is_valid(guider_ui.home_app2_date)) lv_label_set_text(guider_ui.home_app2_date, buf);
    if (lv_obj_is_valid(guider_ui.weather_app_date)) lv_label_set_text(guider_ui.weather_app_date, buf);
    if (lv_obj_is_valid(guider_ui.music_app_date)) lv_label_set_text(guider_ui.music_app_date, buf);
    if (lv_obj_is_valid(guider_ui.smart_home_app_date)) lv_label_set_text(guider_ui.smart_home_app_date, buf);
    if (lv_obj_is_valid(guider_ui.calculator_app_date)) lv_label_set_text(guider_ui.calculator_app_date, buf);
    if (lv_obj_is_valid(guider_ui.deepseek_app_date)) lv_label_set_text(guider_ui.deepseek_app_date, buf);
    if (lv_obj_is_valid(guider_ui.setting_app_date)) lv_label_set_text(guider_ui.setting_app_date, buf);
}

extern "C" bool sync_network_time(void) {
    auto &wifi = Wifi::GetInstance();

    // 建立到 worldtimeapi.org 的 TCP 连接
    wifi.sendAT("AT+CIPSTART=\"TCP\",\"worldtimeapi.org\",80");
    if (wifi.waitResponse("OK", 5000) != 1) {
        return false;
    }

    // 构造 HTTP GET 请求（上海时区）
    const char *req = "GET /api/timezone/Asia/Shanghai HTTP/1.1\r\nHost: worldtimeapi.org\r\nConnection: close\r\n\r\n";
    char cmd[32];
    sprintf(cmd, "AT+CIPSEND=%d", (int)strlen(req));
    wifi.sendAT(cmd);
    if (wifi.waitResponse(">", 2000) != 1) {
        wifi.sendAT("AT+CIPCLOSE");
        wifi.waitResponse("OK", 1000);
        return false;
    }
    // 发送 HTTP 请求正文
    comSendBuf(COM3, (uint8_t *)req, (uint32_t)strlen(req));
    wifi.waitResponse("SEND OK", 8000);

    // 读取响应（按行叠加到缓冲区）
    char resp[2048] = {0};
    char line[512];
    int pos = 0;
    while (1) {
        uint16_t n = wifi.readLine(line, sizeof(line), 600);
        if (n == 0) break;
        if (pos + n >= (int)sizeof(resp) - 1) break;
        memcpy(resp + pos, line, n);
        pos += n; resp[pos] = '\0';
        if (strstr(line, "CLOSED") || strstr(line, "OK")) break;
    }

    // 解析 datetime 字段
    int year=0, month=0, day=0, hour=0, min=0, sec=0;
    bool ok = parse_datetime_iso8601(resp, &year, &month, &day, &hour, &min, &sec);

    // 关闭连接
    wifi.sendAT("AT+CIPCLOSE");
    wifi.waitResponse("OK", 2000);

    if (!ok) return false;

    // 应用到各屏幕的时间与日期标签
    apply_time_to_all(hour, min, sec);
    apply_date_labels(year, month, day);
    return true;
}