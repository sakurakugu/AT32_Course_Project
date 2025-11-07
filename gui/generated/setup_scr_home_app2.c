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



int home_app2_time_min_value = 25;
int home_app2_time_hour_value = 11;
int home_app2_time_sec_value = 50;
void setup_scr_home_app2(lv_ui *ui)
{
    //Write codes home_app2
    ui->home_app2 = lv_obj_create(NULL);
    lv_obj_set_size(ui->home_app2, 480, 320);
    lv_obj_set_scrollbar_mode(ui->home_app2, LV_SCROLLBAR_MODE_OFF);

    //Write style for home_app2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->home_app2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_app2_status_bar
    ui->home_app2_status_bar = lv_obj_create(ui->home_app2);
    lv_obj_set_pos(ui->home_app2_status_bar, 0, 0);
    lv_obj_set_size(ui->home_app2_status_bar, 480, 16);
    lv_obj_set_scrollbar_mode(ui->home_app2_status_bar, LV_SCROLLBAR_MODE_OFF);

    //Write style for home_app2_status_bar, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->home_app2_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_app2_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_app2_status_bar, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_app2_status_bar, lv_color_hex(0x333333), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->home_app2_status_bar, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_app2_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_app2_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_app2_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_app2_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_app2_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_app2_wifi
    ui->home_app2_wifi = lv_img_create(ui->home_app2_status_bar);
    lv_obj_add_flag(ui->home_app2_wifi, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->home_app2_wifi, &_wifi_alpha_16x16);
    lv_img_set_pivot(ui->home_app2_wifi, 50,50);
    lv_img_set_angle(ui->home_app2_wifi, 0);
    lv_obj_set_pos(ui->home_app2_wifi, 456, 0);
    lv_obj_set_size(ui->home_app2_wifi, 16, 16);

    //Write style for home_app2_wifi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->home_app2_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_app2_wifi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_app2_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_app2_wifi, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_app2_voice_on
    ui->home_app2_voice_on = lv_img_create(ui->home_app2_status_bar);
    lv_obj_add_flag(ui->home_app2_voice_on, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->home_app2_voice_on, &_voice_on_alpha_16x16);
    lv_img_set_pivot(ui->home_app2_voice_on, 50,50);
    lv_img_set_angle(ui->home_app2_voice_on, 0);
    lv_obj_set_pos(ui->home_app2_voice_on, 434, 0);
    lv_obj_set_size(ui->home_app2_voice_on, 16, 16);
    lv_obj_add_flag(ui->home_app2_voice_on, LV_OBJ_FLAG_HIDDEN);

    //Write style for home_app2_voice_on, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->home_app2_voice_on, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_app2_voice_on, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_app2_voice_on, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_app2_voice_on, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_app2_voice_off
    ui->home_app2_voice_off = lv_img_create(ui->home_app2_status_bar);
    lv_obj_add_flag(ui->home_app2_voice_off, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->home_app2_voice_off, &_voice_off_alpha_16x16);
    lv_img_set_pivot(ui->home_app2_voice_off, 50,50);
    lv_img_set_angle(ui->home_app2_voice_off, 0);
    lv_obj_set_pos(ui->home_app2_voice_off, 434, 0);
    lv_obj_set_size(ui->home_app2_voice_off, 16, 16);

    //Write style for home_app2_voice_off, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->home_app2_voice_off, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_app2_voice_off, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_app2_voice_off, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_app2_voice_off, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_app2_time
    static bool home_app2_time_timer_enabled = false;
    ui->home_app2_time = lv_dclock_create(ui->home_app2_status_bar, "11:25");
    if (!home_app2_time_timer_enabled) {
        lv_timer_create(home_app2_time_timer, 1000, NULL);
        home_app2_time_timer_enabled = true;
    }
    lv_obj_set_pos(ui->home_app2_time, 220, 0);
    lv_obj_set_size(ui->home_app2_time, 46, 16);

    //Write style for home_app2_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->home_app2_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_app2_time, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_app2_time, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->home_app2_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_app2_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_app2_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_app2_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_app2_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_app2_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_app2_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_app2_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_app2_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_app2_date
    ui->home_app2_date = lv_label_create(ui->home_app2_status_bar);
    lv_label_set_text(ui->home_app2_date, "2023/07/31");
    lv_obj_set_style_text_align(ui->home_app2_date, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_add_flag(ui->home_app2_date, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ui->home_app2_date, home_app2_date_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_set_pos(ui->home_app2_date, 0, 1);
    lv_obj_set_size(ui->home_app2_date, 112, 16);

    //Write style for home_app2_date, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->home_app2_date, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_app2_date, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->home_app2_date, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_app2_date, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_app2_date, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_app2_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->home_app2_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_app2_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_app2_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_app2_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_app2_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_app2_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_app2_home_page
    ui->home_app2_home_page = lv_obj_create(ui->home_app2);
    lv_obj_set_pos(ui->home_app2_home_page, 0, 16);
    lv_obj_set_size(ui->home_app2_home_page, 480, 304);
    lv_obj_set_scrollbar_mode(ui->home_app2_home_page, LV_SCROLLBAR_MODE_OFF);

    //Write style for home_app2_home_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->home_app2_home_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_app2_home_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_app2_home_page, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_app2_home_page, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->home_app2_home_page, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->home_app2_home_page, lv_color_hex(0x8499bf), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->home_app2_home_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->home_app2_home_page, 148, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_app2_home_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_app2_home_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_app2_home_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_app2_home_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_app2_home_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_app2_imgbtn_6
    ui->home_app2_imgbtn_6 = lv_imgbtn_create(ui->home_app2_home_page);
    lv_obj_add_flag(ui->home_app2_imgbtn_6, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->home_app2_imgbtn_6, LV_IMGBTN_STATE_RELEASED, NULL, &_setting_app_alpha_80x80, NULL);
    ui->home_app2_imgbtn_6_label = lv_label_create(ui->home_app2_imgbtn_6);
    lv_label_set_text(ui->home_app2_imgbtn_6_label, "");
    lv_label_set_long_mode(ui->home_app2_imgbtn_6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->home_app2_imgbtn_6_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->home_app2_imgbtn_6, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->home_app2_imgbtn_6, 330, 150);
    lv_obj_set_size(ui->home_app2_imgbtn_6, 80, 80);

    //Write style for home_app2_imgbtn_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->home_app2_imgbtn_6, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_app2_imgbtn_6, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->home_app2_imgbtn_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_app2_imgbtn_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_app2_imgbtn_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_app2_imgbtn_6, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_app2_imgbtn_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for home_app2_imgbtn_6, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->home_app2_imgbtn_6, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->home_app2_imgbtn_6, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->home_app2_imgbtn_6, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->home_app2_imgbtn_6, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->home_app2_imgbtn_6, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->home_app2_imgbtn_6, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for home_app2_imgbtn_6, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->home_app2_imgbtn_6, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->home_app2_imgbtn_6, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->home_app2_imgbtn_6, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->home_app2_imgbtn_6, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->home_app2_imgbtn_6, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->home_app2_imgbtn_6, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for home_app2_imgbtn_6, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->home_app2_imgbtn_6, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->home_app2_imgbtn_6, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes home_app2_imgbtn_5
    ui->home_app2_imgbtn_5 = lv_imgbtn_create(ui->home_app2_home_page);
    lv_obj_add_flag(ui->home_app2_imgbtn_5, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->home_app2_imgbtn_5, LV_IMGBTN_STATE_RELEASED, NULL, &_deepseek_alpha_80x80, NULL);
    ui->home_app2_imgbtn_5_label = lv_label_create(ui->home_app2_imgbtn_5);
    lv_label_set_text(ui->home_app2_imgbtn_5_label, "");
    lv_label_set_long_mode(ui->home_app2_imgbtn_5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->home_app2_imgbtn_5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->home_app2_imgbtn_5, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->home_app2_imgbtn_5, 200, 150);
    lv_obj_set_size(ui->home_app2_imgbtn_5, 80, 80);

    //Write style for home_app2_imgbtn_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->home_app2_imgbtn_5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_app2_imgbtn_5, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->home_app2_imgbtn_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_app2_imgbtn_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_app2_imgbtn_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_app2_imgbtn_5, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_app2_imgbtn_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for home_app2_imgbtn_5, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->home_app2_imgbtn_5, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->home_app2_imgbtn_5, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->home_app2_imgbtn_5, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->home_app2_imgbtn_5, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->home_app2_imgbtn_5, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->home_app2_imgbtn_5, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for home_app2_imgbtn_5, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->home_app2_imgbtn_5, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->home_app2_imgbtn_5, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->home_app2_imgbtn_5, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->home_app2_imgbtn_5, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->home_app2_imgbtn_5, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->home_app2_imgbtn_5, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for home_app2_imgbtn_5, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->home_app2_imgbtn_5, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->home_app2_imgbtn_5, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes home_app2_imgbtn_4
    ui->home_app2_imgbtn_4 = lv_imgbtn_create(ui->home_app2_home_page);
    lv_obj_add_flag(ui->home_app2_imgbtn_4, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->home_app2_imgbtn_4, LV_IMGBTN_STATE_RELEASED, NULL, &_calculator_app_alpha_80x80, NULL);
    ui->home_app2_imgbtn_4_label = lv_label_create(ui->home_app2_imgbtn_4);
    lv_label_set_text(ui->home_app2_imgbtn_4_label, "");
    lv_label_set_long_mode(ui->home_app2_imgbtn_4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->home_app2_imgbtn_4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->home_app2_imgbtn_4, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->home_app2_imgbtn_4, 70, 150);
    lv_obj_set_size(ui->home_app2_imgbtn_4, 80, 80);

    //Write style for home_app2_imgbtn_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->home_app2_imgbtn_4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_app2_imgbtn_4, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->home_app2_imgbtn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_app2_imgbtn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_app2_imgbtn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_app2_imgbtn_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_app2_imgbtn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for home_app2_imgbtn_4, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->home_app2_imgbtn_4, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->home_app2_imgbtn_4, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->home_app2_imgbtn_4, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->home_app2_imgbtn_4, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->home_app2_imgbtn_4, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->home_app2_imgbtn_4, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for home_app2_imgbtn_4, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->home_app2_imgbtn_4, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->home_app2_imgbtn_4, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->home_app2_imgbtn_4, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->home_app2_imgbtn_4, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->home_app2_imgbtn_4, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->home_app2_imgbtn_4, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for home_app2_imgbtn_4, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->home_app2_imgbtn_4, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->home_app2_imgbtn_4, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes home_app2_imgbtn_3
    ui->home_app2_imgbtn_3 = lv_imgbtn_create(ui->home_app2_home_page);
    lv_obj_add_flag(ui->home_app2_imgbtn_3, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->home_app2_imgbtn_3, LV_IMGBTN_STATE_RELEASED, NULL, &_smart_home_app_alpha_80x80, NULL);
    ui->home_app2_imgbtn_3_label = lv_label_create(ui->home_app2_imgbtn_3);
    lv_label_set_text(ui->home_app2_imgbtn_3_label, "");
    lv_label_set_long_mode(ui->home_app2_imgbtn_3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->home_app2_imgbtn_3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->home_app2_imgbtn_3, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->home_app2_imgbtn_3, 329, 49);
    lv_obj_set_size(ui->home_app2_imgbtn_3, 80, 80);

    //Write style for home_app2_imgbtn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->home_app2_imgbtn_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_app2_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->home_app2_imgbtn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_app2_imgbtn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_app2_imgbtn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_app2_imgbtn_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_app2_imgbtn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for home_app2_imgbtn_3, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->home_app2_imgbtn_3, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->home_app2_imgbtn_3, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->home_app2_imgbtn_3, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->home_app2_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->home_app2_imgbtn_3, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->home_app2_imgbtn_3, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for home_app2_imgbtn_3, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->home_app2_imgbtn_3, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->home_app2_imgbtn_3, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->home_app2_imgbtn_3, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->home_app2_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->home_app2_imgbtn_3, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->home_app2_imgbtn_3, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for home_app2_imgbtn_3, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->home_app2_imgbtn_3, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->home_app2_imgbtn_3, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes home_app2_imgbtn_2
    ui->home_app2_imgbtn_2 = lv_imgbtn_create(ui->home_app2_home_page);
    lv_obj_add_flag(ui->home_app2_imgbtn_2, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->home_app2_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, &_music_app_alpha_80x80, NULL);
    ui->home_app2_imgbtn_2_label = lv_label_create(ui->home_app2_imgbtn_2);
    lv_label_set_text(ui->home_app2_imgbtn_2_label, "");
    lv_label_set_long_mode(ui->home_app2_imgbtn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->home_app2_imgbtn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->home_app2_imgbtn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->home_app2_imgbtn_2, 200, 50);
    lv_obj_set_size(ui->home_app2_imgbtn_2, 80, 80);

    //Write style for home_app2_imgbtn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->home_app2_imgbtn_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_app2_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->home_app2_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_app2_imgbtn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_app2_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_app2_imgbtn_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_app2_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for home_app2_imgbtn_2, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->home_app2_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->home_app2_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->home_app2_imgbtn_2, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->home_app2_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->home_app2_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->home_app2_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for home_app2_imgbtn_2, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->home_app2_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->home_app2_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->home_app2_imgbtn_2, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->home_app2_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->home_app2_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->home_app2_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for home_app2_imgbtn_2, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->home_app2_imgbtn_2, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->home_app2_imgbtn_2, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes home_app2_imgbtn_1
    ui->home_app2_imgbtn_1 = lv_imgbtn_create(ui->home_app2_home_page);
    lv_obj_add_flag(ui->home_app2_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->home_app2_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, &_weather_app_alpha_80x80, NULL);
    ui->home_app2_imgbtn_1_label = lv_label_create(ui->home_app2_imgbtn_1);
    lv_label_set_text(ui->home_app2_imgbtn_1_label, "");
    lv_label_set_long_mode(ui->home_app2_imgbtn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->home_app2_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->home_app2_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->home_app2_imgbtn_1, 70, 50);
    lv_obj_set_size(ui->home_app2_imgbtn_1, 80, 80);

    //Write style for home_app2_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->home_app2_imgbtn_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_app2_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->home_app2_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_app2_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_app2_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_app2_imgbtn_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_app2_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for home_app2_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->home_app2_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->home_app2_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->home_app2_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->home_app2_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->home_app2_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->home_app2_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for home_app2_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->home_app2_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->home_app2_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->home_app2_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->home_app2_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->home_app2_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->home_app2_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for home_app2_imgbtn_1, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->home_app2_imgbtn_1, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->home_app2_imgbtn_1, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //The custom code of home_app2.


    //Update current screen layout.
    lv_obj_update_layout(ui->home_app2);

    //Init events for screen.
    events_init_home_app2(ui);
}
