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


extern int home_app2_time_hour_value;
extern int home_app2_time_min_value;
extern int home_app2_time_sec_value;

void home_app2_time_timer(lv_timer_t *timer)
{
    clock_count_24(&home_app2_time_hour_value, &home_app2_time_min_value, &home_app2_time_sec_value);
    if (lv_obj_is_valid(guider_ui.home_app2_time))
    {
        lv_dclock_set_text_fmt(guider_ui.home_app2_time, "%d:%02d", home_app2_time_hour_value, home_app2_time_min_value);
    }
}
static lv_obj_t * home_app2_date_calendar;

void home_app2_date_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_FOCUSED) {
        char * s = lv_label_get_text(btn);
        if(home_app2_date_calendar == NULL) {
            home_app2_date_init_calendar(btn, s);
        }
    }
}

void home_app2_date_init_calendar(lv_obj_t *obj, char * s)
{
    if (home_app2_date_calendar == NULL) {
        lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        home_app2_date_calendar = lv_calendar_create(lv_layer_top());
        lv_obj_t * scr = lv_obj_get_screen(obj);
        lv_coord_t scr_height = lv_obj_get_height(scr);
        lv_coord_t scr_width = lv_obj_get_width(scr);
        lv_obj_set_size(home_app2_date_calendar, scr_width * 0.8, scr_height * 0.8);
        char * year = strtok(s, "/");
        char * month = strtok(NULL, "/");
        char * day = strtok(NULL, "/");
        lv_calendar_set_showed_date(home_app2_date_calendar, atoi(year), atoi(month));
        lv_calendar_date_t highlighted_days[1];       /*Only its pointer will be saved so should be static*/
        highlighted_days[0].year = atoi(year);
        highlighted_days[0].month = atoi(month);
        highlighted_days[0].day = atoi(day);
        lv_calendar_set_highlighted_dates(home_app2_date_calendar, highlighted_days, 1);
        lv_obj_align(home_app2_date_calendar,LV_ALIGN_CENTER, 0, 0);

        lv_obj_add_event_cb(home_app2_date_calendar, home_app2_date_calendar_event_handler, LV_EVENT_ALL,NULL);
        lv_calendar_header_arrow_create(home_app2_date_calendar);
        lv_obj_update_layout(scr);
    }
}

void home_app2_date_calendar_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        lv_calendar_date_t date;
        lv_calendar_get_pressed_date(obj,&date);
        char buf[16];
        lv_snprintf(buf,sizeof(buf),"%d/%02d/%02d", date.year, date.month,date.day);
        lv_label_set_text(guider_ui.home_app2_date, buf);
        lv_obj_clear_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_bg_opa(lv_layer_top(), LV_OPA_TRANSP, 0);
        lv_obj_del(home_app2_date_calendar);
        home_app2_date_calendar = NULL;
    }
}


extern int weather_app_time_hour_value;
extern int weather_app_time_min_value;
extern int weather_app_time_sec_value;

void weather_app_time_timer(lv_timer_t *timer)
{
    clock_count_24(&weather_app_time_hour_value, &weather_app_time_min_value, &weather_app_time_sec_value);
    if (lv_obj_is_valid(guider_ui.weather_app_time))
    {
        lv_dclock_set_text_fmt(guider_ui.weather_app_time, "%d:%02d", weather_app_time_hour_value, weather_app_time_min_value);
    }
}
static lv_obj_t * weather_app_date_calendar;

void weather_app_date_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_FOCUSED) {
        char * s = lv_label_get_text(btn);
        if(weather_app_date_calendar == NULL) {
            weather_app_date_init_calendar(btn, s);
        }
    }
}

void weather_app_date_init_calendar(lv_obj_t *obj, char * s)
{
    if (weather_app_date_calendar == NULL) {
        lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        weather_app_date_calendar = lv_calendar_create(lv_layer_top());
        lv_obj_t * scr = lv_obj_get_screen(obj);
        lv_coord_t scr_height = lv_obj_get_height(scr);
        lv_coord_t scr_width = lv_obj_get_width(scr);
        lv_obj_set_size(weather_app_date_calendar, scr_width * 0.8, scr_height * 0.8);
        char * year = strtok(s, "/");
        char * month = strtok(NULL, "/");
        char * day = strtok(NULL, "/");
        lv_calendar_set_showed_date(weather_app_date_calendar, atoi(year), atoi(month));
        lv_calendar_date_t highlighted_days[1];       /*Only its pointer will be saved so should be static*/
        highlighted_days[0].year = atoi(year);
        highlighted_days[0].month = atoi(month);
        highlighted_days[0].day = atoi(day);
        lv_calendar_set_highlighted_dates(weather_app_date_calendar, highlighted_days, 1);
        lv_obj_align(weather_app_date_calendar,LV_ALIGN_CENTER, 0, 0);

        lv_obj_add_event_cb(weather_app_date_calendar, weather_app_date_calendar_event_handler, LV_EVENT_ALL,NULL);
        lv_calendar_header_arrow_create(weather_app_date_calendar);
        lv_obj_update_layout(scr);
    }
}

void weather_app_date_calendar_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        lv_calendar_date_t date;
        lv_calendar_get_pressed_date(obj,&date);
        char buf[16];
        lv_snprintf(buf,sizeof(buf),"%d/%02d/%02d", date.year, date.month,date.day);
        lv_label_set_text(guider_ui.weather_app_date, buf);
        lv_obj_clear_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_bg_opa(lv_layer_top(), LV_OPA_TRANSP, 0);
        lv_obj_del(weather_app_date_calendar);
        weather_app_date_calendar = NULL;
    }
}


extern int music_app_time_hour_value;
extern int music_app_time_min_value;
extern int music_app_time_sec_value;

void music_app_time_timer(lv_timer_t *timer)
{
    clock_count_24(&music_app_time_hour_value, &music_app_time_min_value, &music_app_time_sec_value);
    if (lv_obj_is_valid(guider_ui.music_app_time))
    {
        lv_dclock_set_text_fmt(guider_ui.music_app_time, "%d:%02d", music_app_time_hour_value, music_app_time_min_value);
    }
}
static lv_obj_t * music_app_date_calendar;

void music_app_date_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_FOCUSED) {
        char * s = lv_label_get_text(btn);
        if(music_app_date_calendar == NULL) {
            music_app_date_init_calendar(btn, s);
        }
    }
}

void music_app_date_init_calendar(lv_obj_t *obj, char * s)
{
    if (music_app_date_calendar == NULL) {
        lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        music_app_date_calendar = lv_calendar_create(lv_layer_top());
        lv_obj_t * scr = lv_obj_get_screen(obj);
        lv_coord_t scr_height = lv_obj_get_height(scr);
        lv_coord_t scr_width = lv_obj_get_width(scr);
        lv_obj_set_size(music_app_date_calendar, scr_width * 0.8, scr_height * 0.8);
        char * year = strtok(s, "/");
        char * month = strtok(NULL, "/");
        char * day = strtok(NULL, "/");
        lv_calendar_set_showed_date(music_app_date_calendar, atoi(year), atoi(month));
        lv_calendar_date_t highlighted_days[1];       /*Only its pointer will be saved so should be static*/
        highlighted_days[0].year = atoi(year);
        highlighted_days[0].month = atoi(month);
        highlighted_days[0].day = atoi(day);
        lv_calendar_set_highlighted_dates(music_app_date_calendar, highlighted_days, 1);
        lv_obj_align(music_app_date_calendar,LV_ALIGN_CENTER, 0, 0);

        lv_obj_add_event_cb(music_app_date_calendar, music_app_date_calendar_event_handler, LV_EVENT_ALL,NULL);
        lv_calendar_header_arrow_create(music_app_date_calendar);
        lv_obj_update_layout(scr);
    }
}

void music_app_date_calendar_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        lv_calendar_date_t date;
        lv_calendar_get_pressed_date(obj,&date);
        char buf[16];
        lv_snprintf(buf,sizeof(buf),"%d/%02d/%02d", date.year, date.month,date.day);
        lv_label_set_text(guider_ui.music_app_date, buf);
        lv_obj_clear_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_bg_opa(lv_layer_top(), LV_OPA_TRANSP, 0);
        lv_obj_del(music_app_date_calendar);
        music_app_date_calendar = NULL;
    }
}


extern int smart_home_app_time_hour_value;
extern int smart_home_app_time_min_value;
extern int smart_home_app_time_sec_value;

void smart_home_app_time_timer(lv_timer_t *timer)
{
    clock_count_24(&smart_home_app_time_hour_value, &smart_home_app_time_min_value, &smart_home_app_time_sec_value);
    if (lv_obj_is_valid(guider_ui.smart_home_app_time))
    {
        lv_dclock_set_text_fmt(guider_ui.smart_home_app_time, "%d:%02d", smart_home_app_time_hour_value, smart_home_app_time_min_value);
    }
}
static lv_obj_t * smart_home_app_date_calendar;

void smart_home_app_date_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_FOCUSED) {
        char * s = lv_label_get_text(btn);
        if(smart_home_app_date_calendar == NULL) {
            smart_home_app_date_init_calendar(btn, s);
        }
    }
}

void smart_home_app_date_init_calendar(lv_obj_t *obj, char * s)
{
    if (smart_home_app_date_calendar == NULL) {
        lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        smart_home_app_date_calendar = lv_calendar_create(lv_layer_top());
        lv_obj_t * scr = lv_obj_get_screen(obj);
        lv_coord_t scr_height = lv_obj_get_height(scr);
        lv_coord_t scr_width = lv_obj_get_width(scr);
        lv_obj_set_size(smart_home_app_date_calendar, scr_width * 0.8, scr_height * 0.8);
        char * year = strtok(s, "/");
        char * month = strtok(NULL, "/");
        char * day = strtok(NULL, "/");
        lv_calendar_set_showed_date(smart_home_app_date_calendar, atoi(year), atoi(month));
        lv_calendar_date_t highlighted_days[1];       /*Only its pointer will be saved so should be static*/
        highlighted_days[0].year = atoi(year);
        highlighted_days[0].month = atoi(month);
        highlighted_days[0].day = atoi(day);
        lv_calendar_set_highlighted_dates(smart_home_app_date_calendar, highlighted_days, 1);
        lv_obj_align(smart_home_app_date_calendar,LV_ALIGN_CENTER, 0, 0);

        lv_obj_add_event_cb(smart_home_app_date_calendar, smart_home_app_date_calendar_event_handler, LV_EVENT_ALL,NULL);
        lv_calendar_header_arrow_create(smart_home_app_date_calendar);
        lv_obj_update_layout(scr);
    }
}

void smart_home_app_date_calendar_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        lv_calendar_date_t date;
        lv_calendar_get_pressed_date(obj,&date);
        char buf[16];
        lv_snprintf(buf,sizeof(buf),"%d/%02d/%02d", date.year, date.month,date.day);
        lv_label_set_text(guider_ui.smart_home_app_date, buf);
        lv_obj_clear_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_bg_opa(lv_layer_top(), LV_OPA_TRANSP, 0);
        lv_obj_del(smart_home_app_date_calendar);
        smart_home_app_date_calendar = NULL;
    }
}


extern int calculator_app_time_hour_value;
extern int calculator_app_time_min_value;
extern int calculator_app_time_sec_value;

void calculator_app_time_timer(lv_timer_t *timer)
{
    clock_count_24(&calculator_app_time_hour_value, &calculator_app_time_min_value, &calculator_app_time_sec_value);
    if (lv_obj_is_valid(guider_ui.calculator_app_time))
    {
        lv_dclock_set_text_fmt(guider_ui.calculator_app_time, "%d:%02d", calculator_app_time_hour_value, calculator_app_time_min_value);
    }
}
static lv_obj_t * calculator_app_date_calendar;

void calculator_app_date_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_FOCUSED) {
        char * s = lv_label_get_text(btn);
        if(calculator_app_date_calendar == NULL) {
            calculator_app_date_init_calendar(btn, s);
        }
    }
}

void calculator_app_date_init_calendar(lv_obj_t *obj, char * s)
{
    if (calculator_app_date_calendar == NULL) {
        lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        calculator_app_date_calendar = lv_calendar_create(lv_layer_top());
        lv_obj_t * scr = lv_obj_get_screen(obj);
        lv_coord_t scr_height = lv_obj_get_height(scr);
        lv_coord_t scr_width = lv_obj_get_width(scr);
        lv_obj_set_size(calculator_app_date_calendar, scr_width * 0.8, scr_height * 0.8);
        char * year = strtok(s, "/");
        char * month = strtok(NULL, "/");
        char * day = strtok(NULL, "/");
        lv_calendar_set_showed_date(calculator_app_date_calendar, atoi(year), atoi(month));
        lv_calendar_date_t highlighted_days[1];       /*Only its pointer will be saved so should be static*/
        highlighted_days[0].year = atoi(year);
        highlighted_days[0].month = atoi(month);
        highlighted_days[0].day = atoi(day);
        lv_calendar_set_highlighted_dates(calculator_app_date_calendar, highlighted_days, 1);
        lv_obj_align(calculator_app_date_calendar,LV_ALIGN_CENTER, 0, 0);

        lv_obj_add_event_cb(calculator_app_date_calendar, calculator_app_date_calendar_event_handler, LV_EVENT_ALL,NULL);
        lv_calendar_header_arrow_create(calculator_app_date_calendar);
        lv_obj_update_layout(scr);
    }
}

void calculator_app_date_calendar_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        lv_calendar_date_t date;
        lv_calendar_get_pressed_date(obj,&date);
        char buf[16];
        lv_snprintf(buf,sizeof(buf),"%d/%02d/%02d", date.year, date.month,date.day);
        lv_label_set_text(guider_ui.calculator_app_date, buf);
        lv_obj_clear_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_bg_opa(lv_layer_top(), LV_OPA_TRANSP, 0);
        lv_obj_del(calculator_app_date_calendar);
        calculator_app_date_calendar = NULL;
    }
}


extern int deepseek_app_time_hour_value;
extern int deepseek_app_time_min_value;
extern int deepseek_app_time_sec_value;

void deepseek_app_time_timer(lv_timer_t *timer)
{
    clock_count_24(&deepseek_app_time_hour_value, &deepseek_app_time_min_value, &deepseek_app_time_sec_value);
    if (lv_obj_is_valid(guider_ui.deepseek_app_time))
    {
        lv_dclock_set_text_fmt(guider_ui.deepseek_app_time, "%d:%02d", deepseek_app_time_hour_value, deepseek_app_time_min_value);
    }
}
static lv_obj_t * deepseek_app_date_calendar;

void deepseek_app_date_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_FOCUSED) {
        char * s = lv_label_get_text(btn);
        if(deepseek_app_date_calendar == NULL) {
            deepseek_app_date_init_calendar(btn, s);
        }
    }
}

void deepseek_app_date_init_calendar(lv_obj_t *obj, char * s)
{
    if (deepseek_app_date_calendar == NULL) {
        lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        deepseek_app_date_calendar = lv_calendar_create(lv_layer_top());
        lv_obj_t * scr = lv_obj_get_screen(obj);
        lv_coord_t scr_height = lv_obj_get_height(scr);
        lv_coord_t scr_width = lv_obj_get_width(scr);
        lv_obj_set_size(deepseek_app_date_calendar, scr_width * 0.8, scr_height * 0.8);
        char * year = strtok(s, "/");
        char * month = strtok(NULL, "/");
        char * day = strtok(NULL, "/");
        lv_calendar_set_showed_date(deepseek_app_date_calendar, atoi(year), atoi(month));
        lv_calendar_date_t highlighted_days[1];       /*Only its pointer will be saved so should be static*/
        highlighted_days[0].year = atoi(year);
        highlighted_days[0].month = atoi(month);
        highlighted_days[0].day = atoi(day);
        lv_calendar_set_highlighted_dates(deepseek_app_date_calendar, highlighted_days, 1);
        lv_obj_align(deepseek_app_date_calendar,LV_ALIGN_CENTER, 0, 0);

        lv_obj_add_event_cb(deepseek_app_date_calendar, deepseek_app_date_calendar_event_handler, LV_EVENT_ALL,NULL);
        lv_calendar_header_arrow_create(deepseek_app_date_calendar);
        lv_obj_update_layout(scr);
    }
}

void deepseek_app_date_calendar_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        lv_calendar_date_t date;
        lv_calendar_get_pressed_date(obj,&date);
        char buf[16];
        lv_snprintf(buf,sizeof(buf),"%d/%02d/%02d", date.year, date.month,date.day);
        lv_label_set_text(guider_ui.deepseek_app_date, buf);
        lv_obj_clear_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_bg_opa(lv_layer_top(), LV_OPA_TRANSP, 0);
        lv_obj_del(deepseek_app_date_calendar);
        deepseek_app_date_calendar = NULL;
    }
}


extern int setting_app_time_hour_value;
extern int setting_app_time_min_value;
extern int setting_app_time_sec_value;

void setting_app_time_timer(lv_timer_t *timer)
{
    clock_count_24(&setting_app_time_hour_value, &setting_app_time_min_value, &setting_app_time_sec_value);
    if (lv_obj_is_valid(guider_ui.setting_app_time))
    {
        lv_dclock_set_text_fmt(guider_ui.setting_app_time, "%d:%02d", setting_app_time_hour_value, setting_app_time_min_value);
    }
}
static lv_obj_t * setting_app_date_calendar;

void setting_app_date_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_FOCUSED) {
        char * s = lv_label_get_text(btn);
        if(setting_app_date_calendar == NULL) {
            setting_app_date_init_calendar(btn, s);
        }
    }
}

void setting_app_date_init_calendar(lv_obj_t *obj, char * s)
{
    if (setting_app_date_calendar == NULL) {
        lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        setting_app_date_calendar = lv_calendar_create(lv_layer_top());
        lv_obj_t * scr = lv_obj_get_screen(obj);
        lv_coord_t scr_height = lv_obj_get_height(scr);
        lv_coord_t scr_width = lv_obj_get_width(scr);
        lv_obj_set_size(setting_app_date_calendar, scr_width * 0.8, scr_height * 0.8);
        char * year = strtok(s, "/");
        char * month = strtok(NULL, "/");
        char * day = strtok(NULL, "/");
        lv_calendar_set_showed_date(setting_app_date_calendar, atoi(year), atoi(month));
        lv_calendar_date_t highlighted_days[1];       /*Only its pointer will be saved so should be static*/
        highlighted_days[0].year = atoi(year);
        highlighted_days[0].month = atoi(month);
        highlighted_days[0].day = atoi(day);
        lv_calendar_set_highlighted_dates(setting_app_date_calendar, highlighted_days, 1);
        lv_obj_align(setting_app_date_calendar,LV_ALIGN_CENTER, 0, 0);

        lv_obj_add_event_cb(setting_app_date_calendar, setting_app_date_calendar_event_handler, LV_EVENT_ALL,NULL);
        lv_calendar_header_arrow_create(setting_app_date_calendar);
        lv_obj_update_layout(scr);
    }
}

void setting_app_date_calendar_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        lv_calendar_date_t date;
        lv_calendar_get_pressed_date(obj,&date);
        char buf[16];
        lv_snprintf(buf,sizeof(buf),"%d/%02d/%02d", date.year, date.month,date.day);
        lv_label_set_text(guider_ui.setting_app_date, buf);
        lv_obj_clear_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_bg_opa(lv_layer_top(), LV_OPA_TRANSP, 0);
        lv_obj_del(setting_app_date_calendar);
        setting_app_date_calendar = NULL;
    }
}


