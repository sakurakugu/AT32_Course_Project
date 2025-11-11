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
#endif

volatile uint8_t wifi_reconnect_requested;

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
void setup_scr_status_app(lv_ui *ui);
void setup_scr_weather_app(lv_ui *ui);
void setup_scr_music_app(lv_ui *ui);
void setup_scr_smart_home_app(lv_ui *ui);
void setup_scr_calculator_app(lv_ui *ui);
void setup_scr_deepseek_app(lv_ui *ui);
void setup_scr_setting_app(lv_ui *ui);
void setup_scr_electronic_organ_app(lv_ui *ui);
void setup_scr_drawing_board_app(lv_ui *ui);
void setup_scr_game2(lv_ui *ui);
void setup_scr_game3(lv_ui *ui);
void setup_scr_game4(lv_ui *ui);
void setup_scr_game5(lv_ui *ui);

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
    if (obj == ui->status_app) {
        out->obj_pp = &ui->status_app;
        out->del_flag_p = &ui->status_app_del;
        out->setup = setup_scr_status_app;
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
    if (obj == ui->deepseek_app) {
        out->obj_pp = &ui->deepseek_app;
        out->del_flag_p = &ui->deepseek_app_del;
        out->setup = setup_scr_deepseek_app;
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
    if (obj == ui->game2) {
        out->obj_pp = &ui->game2;
        out->del_flag_p = &ui->game2_del;
        out->setup = setup_scr_game2;
        return true;
    }
    if (obj == ui->game3) {
        out->obj_pp = &ui->game3;
        out->del_flag_p = &ui->game3_del;
        out->setup = setup_scr_game3;
        return true;
    }
    if (obj == ui->game4) {
        out->obj_pp = &ui->game4;
        out->del_flag_p = &ui->game4_del;
        out->setup = setup_scr_game4;
        return true;
    }
    if (obj == ui->game5) {
        out->obj_pp = &ui->game5;
        out->del_flag_p = &ui->game5_del;
        out->setup = setup_scr_game5;
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
    if (lv_obj_is_valid(ui->music_app_imgbtn_4)) {
        lv_obj_clear_state(ui->music_app_imgbtn_4, LV_STATE_CHECKED);
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

    if (lv_obj_is_valid(ui->music_app_imgbtn_4)) {
        lv_obj_clear_state(ui->music_app_imgbtn_4, LV_STATE_CHECKED);
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

    if (lv_obj_is_valid(ui->music_app_imgbtn_4)) {
        lv_obj_clear_state(ui->music_app_imgbtn_4, LV_STATE_CHECKED);
    }
}

// 播放/暂停切换：依据按钮选中状态控制播放
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
        // 显示“播放”图标，代表当前是暂停状态
        if (music_playing) {
            music_resume = 1; // 进入暂停
        }
    } else {
        // 显示“暂停”图标，代表当前是播放状态
        music_resume = 0; // 取消暂停
        if (!music_playing) {
            music_start = 1; // 从头开始播放当前选曲
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
        beep_setFreq(freq);
        // 点击发音：短促按键音（50ms）
        beep_start(5, 1, 1);
    }
}

// ===============================
// 画板事件实现
// ===============================

drawing_board_ctx_t s_drawing_ctx; // 单屏上下文

// 屏幕删除时释放画布缓冲
void drawing_board_app_delete_cb(lv_event_t *e) {
    drawing_board_ctx_t *ctx = (drawing_board_ctx_t *)lv_event_get_user_data(e);
    if (ctx && ctx->canvas_buf) {
        lv_mem_free(ctx->canvas_buf);
        ctx->canvas_buf = NULL;
    }
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

    // 越界保护
    if (x < 0)
        x = 0;
    else if (x >= DRAW_CANVAS_W)
        x = DRAW_CANVAS_W - 1;
    if (y < 0)
        y = 0;
    else if (y >= DRAW_CANVAS_H)
        y = DRAW_CANVAS_H - 1;

    switch (code) {
    case LV_EVENT_PRESSED: {
        ctx->last_pt.x = x;
        ctx->last_pt.y = y;
        ctx->last_valid = true;

        // 画一个圆点，作为起笔
        lv_draw_rect_dsc_t rect_dsc;
        lv_draw_rect_dsc_init(&rect_dsc);
        rect_dsc.bg_color = lv_colorwheel_get_rgb(guider_ui.drawing_board_app_colorwheel);
        rect_dsc.radius = lv_slider_get_value(guider_ui.drawing_board_app_width_slider) / 2;
        rect_dsc.bg_opa = LV_OPA_COVER;
        int32_t r = rect_dsc.radius;
        if (r < 1)
            r = 1;
        lv_canvas_draw_rect(ctx->canvas, x - r, y - r, r * 2, r * 2, &rect_dsc);
        break;
    }
    case LV_EVENT_PRESSING: {
        if (!ctx->last_valid)
            break;
        // 画上一个点到当前点的线段
        lv_draw_line_dsc_t line_dsc;
        lv_draw_line_dsc_init(&line_dsc);
        line_dsc.color = lv_colorwheel_get_rgb(guider_ui.drawing_board_app_colorwheel);
        line_dsc.width = lv_slider_get_value(guider_ui.drawing_board_app_width_slider);
        line_dsc.round_start = 1;
        line_dsc.round_end = 1;

        lv_point_t p1 = ctx->last_pt;
        lv_point_t p2 = {(lv_coord_t)x, (lv_coord_t)y};

        // 使用 LVGL 画线 API（传入点数组与点数）
        lv_point_t pts[2] = {p1, p2};
        lv_canvas_draw_line(ctx->canvas, pts, 2, &line_dsc);

        ctx->last_pt = p2;
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
    // 清空为白色背景
    lv_canvas_fill_bg(ctx->canvas, lv_color_white(), LV_OPA_COVER);
}

void drawing_board_width_event_cb(lv_event_t *e) {
    // 这里无需立即作画，仅在按压时读取值即可；此处可更新显示或做范围保护
    LV_UNUSED(e);
}

void drawing_board_color_event_cb(lv_event_t *e) {
    // 颜色变化同样在作画事件中实时读取；保留回调以备扩展
    LV_UNUSED(e);
}
