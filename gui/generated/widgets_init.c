/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include "gui_guider.h"
#include "widgets_init.h"
#include <stdlib.h>
#include <string.h>


__attribute__((unused)) void kb_event_cb (lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *kb = lv_event_get_target(e);
    if(code == LV_EVENT_READY || code == LV_EVENT_CANCEL) {
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

__attribute__((unused)) void ta_event_cb (lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
#if LV_USE_KEYBOARD || LV_USE_ZH_KEYBOARD
    lv_obj_t *ta = lv_event_get_target(e);
#endif
    lv_obj_t *kb = lv_event_get_user_data(e);
    if (code == LV_EVENT_FOCUSED || code == LV_EVENT_CLICKED)
    {
#if LV_USE_ZH_KEYBOARD != 0
        lv_zh_keyboard_set_textarea(kb, ta);
#endif
#if LV_USE_KEYBOARD != 0
        lv_keyboard_set_textarea(kb, ta);
#endif
        lv_obj_move_foreground(kb);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
    if (code == LV_EVENT_CANCEL || code == LV_EVENT_DEFOCUSED)
    {

#if LV_USE_ZH_KEYBOARD != 0
        lv_zh_keyboard_set_textarea(kb, ta);
#endif
#if LV_USE_KEYBOARD != 0
        lv_keyboard_set_textarea(kb, ta);
#endif
        lv_obj_move_background(kb);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

#if LV_USE_ANALOGCLOCK != 0
void clock_count(int *hour, int *min, int *sec)
{
    (*sec)++;
    if(*sec == 60)
    {
        *sec = 0;
        (*min)++;
    }
    if(*min == 60)
    {
        *min = 0;
        if(*hour < 12)
        {
            (*hour)++;
        } else {
            (*hour)++;
            *hour = *hour %12;
        }
    }
}
#endif


extern int home_app1_time_hour_value;
extern int home_app1_time_min_value;
extern int home_app1_time_sec_value;

void home_app1_time_timer(lv_timer_t *timer)
{
    clock_count_24(&home_app1_time_hour_value, &home_app1_time_min_value, &home_app1_time_sec_value);
    if (lv_obj_is_valid(guider_ui.home_app1_time))
    {
        lv_dclock_set_text_fmt(guider_ui.home_app1_time, "%d:%02d", home_app1_time_hour_value, home_app1_time_min_value);
    }
}
static lv_obj_t * home_app1_date_calendar;

void home_app1_date_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_FOCUSED) {
        char * s = lv_label_get_text(btn);
        if(home_app1_date_calendar == NULL) {
            home_app1_date_init_calendar(btn, s);
        }
    }
}

void home_app1_date_init_calendar(lv_obj_t *obj, char * s)
{
    if (home_app1_date_calendar == NULL) {
        lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        home_app1_date_calendar = lv_calendar_create(lv_layer_top());
        lv_obj_t * scr = lv_obj_get_screen(obj);
        lv_coord_t scr_height = lv_obj_get_height(scr);
        lv_coord_t scr_width = lv_obj_get_width(scr);
        lv_obj_set_size(home_app1_date_calendar, scr_width * 0.8, scr_height * 0.8);
        char * year = strtok(s, "/");
        char * month = strtok(NULL, "/");
        char * day = strtok(NULL, "/");
        lv_calendar_set_showed_date(home_app1_date_calendar, atoi(year), atoi(month));
        lv_calendar_date_t highlighted_days[1];       /*Only its pointer will be saved so should be static*/
        highlighted_days[0].year = atoi(year);
        highlighted_days[0].month = atoi(month);
        highlighted_days[0].day = atoi(day);
        lv_calendar_set_highlighted_dates(home_app1_date_calendar, highlighted_days, 1);
        lv_obj_align(home_app1_date_calendar,LV_ALIGN_CENTER, 0, 0);

        lv_obj_add_event_cb(home_app1_date_calendar, home_app1_date_calendar_event_handler, LV_EVENT_ALL,NULL);
        lv_calendar_header_arrow_create(home_app1_date_calendar);
        lv_obj_update_layout(scr);
    }
}

void home_app1_date_calendar_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        lv_calendar_date_t date;
        lv_calendar_get_pressed_date(obj,&date);
        char buf[16];
        lv_snprintf(buf,sizeof(buf),"%d/%02d/%02d", date.year, date.month,date.day);
        lv_label_set_text(guider_ui.home_app1_date, buf);
        lv_obj_clear_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_bg_opa(lv_layer_top(), LV_OPA_TRANSP, 0);
        lv_obj_del(home_app1_date_calendar);
        home_app1_date_calendar = NULL;
    }
}



extern int g_time_hour_value;
extern int g_time_min_value;
extern int g_time_sec_value;

void clock_app_analog_clock_1_timer(lv_timer_t *timer)
{
    if (lv_obj_is_valid(guider_ui.clock_app_analog_clock_1))
    {
        lv_analogclock_set_time(guider_ui.clock_app_analog_clock_1, g_time_hour_value, g_time_min_value, g_time_sec_value);
    }
}
void clock_app_calendar_draw_part_begin_event_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    lv_obj_draw_part_dsc_t * dsc = lv_event_get_param(e);
    if(dsc->part == LV_PART_ITEMS) {
        if(dsc->id < 7) {
            dsc->label_dsc->color = lv_color_hex(0x0D3055);
            dsc->label_dsc->font = &lv_font_montserratMedium_12;
        } else if (lv_btnmatrix_has_btn_ctrl(obj, dsc->id, LV_BTNMATRIX_CTRL_DISABLED)) {
            dsc->label_dsc->color = lv_color_hex(0xA9A2A2);
            dsc->label_dsc->font = &lv_font_montserratMedium_12;
            dsc->rect_dsc->bg_opa = 0;
        } else if(lv_btnmatrix_has_btn_ctrl(obj, dsc->id, LV_BTNMATRIX_CTRL_CUSTOM_1)) {
            dsc->label_dsc->color = lv_color_hex(0x0D3055);
            dsc->label_dsc->font = &lv_font_montserratMedium_12;
            dsc->rect_dsc->bg_opa = 255;
            dsc->rect_dsc->bg_color = lv_color_hex(0x01a2b1);
            dsc->rect_dsc->border_opa = 255;
            dsc->rect_dsc->border_width = 1;
            dsc->rect_dsc->border_color = lv_color_hex(0xc0c0c0);
        } else if(lv_btnmatrix_has_btn_ctrl(obj, dsc->id, LV_BTNMATRIX_CTRL_CUSTOM_2)) {
            dsc->label_dsc->color = lv_color_hex(0x0D3055);
            dsc->label_dsc->font = &lv_font_montserratMedium_12;
            dsc->rect_dsc->bg_opa = 255;
            dsc->rect_dsc->bg_color = lv_color_hex(0x2195f6);
        } else {
        }
    }
}
void clock_app_calendar_event_handler(lv_event_t * e)
{
    lv_calendar_date_t date;
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t * obj = lv_event_get_current_target(e);
        lv_calendar_get_pressed_date(obj,&date);
        lv_calendar_set_highlighted_dates(obj, &date, 1);
    }
}

