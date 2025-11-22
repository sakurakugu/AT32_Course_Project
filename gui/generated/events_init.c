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

#ifdef KEIL_COMPILE
#include "../../src/app/weather/weather.h"
#endif
#include "custom.h"
#include "custom.h"

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
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void home_app1_setting_app_icon_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_to(&guider_ui, &guider_ui.setting_app, guider_ui.setting_app_del, setup_scr_setting_app, LV_SCR_LOAD_ANIM_OVER_TOP, 200, 200);
        break;
    }
    default:
        break;
    }
}

static void home_app1_clock_app_icon_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_to(&guider_ui, &guider_ui.clock_app, guider_ui.clock_app_del, setup_scr_clock_app, LV_SCR_LOAD_ANIM_OVER_TOP, 200, 200);
        break;
    }
    default:
        break;
    }
}

static void home_app1_calculator_app_icon_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_to(&guider_ui, &guider_ui.calculator_app, guider_ui.calculator_app_del, setup_scr_calculator_app, LV_SCR_LOAD_ANIM_OVER_TOP, 200, 200);
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
        nav_to(&guider_ui, &guider_ui.smart_home_app, guider_ui.smart_home_app_del, setup_scr_smart_home_app, LV_SCR_LOAD_ANIM_OVER_TOP, 200, 200);
        break;
    }
    default:
        break;
    }
}

static void home_app1_music_app_icon_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_to(&guider_ui, &guider_ui.music_app, guider_ui.music_app_del, setup_scr_music_app, LV_SCR_LOAD_ANIM_OVER_TOP, 200, 200);
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
        nav_to(&guider_ui, &guider_ui.weather_app, guider_ui.weather_app_del, setup_scr_weather_app, LV_SCR_LOAD_ANIM_OVER_TOP, 200, 200);
        break;
    }
    default:
        break;
    }
}

void events_init_home_app1 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->home_app1, home_app1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->home_app1_setting_app_icon, home_app1_setting_app_icon_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->home_app1_clock_app_icon, home_app1_clock_app_icon_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->home_app1_calculator_app_icon, home_app1_calculator_app_icon_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->home_app1_smart_home_app_icon, home_app1_smart_home_app_icon_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->home_app1_music_app_icon, home_app1_music_app_icon_event_handler, LV_EVENT_ALL, ui);
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

static void home_app2_link_game_icon_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_to(&guider_ui, &guider_ui.link_game_app, guider_ui.link_game_app_del, setup_scr_link_game_app, LV_SCR_LOAD_ANIM_OVER_TOP, 200, 200);
        break;
    }
    default:
        break;
    }
}

static void home_app2_minecraft_icon_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_to(&guider_ui, &guider_ui.minecraft_app, guider_ui.minecraft_app_del, setup_scr_minecraft_app, LV_SCR_LOAD_ANIM_OVER_TOP, 200, 200);
        break;
    }
    default:
        break;
    }
}

static void home_app2_drawing_board_icon_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_to(&guider_ui, &guider_ui.drawing_board_app, guider_ui.drawing_board_app_del, setup_scr_drawing_board_app, LV_SCR_LOAD_ANIM_OVER_TOP, 200, 200);
        break;
    }
    default:
        break;
    }
}

static void home_app2_electronic_organ_icon_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_to(&guider_ui, &guider_ui.electronic_organ_app, guider_ui.electronic_organ_app_del, setup_scr_electronic_organ_app, LV_SCR_LOAD_ANIM_OVER_TOP, 200, 200);
        break;
    }
    default:
        break;
    }
}

void events_init_home_app2 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->home_app2, home_app2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->home_app2_link_game_icon, home_app2_link_game_icon_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->home_app2_minecraft_icon, home_app2_minecraft_icon_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->home_app2_drawing_board_icon, home_app2_drawing_board_icon_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->home_app2_electronic_organ_icon, home_app2_electronic_organ_icon_event_handler, LV_EVENT_ALL, ui);
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
            nav_back(&guider_ui);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            nav_back(&guider_ui);
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
#ifdef KEIL_COMPILE
        // 点击更新天气：后台发起一次网络请求并刷新界面
        bool ok = Weather_UpdateUI();
        if (!ok) {
            // 简单错误反馈：在更新时间标签显示失败
            if (lv_obj_is_valid(guider_ui.weather_app_updatetime)) {
                lv_label_set_text(guider_ui.weather_app_updatetime, "上次更新时间：获取失败");
            }
        }
#endif
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

static void music_app_event_handler (lv_event_t *e)
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
            nav_back(&guider_ui);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            nav_back(&guider_ui);
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

void events_init_music_app (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->music_app, music_app_event_handler, LV_EVENT_ALL, ui);
}

static void smart_home_app_IoT_8key_event_handler (lv_event_t *e)
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

static void smart_home_app_IoT_MPU6050_event_handler (lv_event_t *e)
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

static void smart_home_app_IoT_ADC_event_handler (lv_event_t *e)
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

static void smart_home_app_IoT_lm75_event_handler (lv_event_t *e)
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

static void smart_home_app_IoT_led_green_event_handler (lv_event_t *e)
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

static void smart_home_app_IoT_color_led_event_handler (lv_event_t *e)
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

static void smart_home_app_btn_return1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        smart_home_iot_return_event_handler(e);
        break;
    }
    default:
        break;
    }
}

static void smart_home_app_btn_return2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        smart_home_iot_return_event_handler(e);
        break;
    }
    default:
        break;
    }
}

static void smart_home_app_btn_return3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        smart_home_iot_return_event_handler(e);
        break;
    }
    default:
        break;
    }
}

static void smart_home_app_btn_reutrn4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        smart_home_iot_return_event_handler(e);
        break;
    }
    default:
        break;
    }
}

static void smart_home_app_btn_return5_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        smart_home_iot_return_event_handler(e);
        break;
    }
    default:
        break;
    }
}

static void smart_home_app_btn_return6_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        smart_home_iot_return_event_handler(e);
        break;
    }
    default:
        break;
    }
}

static void smart_home_app_back_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_back(&guider_ui);
        break;
    }
    default:
        break;
    }
}

void events_init_smart_home_app (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->smart_home_app_IoT_8key, smart_home_app_IoT_8key_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->smart_home_app_IoT_MPU6050, smart_home_app_IoT_MPU6050_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->smart_home_app_IoT_ADC, smart_home_app_IoT_ADC_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->smart_home_app_IoT_lm75, smart_home_app_IoT_lm75_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->smart_home_app_IoT_led_green, smart_home_app_IoT_led_green_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->smart_home_app_IoT_color_led, smart_home_app_IoT_color_led_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->smart_home_app_btn_return1, smart_home_app_btn_return1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->smart_home_app_btn_return2, smart_home_app_btn_return2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->smart_home_app_btn_return3, smart_home_app_btn_return3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->smart_home_app_btn_reutrn4, smart_home_app_btn_reutrn4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->smart_home_app_btn_return5, smart_home_app_btn_return5_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->smart_home_app_btn_return6, smart_home_app_btn_return6_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->smart_home_app_back_btn, smart_home_app_back_btn_event_handler, LV_EVENT_ALL, ui);
}

static void clock_app_event_handler (lv_event_t *e)
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
            nav_back(&guider_ui);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            nav_back(&guider_ui);
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

static void clock_app_calendar_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        lv_calendar_date_t date;
        lv_obj_t * obj = lv_event_get_current_target(e);
        lv_calendar_get_pressed_date(obj,&date);
        char buf[16];
        lv_snprintf(buf,sizeof(buf),"%d/%02d/%02d", date.year, date.month,date.day);
        if (lv_obj_is_valid(g_status_bar_date)) {
            lv_label_set_text(g_status_bar_date, buf);
        }
        break;
        break;
    }
    default:
        break;
    }
}

void events_init_clock_app (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->clock_app, clock_app_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->clock_app_calendar, clock_app_calendar_event_handler, LV_EVENT_ALL, ui);
}

static void calculator_app_event_handler (lv_event_t *e)
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
            nav_back(&guider_ui);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            nav_back(&guider_ui);
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

void events_init_calculator_app (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->calculator_app, calculator_app_event_handler, LV_EVENT_ALL, ui);
}

static void setting_app_event_handler (lv_event_t *e)
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
            nav_back(&guider_ui);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            nav_back(&guider_ui);
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

void events_init_setting_app (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->setting_app, setting_app_event_handler, LV_EVENT_ALL, ui);
}

static void electronic_organ_app_event_handler (lv_event_t *e)
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
            nav_back(&guider_ui);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            nav_back(&guider_ui);
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

void events_init_electronic_organ_app (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->electronic_organ_app, electronic_organ_app_event_handler, LV_EVENT_ALL, ui);
}

static void drawing_board_app_btn_clear_event_handler (lv_event_t *e)
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

static void drawing_board_app_btn_nav_back_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_back(&guider_ui);
        break;
    }
    default:
        break;
    }
}

void events_init_drawing_board_app (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->drawing_board_app_btn_clear, drawing_board_app_btn_clear_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->drawing_board_app_btn_nav_back, drawing_board_app_btn_nav_back_event_handler, LV_EVENT_ALL, ui);
}

static void minecraft_app_back_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
#ifdef KEIL_COMPILE
        cleanup_scr_minecraft(&guider_ui);
#endif
        nav_back(&guider_ui);
        break;
    }
    default:
        break;
    }
}

void events_init_minecraft_app (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->minecraft_app_back_btn, minecraft_app_back_btn_event_handler, LV_EVENT_ALL, ui);
}

static void link_game_app_back_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_back(&guider_ui);
        break;
    }
    default:
        break;
    }
}

static void link_game_app_reopen_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        LinkGame_ResetEventCb(e);
        break;
    }
    default:
        break;
    }
}

void events_init_link_game_app (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->link_game_app_back_btn, link_game_app_back_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->link_game_app_reopen_btn, link_game_app_reopen_btn_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
