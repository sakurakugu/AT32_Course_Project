#include "weather_service.hpp"

#include "../../config/api_key.h"
#include "../../gui/generated/gui_guider.h"
#include "../../util/logger.h"
#include "../board/network/wifi.hpp"
#include "cJSON.h"
#include "delay.h"
#include "timer.h"
#include "uart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 来自应用的串口接收保护标志（避免心跳任务等抢占 COM3 接收）
extern volatile uint8_t g_com3_guard;

// 全局 UI 结构体（events 已经引用），这里直接使用以便更新控件
extern lv_ui guider_ui;

// 统一的 Host 名称（心知天气正式 API 域名）
static const char *kHost = "api.seniverse.com";

// 尝试依据 HTTP 响应中的 Content-Length 精准提取 JSON 正文；
// 若失败，再退化为“从第一个 '{' 到 'CLOSED' 前最近的 '}'”的方式。
// 返回 true 表示提取成功，结果写入 out（以 NUL 结尾）。
static bool extract_json_segment(const char *in, char *out, int out_size) {
    if (!in || !out || out_size <= 1) return false;

    // 1) 优先解析 Content-Length
    const char *cl = strstr(in, "Content-Length:");
    int body_len = -1;
    if (cl) {
        cl += strlen("Content-Length:");
        // 跳过空格
        while (*cl == ' ' || *cl == '\t') ++cl;
        // 读取十进制数字
        int val = 0;
        const char *p = cl;
        while (*p >= '0' && *p <= '9') {
            val = val * 10 + (*p - '0');
            ++p;
        }
        if (val > 0) body_len = val;
    }

    if (body_len > 0) {
        // 在包含正文的 +IPD 段后面，正文通常紧随 ':' 之后开始
        const char *ipd = nullptr;
        const char *search_from = cl ? cl : in;
        // 使用最后一次出现的 "+IPD," 更稳妥，避免命中头部段
        const char *last_ipd = nullptr;
        const char *tmp = search_from;
        while ((tmp = strstr(tmp, "+IPD,")) != nullptr) {
            last_ipd = tmp;
            tmp += 5; // 跳过 "+IPD,"
        }
        ipd = last_ipd ? last_ipd : strstr(search_from, "+IPD,");

        const char *start = nullptr;
        if (ipd) {
            const char *colon = strchr(ipd, ':');
            if (colon) {
                start = colon + 1; // 正文起点（通常就是 '{'）
            }
        }
        if (!start) {
            // 退化：直接找第一个 '{'
            start = strchr(in, '{');
        }
        if (start && body_len > 0) {
            // 仅当可用数据达到 Content-Length 时才判定成功；否则回退到括号策略
            int available = (int)strlen(start);
            if (available >= body_len) {
                int copy_len = body_len;
                if (copy_len >= out_size) copy_len = out_size - 1;
                memcpy(out, start, copy_len);
                out[copy_len] = '\0';
                LOGD("按 Content-Length 提取 JSON 成功，Content-Length=%d", body_len);
                return true;
            } else {
                // 可用数据不足，说明组合的响应未包含完整正文；回退到 '{'..'}' 提取
                LOGW("Content-Length=%d，但可用仅=%d，回退到括号提取", body_len, available);
            }
        }
    }

    // 2) 退化方案：从第一个 '{' 到最后一个 '}' 并尽量平衡括号
    const char *start = strchr(in, '{');
    if (!start) return false;

    // 策略：找到使括号尽可能平衡的最长子串
    const char *best_end = nullptr;
    int best_balance = 9999; // 最小不平衡度
    int brace_count = 0;
    
    const char *p = start;
    while (*p) {
        if (*p == '{') {
            brace_count++;
        } else if (*p == '}') {
            brace_count--;
            // 记录每个可能的结束位置
            int balance = brace_count < 0 ? -brace_count : brace_count;
            if (balance < best_balance || 
                (balance == best_balance && (!best_end || p > best_end))) {
                best_balance = balance;
                best_end = p;
            }
            // 如果完美平衡且不是第一个'}'，这可能是完整JSON
            if (brace_count == 0 && p > start) {
                best_end = p;
                best_balance = 0;
                // 继续搜索，可能有更长的完整JSON
            }
        }
        // 遇到CLOSED或ERROR等模组输出，停止搜索
        if (strncmp(p, "CLOSED", 6) == 0 || strncmp(p, "ERROR", 5) == 0) {
            break;
        }
        p++;
    }
    
    if (!best_end || best_end < start) {
        LOGW("未找到有效的JSON结束符'}'");
        return false;
    }
    
    int len = (int)(best_end - start + 1);
    if (len <= 0) return false;
    if (len >= out_size) {
        LOGE("JSON 长度=%d 超过缓冲区大小=%d，无法提取", len, out_size);
        return false;
    }
    memcpy(out, start, len);
    out[len] = '\0';
    
    // 报告括号平衡情况
    if (best_balance != 0) {
        LOGW("JSON 括号不平衡 (差值=%d)，但这是最佳匹配", best_balance);
    } else {
        LOGD("JSON 括号完美平衡");
    }
    
    LOGD("按 '{'..'}' 退化提取 JSON 成功，长度=%d", len);
    return true;
}

// 发送 HTTP GET 到指定路径，返回完整响应（含头部），在 out 中
bool WeatherService::http_get_seniverse(const char *path, char *resp_out, int resp_out_size) {
    if (!path || !resp_out || resp_out_size <= 0)
        return false;

    auto &wifi = Wifi::GetInstance();

    // 保护 COM3 接收
    g_com3_guard = 1;

    // 优先尝试 SSL（443），失败则回落到明文 HTTP（80）
    {
        char cmd_ssl[64];
        snprintf(cmd_ssl, sizeof(cmd_ssl), "AT+CIPSTART=\"SSL\",\"%s\",443", kHost);
        wifi.sendAT(cmd_ssl);
    }
    if (wifi.waitResponse("OK", 3000) != 1) {
        // 回落到 HTTP
        char cmd_tcp[64];
        snprintf(cmd_tcp, sizeof(cmd_tcp), "AT+CIPSTART=\"TCP\",\"%s\",80", kHost);
        wifi.sendAT(cmd_tcp);
        if (wifi.waitResponse("OK", 5000) != 1) {
            g_com3_guard = 0;
            return false;
        }
    }

    // 构造请求
    char req[512];
    int req_len = snprintf(req, sizeof(req),
                           "GET %s HTTP/1.1\r\n"
                           "Host: %s\r\n"
                           "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64)\r\n"
                           "Accept: application/json\r\n"
                           "Accept-Encoding: identity\r\n"
                           "Cache-Control: no-cache\r\n"
                           "Connection: close\r\n\r\n",
                           path, kHost);
    if (req_len <= 0 || req_len >= (int)sizeof(req)) {
        wifi.sendAT("AT+CIPCLOSE");
        wifi.waitResponse("OK", 1000);
        g_com3_guard = 0;
        return false;
    }

    // 发送请求
    char cmd[32];
    sprintf(cmd, "AT+CIPSEND=%d", req_len);
    wifi.sendAT(cmd);
    if (wifi.waitResponse(">", 2000) != 1) {
        wifi.sendAT("AT+CIPCLOSE");
        wifi.waitResponse("OK", 1000);
        g_com3_guard = 0;
        return false;
    }
    comSendBuf(COM3, (uint8_t *)req, (uint32_t)req_len);

    // 等到数据到来
    wifi.waitResponse("+IPD", 8000);

    // 先快速读取HTTP头部,提取Content-Length
    int content_length = -1;
    int pos = 0;
    char line[512];
    memset(resp_out, 0, resp_out_size);
    
    // 阶段1: 读取头部并提取Content-Length
    for (int i = 0; i < 20; ++i) { // 最多读20行头部
        uint16_t n = wifi.readLine(line, sizeof(line), 1500);
        if (n == 0) break;
        
        if (pos + (int)n >= resp_out_size - 1) {
            LOGW("响应缓冲区即将溢出(头部阶段)");
            break;
        }
        memcpy(resp_out + pos, line, n);
        pos += n;
        
        // 解析Content-Length
        if (content_length < 0 && strstr(line, "Content-Length:")) {
            const char *cl = strstr(line, "Content-Length:");
            cl += strlen("Content-Length:");
            while (*cl == ' ' || *cl == '\t') ++cl;
            int val = 0;
            while (*cl >= '0' && *cl <= '9') {
                val = val * 10 + (*cl - '0');
                ++cl;
            }
            if (val > 0) {
                content_length = val;
                LOGD("检测到 Content-Length=%d", content_length);
            }
        }
        
        // 检测到空行(\r\n\r\n)表示头部结束
        if (n == 2 && line[0] == '\r' && line[1] == '\n') {
            LOGD("HTTP头部读取完成,pos=%d", pos);
            break;
        }
    }

    // 阶段2: 根据Content-Length精确读取正文
    if (content_length > 0) {
        int body_start = pos;
        int body_received = 0;
        int target_total = pos + content_length;
        
        LOGD("开始接收正文: 需要%d字节, 目标总长度=%d", content_length, target_total);
        
        int no_data_count = 0;
        uint32_t last_recv_tick = Timer_GetTickCount();
        const uint32_t MAX_WAIT_MS = 15000; // 总超时15秒
        
        while (pos < target_total && pos < resp_out_size - 1) {
            // 检查总超时
            if (Timer_GetTickCount() - last_recv_tick > MAX_WAIT_MS) {
                LOGW("正文接收总超时,已收%d/%d字节", pos - body_start, content_length);
                break;
            }
            
            uint16_t n = wifi.readLine(line, sizeof(line), 3000); // 单次读取超时3秒
            if (n == 0) {
                no_data_count++;
                if (no_data_count > 3) { // 连续3次无数据则放弃
                    LOGW("正文接收超时(无数据),已收%d/%d字节", pos - body_start, content_length);
                    break;
                }
                continue;
            }
            no_data_count = 0;
            last_recv_tick = Timer_GetTickCount(); // 重置超时计时
            
            if (pos + (int)n >= resp_out_size - 1) {
                LOGW("响应缓冲区即将溢出(正文阶段)");
                break;
            }
            memcpy(resp_out + pos, line, n);
            pos += n;
            body_received = pos - body_start;
            
            // 检查是否接收完整
            if (body_received >= content_length) {
                LOGD("正文接收完整: %d/%d字节", body_received, content_length);
                break;
            }
        }
    } else {
        // 回退到原来的逻辑: 继续读取直到CLOSED
        LOGW("未检测到Content-Length,使用回退方案");
        int no_data_count = 0;
        bool closed_seen = false;
        while (1) {
            uint16_t n = wifi.readLine(line, sizeof(line), 1500);
            if (n == 0) {
                no_data_count++;
                if (closed_seen && no_data_count >= 2) break;
                if (no_data_count > 5) break;
                continue;
            }
            no_data_count = 0;
            
            if (pos + (int)n >= resp_out_size - 1) break;
            memcpy(resp_out + pos, line, n);
            pos += n;
            if (strstr(line, "CLOSED")) {
                closed_seen = true;
                LOGD("检测到CLOSED");
            }
        }
    }

    // 仅在读取完成后统一添加字符串终止符，避免中间嵌入 NUL 破坏后续 strstr/strchr
    if (pos < resp_out_size)
        resp_out[pos] = '\0';
    
    LOGD("HTTP 响应总长度=%d 字节", pos);

    // 关闭连接
    wifi.sendAT("AT+CIPCLOSE");
    wifi.waitResponse("OK", 2000);

    // 检查状态码
    if (strstr(resp_out, "HTTP/1.1 200") == NULL) {
        g_com3_guard = 0;
        return false;
    }

    g_com3_guard = 0;
    return true;
}

// 解析当前天气并更新界面
bool WeatherService::parse_and_apply_current(lv_ui *ui, const char *http_resp) {
    if (!ui || !http_resp)
        return false;

    // 提取纯 JSON 正文（优先按 Content-Length，失败则退化）
    // 当前天气接口响应通常不超过1KB
    char json_buf[1024];
    const char *body = nullptr;
    if (extract_json_segment(http_resp, json_buf, sizeof(json_buf))) {
        body = json_buf;
    } else {
        LOGE("无法提取有效 JSON 正文（Content-Length / 退化均失败）");
        return false;
    }

    // 调试：打印部分正文（避免过长）
    {
        int body_len = (int)strlen(body);
        int preview_len = body_len > 256 ? 256 : body_len;
        char preview[270];
        memset(preview, 0, sizeof(preview));
        if (preview_len > 0) {
            memcpy(preview, body, preview_len);
        }
        LOGD("当前天气 JSON 正文长度=%d 预览=\"%s%s\"",
             body_len,
             preview_len > 0 ? preview : "",
             body_len > preview_len ? "..." : "");
    }

    cJSON *root = cJSON_Parse(body);
    if (!root) {
        const char *err_ptr = cJSON_GetErrorPtr();
        if (err_ptr) {
            LOGE("当前天气 JSON 解析失败，错误位置附近: %.30s", err_ptr);
        } else {
            LOGE("当前天气 JSON 解析失败（cJSON_Parse 返回 NULL）");
        }
        // 输出完整JSON用于调试（分段输出避免日志截断）
        int body_len = (int)strlen(body);
        LOGD("=== JSON 调试输出开始 (总长%d) ===", body_len);
        for (int i = 0; i < body_len; i += 200) {
            int chunk_len = (body_len - i) > 200 ? 200 : (body_len - i);
            char chunk[201];
            memcpy(chunk, body + i, chunk_len);
            chunk[chunk_len] = '\0';
            LOGD("[%d-%d]: %s", i, i + chunk_len - 1, chunk);
        }
        LOGD("=== JSON 调试输出结束 ===");
        return false;
    }

    bool ok = false;
    cJSON *results = cJSON_GetObjectItemCaseSensitive(root, "results");
    if (results && cJSON_IsArray(results)) {
        cJSON *item0 = cJSON_GetArrayItem(results, 0);
        if (item0) {
            cJSON *location = cJSON_GetObjectItemCaseSensitive(item0, "location");
            cJSON *now = cJSON_GetObjectItemCaseSensitive(item0, "now");
            cJSON *last_update = cJSON_GetObjectItemCaseSensitive(item0, "last_update");

            const char *city = NULL;
            if (location) {
                cJSON *name = cJSON_GetObjectItemCaseSensitive(location, "name");
                if (cJSON_IsString(name) && name->valuestring)
                    city = name->valuestring;
                if (!city) {
                    cJSON *path = cJSON_GetObjectItemCaseSensitive(location, "path");
                    if (cJSON_IsString(path) && path->valuestring)
                        city = path->valuestring;
                }
                if (!city) {
                    LOGW("当前天气：location 字段存在，但未找到有效城市名称(name/path)");
                }
            }

            const char *weather_text = NULL;
            const char *temperature = NULL;
            if (now) {
                cJSON *text = cJSON_GetObjectItemCaseSensitive(now, "text");
                cJSON *temp = cJSON_GetObjectItemCaseSensitive(now, "temperature");
                if (cJSON_IsString(text)) weather_text = text->valuestring;
                if (cJSON_IsString(temp)) temperature = temp->valuestring;
                if (!weather_text || !temperature) {
                    LOGW("当前天气：now 字段存在，但 text(%s) 或 temperature(%s) 缺失",
                         weather_text ? "ok" : "null",
                         temperature ? "ok" : "null");
                }
            }

            const char *update_time = NULL;
            if (cJSON_IsString(last_update)) update_time = last_update->valuestring;
            if (!update_time) {
                LOGW("当前天气：last_update 字段缺失或非字符串");
            }

            LOGD("当前天气解析结果：city=\"%s\" temp=\"%s\" text=\"%s\" update=\"%s\"",
                 city ? city : "",
                 temperature ? temperature : "",
                 weather_text ? weather_text : "",
                 update_time ? update_time : "");

            // 更新 LVGL 标签
            if (city && lv_obj_is_valid(ui->weather_app_city)) {
                lv_label_set_text(ui->weather_app_city, city);
            }
            if (temperature && lv_obj_is_valid(ui->weather_app_temperature)) {
                char buf[32];
                snprintf(buf, sizeof(buf), "%s", temperature);
                lv_label_set_text(ui->weather_app_temperature, buf);
            }
            if (lv_obj_is_valid(ui->weather_app_unit)) {
                lv_label_set_text(ui->weather_app_unit, "°C");
            }
            if (weather_text && lv_obj_is_valid(ui->weather_app_weather)) {
                char buf[64];
                snprintf(buf, sizeof(buf), "天气: %s", weather_text);
                lv_label_set_text(ui->weather_app_weather, buf);
            }
            if (update_time && lv_obj_is_valid(ui->weather_app_updatetime)) {
                char buf[96];
                snprintf(buf, sizeof(buf), "上次更新时间：%s", update_time);
                lv_label_set_text(ui->weather_app_updatetime, buf);
            }

            ok = true;
            LOGI("当前天气解析并应用 UI 成功");
        }
    }
    if (!ok) {
        LOGE("当前天气解析失败：未找到期望的 results[0] 结构");
    }

    cJSON_Delete(root);
    return ok;
}

// 解析逐日天气并更新三天的标签
bool WeatherService::parse_and_apply_daily(lv_ui *ui, const char *http_resp) {
    if (!ui || !http_resp)
        return false;

    // 提取纯 JSON 正文（优先按 Content-Length，失败则退化）
    // 3天预报接口响应通常在1-1.5KB左右
    char json_buf[1536];
    const char *body = nullptr;
    if (extract_json_segment(http_resp, json_buf, sizeof(json_buf))) {
        body = json_buf;
    } else {
        LOGE("无法提取有效 JSON 正文（Content-Length / 退化均失败）");
        return false;
    }

    // 调试：打印部分正文（避免过长）
    {
        int body_len = (int)strlen(body);
        int preview_len = body_len > 256 ? 256 : body_len;
        char preview[270];
        memset(preview, 0, sizeof(preview));
        if (preview_len > 0) {
            memcpy(preview, body, preview_len);
        }
        LOGD("每日预报 JSON 正文长度=%d 预览=\"%s%s\"",
             body_len,
             preview_len > 0 ? preview : "",
             body_len > preview_len ? "..." : "");
    }

    cJSON *root = cJSON_Parse(body);
    if (!root) {
        const char *err_ptr = cJSON_GetErrorPtr();
        if (err_ptr) {
            LOGE("每日预报 JSON 解析失败，错误位置附近: %.30s", err_ptr);
        } else {
            LOGE("每日预报 JSON 解析失败（cJSON_Parse 返回 NULL）");
        }
        // 输出完整JSON用于调试（分段输出避免日志截断）
        int body_len = (int)strlen(body);
        LOGD("=== JSON 调试输出开始 (总长%d) ===", body_len);
        for (int i = 0; i < body_len; i += 200) {
            int chunk_len = (body_len - i) > 200 ? 200 : (body_len - i);
            char chunk[201];
            memcpy(chunk, body + i, chunk_len);
            chunk[chunk_len] = '\0';
            LOGD("[%d-%d]: %s", i, i + chunk_len - 1, chunk);
        }
        LOGD("=== JSON 调试输出结束 ===");
        return false;
    }

    bool ok = false;
    cJSON *results = cJSON_GetObjectItemCaseSensitive(root, "results");
    if (results && cJSON_IsArray(results)) {
        cJSON *item0 = cJSON_GetArrayItem(results, 0);
        if (item0) {
            cJSON *daily = cJSON_GetObjectItemCaseSensitive(item0, "daily");
            if (daily && cJSON_IsArray(daily)) {
                for (int i = 0; i < 3; ++i) {
                    cJSON *d = cJSON_GetArrayItem(daily, i);
                    if (!d) break;
                    const char *text_day = NULL;
                    const char *text_night = NULL;
                    const char *high = NULL;
                    const char *low = NULL;

                    cJSON *jd = cJSON_GetObjectItemCaseSensitive(d, "text_day");
                    cJSON *jn = cJSON_GetObjectItemCaseSensitive(d, "text_night");
                    cJSON *jh = cJSON_GetObjectItemCaseSensitive(d, "high");
                    cJSON *jl = cJSON_GetObjectItemCaseSensitive(d, "low");
                    if (cJSON_IsString(jd)) text_day = jd->valuestring;
                    if (cJSON_IsString(jn)) text_night = jn->valuestring;
                    if (cJSON_IsString(jh)) high = jh->valuestring;
                    if (cJSON_IsString(jl)) low = jl->valuestring;

                    LOGD("第%d天：text_day=\"%s\" text_night=\"%s\" high=\"%s\" low=\"%s\"",
                         i + 1,
                         text_day ? text_day : "",
                         text_night ? text_night : "",
                         high ? high : "",
                         low ? low : "");

                    // 选择对应的 UI 控件
                    lv_obj_t **label_text_day = nullptr;
                    lv_obj_t **label_text_night = nullptr;
                    lv_obj_t **label_num_day = nullptr;
                    lv_obj_t **label_num_night = nullptr;
                    if (i == 0) {
                        label_text_day = &ui->weather_app_text_day1;
                        label_text_night = &ui->weather_app_text_night1;
                        label_num_day = &ui->weather_app_num_day1;
                        label_num_night = &ui->weather_app_num_night1;
                    } else if (i == 1) {
                        label_text_day = &ui->weather_app_text_day2;
                        label_text_night = &ui->weather_app_text_night2;
                        label_num_day = &ui->weather_app_num_day2;
                        label_num_night = &ui->weather_app_num_night2;
                    } else if (i == 2) {
                        label_text_day = &ui->weather_app_text_day3;
                        label_text_night = &ui->weather_app_text_night3;
                        label_num_day = &ui->weather_app_num_day3;
                        label_num_night = &ui->weather_app_num_night3;
                    }

                    if (label_text_day && *label_text_day && lv_obj_is_valid(*label_text_day) && text_day)
                        lv_label_set_text(*label_text_day, text_day);
                    if (label_text_night && *label_text_night && lv_obj_is_valid(*label_text_night) && text_night)
                        lv_label_set_text(*label_text_night, text_night);
                    if (label_num_day && *label_num_day && lv_obj_is_valid(*label_num_day) && high) {
                        char buf[24];
                        snprintf(buf, sizeof(buf), "%s°C", high);
                        lv_label_set_text(*label_num_day, buf);
                    }
                    if (label_num_night && *label_num_night && lv_obj_is_valid(*label_num_night) && low) {
                        char buf[24];
                        snprintf(buf, sizeof(buf), "%s°C", low);
                        lv_label_set_text(*label_num_night, buf);
                    }
                }
                ok = true;
                LOGI("每日预报解析并应用 UI 成功");
            }
        }
    }
    if (!ok) {
        LOGE("每日预报解析失败：未找到期望的 results[0].daily 数组");
    }

    cJSON_Delete(root);
    return ok;
}

bool WeatherService::UpdateWeather(lv_ui *ui) {
    if (!ui)
        return false;

    char resp[2048]; // HTTP响应缓冲区(包含头部+正文)
    char path[256];

    // 当前天气
    bool ok1 = false;
    // 心知天气：当前天气接口
    // 示例：https://api.seniverse.com/v3/weather/now.json?key=YOUR_KEY&location=ip&language=zh-Hans&unit=c
    snprintf(path, sizeof(path), 
             "/v3/weather/now.json?key=%s&location=%s&language=zh-Hans&unit=c",
             API_KEY_WEATHER, "ip");
    if (http_get_seniverse(path, resp, sizeof(resp))) {
        ok1 = parse_and_apply_current(ui, resp);
        LOGI("当前天气解析结果：%s", ok1 ? "成功" : "失败");
    } else {
        LOGE("天气请求失败：可能是无网络或 API 密钥无效");
    }

    // 未来 3 天（今天、明天、后天）（免费版）
    bool ok2 = false;
    // 心知天气：未来每日预报接口（免费版支持 3 天）
    // 示例：https://api.seniverse.com/v3/weather/daily.json?key=YOUR_KEY&location=ip&language=zh-Hans&unit=c&start=0&days=3
    snprintf(path, sizeof(path),
             "/v3/weather/daily.json?key=%s&location=%s&language=zh-Hans&unit=c&start=0&days=3",
             API_KEY_WEATHER, "ip");
    if (http_get_seniverse(path, resp, sizeof(resp))) {
        ok2 = parse_and_apply_daily(ui, resp);
        LOGI("每日预报解析结果：%s", ok2 ? "成功" : "失败");
    } else {
        LOGE("天气请求失败：可能是无网络或 API 密钥无效");
    }

    return ok1 || ok2;
}

// C 包装，供 C 事件回调调用
extern "C" bool weather_update_ui(void) {
    return WeatherService::GetInstance().UpdateWeather(&guider_ui);
}