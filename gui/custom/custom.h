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

extern volatile uint8_t wifi_reconnect_requested; // WiFi异步连接请求标志（由心跳或启动时触发）

void custom_init(lv_ui *ui);

void update_volume_icon(lv_ui *ui, uint8_t volume); // 更新音量图标
void calc_key_event_handler(lv_event_t *e);         // 计算器按键事件处理器
void wifi_link_btn_event_handler(lv_event_t *e);    // 绑定点击“wifi连接”按钮事件

// 设置页事件：亮度滑块、声音滑块、同步网络时间开关
#ifdef KEIL_COMPILE
void setting_app_light_slider_event_handler(lv_event_t *e);
void setting_app_sync_net_time_sw_event_handler(lv_event_t *e);
#endif

// ——— 导航与状态栏统一 ———
// 统一状态栏初始化（放在顶层图层），在 custom_init 中调用
void status_bar_init(lv_ui *ui);

// 导航：进入新页面（自动将当前页面压栈），以及返回上一个页面
void nav_to(lv_ui *ui,                    // ui
            lv_obj_t **new_scr,           // 新页面指针
            bool new_scr_del,             // 是否删除旧页面
            ui_setup_scr_t setup_scr,     // 新页面初始化函数指针
            lv_scr_load_anim_t anim_type, // 动画类型
            uint32_t time,                // 动画持续时间
            uint32_t delay                // 动画延迟时间
);

void nav_back(lv_ui *ui);

#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
