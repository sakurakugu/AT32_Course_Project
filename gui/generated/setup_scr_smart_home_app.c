/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



int smart_home_app_time_min_value = 25;
int smart_home_app_time_hour_value = 11;
int smart_home_app_time_sec_value = 50;
void setup_scr_smart_home_app(lv_ui *ui)
{
    //Write codes smart_home_app
    ui->smart_home_app = lv_obj_create(NULL);
    lv_obj_set_size(ui->smart_home_app, 480, 320);
    lv_obj_set_scrollbar_mode(ui->smart_home_app, LV_SCROLLBAR_MODE_OFF);

    //Write style for smart_home_app, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->smart_home_app, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_status_bar
    ui->smart_home_app_status_bar = lv_obj_create(ui->smart_home_app);
    lv_obj_set_pos(ui->smart_home_app_status_bar, 0, 0);
    lv_obj_set_size(ui->smart_home_app_status_bar, 480, 16);
    lv_obj_set_scrollbar_mode(ui->smart_home_app_status_bar, LV_SCROLLBAR_MODE_OFF);

    //Write style for smart_home_app_status_bar, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_status_bar, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->smart_home_app_status_bar, lv_color_hex(0x333333), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->smart_home_app_status_bar, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_wifi
    ui->smart_home_app_wifi = lv_img_create(ui->smart_home_app_status_bar);
    lv_obj_add_flag(ui->smart_home_app_wifi, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->smart_home_app_wifi, &_wifi_alpha_16x16);
    lv_img_set_pivot(ui->smart_home_app_wifi, 50,50);
    lv_img_set_angle(ui->smart_home_app_wifi, 0);
    lv_obj_set_pos(ui->smart_home_app_wifi, 456, 0);
    lv_obj_set_size(ui->smart_home_app_wifi, 16, 16);

    //Write style for smart_home_app_wifi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->smart_home_app_wifi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->smart_home_app_wifi, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_voice_on
    ui->smart_home_app_voice_on = lv_img_create(ui->smart_home_app_status_bar);
    lv_obj_add_flag(ui->smart_home_app_voice_on, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->smart_home_app_voice_on, &_voice_on_alpha_16x16);
    lv_img_set_pivot(ui->smart_home_app_voice_on, 50,50);
    lv_img_set_angle(ui->smart_home_app_voice_on, 0);
    lv_obj_set_pos(ui->smart_home_app_voice_on, 434, 0);
    lv_obj_set_size(ui->smart_home_app_voice_on, 16, 16);
    lv_obj_add_flag(ui->smart_home_app_voice_on, LV_OBJ_FLAG_HIDDEN);

    //Write style for smart_home_app_voice_on, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_voice_on, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->smart_home_app_voice_on, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_voice_on, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->smart_home_app_voice_on, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_voice_off
    ui->smart_home_app_voice_off = lv_img_create(ui->smart_home_app_status_bar);
    lv_obj_add_flag(ui->smart_home_app_voice_off, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->smart_home_app_voice_off, &_voice_off_alpha_16x16);
    lv_img_set_pivot(ui->smart_home_app_voice_off, 50,50);
    lv_img_set_angle(ui->smart_home_app_voice_off, 0);
    lv_obj_set_pos(ui->smart_home_app_voice_off, 434, 0);
    lv_obj_set_size(ui->smart_home_app_voice_off, 16, 16);

    //Write style for smart_home_app_voice_off, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_voice_off, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->smart_home_app_voice_off, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_voice_off, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->smart_home_app_voice_off, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_time
    static bool smart_home_app_time_timer_enabled = false;
    ui->smart_home_app_time = lv_dclock_create(ui->smart_home_app_status_bar, "11:25");
    if (!smart_home_app_time_timer_enabled) {
        lv_timer_create(smart_home_app_time_timer, 1000, NULL);
        smart_home_app_time_timer_enabled = true;
    }
    lv_obj_set_pos(ui->smart_home_app_time, 220, 0);
    lv_obj_set_size(ui->smart_home_app_time, 46, 16);

    //Write style for smart_home_app_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->smart_home_app_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_time, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_time, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_date
    ui->smart_home_app_date = lv_label_create(ui->smart_home_app_status_bar);
    lv_label_set_text(ui->smart_home_app_date, "2023/07/31");
    lv_obj_set_style_text_align(ui->smart_home_app_date, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_add_flag(ui->smart_home_app_date, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ui->smart_home_app_date, smart_home_app_date_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_set_pos(ui->smart_home_app_date, 0, 1);
    lv_obj_set_size(ui->smart_home_app_date, 112, 16);

    //Write style for smart_home_app_date, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->smart_home_app_date, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_date, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_date, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_date, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_date, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->smart_home_app_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_cont_1
    ui->smart_home_app_cont_1 = lv_obj_create(ui->smart_home_app);
    lv_obj_set_pos(ui->smart_home_app_cont_1, 0, 16);
    lv_obj_set_size(ui->smart_home_app_cont_1, 480, 304);
    lv_obj_set_scrollbar_mode(ui->smart_home_app_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for smart_home_app_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->smart_home_app_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->smart_home_app_cont_1, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->smart_home_app_cont_1, lv_color_hex(0x4486c3), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->smart_home_app_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->smart_home_app_cont_1, 148, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_imgbtn_6
    ui->smart_home_app_imgbtn_6 = lv_imgbtn_create(ui->smart_home_app_cont_1);
    lv_obj_add_flag(ui->smart_home_app_imgbtn_6, LV_OBJ_FLAG_CHECKABLE);
    ui->smart_home_app_imgbtn_6_label = lv_label_create(ui->smart_home_app_imgbtn_6);
    lv_label_set_text(ui->smart_home_app_imgbtn_6_label, "");
    lv_label_set_long_mode(ui->smart_home_app_imgbtn_6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->smart_home_app_imgbtn_6_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->smart_home_app_imgbtn_6, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->smart_home_app_imgbtn_6, 330, 150);
    lv_obj_set_size(ui->smart_home_app_imgbtn_6, 80, 80);

    //Write style for smart_home_app_imgbtn_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->smart_home_app_imgbtn_6, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_imgbtn_6, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_imgbtn_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_imgbtn_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_imgbtn_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->smart_home_app_imgbtn_6, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_imgbtn_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for smart_home_app_imgbtn_6, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_imgbtn_6, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->smart_home_app_imgbtn_6, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->smart_home_app_imgbtn_6, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->smart_home_app_imgbtn_6, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->smart_home_app_imgbtn_6, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->smart_home_app_imgbtn_6, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for smart_home_app_imgbtn_6, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_imgbtn_6, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->smart_home_app_imgbtn_6, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->smart_home_app_imgbtn_6, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->smart_home_app_imgbtn_6, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->smart_home_app_imgbtn_6, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->smart_home_app_imgbtn_6, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for smart_home_app_imgbtn_6, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_imgbtn_6, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->smart_home_app_imgbtn_6, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes smart_home_app_imgbtn_5
    ui->smart_home_app_imgbtn_5 = lv_imgbtn_create(ui->smart_home_app_cont_1);
    lv_obj_add_flag(ui->smart_home_app_imgbtn_5, LV_OBJ_FLAG_CHECKABLE);
    ui->smart_home_app_imgbtn_5_label = lv_label_create(ui->smart_home_app_imgbtn_5);
    lv_label_set_text(ui->smart_home_app_imgbtn_5_label, "");
    lv_label_set_long_mode(ui->smart_home_app_imgbtn_5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->smart_home_app_imgbtn_5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->smart_home_app_imgbtn_5, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->smart_home_app_imgbtn_5, 200, 150);
    lv_obj_set_size(ui->smart_home_app_imgbtn_5, 80, 80);

    //Write style for smart_home_app_imgbtn_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->smart_home_app_imgbtn_5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_imgbtn_5, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_imgbtn_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_imgbtn_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_imgbtn_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->smart_home_app_imgbtn_5, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_imgbtn_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for smart_home_app_imgbtn_5, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_imgbtn_5, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->smart_home_app_imgbtn_5, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->smart_home_app_imgbtn_5, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->smart_home_app_imgbtn_5, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->smart_home_app_imgbtn_5, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->smart_home_app_imgbtn_5, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for smart_home_app_imgbtn_5, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_imgbtn_5, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->smart_home_app_imgbtn_5, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->smart_home_app_imgbtn_5, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->smart_home_app_imgbtn_5, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->smart_home_app_imgbtn_5, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->smart_home_app_imgbtn_5, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for smart_home_app_imgbtn_5, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_imgbtn_5, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->smart_home_app_imgbtn_5, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes smart_home_app_imgbtn_4
    ui->smart_home_app_imgbtn_4 = lv_imgbtn_create(ui->smart_home_app_cont_1);
    lv_obj_add_flag(ui->smart_home_app_imgbtn_4, LV_OBJ_FLAG_CHECKABLE);
    ui->smart_home_app_imgbtn_4_label = lv_label_create(ui->smart_home_app_imgbtn_4);
    lv_label_set_text(ui->smart_home_app_imgbtn_4_label, "");
    lv_label_set_long_mode(ui->smart_home_app_imgbtn_4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->smart_home_app_imgbtn_4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->smart_home_app_imgbtn_4, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->smart_home_app_imgbtn_4, 70, 150);
    lv_obj_set_size(ui->smart_home_app_imgbtn_4, 80, 80);

    //Write style for smart_home_app_imgbtn_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->smart_home_app_imgbtn_4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_imgbtn_4, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_imgbtn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_imgbtn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_imgbtn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->smart_home_app_imgbtn_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_imgbtn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for smart_home_app_imgbtn_4, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_imgbtn_4, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->smart_home_app_imgbtn_4, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->smart_home_app_imgbtn_4, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->smart_home_app_imgbtn_4, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->smart_home_app_imgbtn_4, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->smart_home_app_imgbtn_4, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for smart_home_app_imgbtn_4, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_imgbtn_4, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->smart_home_app_imgbtn_4, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->smart_home_app_imgbtn_4, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->smart_home_app_imgbtn_4, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->smart_home_app_imgbtn_4, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->smart_home_app_imgbtn_4, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for smart_home_app_imgbtn_4, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_imgbtn_4, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->smart_home_app_imgbtn_4, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes smart_home_app_imgbtn_3
    ui->smart_home_app_imgbtn_3 = lv_imgbtn_create(ui->smart_home_app_cont_1);
    lv_obj_add_flag(ui->smart_home_app_imgbtn_3, LV_OBJ_FLAG_CHECKABLE);
    ui->smart_home_app_imgbtn_3_label = lv_label_create(ui->smart_home_app_imgbtn_3);
    lv_label_set_text(ui->smart_home_app_imgbtn_3_label, "");
    lv_label_set_long_mode(ui->smart_home_app_imgbtn_3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->smart_home_app_imgbtn_3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->smart_home_app_imgbtn_3, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->smart_home_app_imgbtn_3, 330, 50);
    lv_obj_set_size(ui->smart_home_app_imgbtn_3, 80, 80);

    //Write style for smart_home_app_imgbtn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->smart_home_app_imgbtn_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_imgbtn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_imgbtn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_imgbtn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->smart_home_app_imgbtn_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_imgbtn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for smart_home_app_imgbtn_3, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_imgbtn_3, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->smart_home_app_imgbtn_3, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->smart_home_app_imgbtn_3, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->smart_home_app_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->smart_home_app_imgbtn_3, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->smart_home_app_imgbtn_3, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for smart_home_app_imgbtn_3, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_imgbtn_3, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->smart_home_app_imgbtn_3, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->smart_home_app_imgbtn_3, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->smart_home_app_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->smart_home_app_imgbtn_3, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->smart_home_app_imgbtn_3, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for smart_home_app_imgbtn_3, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_imgbtn_3, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->smart_home_app_imgbtn_3, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes smart_home_app_imgbtn_2
    ui->smart_home_app_imgbtn_2 = lv_imgbtn_create(ui->smart_home_app_cont_1);
    lv_obj_add_flag(ui->smart_home_app_imgbtn_2, LV_OBJ_FLAG_CHECKABLE);
    ui->smart_home_app_imgbtn_2_label = lv_label_create(ui->smart_home_app_imgbtn_2);
    lv_label_set_text(ui->smart_home_app_imgbtn_2_label, "");
    lv_label_set_long_mode(ui->smart_home_app_imgbtn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->smart_home_app_imgbtn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->smart_home_app_imgbtn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->smart_home_app_imgbtn_2, 200, 50);
    lv_obj_set_size(ui->smart_home_app_imgbtn_2, 80, 80);

    //Write style for smart_home_app_imgbtn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->smart_home_app_imgbtn_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_imgbtn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->smart_home_app_imgbtn_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for smart_home_app_imgbtn_2, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->smart_home_app_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->smart_home_app_imgbtn_2, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->smart_home_app_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->smart_home_app_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->smart_home_app_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for smart_home_app_imgbtn_2, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->smart_home_app_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->smart_home_app_imgbtn_2, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->smart_home_app_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->smart_home_app_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->smart_home_app_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for smart_home_app_imgbtn_2, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_imgbtn_2, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->smart_home_app_imgbtn_2, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes smart_home_app_imgbtn_1
    ui->smart_home_app_imgbtn_1 = lv_imgbtn_create(ui->smart_home_app_cont_1);
    lv_obj_add_flag(ui->smart_home_app_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    ui->smart_home_app_imgbtn_1_label = lv_label_create(ui->smart_home_app_imgbtn_1);
    lv_label_set_text(ui->smart_home_app_imgbtn_1_label, "");
    lv_label_set_long_mode(ui->smart_home_app_imgbtn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->smart_home_app_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->smart_home_app_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->smart_home_app_imgbtn_1, 70, 50);
    lv_obj_set_size(ui->smart_home_app_imgbtn_1, 80, 80);

    //Write style for smart_home_app_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->smart_home_app_imgbtn_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->smart_home_app_imgbtn_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for smart_home_app_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->smart_home_app_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->smart_home_app_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->smart_home_app_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->smart_home_app_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->smart_home_app_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for smart_home_app_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->smart_home_app_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->smart_home_app_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->smart_home_app_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->smart_home_app_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->smart_home_app_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for smart_home_app_imgbtn_1, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_imgbtn_1, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->smart_home_app_imgbtn_1, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //The custom code of smart_home_app.


    //Update current screen layout.
    lv_obj_update_layout(ui->smart_home_app);

    //Init events for screen.
    events_init_smart_home_app(ui);
}
