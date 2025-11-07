/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef WIDGET_INIT_H
#define WIDGET_INIT_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "gui_guider.h"

__attribute__((unused)) void kb_event_cb(lv_event_t *e);
__attribute__((unused)) void ta_event_cb(lv_event_t *e);
#if LV_USE_ANALOGCLOCK != 0
void clock_count(int *hour, int *min, int *sec);
#endif


void home_app1_time_timer(lv_timer_t *timer);
void home_app1_date_event_handler(lv_event_t *e);
void home_app1_date_calendar_event_handler(lv_event_t *e);
void home_app1_date_init_calendar(lv_obj_t *obj, char * s);
void home_app2_time_timer(lv_timer_t *timer);
void home_app2_date_event_handler(lv_event_t *e);
void home_app2_date_calendar_event_handler(lv_event_t *e);
void home_app2_date_init_calendar(lv_obj_t *obj, char * s);
void weather_app_time_timer(lv_timer_t *timer);
void weather_app_date_event_handler(lv_event_t *e);
void weather_app_date_calendar_event_handler(lv_event_t *e);
void weather_app_date_init_calendar(lv_obj_t *obj, char * s);
void music_app_time_timer(lv_timer_t *timer);
void music_app_date_event_handler(lv_event_t *e);
void music_app_date_calendar_event_handler(lv_event_t *e);
void music_app_date_init_calendar(lv_obj_t *obj, char * s);
void smart_home_app_time_timer(lv_timer_t *timer);
void smart_home_app_date_event_handler(lv_event_t *e);
void smart_home_app_date_calendar_event_handler(lv_event_t *e);
void smart_home_app_date_init_calendar(lv_obj_t *obj, char * s);
void calculator_app_time_timer(lv_timer_t *timer);
void calculator_app_date_event_handler(lv_event_t *e);
void calculator_app_date_calendar_event_handler(lv_event_t *e);
void calculator_app_date_init_calendar(lv_obj_t *obj, char * s);
void deepseek_app_time_timer(lv_timer_t *timer);
void deepseek_app_date_event_handler(lv_event_t *e);
void deepseek_app_date_calendar_event_handler(lv_event_t *e);
void deepseek_app_date_init_calendar(lv_obj_t *obj, char * s);
void setting_app_time_timer(lv_timer_t *timer);
void setting_app_date_event_handler(lv_event_t *e);
void setting_app_date_calendar_event_handler(lv_event_t *e);
void setting_app_date_init_calendar(lv_obj_t *obj, char * s);

#ifdef __cplusplus
}
#endif
#endif
