#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "gui_guider.h"

#ifdef __cplusplus
extern "C" {
#endif

void setting_app_wifi_link_btn_event_handler(lv_event_t *e); // 绑定点击“wifi连接”按钮事件
void setting_app_light_slider_event_handler(lv_event_t *e);
void setting_app_sync_net_time_sw_event_handler(lv_event_t *e);
void setting_app_sound_sw_event_handler(lv_event_t *e);
extern void setting_app_update_wifi_name_label(lv_ui *ui, const char *ssid);
extern void setting_app_beep_set_mute(bool mute);

#ifdef __cplusplus
}
#endif