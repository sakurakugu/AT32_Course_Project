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
#include <stdbool.h>
#include <stdio.h>

#include "../../src/app/calculator/calculator.h" // 计算器接口：供界面自定义代码调用
#include "../../src/board/network/wifi.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "../../src/app/minecraft/minecraft.h"
#ifdef __cplusplus
}
#endif

extern volatile uint8_t wifi_reconnect_requested; // WiFi异步连接请求标志（由心跳或启动时触发）

// 全局变量：状态栏日期标签（用于更新日期）
extern lv_obj_t *g_status_bar_date;
// 全局变量：时间小时、分钟、秒（用于更新时间）
extern int g_time_hour_value;
extern int g_time_min_value;
extern int g_time_sec_value;

void custom_init(lv_ui *ui);

void update_volume_icon(lv_ui *ui, uint8_t volume); // 更新音量图标
void calc_key_event_handler(lv_event_t *e);         // 计算器按键事件处理器
#ifdef KEIL_COMPILE
void wifi_link_btn_event_handler(lv_event_t *e);    // 绑定点击“wifi连接”按钮事件
#endif

// 音乐播放器事件
void music_list_item_event_handler(lv_event_t *e);      // 列表项点击播放对应歌曲
void music_prev_btn_event_handler(lv_event_t *e);       // 切换到上一首（循环）
void music_next_btn_event_handler(lv_event_t *e);       // 切换到下一首（循环）
void music_play_pause_btn_event_handler(lv_event_t *e); // 播放/暂停切换

// 智能家居事件
void smart_home_iot_color_led_event_handler(lv_event_t *e);     // IoT页面彩灯图标点击事件
void smart_home_iot_led_green_event_handler(lv_event_t *e);     // IoT页面绿灯图标点击事件
void smart_home_iot_adc_event_handler(lv_event_t *e);           // IoT页面ADC图标点击事件
void smart_home_iot_mpu6050_event_handler(lv_event_t *e);       // IoT页面MPU6050图标点击事件
void smart_home_iot_lm75_event_handler(lv_event_t *e);          // IoT页面LM75图标点击事件
void smart_home_iot_8key_event_handler(lv_event_t *e);          // IoT页面8Key图标点击事件
void smart_home_iot_return_event_handler(lv_event_t *e);        // IoT页面返回按键点击事件（关闭所有子页面）
void smart_home_color_led_sw_event_handler(lv_event_t *e);      // 彩灯开关事件
void smart_home_color_led_cpicker_event_handler(lv_event_t *e); // 彩灯颜色选择事件
void smart_home_color_led_light_slider_event_handler(lv_event_t *e); // 彩灯亮度滑块事件
void smart_home_led_green_sw_event_handler(lv_event_t *e);      // 绿灯开关事件

// 通用页面滑动控制（供事件内部调用）
void smart_home_close_all_pages_with_slide(lv_ui *ui);          // 关闭所有IoT子页面（滑出并隐藏）
void smart_home_open_page_with_slide(lv_ui *ui, lv_obj_t *page);// 打开指定页面（滑入），并关闭其他页面

#ifdef KEIL_COMPILE
// 设置页事件：亮度滑块、声音滑块、同步网络时间开关
void setting_app_light_slider_event_handler(lv_event_t *e);
void setting_app_sync_net_time_sw_event_handler(lv_event_t *e);
// 电子琴：按钮矩阵事件（点击后按音发声）
void electronic_organ_btnm_event_handler(lv_event_t *e);
#endif


// ——— 导航与状态栏统一 ———
void status_bar_init(lv_ui *ui);           // 统一状态栏初始化（放在顶层图层），在 custom_init 中调用
void status_bar_set_visible(bool visible); // 控制状态栏显隐

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

// 画布

// 画板实现：绘图画布 + 颜色选择 + 笔宽设置 + 清空
// 注：为支持 lv_canvas_draw_line/rect，需要使用 TRUE_COLOR 画布缓冲。
// 缓冲类型统一按字节指针管理。
#define DRAW_CANVAS_W 302
#define DRAW_CANVAS_H 286
#define DRAW_MAX_SEGMENTS 1024
typedef struct draw_seg_s {
    lv_color_t color;
    uint16_t width;
    lv_point_t p1;
    lv_point_t p2;
} draw_seg_t;
typedef struct drawing_board_ctx_s {
    lv_obj_t *canvas;
    lv_point_t last_pt;
    bool last_valid;
    uint16_t seg_count;
    draw_seg_t segs[DRAW_MAX_SEGMENTS];
} drawing_board_ctx_t;

extern drawing_board_ctx_t s_drawing_ctx;

void drawing_board_app_delete_cb(lv_event_t *e);   // 删除画布
void drawing_board_canvas_event_cb(lv_event_t *e); // 画布点击事件
void drawing_board_clear_event_cb(lv_event_t *e);  // 清空画布
void drawing_board_width_event_cb(lv_event_t *e);  // 笔宽选择事件
void drawing_board_color_event_cb(lv_event_t *e);  // 颜色选择事件
void drawing_board_paint_draw_event_cb(lv_event_t *e);

// ===============================
// 我的世界游戏实现
// ===============================

extern lv_timer_t *minecraft_timer;
extern lv_obj_t *minecraft_img;

// 游戏循环定时器回调
extern void minecraft_timer_cb(lv_timer_t *timer);
extern void cleanup_scr_minecraft(lv_ui *ui);
extern void minecraft_app_screen_delete_event_handler(lv_event_t *e);

// ===============================
// 时钟实现
// ===============================

extern void clock_app_start_or_pausing_btn_event_handler(lv_event_t *e);
extern void clock_app_reset_btn_event_handler(lv_event_t *e);
extern void clock_app_timer_SPC_btn_event_handler(lv_event_t *e);
extern void clock_app_timer_reset_btn_event_handler(lv_event_t *e);
extern void clock_app_timer_bell_btn_event_handler(lv_event_t *e);
extern void clock_app_init_customize(lv_ui *ui);

#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
