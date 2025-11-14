#include "task_key.h"
#include "beep.hpp"
#include "gui_guider.h"
#include "key.h"
#include <FreeRTOS.h>
#include <task.h>

extern "C" {
#include "../app/minecraft/minecraft.h"
}

// 获取 smart_home_app 中的 1~8 号按钮对象
static inline lv_obj_t *get_smart_home_key_btn(uint8_t idx) {
    switch (idx) {
    case 1:
        return guider_ui.smart_home_app_btn_1;
    case 2:
        return guider_ui.smart_home_app_btn_2;
    case 3:
        return guider_ui.smart_home_app_btn_3;
    case 4:
        return guider_ui.smart_home_app_btn_4;
    case 5:
        return guider_ui.smart_home_app_btn_5;
    case 6:
        return guider_ui.smart_home_app_btn_6;
    case 7:
        return guider_ui.smart_home_app_btn_7;
    case 8:
        return guider_ui.smart_home_app_btn_8;
    default:
        return NULL;
    }
}

// 根据键编号设置按钮的按下/抬起 UI 状态，同时派发 LVGL 事件
static inline void set_smart_home_key_btn_pressed(uint8_t idx, bool pressed) {
    lv_obj_t *btn = get_smart_home_key_btn(idx);
    if (!btn)
        return;
    if (pressed) {
        lv_obj_add_state(btn, LV_STATE_PRESSED);
        lv_event_send(btn, LV_EVENT_PRESSED, NULL);
    } else {
        lv_obj_clear_state(btn, LV_STATE_PRESSED);
        lv_event_send(btn, LV_EVENT_RELEASED, NULL);
    }
}

void TaskKeys([[maybe_unused]] void *pvParameters) {
    for (;;) {
        uint8_t keyvalue = Key::GetInstance().get();

        // 检查当前是否在Minecraft游戏界面
        lv_obj_t *current_screen = lv_scr_act();
        bool is_minecraft_screen = (current_screen == guider_ui.minecraft_app);

        // Minecraft游戏按键处理
        if (is_minecraft_screen) {
            if (keyvalue == KEY_1_DOWN) { // KEY1 - 前进
                minecraft_handle_key(MINECRAFT_KEY_UP);
            } else if (keyvalue == KEY_1_UP) {
                minecraft_handle_key(0);
            } else if (keyvalue == KEY_2_DOWN) { // KEY2 - 右转
                minecraft_handle_key(MINECRAFT_KEY_RIGHT);
            } else if (keyvalue == KEY_2_UP) {
                minecraft_handle_key(0);
            } else if (keyvalue == KEY_3_DOWN) { // KEY3 - 后退
                minecraft_handle_key(MINECRAFT_KEY_DOWN);
            } else if (keyvalue == KEY_3_UP) {
                minecraft_handle_key(0);
            } else if (keyvalue == KEY_4_DOWN) { // KEY4 - 左转
                minecraft_handle_key(MINECRAFT_KEY_LEFT);
            } else if (keyvalue == KEY_4_UP) {
                minecraft_handle_key(0);
            } else if (keyvalue == KEY_5_DOWN) { // KEY5 - 低头
                minecraft_handle_key(MINECRAFT_KEY_LOOK_DOWN);
            } else if (keyvalue == KEY_5_UP) {
                minecraft_handle_key(0);
            } else if (keyvalue == KEY_7_DOWN) { // KEY7 - 抬头
                minecraft_handle_key(MINECRAFT_KEY_LOOK_UP);
            } else if (keyvalue == KEY_7_UP) {
                minecraft_handle_key(0);

            } else if (keyvalue == KEY_8_DOWN) { // KEY8 - 攻击/破坏
                minecraft_handle_key(MINECRAFT_KEY_ACTION);
            } else if (keyvalue == KEY_8_UP) {
                minecraft_handle_key(0);
            }
        }

        // 将硬件按键事件映射到 smart_home_app 的 8 个按钮按下/抬起
        if (keyvalue >= KEY_1_DOWN && keyvalue <= KEY_8_LONG) {
            uint8_t idx = ((keyvalue - 1) / 3) + 1; // 1~8
            uint8_t type = ((keyvalue - 1) % 3);    // 0:DOWN, 1:UP, 2:LONG
            if (type == 0) {
                g_beep.keyTone();
                set_smart_home_key_btn_pressed(idx, true);
            } else if (type == 1) {
                set_smart_home_key_btn_pressed(idx, false);
            }
        }

        if (keyvalue == KEY_1_DOWN) {}
        if (keyvalue == KEY_2_DOWN) {
            // LOGI("KEY_2_DOWN - 切换照明状态\r\n");
            // IoT::GetInstance().Control_Lighting(!lighting_status);
            // IoT::GetInstance().Send_Status_Report();
        }
        if (keyvalue == KEY_3_DOWN) {
            // if (!music_playing) {
            //     LOGI("KEY_3_DOWN - 开始播放音乐\r\n");
            //     music_start = 1;  /* 由音乐任务消费 */
            //     music_resume = 0; /* 确保处于播放状态 */
            // } else {
            //     music_resume = !music_resume;
            //     LOGI("KEY_3_DOWN - %s播放\r\n", music_resume ? "暂停" : "继续");
            //     if (music_resume) {
            //         g_beep.disableOutput(); /* 立即静音 */
            //     }
            // }
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}