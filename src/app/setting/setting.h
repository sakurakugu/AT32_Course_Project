#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

extern volatile uint8_t wifi_reconnect_requested; // WiFi异步连接请求标志（由心跳或启动时触发）

// 网络时间同步接口
bool Setting_SyncNetworkTime(bool sync);
// 设置背光亮度百分比（0..100）。使用PWM占空比控制：0=关闭，100=最亮。
void Setting_BacklightSetPercent(uint8_t percent);

void wifi_link_btn_event_handler(lv_event_t *e); // 绑定点击“wifi连接”按钮事件
void setting_app_light_slider_event_handler(lv_event_t *e);
void setting_app_sync_net_time_sw_event_handler(lv_event_t *e);
void setting_app_sound_sw_event_handler(lv_event_t *e);

#ifdef __cplusplus
}
#endif