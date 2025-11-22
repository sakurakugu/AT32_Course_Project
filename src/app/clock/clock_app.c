#include "clock_app.h"
#include "beep.h"
#include <stdio.h>

// ===============================
// 时钟事件实现
// ===============================
int g_time_min_value = 25;
int g_time_hour_value = 11;
int g_time_sec_value = 50;

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
        lv_analogclock_set_time(guider_ui.clock_app_analog_clock_1, g_time_hour_value, g_time_min_value,
                                g_time_sec_value);
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
