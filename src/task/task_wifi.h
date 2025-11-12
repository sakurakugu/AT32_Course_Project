#pragma once
#include <stdint.h>

extern void TaskWiFi(void *pvParameters);
extern void update_wifi_name_label(lv_ui *ui, const char *ssid);
extern void TaskWiFi(void *pvParameters);
extern uint8_t should_reconnect();
