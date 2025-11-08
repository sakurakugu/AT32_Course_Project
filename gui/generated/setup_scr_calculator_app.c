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



int calculator_app_time_min_value = 25;
int calculator_app_time_hour_value = 11;
int calculator_app_time_sec_value = 50;
void setup_scr_calculator_app(lv_ui *ui)
{
    //Write codes calculator_app
    ui->calculator_app = lv_obj_create(NULL);
    lv_obj_set_size(ui->calculator_app, 480, 320);
    lv_obj_set_scrollbar_mode(ui->calculator_app, LV_SCROLLBAR_MODE_OFF);

    //Write style for calculator_app, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->calculator_app, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculator_app_status_bar
    ui->calculator_app_status_bar = lv_obj_create(ui->calculator_app);
    lv_obj_set_pos(ui->calculator_app_status_bar, 0, 0);
    lv_obj_set_size(ui->calculator_app_status_bar, 480, 16);
    lv_obj_set_scrollbar_mode(ui->calculator_app_status_bar, LV_SCROLLBAR_MODE_OFF);

    //Write style for calculator_app_status_bar, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->calculator_app_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculator_app_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->calculator_app_status_bar, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calculator_app_status_bar, lv_color_hex(0x333333), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calculator_app_status_bar, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->calculator_app_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->calculator_app_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->calculator_app_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->calculator_app_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculator_app_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculator_app_wifi
    ui->calculator_app_wifi = lv_img_create(ui->calculator_app_status_bar);
    lv_obj_add_flag(ui->calculator_app_wifi, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->calculator_app_wifi, &_wifi_alpha_16x16);
    lv_img_set_pivot(ui->calculator_app_wifi, 50,50);
    lv_img_set_angle(ui->calculator_app_wifi, 0);
    lv_obj_set_pos(ui->calculator_app_wifi, 456, 0);
    lv_obj_set_size(ui->calculator_app_wifi, 16, 16);

    //Write style for calculator_app_wifi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->calculator_app_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->calculator_app_wifi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculator_app_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->calculator_app_wifi, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculator_app_voice_on
    ui->calculator_app_voice_on = lv_img_create(ui->calculator_app_status_bar);
    lv_obj_add_flag(ui->calculator_app_voice_on, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->calculator_app_voice_on, &_voice_on_alpha_16x16);
    lv_img_set_pivot(ui->calculator_app_voice_on, 50,50);
    lv_img_set_angle(ui->calculator_app_voice_on, 0);
    lv_obj_set_pos(ui->calculator_app_voice_on, 434, 0);
    lv_obj_set_size(ui->calculator_app_voice_on, 16, 16);
    lv_obj_add_flag(ui->calculator_app_voice_on, LV_OBJ_FLAG_HIDDEN);

    //Write style for calculator_app_voice_on, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->calculator_app_voice_on, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->calculator_app_voice_on, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculator_app_voice_on, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->calculator_app_voice_on, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculator_app_voice_off
    ui->calculator_app_voice_off = lv_img_create(ui->calculator_app_status_bar);
    lv_obj_add_flag(ui->calculator_app_voice_off, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->calculator_app_voice_off, &_voice_off_alpha_16x16);
    lv_img_set_pivot(ui->calculator_app_voice_off, 50,50);
    lv_img_set_angle(ui->calculator_app_voice_off, 0);
    lv_obj_set_pos(ui->calculator_app_voice_off, 434, 0);
    lv_obj_set_size(ui->calculator_app_voice_off, 16, 16);

    //Write style for calculator_app_voice_off, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->calculator_app_voice_off, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->calculator_app_voice_off, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculator_app_voice_off, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->calculator_app_voice_off, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculator_app_time
    static bool calculator_app_time_timer_enabled = false;
    ui->calculator_app_time = lv_dclock_create(ui->calculator_app_status_bar, "11:25");
    if (!calculator_app_time_timer_enabled) {
        lv_timer_create(calculator_app_time_timer, 1000, NULL);
        calculator_app_time_timer_enabled = true;
    }
    lv_obj_set_pos(ui->calculator_app_time, 220, 0);
    lv_obj_set_size(ui->calculator_app_time, 46, 16);

    //Write style for calculator_app_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->calculator_app_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->calculator_app_time, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calculator_app_time, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calculator_app_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->calculator_app_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->calculator_app_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->calculator_app_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->calculator_app_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->calculator_app_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->calculator_app_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->calculator_app_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculator_app_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculator_app_date
    ui->calculator_app_date = lv_label_create(ui->calculator_app_status_bar);
    lv_label_set_text(ui->calculator_app_date, "2023/07/31");
    lv_obj_set_style_text_align(ui->calculator_app_date, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_add_flag(ui->calculator_app_date, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ui->calculator_app_date, calculator_app_date_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_set_pos(ui->calculator_app_date, 0, 1);
    lv_obj_set_size(ui->calculator_app_date, 112, 16);

    //Write style for calculator_app_date, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->calculator_app_date, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calculator_app_date, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calculator_app_date, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->calculator_app_date, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->calculator_app_date, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->calculator_app_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->calculator_app_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculator_app_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->calculator_app_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->calculator_app_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->calculator_app_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculator_app_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculator_app_caalculator_page
    ui->calculator_app_caalculator_page = lv_obj_create(ui->calculator_app);
    lv_obj_set_pos(ui->calculator_app_caalculator_page, 0, 16);
    lv_obj_set_size(ui->calculator_app_caalculator_page, 480, 304);
    lv_obj_set_scrollbar_mode(ui->calculator_app_caalculator_page, LV_SCROLLBAR_MODE_OFF);

    //Write style for calculator_app_caalculator_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->calculator_app_caalculator_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculator_app_caalculator_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->calculator_app_caalculator_page, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calculator_app_caalculator_page, lv_color_hex(0xcccccc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calculator_app_caalculator_page, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->calculator_app_caalculator_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->calculator_app_caalculator_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->calculator_app_caalculator_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->calculator_app_caalculator_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculator_app_caalculator_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculator_app_btn_equal
    ui->calculator_app_btn_equal = lv_btn_create(ui->calculator_app_caalculator_page);
    ui->calculator_app_btn_equal_label = lv_label_create(ui->calculator_app_btn_equal);
    lv_label_set_text(ui->calculator_app_btn_equal_label, "=");
    lv_label_set_long_mode(ui->calculator_app_btn_equal_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->calculator_app_btn_equal_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->calculator_app_btn_equal, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->calculator_app_btn_equal_label, LV_PCT(100));
    lv_obj_set_pos(ui->calculator_app_btn_equal, 400, 250);
    lv_obj_set_size(ui->calculator_app_btn_equal, 60, 40);

    //Write style for calculator_app_btn_equal, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->calculator_app_btn_equal, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calculator_app_btn_equal, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calculator_app_btn_equal, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->calculator_app_btn_equal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculator_app_btn_equal, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculator_app_btn_equal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->calculator_app_btn_equal, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calculator_app_btn_equal, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calculator_app_btn_equal, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->calculator_app_btn_equal, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculator_app_btn_add
    ui->calculator_app_btn_add = lv_btn_create(ui->calculator_app_caalculator_page);
    ui->calculator_app_btn_add_label = lv_label_create(ui->calculator_app_btn_add);
    lv_label_set_text(ui->calculator_app_btn_add_label, "+");
    lv_label_set_long_mode(ui->calculator_app_btn_add_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->calculator_app_btn_add_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->calculator_app_btn_add, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->calculator_app_btn_add_label, LV_PCT(100));
    lv_obj_set_pos(ui->calculator_app_btn_add, 400, 196);
    lv_obj_set_size(ui->calculator_app_btn_add, 60, 40);

    //Write style for calculator_app_btn_add, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->calculator_app_btn_add, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calculator_app_btn_add, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calculator_app_btn_add, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->calculator_app_btn_add, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculator_app_btn_add, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculator_app_btn_add, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->calculator_app_btn_add, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calculator_app_btn_add, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calculator_app_btn_add, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->calculator_app_btn_add, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculator_app_btn_subtract
    ui->calculator_app_btn_subtract = lv_btn_create(ui->calculator_app_caalculator_page);
    ui->calculator_app_btn_subtract_label = lv_label_create(ui->calculator_app_btn_subtract);
    lv_label_set_text(ui->calculator_app_btn_subtract_label, "-");
    lv_label_set_long_mode(ui->calculator_app_btn_subtract_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->calculator_app_btn_subtract_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->calculator_app_btn_subtract, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->calculator_app_btn_subtract_label, LV_PCT(100));
    lv_obj_set_pos(ui->calculator_app_btn_subtract, 400, 141);
    lv_obj_set_size(ui->calculator_app_btn_subtract, 60, 40);

    //Write style for calculator_app_btn_subtract, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->calculator_app_btn_subtract, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calculator_app_btn_subtract, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calculator_app_btn_subtract, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->calculator_app_btn_subtract, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculator_app_btn_subtract, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculator_app_btn_subtract, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->calculator_app_btn_subtract, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calculator_app_btn_subtract, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calculator_app_btn_subtract, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->calculator_app_btn_subtract, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculator_app_btn_backspace
    ui->calculator_app_btn_backspace = lv_btn_create(ui->calculator_app_caalculator_page);
    ui->calculator_app_btn_backspace_label = lv_label_create(ui->calculator_app_btn_backspace);
    lv_label_set_text(ui->calculator_app_btn_backspace_label, "⬅");
    lv_label_set_long_mode(ui->calculator_app_btn_backspace_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->calculator_app_btn_backspace_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->calculator_app_btn_backspace, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->calculator_app_btn_backspace_label, LV_PCT(100));
    lv_obj_set_pos(ui->calculator_app_btn_backspace, 400, 84);
    lv_obj_set_size(ui->calculator_app_btn_backspace, 60, 40);

    //Write style for calculator_app_btn_backspace, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->calculator_app_btn_backspace, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calculator_app_btn_backspace, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calculator_app_btn_backspace, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->calculator_app_btn_backspace, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculator_app_btn_backspace, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculator_app_btn_backspace, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->calculator_app_btn_backspace, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calculator_app_btn_backspace, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calculator_app_btn_backspace, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->calculator_app_btn_backspace, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculator_app_btn_num_3
    ui->calculator_app_btn_num_3 = lv_btn_create(ui->calculator_app_caalculator_page);
    ui->calculator_app_btn_num_3_label = lv_label_create(ui->calculator_app_btn_num_3);
    lv_label_set_text(ui->calculator_app_btn_num_3_label, "3");
    lv_label_set_long_mode(ui->calculator_app_btn_num_3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->calculator_app_btn_num_3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->calculator_app_btn_num_3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->calculator_app_btn_num_3_label, LV_PCT(100));
    lv_obj_set_pos(ui->calculator_app_btn_num_3, 310, 250);
    lv_obj_set_size(ui->calculator_app_btn_num_3, 60, 40);

    //Write style for calculator_app_btn_num_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->calculator_app_btn_num_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calculator_app_btn_num_3, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calculator_app_btn_num_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->calculator_app_btn_num_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculator_app_btn_num_3, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculator_app_btn_num_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->calculator_app_btn_num_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calculator_app_btn_num_3, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calculator_app_btn_num_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->calculator_app_btn_num_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculator_app_btn_num_6
    ui->calculator_app_btn_num_6 = lv_btn_create(ui->calculator_app_caalculator_page);
    ui->calculator_app_btn_num_6_label = lv_label_create(ui->calculator_app_btn_num_6);
    lv_label_set_text(ui->calculator_app_btn_num_6_label, "6");
    lv_label_set_long_mode(ui->calculator_app_btn_num_6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->calculator_app_btn_num_6_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->calculator_app_btn_num_6, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->calculator_app_btn_num_6_label, LV_PCT(100));
    lv_obj_set_pos(ui->calculator_app_btn_num_6, 310, 196);
    lv_obj_set_size(ui->calculator_app_btn_num_6, 60, 40);

    //Write style for calculator_app_btn_num_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->calculator_app_btn_num_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calculator_app_btn_num_6, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calculator_app_btn_num_6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->calculator_app_btn_num_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculator_app_btn_num_6, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculator_app_btn_num_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->calculator_app_btn_num_6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calculator_app_btn_num_6, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calculator_app_btn_num_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->calculator_app_btn_num_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculator_app_btn_num_9
    ui->calculator_app_btn_num_9 = lv_btn_create(ui->calculator_app_caalculator_page);
    ui->calculator_app_btn_num_9_label = lv_label_create(ui->calculator_app_btn_num_9);
    lv_label_set_text(ui->calculator_app_btn_num_9_label, "9");
    lv_label_set_long_mode(ui->calculator_app_btn_num_9_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->calculator_app_btn_num_9_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->calculator_app_btn_num_9, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->calculator_app_btn_num_9_label, LV_PCT(100));
    lv_obj_set_pos(ui->calculator_app_btn_num_9, 310, 141);
    lv_obj_set_size(ui->calculator_app_btn_num_9, 60, 40);

    //Write style for calculator_app_btn_num_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->calculator_app_btn_num_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calculator_app_btn_num_9, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calculator_app_btn_num_9, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->calculator_app_btn_num_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculator_app_btn_num_9, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculator_app_btn_num_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->calculator_app_btn_num_9, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calculator_app_btn_num_9, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calculator_app_btn_num_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->calculator_app_btn_num_9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculator_app_btn_multiply
    ui->calculator_app_btn_multiply = lv_btn_create(ui->calculator_app_caalculator_page);
    ui->calculator_app_btn_multiply_label = lv_label_create(ui->calculator_app_btn_multiply);
    lv_label_set_text(ui->calculator_app_btn_multiply_label, "x");
    lv_label_set_long_mode(ui->calculator_app_btn_multiply_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->calculator_app_btn_multiply_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->calculator_app_btn_multiply, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->calculator_app_btn_multiply_label, LV_PCT(100));
    lv_obj_set_pos(ui->calculator_app_btn_multiply, 310, 86);
    lv_obj_set_size(ui->calculator_app_btn_multiply, 60, 40);

    //Write style for calculator_app_btn_multiply, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->calculator_app_btn_multiply, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calculator_app_btn_multiply, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calculator_app_btn_multiply, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->calculator_app_btn_multiply, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculator_app_btn_multiply, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculator_app_btn_multiply, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->calculator_app_btn_multiply, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calculator_app_btn_multiply, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calculator_app_btn_multiply, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->calculator_app_btn_multiply, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculator_app_btn_num_2
    ui->calculator_app_btn_num_2 = lv_btn_create(ui->calculator_app_caalculator_page);
    ui->calculator_app_btn_num_2_label = lv_label_create(ui->calculator_app_btn_num_2);
    lv_label_set_text(ui->calculator_app_btn_num_2_label, "2");
    lv_label_set_long_mode(ui->calculator_app_btn_num_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->calculator_app_btn_num_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->calculator_app_btn_num_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->calculator_app_btn_num_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->calculator_app_btn_num_2, 215, 250);
    lv_obj_set_size(ui->calculator_app_btn_num_2, 60, 40);

    //Write style for calculator_app_btn_num_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->calculator_app_btn_num_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calculator_app_btn_num_2, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calculator_app_btn_num_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->calculator_app_btn_num_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculator_app_btn_num_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculator_app_btn_num_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->calculator_app_btn_num_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calculator_app_btn_num_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calculator_app_btn_num_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->calculator_app_btn_num_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculator_app_btn_num_5
    ui->calculator_app_btn_num_5 = lv_btn_create(ui->calculator_app_caalculator_page);
    ui->calculator_app_btn_num_5_label = lv_label_create(ui->calculator_app_btn_num_5);
    lv_label_set_text(ui->calculator_app_btn_num_5_label, "5");
    lv_label_set_long_mode(ui->calculator_app_btn_num_5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->calculator_app_btn_num_5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->calculator_app_btn_num_5, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->calculator_app_btn_num_5_label, LV_PCT(100));
    lv_obj_set_pos(ui->calculator_app_btn_num_5, 215, 196);
    lv_obj_set_size(ui->calculator_app_btn_num_5, 60, 40);

    //Write style for calculator_app_btn_num_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->calculator_app_btn_num_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calculator_app_btn_num_5, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calculator_app_btn_num_5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->calculator_app_btn_num_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculator_app_btn_num_5, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculator_app_btn_num_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->calculator_app_btn_num_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calculator_app_btn_num_5, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calculator_app_btn_num_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->calculator_app_btn_num_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculator_app_btn_num_8
    ui->calculator_app_btn_num_8 = lv_btn_create(ui->calculator_app_caalculator_page);
    ui->calculator_app_btn_num_8_label = lv_label_create(ui->calculator_app_btn_num_8);
    lv_label_set_text(ui->calculator_app_btn_num_8_label, "8");
    lv_label_set_long_mode(ui->calculator_app_btn_num_8_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->calculator_app_btn_num_8_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->calculator_app_btn_num_8, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->calculator_app_btn_num_8_label, LV_PCT(100));
    lv_obj_set_pos(ui->calculator_app_btn_num_8, 215, 141);
    lv_obj_set_size(ui->calculator_app_btn_num_8, 60, 40);

    //Write style for calculator_app_btn_num_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->calculator_app_btn_num_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calculator_app_btn_num_8, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calculator_app_btn_num_8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->calculator_app_btn_num_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculator_app_btn_num_8, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculator_app_btn_num_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->calculator_app_btn_num_8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calculator_app_btn_num_8, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calculator_app_btn_num_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->calculator_app_btn_num_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculator_app_btn_divide
    ui->calculator_app_btn_divide = lv_btn_create(ui->calculator_app_caalculator_page);
    ui->calculator_app_btn_divide_label = lv_label_create(ui->calculator_app_btn_divide);
    lv_label_set_text(ui->calculator_app_btn_divide_label, "÷");
    lv_label_set_long_mode(ui->calculator_app_btn_divide_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->calculator_app_btn_divide_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->calculator_app_btn_divide, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->calculator_app_btn_divide_label, LV_PCT(100));
    lv_obj_set_pos(ui->calculator_app_btn_divide, 215, 86);
    lv_obj_set_size(ui->calculator_app_btn_divide, 60, 40);

    //Write style for calculator_app_btn_divide, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->calculator_app_btn_divide, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calculator_app_btn_divide, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calculator_app_btn_divide, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->calculator_app_btn_divide, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculator_app_btn_divide, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculator_app_btn_divide, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->calculator_app_btn_divide, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calculator_app_btn_divide, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calculator_app_btn_divide, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->calculator_app_btn_divide, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculator_app_btn_num_1
    ui->calculator_app_btn_num_1 = lv_btn_create(ui->calculator_app_caalculator_page);
    ui->calculator_app_btn_num_1_label = lv_label_create(ui->calculator_app_btn_num_1);
    lv_label_set_text(ui->calculator_app_btn_num_1_label, "1");
    lv_label_set_long_mode(ui->calculator_app_btn_num_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->calculator_app_btn_num_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->calculator_app_btn_num_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->calculator_app_btn_num_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->calculator_app_btn_num_1, 121, 250);
    lv_obj_set_size(ui->calculator_app_btn_num_1, 60, 40);

    //Write style for calculator_app_btn_num_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->calculator_app_btn_num_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calculator_app_btn_num_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calculator_app_btn_num_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->calculator_app_btn_num_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculator_app_btn_num_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculator_app_btn_num_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->calculator_app_btn_num_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calculator_app_btn_num_1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calculator_app_btn_num_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->calculator_app_btn_num_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculator_app_btn_num_4
    ui->calculator_app_btn_num_4 = lv_btn_create(ui->calculator_app_caalculator_page);
    ui->calculator_app_btn_num_4_label = lv_label_create(ui->calculator_app_btn_num_4);
    lv_label_set_text(ui->calculator_app_btn_num_4_label, "4");
    lv_label_set_long_mode(ui->calculator_app_btn_num_4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->calculator_app_btn_num_4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->calculator_app_btn_num_4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->calculator_app_btn_num_4_label, LV_PCT(100));
    lv_obj_set_pos(ui->calculator_app_btn_num_4, 121, 196);
    lv_obj_set_size(ui->calculator_app_btn_num_4, 60, 40);

    //Write style for calculator_app_btn_num_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->calculator_app_btn_num_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calculator_app_btn_num_4, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calculator_app_btn_num_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->calculator_app_btn_num_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculator_app_btn_num_4, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculator_app_btn_num_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->calculator_app_btn_num_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calculator_app_btn_num_4, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calculator_app_btn_num_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->calculator_app_btn_num_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculator_app_btn_num_7
    ui->calculator_app_btn_num_7 = lv_btn_create(ui->calculator_app_caalculator_page);
    ui->calculator_app_btn_num_7_label = lv_label_create(ui->calculator_app_btn_num_7);
    lv_label_set_text(ui->calculator_app_btn_num_7_label, "7");
    lv_label_set_long_mode(ui->calculator_app_btn_num_7_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->calculator_app_btn_num_7_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->calculator_app_btn_num_7, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->calculator_app_btn_num_7_label, LV_PCT(100));
    lv_obj_set_pos(ui->calculator_app_btn_num_7, 121, 141);
    lv_obj_set_size(ui->calculator_app_btn_num_7, 60, 40);

    //Write style for calculator_app_btn_num_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->calculator_app_btn_num_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calculator_app_btn_num_7, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calculator_app_btn_num_7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->calculator_app_btn_num_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculator_app_btn_num_7, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculator_app_btn_num_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->calculator_app_btn_num_7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calculator_app_btn_num_7, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calculator_app_btn_num_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->calculator_app_btn_num_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculator_app_btn_clear
    ui->calculator_app_btn_clear = lv_btn_create(ui->calculator_app_caalculator_page);
    ui->calculator_app_btn_clear_label = lv_label_create(ui->calculator_app_btn_clear);
    lv_label_set_text(ui->calculator_app_btn_clear_label, "C");
    lv_label_set_long_mode(ui->calculator_app_btn_clear_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->calculator_app_btn_clear_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->calculator_app_btn_clear, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->calculator_app_btn_clear_label, LV_PCT(100));
    lv_obj_set_pos(ui->calculator_app_btn_clear, 121, 86);
    lv_obj_set_size(ui->calculator_app_btn_clear, 60, 40);

    //Write style for calculator_app_btn_clear, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->calculator_app_btn_clear, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calculator_app_btn_clear, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calculator_app_btn_clear, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->calculator_app_btn_clear, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculator_app_btn_clear, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculator_app_btn_clear, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->calculator_app_btn_clear, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calculator_app_btn_clear, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calculator_app_btn_clear, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->calculator_app_btn_clear, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculator_app_btn_num_0
    ui->calculator_app_btn_num_0 = lv_btn_create(ui->calculator_app_caalculator_page);
    ui->calculator_app_btn_num_0_label = lv_label_create(ui->calculator_app_btn_num_0);
    lv_label_set_text(ui->calculator_app_btn_num_0_label, "0");
    lv_label_set_long_mode(ui->calculator_app_btn_num_0_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->calculator_app_btn_num_0_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->calculator_app_btn_num_0, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->calculator_app_btn_num_0_label, LV_PCT(100));
    lv_obj_set_pos(ui->calculator_app_btn_num_0, 24, 250);
    lv_obj_set_size(ui->calculator_app_btn_num_0, 60, 40);

    //Write style for calculator_app_btn_num_0, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->calculator_app_btn_num_0, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calculator_app_btn_num_0, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calculator_app_btn_num_0, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->calculator_app_btn_num_0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculator_app_btn_num_0, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculator_app_btn_num_0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->calculator_app_btn_num_0, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calculator_app_btn_num_0, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calculator_app_btn_num_0, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->calculator_app_btn_num_0, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculator_app_btn_modulus
    ui->calculator_app_btn_modulus = lv_btn_create(ui->calculator_app_caalculator_page);
    ui->calculator_app_btn_modulus_label = lv_label_create(ui->calculator_app_btn_modulus);
    lv_label_set_text(ui->calculator_app_btn_modulus_label, "%");
    lv_label_set_long_mode(ui->calculator_app_btn_modulus_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->calculator_app_btn_modulus_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->calculator_app_btn_modulus, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->calculator_app_btn_modulus_label, LV_PCT(100));
    lv_obj_set_pos(ui->calculator_app_btn_modulus, 24, 196);
    lv_obj_set_size(ui->calculator_app_btn_modulus, 60, 40);

    //Write style for calculator_app_btn_modulus, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->calculator_app_btn_modulus, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calculator_app_btn_modulus, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calculator_app_btn_modulus, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->calculator_app_btn_modulus, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculator_app_btn_modulus, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculator_app_btn_modulus, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->calculator_app_btn_modulus, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calculator_app_btn_modulus, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calculator_app_btn_modulus, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->calculator_app_btn_modulus, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculator_app_btn_right_parenthesis
    ui->calculator_app_btn_right_parenthesis = lv_btn_create(ui->calculator_app_caalculator_page);
    ui->calculator_app_btn_right_parenthesis_label = lv_label_create(ui->calculator_app_btn_right_parenthesis);
    lv_label_set_text(ui->calculator_app_btn_right_parenthesis_label, ")");
    lv_label_set_long_mode(ui->calculator_app_btn_right_parenthesis_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->calculator_app_btn_right_parenthesis_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->calculator_app_btn_right_parenthesis, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->calculator_app_btn_right_parenthesis_label, LV_PCT(100));
    lv_obj_set_pos(ui->calculator_app_btn_right_parenthesis, 24, 141);
    lv_obj_set_size(ui->calculator_app_btn_right_parenthesis, 60, 40);

    //Write style for calculator_app_btn_right_parenthesis, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->calculator_app_btn_right_parenthesis, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calculator_app_btn_right_parenthesis, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calculator_app_btn_right_parenthesis, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->calculator_app_btn_right_parenthesis, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculator_app_btn_right_parenthesis, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculator_app_btn_right_parenthesis, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->calculator_app_btn_right_parenthesis, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calculator_app_btn_right_parenthesis, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calculator_app_btn_right_parenthesis, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->calculator_app_btn_right_parenthesis, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculator_app_btn_left_parenthesis
    ui->calculator_app_btn_left_parenthesis = lv_btn_create(ui->calculator_app_caalculator_page);
    ui->calculator_app_btn_left_parenthesis_label = lv_label_create(ui->calculator_app_btn_left_parenthesis);
    lv_label_set_text(ui->calculator_app_btn_left_parenthesis_label, "(");
    lv_label_set_long_mode(ui->calculator_app_btn_left_parenthesis_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->calculator_app_btn_left_parenthesis_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->calculator_app_btn_left_parenthesis, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->calculator_app_btn_left_parenthesis_label, LV_PCT(100));
    lv_obj_set_pos(ui->calculator_app_btn_left_parenthesis, 24, 86);
    lv_obj_set_size(ui->calculator_app_btn_left_parenthesis, 60, 40);

    //Write style for calculator_app_btn_left_parenthesis, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->calculator_app_btn_left_parenthesis, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calculator_app_btn_left_parenthesis, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calculator_app_btn_left_parenthesis, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->calculator_app_btn_left_parenthesis, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculator_app_btn_left_parenthesis, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculator_app_btn_left_parenthesis, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->calculator_app_btn_left_parenthesis, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calculator_app_btn_left_parenthesis, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calculator_app_btn_left_parenthesis, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->calculator_app_btn_left_parenthesis, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculator_app_label_1
    ui->calculator_app_label_1 = lv_label_create(ui->calculator_app);
    lv_label_set_text(ui->calculator_app_label_1, "语法错误除零错误");
    lv_label_set_long_mode(ui->calculator_app_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->calculator_app_label_1, 21, 40);
    lv_obj_set_size(ui->calculator_app_label_1, 442, 35);

    //Write style for calculator_app_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->calculator_app_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculator_app_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->calculator_app_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calculator_app_label_1, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calculator_app_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->calculator_app_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->calculator_app_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->calculator_app_label_1, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->calculator_app_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calculator_app_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calculator_app_label_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->calculator_app_label_1, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->calculator_app_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->calculator_app_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->calculator_app_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculator_app_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of calculator_app.
    calculator_init(ui->calculator_app_label_1);

    // 为所有按键绑定事件与按键值
    static const char *K_0 = "0";
    static const char *K_1 = "1";
    static const char *K_2 = "2";
    static const char *K_3 = "3";
    static const char *K_4 = "4";
    static const char *K_5 = "5";
    static const char *K_6 = "6";
    static const char *K_7 = "7";
    static const char *K_8 = "8";
    static const char *K_9 = "9";
    static const char *K_ADD = "+";
    static const char *K_SUB = "-";
    static const char *K_MUL = "*";   // 映射 'x' 为 '*'
    static const char *K_DIV = "/";   // 映射 '÷' 为 '/'
    static const char *K_MOD = "%";
    static const char *K_LP  = "(";
    static const char *K_RP  = ")";
    static const char *K_EQ  = "=";
    static const char *K_CLR = "C";
    static const char *K_BS  = "⬅";

    lv_obj_add_event_cb(ui->calculator_app_btn_num_0, calc_key_event_handler, LV_EVENT_ALL, (void *)K_0);
    lv_obj_add_event_cb(ui->calculator_app_btn_num_1, calc_key_event_handler, LV_EVENT_ALL, (void *)K_1);
    lv_obj_add_event_cb(ui->calculator_app_btn_num_2, calc_key_event_handler, LV_EVENT_ALL, (void *)K_2);
    lv_obj_add_event_cb(ui->calculator_app_btn_num_3, calc_key_event_handler, LV_EVENT_ALL, (void *)K_3);
    lv_obj_add_event_cb(ui->calculator_app_btn_num_4, calc_key_event_handler, LV_EVENT_ALL, (void *)K_4);
    lv_obj_add_event_cb(ui->calculator_app_btn_num_5, calc_key_event_handler, LV_EVENT_ALL, (void *)K_5);
    lv_obj_add_event_cb(ui->calculator_app_btn_num_6, calc_key_event_handler, LV_EVENT_ALL, (void *)K_6);
    lv_obj_add_event_cb(ui->calculator_app_btn_num_7, calc_key_event_handler, LV_EVENT_ALL, (void *)K_7);
    lv_obj_add_event_cb(ui->calculator_app_btn_num_8, calc_key_event_handler, LV_EVENT_ALL, (void *)K_8);
    lv_obj_add_event_cb(ui->calculator_app_btn_num_9, calc_key_event_handler, LV_EVENT_ALL, (void *)K_9);

    lv_obj_add_event_cb(ui->calculator_app_btn_add,       calc_key_event_handler, LV_EVENT_ALL, (void *)K_ADD);
    lv_obj_add_event_cb(ui->calculator_app_btn_subtract,  calc_key_event_handler, LV_EVENT_ALL, (void *)K_SUB);
    lv_obj_add_event_cb(ui->calculator_app_btn_multiply,  calc_key_event_handler, LV_EVENT_ALL, (void *)K_MUL);
    lv_obj_add_event_cb(ui->calculator_app_btn_divide,    calc_key_event_handler, LV_EVENT_ALL, (void *)K_DIV);
    lv_obj_add_event_cb(ui->calculator_app_btn_modulus,   calc_key_event_handler, LV_EVENT_ALL, (void *)K_MOD);
    lv_obj_add_event_cb(ui->calculator_app_btn_left_parenthesis,  calc_key_event_handler, LV_EVENT_ALL, (void *)K_LP);
    lv_obj_add_event_cb(ui->calculator_app_btn_right_parenthesis, calc_key_event_handler, LV_EVENT_ALL, (void *)K_RP);
    lv_obj_add_event_cb(ui->calculator_app_btn_equal,     calc_key_event_handler, LV_EVENT_ALL, (void *)K_EQ);
    lv_obj_add_event_cb(ui->calculator_app_btn_clear,     calc_key_event_handler, LV_EVENT_ALL, (void *)K_CLR);
    lv_obj_add_event_cb(ui->calculator_app_btn_backspace, calc_key_event_handler, LV_EVENT_ALL, (void *)K_BS);

    //Update current screen layout.
    lv_obj_update_layout(ui->calculator_app);

    //Init events for screen.
    events_init_calculator_app(ui);
}
