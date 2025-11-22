/**
 * @file custom.c
 * @brief 自定义函数实现文件
 * @details 包含自定义函数的实现，如更新音量图标等（该文件不会被覆盖）
 */

#include "custom.h"
#include "lvgl.h"
#include <stdio.h>
#include <string.h>

#include "../../src/app/calculator/calculator.h"
#include "../../src/app/music/music.h"  // 音乐模块控制标志与曲目定义
#include "../../src/board/sound/beep.h" // 蜂鸣器接口：设定频率并发声
#include "../lvgl/src/extra/widgets/dclock/lv_dclock.h"

#ifdef KEIL_COMPILE
// 背光、音量、网络时间同步接口
#include "../../src/app/setting/setting.h"
// 智能家居：LED 和 Color LED 控制
#include "../../src/board/led/color_led.h"
#include "../../src/board/led/led.h"
#endif

void custom_init(lv_ui *ui) {
    // 初始化统一状态栏与导航栈
    status_bar_init(ui);
    // 清空导航栈
    // （栈定义在本文件的静态区域）
    // 无需额外操作：status_bar_init 不依赖当前屏幕
}

/**
 * @brief 更新音量图标
 * @param ui 指向lv_ui结构体的指针，用于访问GUI元素
 * @param volume 音量值，0表示静音，1-100表示不同音量等级
 */
void update_volume_icon(lv_ui *ui, uint8_t volume) {
    if (volume > 0) {
        // 显示“有音量”
        // lv_obj_clear_flag(ui->screen_voice_on, LV_OBJ_FLAG_HIDDEN);
        // lv_obj_add_flag(ui->screen_voice_off, LV_OBJ_FLAG_HIDDEN);
    } else {
        // 显示“静音”
        // lv_obj_add_flag(ui->screen_voice_on, LV_OBJ_FLAG_HIDDEN);
        // lv_obj_clear_flag(ui->screen_voice_off, LV_OBJ_FLAG_HIDDEN);
    }
}

// 统一的按键事件处理器：从 user_data 读取按键字符串并转交给计算器
void calc_key_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        const char *key = (const char *)lv_event_get_user_data(e);
        calculator_input_key(key);
    }
}

#ifdef KEIL_COMPILE
// 点击“连接”按钮事件：读取输入->触发异步连接->成功后写EEPROM
void wifi_link_btn_event_handler(lv_event_t *e) {
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui)
        return;

    const char *ssid_text = lv_textarea_get_text(ui->setting_app_wifi_name_input);
    const char *pwd_text = lv_textarea_get_text(ui->setting_app_wifi_password_input);

    if (!ssid_text || !pwd_text)
        return;

    // 复制到运行时缓冲，并更新全局凭据指针
    strncpy(wifi_ssid, ssid_text, sizeof(wifi_ssid) - 1);
    strncpy(wifi_password, pwd_text, sizeof(wifi_password) - 1);
    wifi_ssid[sizeof(wifi_ssid) - 1] = '\0';
    wifi_password[sizeof(wifi_password) - 1] = '\0';

    // 由后台任务异步完成连接，避免阻塞UI
    wifi_reconnect_requested = 1;
}
#endif

#ifdef KEIL_COMPILE
// 亮度滑块事件：0 关闭背光；>0 打开背光（如需PWM可在 backlight_set_percent 内扩展）
void setting_app_light_slider_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_VALUE_CHANGED)
        return;
    lv_obj_t *slider = lv_event_get_target(e);
    int32_t val = lv_slider_get_value(slider); // 0..100
    backlight_set_percent((uint8_t)val);
}

// 同步网络时间开关：打开时立即触发一次与服务器的时间同步
void setting_app_sync_net_time_sw_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_VALUE_CHANGED)
        return;
    lv_obj_t *sw = lv_event_get_target(e);
    bool enabled = lv_obj_has_state(sw, LV_STATE_CHECKED);
    if (enabled) {
        // 触发一次同步（内部会更新各屏幕的时分秒与日期标签）
        (void)sync_network_time(true);
    }
}
#endif

// ===============================
// 统一状态栏（顶层图层）
// ===============================

// 资源声明（图标）
extern const lv_img_dsc_t _wifi_alpha_16x16;
extern const lv_img_dsc_t _voice_on_alpha_16x16;
extern const lv_img_dsc_t _voice_off_alpha_16x16;

static lv_obj_t *g_status_bar;
static lv_obj_t *g_status_bar_wifi;
static lv_obj_t *g_status_bar_voice_on;
static lv_obj_t *g_status_bar_voice_off;
static lv_obj_t *g_status_bar_time;
static lv_timer_t *g_status_bar_timer;
lv_obj_t *g_status_bar_date;
int g_time_min_value = 25;
int g_time_hour_value = 11;
int g_time_sec_value = 50;

static void status_bar_timer_cb(lv_timer_t *timer) {
    (void)timer;
    clock_count_24(&g_time_hour_value, &g_time_min_value, &g_time_sec_value);
    if (lv_obj_is_valid(g_status_bar_time)) {
        lv_dclock_set_text_fmt(g_status_bar_time, "%d:%02d", g_time_hour_value, g_time_min_value);
    }
}

void status_bar_init(lv_ui *ui) {
    (void)ui;
    // 创建顶层状态栏容器
    g_status_bar = lv_obj_create(lv_layer_top());
    lv_obj_set_pos(g_status_bar, 0, 0);
    lv_obj_set_size(g_status_bar, 480, 16);
    lv_obj_set_scrollbar_mode(g_status_bar, LV_SCROLLBAR_MODE_OFF);
    // 风格与生成代码保持一致
    lv_obj_set_style_border_width(g_status_bar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(g_status_bar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(g_status_bar, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(g_status_bar, lv_color_hex(0x333333), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(g_status_bar, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(g_status_bar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(g_status_bar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(g_status_bar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(g_status_bar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(g_status_bar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // WiFi 图标
    g_status_bar_wifi = lv_img_create(g_status_bar);
    lv_obj_add_flag(g_status_bar_wifi, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(g_status_bar_wifi, &_wifi_alpha_16x16);
    lv_img_set_pivot(g_status_bar_wifi, 50, 50);
    lv_img_set_angle(g_status_bar_wifi, 0);
    lv_obj_set_pos(g_status_bar_wifi, 456, 0);
    lv_obj_set_size(g_status_bar_wifi, 16, 16);

    // 音量图标（on/off）
    g_status_bar_voice_on = lv_img_create(g_status_bar);
    lv_obj_add_flag(g_status_bar_voice_on, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(g_status_bar_voice_on, &_voice_on_alpha_16x16);
    lv_img_set_pivot(g_status_bar_voice_on, 50, 50);
    lv_img_set_angle(g_status_bar_voice_on, 0);
    lv_obj_set_pos(g_status_bar_voice_on, 434, 0);
    lv_obj_set_size(g_status_bar_voice_on, 16, 16);
    lv_obj_add_flag(g_status_bar_voice_on, LV_OBJ_FLAG_HIDDEN);

    g_status_bar_voice_off = lv_img_create(g_status_bar);
    lv_obj_add_flag(g_status_bar_voice_off, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(g_status_bar_voice_off, &_voice_off_alpha_16x16);
    lv_img_set_pivot(g_status_bar_voice_off, 50, 50);
    lv_img_set_angle(g_status_bar_voice_off, 0);
    lv_obj_set_pos(g_status_bar_voice_off, 434, 0);
    lv_obj_set_size(g_status_bar_voice_off, 16, 16);

    // 时间
    g_status_bar_time = lv_dclock_create(g_status_bar, "11:25");
    lv_obj_set_pos(g_status_bar_time, 220, 0);
    lv_obj_set_size(g_status_bar_time, 46, 16);
    lv_obj_set_style_radius(g_status_bar_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(g_status_bar_time, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(g_status_bar_time, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(g_status_bar_time, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(g_status_bar_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(g_status_bar_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(g_status_bar_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(g_status_bar_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(g_status_bar_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(g_status_bar_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(g_status_bar_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(g_status_bar_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // 日期（占位文本，可由网络时间更新）
    g_status_bar_date = lv_label_create(g_status_bar);
    lv_label_set_text(g_status_bar_date, "2023/07/31");
    lv_obj_set_style_text_align(g_status_bar_date, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_add_flag(g_status_bar_date, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_pos(g_status_bar_date, 0, 1);
    lv_obj_set_size(g_status_bar_date, 112, 16);
    lv_obj_set_style_text_color(g_status_bar_date, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(g_status_bar_date, &lv_font_montserratMedium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(g_status_bar_date, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(g_status_bar_date, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(g_status_bar_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(g_status_bar_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(g_status_bar_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(g_status_bar_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(g_status_bar_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(g_status_bar_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(g_status_bar_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // 定时器：每秒更新时间
    if (!g_status_bar_timer) {
        g_status_bar_timer = lv_timer_create(status_bar_timer_cb, 1000, NULL);
    }
}

void status_bar_set_visible(bool visible) {
    if (!lv_obj_is_valid(g_status_bar))
        return;
    if (visible) {
        lv_obj_clear_flag(g_status_bar, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_add_flag(g_status_bar, LV_OBJ_FLAG_HIDDEN);
    }
}

// ===============================
// 导航栈与辅助函数
// ===============================

typedef struct {
    lv_obj_t **obj_pp;    // 屏幕对象指针的地址（供 ui_load_scr_animation 使用）
    bool *del_flag_p;     // 屏幕删除标记指针（读取其值以判断是否需要 setup_scr）
    ui_setup_scr_t setup; // 对应的 setup_scr_* 函数
} ScreenMeta;

static ScreenMeta nav_stack[16];
static int nav_sp = 0;

// 前置声明：各屏幕的 setup_scr 函数（由生成代码提供）
void setup_scr_home_app1(lv_ui *ui);
void setup_scr_home_app2(lv_ui *ui);
void setup_scr_weather_app(lv_ui *ui);
void setup_scr_music_app(lv_ui *ui);
void setup_scr_smart_home_app(lv_ui *ui);
void setup_scr_calculator_app(lv_ui *ui);
void setup_scr_clock_app(lv_ui *ui);
void setup_scr_setting_app(lv_ui *ui);
void setup_scr_electronic_organ_app(lv_ui *ui);
void setup_scr_drawing_board_app(lv_ui *ui);
void setup_scr_minecraft_app(lv_ui *ui);
void setup_scr_link_game_app(lv_ui *ui);

static bool get_meta_for_obj(lv_ui *ui, lv_obj_t *obj, ScreenMeta *out) {
    if (!ui || !obj || !out)
        return false;
    if (obj == ui->home_app1) {
        out->obj_pp = &ui->home_app1;
        out->del_flag_p = &ui->home_app1_del;
        out->setup = setup_scr_home_app1;
        return true;
    }
    if (obj == ui->home_app2) {
        out->obj_pp = &ui->home_app2;
        out->del_flag_p = &ui->home_app2_del;
        out->setup = setup_scr_home_app2;
        return true;
    }
    if (obj == ui->weather_app) {
        out->obj_pp = &ui->weather_app;
        out->del_flag_p = &ui->weather_app_del;
        out->setup = setup_scr_weather_app;
        return true;
    }
    if (obj == ui->music_app) {
        out->obj_pp = &ui->music_app;
        out->del_flag_p = &ui->music_app_del;
        out->setup = setup_scr_music_app;
        return true;
    }
    if (obj == ui->smart_home_app) {
        out->obj_pp = &ui->smart_home_app;
        out->del_flag_p = &ui->smart_home_app_del;
        out->setup = setup_scr_smart_home_app;
        return true;
    }
    if (obj == ui->calculator_app) {
        out->obj_pp = &ui->calculator_app;
        out->del_flag_p = &ui->calculator_app_del;
        out->setup = setup_scr_calculator_app;
        return true;
    }
    if (obj == ui->clock_app) {
        out->obj_pp = &ui->clock_app;
        out->del_flag_p = &ui->clock_app_del;
        out->setup = setup_scr_clock_app;
        return true;
    }
    if (obj == ui->setting_app) {
        out->obj_pp = &ui->setting_app;
        out->del_flag_p = &ui->setting_app_del;
        out->setup = setup_scr_setting_app;
        return true;
    }
    if (obj == ui->electronic_organ_app) {
        out->obj_pp = &ui->electronic_organ_app;
        out->del_flag_p = &ui->electronic_organ_app_del;
        out->setup = setup_scr_electronic_organ_app;
        return true;
    }
    if (obj == ui->drawing_board_app) {
        out->obj_pp = &ui->drawing_board_app;
        out->del_flag_p = &ui->drawing_board_app_del;
        out->setup = setup_scr_drawing_board_app;
        return true;
    }
    if (obj == ui->minecraft_app) {
        out->obj_pp = &ui->minecraft_app;
        out->del_flag_p = &ui->minecraft_app_del;
        out->setup = setup_scr_minecraft_app;
        return true;
    }
    if (obj == ui->link_game_app) {
        out->obj_pp = &ui->link_game_app;
        out->del_flag_p = &ui->link_game_app_del;
        out->setup = setup_scr_link_game_app;
        return true;
    }
    return false;
}

static bool get_current_meta(lv_ui *ui, ScreenMeta *out) {
    lv_obj_t *act = lv_scr_act();
    return get_meta_for_obj(ui, act, out);
}

void nav_to(lv_ui *ui, lv_obj_t **new_scr, bool new_scr_del, ui_setup_scr_t setup_scr, lv_scr_load_anim_t anim_type,
            uint32_t time, uint32_t delay) {
    ScreenMeta cur;
    if (get_current_meta(ui, &cur)) {
        if (nav_sp < (int)(sizeof(nav_stack) / sizeof(nav_stack[0]))) {
            nav_stack[nav_sp++] = cur;
        }
        ui_load_scr_animation(ui, new_scr, new_scr_del, cur.del_flag_p, setup_scr, anim_type, time, delay, false, true);
    } else {
        // 回退方案：无当前页面识别，直接加载目标
        bool dummy = true;
        ui_load_scr_animation(ui, new_scr, new_scr_del, &dummy, setup_scr, anim_type, time, delay, false, true);
    }
}

void nav_back(lv_ui *ui) {
    if (nav_sp <= 0) {
        // 栈空：不执行操作（保持当前页面）
        return;
    }
    ScreenMeta prev = nav_stack[--nav_sp];
    ScreenMeta cur;
    (void)get_current_meta(ui, &cur);                                     // 若失败，cur.del_flag_p 可能为 NULL
    bool *old_del = cur.del_flag_p ? cur.del_flag_p : &ui->home_app1_del; // 回退默认到 home
    bool prev_del_val = prev.del_flag_p ? *prev.del_flag_p : true;
    ui_load_scr_animation(ui, prev.obj_pp, prev_del_val, old_del, prev.setup, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 200,
                          false, true);
}

// ===============================
// 音乐播放器事件实现
// ===============================

#ifdef KEIL_COMPILE

static void anim_img_angle_exec(void *var, int32_t v) {
    lv_img_set_angle((lv_obj_t *)var, v);
}

static void stylus_to_play_ready_cb(lv_anim_t *a) {
    (void)a;
    if (!lv_obj_is_valid(guider_ui.music_app_music_recode))
        return;
    lv_anim_del(guider_ui.music_app_music_recode, anim_img_angle_exec);
    ui_animation(guider_ui.music_app_music_recode, 2000, 0, 0, 3600, lv_anim_path_linear, LV_ANIM_REPEAT_INFINITE, 0, 0,
                 0, anim_img_angle_exec, NULL, NULL, NULL);
}

// 列表项点击：根据点击项设置曲目并开始播放
void music_list_item_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_CLICKED)
        return;
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui)
        return;
    lv_obj_t *target = lv_event_get_target(e);

    int sel = 0;
    if (target == ui->music_app_music_list_item0) {
        sel = 0;
    } else if (target == ui->music_app_music_list_item1) {
        sel = 1;
    } else if (target == ui->music_app_music_list_item2) {
        sel = 2;
    } else {
        return; // 未识别的项
    }

    music_song_id = sel;
    music_resume = 0;  // 确保为播放状态
    music_playing = 0; // 终止当前曲目（若在播放）
    music_start = 1;   // 触发播放任务从头开始

    // 播放按钮状态更新为“播放中”（显示暂停图标）
    if (lv_obj_is_valid(ui->music_app_music_player_or_pause_btn)) {
        lv_obj_clear_state(ui->music_app_music_player_or_pause_btn, LV_STATE_CHECKED);
    }

    if (lv_obj_is_valid(ui->music_app_music_stylus)) {
        lv_anim_del(ui->music_app_music_stylus, anim_img_angle_exec);
        ui_animation(ui->music_app_music_stylus, 400, 0, -240, 0, lv_anim_path_ease_in_out, 0, 0, 0, 0,
                     anim_img_angle_exec, NULL, stylus_to_play_ready_cb, NULL);
    } else if (lv_obj_is_valid(ui->music_app_music_recode)) {
        lv_anim_del(ui->music_app_music_recode, anim_img_angle_exec);
        ui_animation(ui->music_app_music_recode, 2000, 0, 0, 3600, lv_anim_path_linear, LV_ANIM_REPEAT_INFINITE, 0, 0,
                     0, anim_img_angle_exec, NULL, NULL, NULL);
    }
}

// 上一首：索引减一并循环，然后重启播放
void music_prev_btn_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_CLICKED)
        return;
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui)
        return;

    music_song_id = (music_song_id + 3 - 1) % 3;
    music_resume = 0;
    music_playing = 0;
    music_start = 1;

    if (lv_obj_is_valid(ui->music_app_music_player_or_pause_btn)) {
        lv_obj_clear_state(ui->music_app_music_player_or_pause_btn, LV_STATE_CHECKED);
    }

    if (lv_obj_is_valid(ui->music_app_music_stylus)) {
        lv_anim_del(ui->music_app_music_stylus, anim_img_angle_exec);
        ui_animation(ui->music_app_music_stylus, 400, 0, -240, 0, lv_anim_path_ease_in_out, 0, 0, 0, 0,
                     anim_img_angle_exec, NULL, stylus_to_play_ready_cb, NULL);
    } else if (lv_obj_is_valid(ui->music_app_music_recode)) {
        lv_anim_del(ui->music_app_music_recode, anim_img_angle_exec);
        ui_animation(ui->music_app_music_recode, 2000, 0, 0, 3600, lv_anim_path_linear, LV_ANIM_REPEAT_INFINITE, 0, 0,
                     0, anim_img_angle_exec, NULL, NULL, NULL);
    }
}

// 下一首：索引加一并循环，然后重启播放
void music_next_btn_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_CLICKED)
        return;
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui)
        return;

    music_song_id = (music_song_id + 1) % 3;
    music_resume = 0;
    music_playing = 0;
    music_start = 1;

    if (lv_obj_is_valid(ui->music_app_music_player_or_pause_btn)) {
        lv_obj_clear_state(ui->music_app_music_player_or_pause_btn, LV_STATE_CHECKED);
    }

    if (lv_obj_is_valid(ui->music_app_music_stylus)) {
        lv_anim_del(ui->music_app_music_stylus, anim_img_angle_exec);
        ui_animation(ui->music_app_music_stylus, 400, 0, -240, 0, lv_anim_path_ease_in_out, 0, 0, 0, 0,
                     anim_img_angle_exec, NULL, stylus_to_play_ready_cb, NULL);
    } else if (lv_obj_is_valid(ui->music_app_music_recode)) {
        lv_anim_del(ui->music_app_music_recode, anim_img_angle_exec);
        ui_animation(ui->music_app_music_recode, 2000, 0, 0, 3600, lv_anim_path_linear, LV_ANIM_REPEAT_INFINITE, 0, 0,
                     0, anim_img_angle_exec, NULL, NULL, NULL);
    }
}

void music_play_pause_btn_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (!(code == LV_EVENT_VALUE_CHANGED || code == LV_EVENT_CLICKED))
        return;
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui)
        return;
    lv_obj_t *btn = lv_event_get_target(e);
    bool checked = lv_obj_has_state(btn, LV_STATE_CHECKED);

    if (checked) {
        if (music_playing) {
            music_resume = 1;
        }
        if (lv_obj_is_valid(ui->music_app_music_recode)) {
            lv_anim_del(ui->music_app_music_recode, anim_img_angle_exec);
        }
        if (lv_obj_is_valid(ui->music_app_music_stylus)) {
            lv_anim_del(ui->music_app_music_stylus, anim_img_angle_exec);
            int32_t cur = lv_img_get_angle(ui->music_app_music_stylus);
            ui_animation(ui->music_app_music_stylus, 400, 0, cur, -240, lv_anim_path_ease_in_out, 0, 0, 0, 0,
                         anim_img_angle_exec, NULL, NULL, NULL);
        }
    } else {
        music_resume = 0;
        if (!music_playing) {
            music_start = 1;
        }
        if (lv_obj_is_valid(ui->music_app_music_stylus)) {
            lv_anim_del(ui->music_app_music_stylus, anim_img_angle_exec);
            ui_animation(ui->music_app_music_stylus, 400, 0, -240, 0, lv_anim_path_ease_in_out, 0, 0, 0, 0,
                         anim_img_angle_exec, NULL, stylus_to_play_ready_cb, NULL);
        } else if (lv_obj_is_valid(ui->music_app_music_recode)) {
            lv_anim_del(ui->music_app_music_recode, anim_img_angle_exec);
            ui_animation(ui->music_app_music_recode, 2000, 0, 0, 3600, lv_anim_path_linear, LV_ANIM_REPEAT_INFINITE, 0,
                         0, 0, anim_img_angle_exec, NULL, NULL, NULL);
        }
    }
}

// 电子琴：按钮矩阵点击发声
void electronic_organ_btnm_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_VALUE_CHANGED)
        return;

    lv_obj_t *btnm = lv_event_get_target(e);
    uint16_t id = lv_btnmatrix_get_selected_btn(btnm);
    const char *txt = lv_btnmatrix_get_btn_text(btnm, id);
    if (!txt || !txt[0])
        return;

    uint16_t freq = 0;
    int n = (txt[1] >= '0' && txt[1] <= '7') ? (txt[1] - '0') : 0;
    if (n < 1 || n > 7)
        return;

    switch (txt[0]) {
    case 'L':
        switch (n) {
        case 1:
            freq = TONE_L1;
            break;
        case 2:
            freq = TONE_L2;
            break;
        case 3:
            freq = TONE_L3;
            break;
        case 4:
            freq = TONE_L4;
            break;
        case 5:
            freq = TONE_L5;
            break;
        case 6:
            freq = TONE_L6;
            break;
        case 7:
            freq = TONE_L7;
            break;
        }
        break;
    case 'M':
        switch (n) {
        case 1:
            freq = TONE_M1;
            break;
        case 2:
            freq = TONE_M2;
            break;
        case 3:
            freq = TONE_M3;
            break;
        case 4:
            freq = TONE_M4;
            break;
        case 5:
            freq = TONE_M5;
            break;
        case 6:
            freq = TONE_M6;
            break;
        case 7:
            freq = TONE_M7;
            break;
        }
        break;
    case 'H':
        switch (n) {
        case 1:
            freq = TONE_H1;
            break;
        case 2:
            freq = TONE_H2;
            break;
        case 3:
            freq = TONE_H3;
            break;
        case 4:
            freq = TONE_H4;
            break;
        case 5:
            freq = TONE_H5;
            break;
        case 6:
            freq = TONE_H6;
            break;
        case 7:
            freq = TONE_H7;
            break;
        }
        break;
    default:
        break;
    }

    if (freq > 0) {
        Beep_SetFreq(freq);
        // 点击发音：短促按键音（50ms）
        Beep_Start(5, 1, 1);
    }
}
#endif

// ===============================
// 画板事件实现
// ===============================

drawing_board_ctx_t s_drawing_ctx; // 单屏上下文

// 屏幕删除时释放画布缓冲
void drawing_board_app_delete_cb(lv_event_t *e) {
    drawing_board_ctx_t *ctx = (drawing_board_ctx_t *)lv_event_get_user_data(e);
    if (!ctx)
        return;
    ctx->seg_count = 0;
    ctx->last_valid = false;
}

void drawing_board_canvas_event_cb(lv_event_t *e) {
    drawing_board_ctx_t *ctx = (drawing_board_ctx_t *)lv_event_get_user_data(e);
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *canvas = lv_event_get_target(e);

    lv_indev_t *indev = lv_indev_get_act();
    if (!indev)
        return;

    lv_point_t p;
    lv_indev_get_point(indev, &p);

    // 转换为画布局部坐标
    lv_area_t a;
    lv_obj_get_coords(canvas, &a);
    int32_t x = p.x - a.x1;
    int32_t y = p.y - a.y1;
    lv_coord_t obj_w = lv_obj_get_width(canvas);
    lv_coord_t obj_h = lv_obj_get_height(canvas);

    // 越界保护
    if (x < 0)
        x = 0;
    else if (x >= obj_w)
        x = obj_w - 1;
    if (y < 0)
        y = 0;
    else if (y >= obj_h)
        y = obj_h - 1;

    switch (code) {
    case LV_EVENT_PRESSED: {
        ctx->last_pt.x = x;
        ctx->last_pt.y = y;
        ctx->last_valid = true;
        if (ctx->seg_count < DRAW_MAX_SEGMENTS) {
            draw_seg_t *s = &ctx->segs[ctx->seg_count++];
            s->color = lv_colorwheel_get_rgb(guider_ui.drawing_board_app_colorwheel);
            uint16_t w = (uint16_t)lv_slider_get_value(guider_ui.drawing_board_app_width_slider);
            if (w == 0)
                w = 1;
            s->width = w;
            s->p1.x = (lv_coord_t)x;
            s->p1.y = (lv_coord_t)y;
            s->p2 = s->p1;
        }
        lv_obj_invalidate(canvas);
        break;
    }
    case LV_EVENT_PRESSING: {
        if (!ctx->last_valid)
            break;
        if (ctx->seg_count < DRAW_MAX_SEGMENTS) {
            draw_seg_t *s = &ctx->segs[ctx->seg_count++];
            s->color = lv_colorwheel_get_rgb(guider_ui.drawing_board_app_colorwheel);
            uint16_t w = (uint16_t)lv_slider_get_value(guider_ui.drawing_board_app_width_slider);
            if (w == 0)
                w = 1;
            s->width = w;
            s->p1 = ctx->last_pt;
            s->p2.x = (lv_coord_t)x;
            s->p2.y = (lv_coord_t)y;
            ctx->last_pt = s->p2;
        }
        lv_obj_invalidate(canvas);
        break;
    }
    case LV_EVENT_RELEASED: {
        ctx->last_valid = false;
        break;
    }
    default:
        break;
    }
}

void drawing_board_clear_event_cb(lv_event_t *e) {
    drawing_board_ctx_t *ctx = (drawing_board_ctx_t *)lv_event_get_user_data(e);
    if (!ctx)
        return;
    ctx->seg_count = 0;
    lv_obj_invalidate(ctx->canvas);
}

void drawing_board_width_event_cb(lv_event_t *e) {
    // 这里无需立即作画，仅在按压时读取值即可；此处可更新显示或做范围保护
    LV_UNUSED(e);
}

void drawing_board_color_event_cb(lv_event_t *e) {
    // 颜色变化同样在作画事件中实时读取；保留回调以备扩展
    LV_UNUSED(e);
}

void drawing_board_paint_draw_event_cb(lv_event_t *e) {
    drawing_board_ctx_t *ctx = (drawing_board_ctx_t *)lv_event_get_user_data(e);
    lv_obj_t *obj = lv_event_get_target(e);
    lv_draw_ctx_t *draw_ctx = lv_event_get_draw_ctx(e);
    lv_area_t area;
    lv_obj_get_content_coords(obj, &area);
    lv_draw_rect_dsc_t rd;
    lv_draw_rect_dsc_init(&rd);
    rd.bg_color = lv_color_white();
    rd.bg_opa = LV_OPA_COVER;
    lv_draw_rect(draw_ctx, &rd, &area);
    for (uint16_t i = 0; i < ctx->seg_count; i++) {
        draw_seg_t *s = &ctx->segs[i];
        lv_draw_line_dsc_t ld;
        lv_draw_line_dsc_init(&ld);
        ld.color = s->color;
        ld.width = s->width;
        ld.round_start = 1;
        ld.round_end = 1;
        lv_draw_line(draw_ctx, &ld, &s->p1, &s->p2);
    }
}

// ===============================
// 智能家居事件实现
// ===============================

// —— 通用滑动动画辅助 ——
static void smart_home_anim_hide_ready_cb(lv_anim_t *a) {
    lv_obj_t *obj = (lv_obj_t *)a->var;
    if (lv_obj_is_valid(obj)) {
        lv_obj_t *parent = lv_obj_get_parent(obj);
        lv_coord_t w = lv_obj_get_width(obj);
        lv_coord_t parent_w = lv_obj_is_valid(parent) ? lv_obj_get_width(parent) : lv_obj_get_x(obj);
        lv_obj_set_x(obj, parent_w - w);
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
    }
}

static void smart_home_slide_in(lv_obj_t *page) {
    if (!lv_obj_is_valid(page))
        return;
    lv_coord_t end_x = lv_obj_get_x(page);
    lv_coord_t y = lv_obj_get_y(page);
    lv_coord_t w = lv_obj_get_width(page);

    // 从右侧外部开始，清除隐藏
    lv_obj_clear_flag(page, LV_OBJ_FLAG_HIDDEN); // 清除隐藏标志位，确保页面可见
    lv_obj_set_pos(page, end_x + w, y);          // 设置初始位置为右侧外部，准备滑动进入

    lv_anim_t a;
    lv_anim_init(&a);                                          // 从右侧外部开始，滑动到目标位置
    lv_anim_set_var(&a, page);                                 // 目标对象：要滑动的页面
    lv_anim_set_values(&a, end_x + w, end_x);                  // 从右侧外部开始，滑动到目标位置
    lv_anim_set_time(&a, 250);                                 // 动画时间：250ms
    lv_anim_set_path_cb(&a, lv_anim_path_ease_out);            // 动画路径：缓出
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_x); // 动画执行回调：设置对象的 x 坐标
    lv_anim_start(&a);                                         // 启动动画
}

static void smart_home_slide_out_and_hide(lv_obj_t *page) {
    if (!lv_obj_is_valid(page))
        return; // 无效页面，直接返回
    if (lv_obj_has_flag(page, LV_OBJ_FLAG_HIDDEN))
        return;                                 // 已隐藏，无需操作
    lv_coord_t start_x = lv_obj_get_x(page);    // 获取当前页面的 x 坐标
    lv_obj_t *parent = lv_obj_get_parent(page); // 获取父容器（假设为屏幕）
    lv_coord_t parent_w = lv_obj_is_valid(parent)
                              ? lv_obj_get_width(parent)
                              : (start_x + lv_obj_get_width(page)); // 父容器宽度（如果无效，默认使用当前页面宽度）

    lv_anim_t a;
    lv_anim_init(&a);                                          // 初始化动画
    lv_anim_set_var(&a, page);                                 // 目标对象：要滑动的页面
    lv_anim_set_values(&a, start_x, parent_w);                 // 从当前位置滑动到父容器宽度（右侧外部）
    lv_anim_set_time(&a, 200);                                 // 动画时间：200ms
    lv_anim_set_path_cb(&a, lv_anim_path_ease_in);             // 动画路径：缓入
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_x); // 动画执行回调：设置对象的 x 坐标
    lv_anim_set_ready_cb(&a, smart_home_anim_hide_ready_cb);   // 动画完成回调：隐藏对象
    lv_anim_start(&a);                                         // 启动动画
}

void smart_home_close_all_pages_with_slide(lv_ui *ui) {
    if (!ui)
        return;
    smart_home_slide_out_and_hide(ui->smart_home_app_color_led_page);
    smart_home_slide_out_and_hide(ui->smart_home_app_led_green_page);
    smart_home_slide_out_and_hide(ui->smart_home_app_lm75_page);
    smart_home_slide_out_and_hide(ui->smart_home_app_ADC_page);
    smart_home_slide_out_and_hide(ui->smart_home_app_MPU6050_page);
    smart_home_slide_out_and_hide(ui->smart_home_app_key_page);
}

void smart_home_open_page_with_slide(lv_ui *ui, lv_obj_t *page) {
    if (!ui || !lv_obj_is_valid(page))
        return;
    // 先关闭其他已打开页面
    if (page != ui->smart_home_app_color_led_page)
        smart_home_slide_out_and_hide(ui->smart_home_app_color_led_page);
    if (page != ui->smart_home_app_led_green_page)
        smart_home_slide_out_and_hide(ui->smart_home_app_led_green_page);
    if (page != ui->smart_home_app_lm75_page)
        smart_home_slide_out_and_hide(ui->smart_home_app_lm75_page);
    if (page != ui->smart_home_app_ADC_page)
        smart_home_slide_out_and_hide(ui->smart_home_app_ADC_page);
    if (page != ui->smart_home_app_MPU6050_page)
        smart_home_slide_out_and_hide(ui->smart_home_app_MPU6050_page);
    if (page != ui->smart_home_app_key_page)
        smart_home_slide_out_and_hide(ui->smart_home_app_key_page);

    // 打开目标页面（右->左滑入）
    smart_home_slide_in(page);
}
// IoT页面 - 彩灯图标点击事件
void smart_home_iot_color_led_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_CLICKED)
        return;

    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui)
        return;
    smart_home_open_page_with_slide(ui, ui->smart_home_app_color_led_page);
}

// IoT页面 - 绿灯图标点击事件
void smart_home_iot_led_green_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_CLICKED)
        return;

    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui)
        return;
    smart_home_open_page_with_slide(ui, ui->smart_home_app_led_green_page);
}

// IoT页面 - ADC图标点击事件
void smart_home_iot_adc_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_CLICKED)
        return;
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui)
        return;
    smart_home_open_page_with_slide(ui, ui->smart_home_app_ADC_page);
}

// IoT页面 - MPU6050图标点击事件
void smart_home_iot_mpu6050_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_CLICKED)
        return;
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui)
        return;
    smart_home_open_page_with_slide(ui, ui->smart_home_app_MPU6050_page);
}

// IoT页面 - LM75图标点击事件
void smart_home_iot_lm75_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_CLICKED)
        return;
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui)
        return;
    smart_home_open_page_with_slide(ui, ui->smart_home_app_lm75_page);
}

// IoT页面 - 8Key图标点击事件
void smart_home_iot_8key_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_CLICKED)
        return;
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui)
        return;
    smart_home_open_page_with_slide(ui, ui->smart_home_app_key_page);
}

// IoT页面点击返回按键：关闭所有子页面（统一滑出）
void smart_home_iot_return_event_handler(lv_event_t *e) {
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui)
        return;
    smart_home_close_all_pages_with_slide(ui);
}

#ifdef KEIL_COMPILE
// 彩灯开关事件：点击切换彩灯状态
void smart_home_color_led_sw_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_VALUE_CHANGED)
        return;

    lv_obj_t *sw = lv_event_get_target(e);
    bool checked = lv_obj_has_state(sw, LV_STATE_CHECKED);

    if (checked) {
        // 打开彩灯
        ColorLed_TurnOn();
    } else {
        // 关闭彩灯
        ColorLed_TurnOff();
    }
}

// 彩灯颜色选择事件：点击选择颜色
void smart_home_color_led_cpicker_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_VALUE_CHANGED)
        return;

    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui)
        return;

    if (!lv_obj_has_state(ui->smart_home_app_color_led_sw, LV_STATE_CHECKED))
        return;

    lv_obj_t *cpicker = lv_event_get_target(e);
    lv_color_t color = lv_colorwheel_get_rgb(cpicker);
    uint32_t raw = lv_color_to32(color);
    lv_color32_t c32;
    c32.full = raw;
    uint8_t r = c32.ch.red;
    uint8_t g = c32.ch.green;
    uint8_t b = c32.ch.blue;

    // 获取当前亮度
    int32_t brightness = 100;
    if (lv_obj_is_valid(ui->smart_home_app_color_led_light_div_slider)) {
        brightness = lv_slider_get_value(ui->smart_home_app_color_led_light_div_slider);
    }

    // 应用亮度调整
    r = (uint8_t)((r * brightness) / 100);
    g = (uint8_t)((g * brightness) / 100);
    b = (uint8_t)((b * brightness) / 100);

    // 设置颜色
    ColorLed_SetColor(r, g, b);
}

// 彩灯亮度滑块事件：滑动调整亮度
void smart_home_color_led_light_slider_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_VALUE_CHANGED)
        return;

    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui)
        return;

    if (!lv_obj_has_state(ui->smart_home_app_color_led_sw, LV_STATE_CHECKED))
        return;

    lv_obj_t *slider = lv_event_get_target(e);
    int32_t brightness = lv_slider_get_value(slider); // 0-100

    // 获取当前颜色
    lv_color_t color = lv_colorwheel_get_rgb(ui->smart_home_app_color_led_cpicker);
    uint32_t raw = lv_color_to32(color);
    lv_color32_t c32;
    c32.full = raw;
    uint8_t r = c32.ch.red;
    uint8_t g = c32.ch.green;
    uint8_t b = c32.ch.blue;

    // 应用亮度调整
    r = (uint8_t)((r * brightness) / 100);
    g = (uint8_t)((g * brightness) / 100);
    b = (uint8_t)((b * brightness) / 100);

    // 设置颜色
    ColorLed_SetColor(r, g, b);
}

// 绿灯开关事件
void smart_home_led_green_sw_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_VALUE_CHANGED)
        return;

    lv_obj_t *sw = lv_event_get_target(e);
    bool checked = lv_obj_has_state(sw, LV_STATE_CHECKED);

    if (checked) {
        // 打开绿灯
        LED_TurnOn(LED_Green);
    } else {
        // 关闭绿灯
        LED_TurnOff(LED_Green);
    }
}
#endif

// ===============================
// 我的世界游戏实现
// ===============================

#ifdef KEIL_COMPILE
lv_timer_t *minecraft_timer = NULL;
lv_obj_t *minecraft_img = NULL;

// 游戏循环定时器回调
void minecraft_timer_cb(lv_timer_t *timer) {
    (void)timer;

    minecraft_loop();
    if (lv_obj_is_valid(minecraft_img)) {
        lv_obj_invalidate(minecraft_img);
    }
}

void cleanup_scr_minecraft(lv_ui *ui) {
    // 停止定时器
    if (minecraft_timer) {
        lv_timer_del(minecraft_timer);
        minecraft_timer = NULL;
    }
    if (lv_obj_is_valid(minecraft_img)) {
        lv_obj_del(minecraft_img);
        minecraft_img = NULL;
    }
    minecraft_deinit();
    (void)ui;
}
#endif

void minecraft_app_screen_delete_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_DELETE: {
        cleanup_scr_minecraft(&guider_ui);
        break;
    }
    default:
        break;
    }
}

// ===============================
// 时钟事件实现
// ===============================

static lv_timer_t *s_sw_timer;
static int s_sw_cs;
static uint8_t s_sw_running;
static void s_stopwatch_cb(lv_timer_t *t) {
    (void)t;
    s_sw_cs++;
    int cs = s_sw_cs % 100;
    int total_s = s_sw_cs / 100;
    int s = total_s % 60;
    int m = total_s / 60;
    if (lv_obj_is_valid(guider_ui.clock_app_second_chronograph)) {
        char buf[16];
        lv_snprintf(buf, sizeof(buf), "%02d:%02d.%02d", m, s, cs);
        lv_label_set_text(guider_ui.clock_app_second_chronograph, buf);
    }
}
void clock_app_start_or_pausing_btn_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_CLICKED)
        return;
    if (s_sw_running) {
        if (s_sw_timer) {
            lv_timer_del(s_sw_timer);
            s_sw_timer = NULL;
        }
        s_sw_running = 0;
        if (lv_obj_is_valid(guider_ui.clock_app_start_or_pausing_btn_label)) {
            lv_label_set_text(guider_ui.clock_app_start_or_pausing_btn_label, "开始");
        }
    } else {
        if (!s_sw_timer)
            s_sw_timer = lv_timer_create(s_stopwatch_cb, 10, NULL);
        s_sw_running = 1;
        if (lv_obj_is_valid(guider_ui.clock_app_start_or_pausing_btn_label)) {
            lv_label_set_text(guider_ui.clock_app_start_or_pausing_btn_label, "暂停");
        }
    }
}
void clock_app_reset_btn_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_CLICKED)
        return;
    if (s_sw_timer) {
        lv_timer_del(s_sw_timer);
        s_sw_timer = NULL;
    }
    s_sw_running = 0;
    s_sw_cs = 0;
    if (lv_obj_is_valid(guider_ui.clock_app_second_chronograph)) {
        lv_label_set_text(guider_ui.clock_app_second_chronograph, "00:00.00");
    }
    if (lv_obj_is_valid(guider_ui.clock_app_start_or_pausing_btn_label)) {
        lv_label_set_text(guider_ui.clock_app_start_or_pausing_btn_label, "开始");
    }
}

static lv_timer_t *s_timer;
static int s_timer_remain;
static uint8_t s_timer_running;
static uint8_t s_timer_bell_on;
static uint8_t s_timer_ringing;
static lv_timer_t *s_ring_flag_clear;
static int s_timer_initial;
static void s_ring_clear_cb(lv_timer_t *tt) {
    (void)tt;
    s_timer_ringing = 0;
    if (s_ring_flag_clear) {
        lv_timer_del(s_ring_flag_clear);
        s_ring_flag_clear = NULL;
    }
}
static int parse_hhmmss(const char *txt) {
    int h = 0, m = 0, s = 0;
    if (!txt)
        return 0;
    int n = sscanf(txt, "%d:%d:%d", &h, &m, &s);
    if (n != 3)
        return 0;
    if (h < 0 || m < 0 || s < 0)
        return 0;
    if (m >= 60 || s >= 60)
        return 0;
    return h * 3600 + m * 60 + s;
}
static void update_timer_display() {
    int h = s_timer_remain / 3600;
    int m = (s_timer_remain % 3600) / 60;
    int s = s_timer_remain % 60;
    char buf[16];
    lv_snprintf(buf, sizeof(buf), "%02d:%02d:%02d", h, m, s);
    if (lv_obj_is_valid(guider_ui.clock_app_timer_show))
        lv_textarea_set_text(guider_ui.clock_app_timer_show, buf);
}
static void s_countdown_cb(lv_timer_t *t) {
    (void)t;
    if (s_timer_remain > 0) {
        s_timer_remain--;
        update_timer_display();
        if (s_timer_remain == 0) {
            if (s_timer) {
                lv_timer_del(s_timer);
                s_timer = NULL;
            }
            s_timer_running = 0;
            if (s_timer_bell_on) {
                Beep_SetFreq(1500);
                Beep_Start(3000, 1, 1);
                s_timer_ringing = 1;
                if (s_ring_flag_clear) {
                    lv_timer_del(s_ring_flag_clear);
                    s_ring_flag_clear = NULL;
                }
                s_ring_flag_clear = lv_timer_create(s_ring_clear_cb, 30000, NULL);
                if (lv_obj_is_valid(guider_ui.clock_app_timer_SPC_btn_label)) {
                    lv_label_set_text(guider_ui.clock_app_timer_SPC_btn_label, "关闭");
                }
            } else {
                if (lv_obj_is_valid(guider_ui.clock_app_timer_SPC_btn_label)) {
                    lv_label_set_text(guider_ui.clock_app_timer_SPC_btn_label, "开始");
                }
            }
        }
    }
}
void clock_app_timer_SPC_btn_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_CLICKED)
        return;
    if (s_timer_ringing) {
        Beep_Stop();
        s_timer_ringing = 0;
        if (lv_obj_is_valid(guider_ui.clock_app_timer_SPC_btn_label)) {
            lv_label_set_text(guider_ui.clock_app_timer_SPC_btn_label, "开始");
        }
        return;
    }
    if (!s_timer_running) {
        const char *txt = lv_textarea_get_text(guider_ui.clock_app_timer_show);
        int sec = parse_hhmmss(txt);
        if (sec <= 0)
            return;
        s_timer_remain = sec;
        s_timer_initial = sec;
        update_timer_display();
        if (!s_timer)
            s_timer = lv_timer_create(s_countdown_cb, 1000, NULL);
        s_timer_running = 1;
        if (lv_obj_is_valid(guider_ui.clock_app_timer_SPC_btn_label)) {
            lv_label_set_text(guider_ui.clock_app_timer_SPC_btn_label, "暂停");
        }
    } else {
        if (s_timer) {
            lv_timer_del(s_timer);
            s_timer = NULL;
        }
        s_timer_running = 0;
        if (lv_obj_is_valid(guider_ui.clock_app_timer_SPC_btn_label)) {
            lv_label_set_text(guider_ui.clock_app_timer_SPC_btn_label, "开始");
        }
    }
}
void clock_app_timer_reset_btn_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_CLICKED)
        return;
    if (s_timer) {
        lv_timer_del(s_timer);
        s_timer = NULL;
    }
    s_timer_running = 0;
    if (s_timer_initial > 0) {
        s_timer_remain = s_timer_initial;
    } else {
        s_timer_remain = 0;
    }
    if (s_timer_ringing) {
        Beep_Stop();
        s_timer_ringing = 0;
    }
    update_timer_display();
    if (lv_obj_is_valid(guider_ui.clock_app_timer_SPC_btn_label)) {
        lv_label_set_text(guider_ui.clock_app_timer_SPC_btn_label, "开始");
    }
}
void clock_app_timer_bell_btn_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_CLICKED)
        return;
    s_timer_bell_on = !s_timer_bell_on;
    static lv_style_t s_style_strike;
    static uint8_t s_style_strike_inited;
    if (!s_style_strike_inited) {
        lv_style_init(&s_style_strike);
        lv_style_set_text_decor(&s_style_strike, LV_TEXT_DECOR_STRIKETHROUGH);
        s_style_strike_inited = 1;
    }
    if (lv_obj_is_valid(guider_ui.clock_app_timer_bell_btn_label)) {
        if (s_timer_bell_on) {
            lv_obj_remove_style(guider_ui.clock_app_timer_bell_btn_label, &s_style_strike, LV_PART_MAIN);
        } else {
            lv_obj_add_style(guider_ui.clock_app_timer_bell_btn_label, &s_style_strike, LV_PART_MAIN);
        }
    }
}
void clock_app_init_customize(lv_ui *ui) {
    (void)ui;
    s_timer_bell_on = 1;
    if (lv_obj_is_valid(guider_ui.clock_app_reset_btn)) {
        lv_obj_clear_flag(guider_ui.clock_app_reset_btn, LV_OBJ_FLAG_HIDDEN);
    }
    if (lv_obj_is_valid(guider_ui.clock_app_start_or_pausing_btn_label)) {
        lv_label_set_text(guider_ui.clock_app_start_or_pausing_btn_label, "开始");
    }
    if (lv_obj_is_valid(guider_ui.clock_app_timer_SPC_btn_label)) {
        lv_label_set_text(guider_ui.clock_app_timer_SPC_btn_label, "开始");
    }
    if (lv_obj_is_valid(guider_ui.clock_app_analog_clock_1)) {
        lv_analogclock_set_time(guider_ui.clock_app_analog_clock_1, g_time_hour_value, g_time_min_value, g_time_sec_value);
    }
    static lv_style_t s_style_strike;
    static uint8_t s_style_strike_inited;
    if (!s_style_strike_inited) {
        lv_style_init(&s_style_strike);
        lv_style_set_text_decor(&s_style_strike, LV_TEXT_DECOR_STRIKETHROUGH);
        s_style_strike_inited = 1;
    }
    if (lv_obj_is_valid(guider_ui.clock_app_timer_bell_btn_label)) {
        lv_obj_remove_style(guider_ui.clock_app_timer_bell_btn_label, &s_style_strike, LV_PART_MAIN);
    }
}
