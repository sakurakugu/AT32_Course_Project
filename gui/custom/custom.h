/**
 * @file custom.h
 * @brief 自定义函数头文件
 * @details 包含自定义函数的声明，如更新音量图标等（该文件不会被覆盖）
 */

#ifndef __CUSTOM_H_
#define __CUSTOM_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"
#include <stdio.h>

#include "../../src/app/calculator/calculator.h" // 计算器接口：供界面自定义代码调用
#include "../../src/board/network/wifi.h"

extern volatile uint8_t wifi_reconnect_requested;  // WiFi异步连接请求标志（由心跳或启动时触发）

void custom_init(lv_ui *ui);

void update_volume_icon(lv_ui *ui, uint8_t volume); // 更新音量图标
void calc_key_event_handler(lv_event_t *e);         // 计算器按键事件处理器
void wifi_link_btn_event_handler(lv_event_t *e);    // 绑定点击“wifi连接”按钮事件

#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
