#include "setting.hpp"
#include "../board/lcd/lcd.h"
#include "../network/wifi.hpp"
#include "logger.h"
#include "lvgl.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// 来自应用的串口接收保护标志
extern volatile uint8_t g_com3_guard;

#ifdef __cplusplus
extern "C" {
#endif

bool sync_network_time(bool sync) {
    return Setting::GetInstance().sync_network_time(sync);
}
void backlight_set_percent(uint8_t percent) {
    Setting::GetInstance().backlight_set_percent(percent);
}

#ifdef __cplusplus
}
#endif

// 引用各屏幕的时钟全局变量（widgets_init.c 中以 extern 引用）
extern int g_time_hour_value;
extern int g_time_min_value;
extern int g_time_sec_value;

extern lv_obj_t *g_status_bar_date;

bool Setting::sync_network_time(bool sync) {
    auto &wifi = Wifi::GetInstance();

    LOGI("开始同步网络时间\n");

    // 保护COM3接收，避免IoT任务抢占HTTP响应
    g_com3_guard = 1;

    // 建立到 quan.suning.com 的 TCP 连接
    wifi.sendAT("AT+CIPSTART=\"TCP\",\"quan.suning.com\",80");
    if (wifi.waitResponse("OK", 5000) != 1) {
        g_com3_guard = 0;
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
    wifi.sendAT(cmd);
    if (wifi.waitResponse(">", 2000) != 1) {
        wifi.sendAT("AT+CIPCLOSE");
        wifi.waitResponse("OK", 1000);
        g_com3_guard = 0;
        return false;
    }
    // 发送 HTTP 请求正文
    comSendBuf(COM3, (uint8_t *)req, (uint32_t)strlen(req));
    // 不再等待 "SEND OK"，直接读取所有行直到连接关闭
    // 等待数据到来标记 "+IPD"，确认服务端已返回数据
    wifi.waitResponse("+IPD", 8000);

    // 读取响应（按行叠加到缓冲区）
    char resp[2048] = {0};
    char line[512];
    int pos = 0;
    while (1) {
        uint16_t n = wifi.readLine(line, sizeof(line), 1500);
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
        wifi.sendAT("AT+CIPCLOSE");
        wifi.waitResponse("OK", 2000);
        LOGI("HTTP状态非200，响应前200字节: %.*s\n", 200, resp);
        g_com3_guard = 0;
        return false;
    }

    // 解析时间字段
    int year = 0, month = 0, day = 0, hour = 0, min = 0, sec = 0;
    bool ok = parse_datetime_iso8601(resp, &year, &month, &day, &hour, &min, &sec);

    // 关闭连接
    wifi.sendAT("AT+CIPCLOSE");
    wifi.waitResponse("OK", 2000);

    if (!ok) {
        // 打印响应片段帮助定位问题
        LOGI("解析网络时间失败，响应前200字节: %.*s\n", 200, resp);
        return false;
    }

    // 应用到各屏幕的时间与日期标签
    apply_time_to_all(hour, min, sec);
    apply_date_labels(year, month, day);

    LOGI("同步网络时间成功：%04d-%02d-%02d %02d:%02d:%02d\n", year, month, day, hour, min, sec);
    g_com3_guard = 0;
    return true;
}

bool Setting::parse_datetime_iso8601(const char *json, int *year, int *month, int *day, int *hour, int *min, int *sec) {
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

void Setting::apply_time_to_all(int hour, int min, int sec) {
    g_time_hour_value = hour;
    g_time_min_value = min;
    g_time_sec_value = sec;
}

void Setting::apply_date_labels(int year, int month, int day) {
    char buf[20];
    snprintf(buf, sizeof(buf), "%d/%02d/%02d", year, month, day);
    if (lv_obj_is_valid(g_status_bar_date))
        lv_label_set_text(g_status_bar_date, buf);
}

void Setting::backlight_set_percent(uint8_t percent) {
    if (percent == 0) {
        LCD_BL_LOW();
    } else {
        LCD_BL_HIGH();
    }
}