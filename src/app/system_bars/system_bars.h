#pragma once

#include "gui_guider.h"

#ifdef __cplusplus
extern "C" {
#endif

// ——— 导航与状态栏统一 ———

void status_bar_init(lv_ui *ui);                    // 统一状态栏初始化（放在顶层图层），在 custom_init 中调用
void status_bar_set_visible(bool visible);          // 控制状态栏显隐
void status_bar_update_wifi(bool connected);        // 控制WiFi图标显隐
void update_volume_icon(lv_ui *ui, uint8_t volume); // 更新音量图标
void status_bar_update_sound(bool on);
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