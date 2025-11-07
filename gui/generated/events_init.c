/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif


static void home_app1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.home_app2, guider_ui.home_app2_del, &guider_ui.home_app1_del, setup_scr_home_app2, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 200, false, true);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.home_app2, guider_ui.home_app2_del, &guider_ui.home_app1_del, setup_scr_home_app2, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 200, false, true);
            break;
        }
        case LV_DIR_BOTTOM:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.status_app, guider_ui.status_app_del, &guider_ui.home_app1_del, setup_scr_status_app, LV_SCR_LOAD_ANIM_OVER_BOTTOM, 200, 200, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void home_app1_smart_home_app_icon_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {

        break;
    }
    default:
        break;
    }
}

static void home_app1_weather_app_icon_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.weather_app, guider_ui.weather_app_del, &guider_ui.home_app1_del, setup_scr_weather_app, LV_SCR_LOAD_ANIM_OVER_TOP, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_home_app1 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->home_app1, home_app1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->home_app1_smart_home_app_icon, home_app1_smart_home_app_icon_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->home_app1_weather_app_icon, home_app1_weather_app_icon_event_handler, LV_EVENT_ALL, ui);
}

static void home_app2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.home_app1, guider_ui.home_app1_del, &guider_ui.home_app2_del, setup_scr_home_app1, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 200, false, true);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.home_app1, guider_ui.home_app1_del, &guider_ui.home_app2_del, setup_scr_home_app1, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 200, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

void events_init_home_app2 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->home_app2, home_app2_event_handler, LV_EVENT_ALL, ui);
}

static void status_app_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_TOP:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.home_app1, guider_ui.home_app1_del, &guider_ui.status_app_del, setup_scr_home_app1, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 200, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

void events_init_status_app (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->status_app, status_app_event_handler, LV_EVENT_ALL, ui);
}

static void weather_app_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.home_app1, guider_ui.home_app1_del, &guider_ui.weather_app_del, setup_scr_home_app1, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 200, false, true);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.home_app1, guider_ui.home_app1_del, &guider_ui.weather_app_del, setup_scr_home_app1, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 200, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void weather_app_update_weather_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {

        break;
    }
    default:
        break;
    }
}

void events_init_weather_app (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->weather_app, weather_app_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->weather_app_update_weather_btn, weather_app_update_weather_btn_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
