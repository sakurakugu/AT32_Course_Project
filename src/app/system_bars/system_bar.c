#include "system_bars.h"
#include "clock_app.h"

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

static void status_bar_timer_cb(lv_timer_t *timer) {
    (void)timer;
    clock_count_24(&clock_app_g_time_hour_value, &clock_app_g_time_min_value, &clock_app_g_time_sec_value);
    if (lv_obj_is_valid(g_status_bar_time)) {
        lv_dclock_set_text_fmt(g_status_bar_time, "%d:%02d", clock_app_g_time_hour_value, clock_app_g_time_min_value);
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
    lv_obj_add_flag(g_status_bar_wifi, LV_OBJ_FLAG_HIDDEN);

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
    status_bar_update_wifi(false);
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

void status_bar_update_sound(bool on) {
    if (!lv_obj_is_valid(g_status_bar_voice_on) || !lv_obj_is_valid(g_status_bar_voice_off))
        return;
    if (on) {
        lv_obj_clear_flag(g_status_bar_voice_on, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(g_status_bar_voice_off, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_add_flag(g_status_bar_voice_on, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(g_status_bar_voice_off, LV_OBJ_FLAG_HIDDEN);
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

void status_bar_update_wifi(bool connected) {
    if (!lv_obj_is_valid(g_status_bar_wifi))
        return;
    if (connected) {
        lv_obj_clear_flag(g_status_bar_wifi, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_add_flag(g_status_bar_wifi, LV_OBJ_FLAG_HIDDEN);
    }
    if (lv_obj_is_valid(g_status_bar_voice_on)) {
        lv_obj_set_pos(g_status_bar_voice_on, connected ? 434 : 456, 0);
    }
    if (lv_obj_is_valid(g_status_bar_voice_off)) {
        lv_obj_set_pos(g_status_bar_voice_off, connected ? 434 : 456, 0);
    }
}

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
