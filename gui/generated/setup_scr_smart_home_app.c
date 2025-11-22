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



void setup_scr_smart_home_app(lv_ui *ui)
{
    //Write codes smart_home_app
    ui->smart_home_app = lv_obj_create(NULL);
    lv_obj_set_size(ui->smart_home_app, 480, 320);
    lv_obj_set_scrollbar_mode(ui->smart_home_app, LV_SCROLLBAR_MODE_OFF);

    //Write style for smart_home_app, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->smart_home_app, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_IoT_page
    ui->smart_home_app_IoT_page = lv_obj_create(ui->smart_home_app);
    lv_obj_set_pos(ui->smart_home_app_IoT_page, 0, 16);
    lv_obj_set_size(ui->smart_home_app_IoT_page, 480, 304);
    lv_obj_set_scrollbar_mode(ui->smart_home_app_IoT_page, LV_SCROLLBAR_MODE_OFF);

    //Write style for smart_home_app_IoT_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_IoT_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_IoT_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_IoT_page, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->smart_home_app_IoT_page, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->smart_home_app_IoT_page, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->smart_home_app_IoT_page, lv_color_hex(0x4486c3), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->smart_home_app_IoT_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->smart_home_app_IoT_page, 148, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_IoT_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_IoT_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_IoT_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_IoT_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_IoT_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_IoT_8key
    ui->smart_home_app_IoT_8key = lv_imgbtn_create(ui->smart_home_app_IoT_page);
    lv_obj_add_flag(ui->smart_home_app_IoT_8key, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->smart_home_app_IoT_8key, LV_IMGBTN_STATE_RELEASED, NULL, &_IoT_key_alpha_80x80, NULL);
    ui->smart_home_app_IoT_8key_label = lv_label_create(ui->smart_home_app_IoT_8key);
    lv_label_set_text(ui->smart_home_app_IoT_8key_label, "");
    lv_label_set_long_mode(ui->smart_home_app_IoT_8key_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->smart_home_app_IoT_8key_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->smart_home_app_IoT_8key, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->smart_home_app_IoT_8key, 200, 150);
    lv_obj_set_size(ui->smart_home_app_IoT_8key, 80, 80);

    //Write style for smart_home_app_IoT_8key, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->smart_home_app_IoT_8key, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_IoT_8key, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_IoT_8key, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_IoT_8key, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_IoT_8key, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->smart_home_app_IoT_8key, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_IoT_8key, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for smart_home_app_IoT_8key, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_IoT_8key, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->smart_home_app_IoT_8key, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->smart_home_app_IoT_8key, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->smart_home_app_IoT_8key, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->smart_home_app_IoT_8key, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->smart_home_app_IoT_8key, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for smart_home_app_IoT_8key, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_IoT_8key, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->smart_home_app_IoT_8key, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->smart_home_app_IoT_8key, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->smart_home_app_IoT_8key, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->smart_home_app_IoT_8key, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->smart_home_app_IoT_8key, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for smart_home_app_IoT_8key, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_IoT_8key, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->smart_home_app_IoT_8key, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes smart_home_app_IoT_MPU6050
    ui->smart_home_app_IoT_MPU6050 = lv_imgbtn_create(ui->smart_home_app_IoT_page);
    lv_obj_add_flag(ui->smart_home_app_IoT_MPU6050, LV_OBJ_FLAG_CHECKABLE);
    ui->smart_home_app_IoT_MPU6050_label = lv_label_create(ui->smart_home_app_IoT_MPU6050);
    lv_label_set_text(ui->smart_home_app_IoT_MPU6050_label, "");
    lv_label_set_long_mode(ui->smart_home_app_IoT_MPU6050_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->smart_home_app_IoT_MPU6050_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->smart_home_app_IoT_MPU6050, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->smart_home_app_IoT_MPU6050, 330, 150);
    lv_obj_set_size(ui->smart_home_app_IoT_MPU6050, 80, 80);
    lv_obj_add_flag(ui->smart_home_app_IoT_MPU6050, LV_OBJ_FLAG_HIDDEN);

    //Write style for smart_home_app_IoT_MPU6050, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->smart_home_app_IoT_MPU6050, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_IoT_MPU6050, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_IoT_MPU6050, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_IoT_MPU6050, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_IoT_MPU6050, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->smart_home_app_IoT_MPU6050, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_IoT_MPU6050, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for smart_home_app_IoT_MPU6050, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_IoT_MPU6050, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->smart_home_app_IoT_MPU6050, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->smart_home_app_IoT_MPU6050, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->smart_home_app_IoT_MPU6050, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->smart_home_app_IoT_MPU6050, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->smart_home_app_IoT_MPU6050, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for smart_home_app_IoT_MPU6050, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_IoT_MPU6050, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->smart_home_app_IoT_MPU6050, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->smart_home_app_IoT_MPU6050, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->smart_home_app_IoT_MPU6050, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->smart_home_app_IoT_MPU6050, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->smart_home_app_IoT_MPU6050, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for smart_home_app_IoT_MPU6050, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_IoT_MPU6050, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->smart_home_app_IoT_MPU6050, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes smart_home_app_IoT_ADC
    ui->smart_home_app_IoT_ADC = lv_imgbtn_create(ui->smart_home_app_IoT_page);
    lv_obj_add_flag(ui->smart_home_app_IoT_ADC, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->smart_home_app_IoT_ADC, LV_IMGBTN_STATE_RELEASED, NULL, &_IoT_ADC_alpha_80x80, NULL);
    ui->smart_home_app_IoT_ADC_label = lv_label_create(ui->smart_home_app_IoT_ADC);
    lv_label_set_text(ui->smart_home_app_IoT_ADC_label, "");
    lv_label_set_long_mode(ui->smart_home_app_IoT_ADC_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->smart_home_app_IoT_ADC_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->smart_home_app_IoT_ADC, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->smart_home_app_IoT_ADC, 69, 150);
    lv_obj_set_size(ui->smart_home_app_IoT_ADC, 80, 80);

    //Write style for smart_home_app_IoT_ADC, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->smart_home_app_IoT_ADC, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_IoT_ADC, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_IoT_ADC, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_IoT_ADC, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_IoT_ADC, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->smart_home_app_IoT_ADC, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_IoT_ADC, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for smart_home_app_IoT_ADC, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_IoT_ADC, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->smart_home_app_IoT_ADC, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->smart_home_app_IoT_ADC, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->smart_home_app_IoT_ADC, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->smart_home_app_IoT_ADC, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->smart_home_app_IoT_ADC, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for smart_home_app_IoT_ADC, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_IoT_ADC, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->smart_home_app_IoT_ADC, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->smart_home_app_IoT_ADC, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->smart_home_app_IoT_ADC, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->smart_home_app_IoT_ADC, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->smart_home_app_IoT_ADC, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for smart_home_app_IoT_ADC, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_IoT_ADC, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->smart_home_app_IoT_ADC, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes smart_home_app_IoT_lm75
    ui->smart_home_app_IoT_lm75 = lv_imgbtn_create(ui->smart_home_app_IoT_page);
    lv_obj_add_flag(ui->smart_home_app_IoT_lm75, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->smart_home_app_IoT_lm75, LV_IMGBTN_STATE_RELEASED, NULL, &_IoT_lm75_alpha_80x80, NULL);
    ui->smart_home_app_IoT_lm75_label = lv_label_create(ui->smart_home_app_IoT_lm75);
    lv_label_set_text(ui->smart_home_app_IoT_lm75_label, "");
    lv_label_set_long_mode(ui->smart_home_app_IoT_lm75_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->smart_home_app_IoT_lm75_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->smart_home_app_IoT_lm75, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->smart_home_app_IoT_lm75, 330, 50);
    lv_obj_set_size(ui->smart_home_app_IoT_lm75, 80, 80);

    //Write style for smart_home_app_IoT_lm75, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->smart_home_app_IoT_lm75, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_IoT_lm75, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_IoT_lm75, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_IoT_lm75, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_IoT_lm75, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->smart_home_app_IoT_lm75, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_IoT_lm75, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for smart_home_app_IoT_lm75, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_IoT_lm75, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->smart_home_app_IoT_lm75, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->smart_home_app_IoT_lm75, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->smart_home_app_IoT_lm75, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->smart_home_app_IoT_lm75, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->smart_home_app_IoT_lm75, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for smart_home_app_IoT_lm75, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_IoT_lm75, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->smart_home_app_IoT_lm75, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->smart_home_app_IoT_lm75, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->smart_home_app_IoT_lm75, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->smart_home_app_IoT_lm75, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->smart_home_app_IoT_lm75, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for smart_home_app_IoT_lm75, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_IoT_lm75, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->smart_home_app_IoT_lm75, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes smart_home_app_IoT_led_green
    ui->smart_home_app_IoT_led_green = lv_imgbtn_create(ui->smart_home_app_IoT_page);
    lv_obj_add_flag(ui->smart_home_app_IoT_led_green, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->smart_home_app_IoT_led_green, LV_IMGBTN_STATE_RELEASED, NULL, &_IoT_green_led_alpha_80x80, NULL);
    ui->smart_home_app_IoT_led_green_label = lv_label_create(ui->smart_home_app_IoT_led_green);
    lv_label_set_text(ui->smart_home_app_IoT_led_green_label, "");
    lv_label_set_long_mode(ui->smart_home_app_IoT_led_green_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->smart_home_app_IoT_led_green_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->smart_home_app_IoT_led_green, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->smart_home_app_IoT_led_green, 200, 49);
    lv_obj_set_size(ui->smart_home_app_IoT_led_green, 80, 80);

    //Write style for smart_home_app_IoT_led_green, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->smart_home_app_IoT_led_green, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_IoT_led_green, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_IoT_led_green, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_IoT_led_green, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_IoT_led_green, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->smart_home_app_IoT_led_green, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_IoT_led_green, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for smart_home_app_IoT_led_green, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_IoT_led_green, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->smart_home_app_IoT_led_green, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->smart_home_app_IoT_led_green, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->smart_home_app_IoT_led_green, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->smart_home_app_IoT_led_green, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->smart_home_app_IoT_led_green, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for smart_home_app_IoT_led_green, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_IoT_led_green, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->smart_home_app_IoT_led_green, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->smart_home_app_IoT_led_green, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->smart_home_app_IoT_led_green, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->smart_home_app_IoT_led_green, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->smart_home_app_IoT_led_green, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for smart_home_app_IoT_led_green, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_IoT_led_green, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->smart_home_app_IoT_led_green, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes smart_home_app_IoT_color_led
    ui->smart_home_app_IoT_color_led = lv_imgbtn_create(ui->smart_home_app_IoT_page);
    lv_obj_add_flag(ui->smart_home_app_IoT_color_led, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->smart_home_app_IoT_color_led, LV_IMGBTN_STATE_RELEASED, NULL, &_IoT_color_led_alpha_80x80, NULL);
    ui->smart_home_app_IoT_color_led_label = lv_label_create(ui->smart_home_app_IoT_color_led);
    lv_label_set_text(ui->smart_home_app_IoT_color_led_label, "");
    lv_label_set_long_mode(ui->smart_home_app_IoT_color_led_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->smart_home_app_IoT_color_led_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->smart_home_app_IoT_color_led, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->smart_home_app_IoT_color_led, 70, 50);
    lv_obj_set_size(ui->smart_home_app_IoT_color_led, 80, 80);

    //Write style for smart_home_app_IoT_color_led, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->smart_home_app_IoT_color_led, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_IoT_color_led, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_IoT_color_led, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_IoT_color_led, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_IoT_color_led, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->smart_home_app_IoT_color_led, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_IoT_color_led, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for smart_home_app_IoT_color_led, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_IoT_color_led, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->smart_home_app_IoT_color_led, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->smart_home_app_IoT_color_led, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->smart_home_app_IoT_color_led, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->smart_home_app_IoT_color_led, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->smart_home_app_IoT_color_led, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for smart_home_app_IoT_color_led, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_IoT_color_led, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->smart_home_app_IoT_color_led, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->smart_home_app_IoT_color_led, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->smart_home_app_IoT_color_led, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->smart_home_app_IoT_color_led, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->smart_home_app_IoT_color_led, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for smart_home_app_IoT_color_led, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->smart_home_app_IoT_color_led, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->smart_home_app_IoT_color_led, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes smart_home_app_color_led_page
    ui->smart_home_app_color_led_page = lv_obj_create(ui->smart_home_app);
    lv_obj_set_pos(ui->smart_home_app_color_led_page, 220, 16);
    lv_obj_set_size(ui->smart_home_app_color_led_page, 260, 304);
    lv_obj_set_scrollbar_mode(ui->smart_home_app_color_led_page, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->smart_home_app_color_led_page, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->smart_home_app_color_led_page, LV_OBJ_FLAG_HIDDEN);

    //Write style for smart_home_app_color_led_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_color_led_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_color_led_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_color_led_page, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->smart_home_app_color_led_page, lv_color_hex(0xededed), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->smart_home_app_color_led_page, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_color_led_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_color_led_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_color_led_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_color_led_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_color_led_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_color_led_cpicker
    ui->smart_home_app_color_led_cpicker = lv_colorwheel_create(ui->smart_home_app_color_led_page, true);
    lv_obj_set_pos(ui->smart_home_app_color_led_cpicker, 75, 57);
    lv_obj_set_size(ui->smart_home_app_color_led_cpicker, 125, 125);

    //Write style for smart_home_app_color_led_cpicker, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(ui->smart_home_app_color_led_cpicker, 24, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_color_led_name
    ui->smart_home_app_color_led_name = lv_label_create(ui->smart_home_app_color_led_page);
    lv_label_set_text(ui->smart_home_app_color_led_name, "彩灯设备");
    lv_label_set_long_mode(ui->smart_home_app_color_led_name, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_color_led_name, 85, 20);
    lv_obj_set_size(ui->smart_home_app_color_led_name, 105, 20);

    //Write style for smart_home_app_color_led_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_color_led_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_color_led_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_color_led_name, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_color_led_name, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_color_led_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_color_led_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_color_led_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_color_led_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_color_led_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_color_led_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_color_led_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_color_led_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_color_led_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_color_led_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_color_led_sw_div
    ui->smart_home_app_color_led_sw_div = lv_obj_create(ui->smart_home_app_color_led_page);
    lv_obj_set_pos(ui->smart_home_app_color_led_sw_div, 30, 255);
    lv_obj_set_size(ui->smart_home_app_color_led_sw_div, 208, 21);
    lv_obj_set_scrollbar_mode(ui->smart_home_app_color_led_sw_div, LV_SCROLLBAR_MODE_OFF);

    //Write style for smart_home_app_color_led_sw_div, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_color_led_sw_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_color_led_sw_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_color_led_sw_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_color_led_sw_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_color_led_sw_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_color_led_sw_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_color_led_sw_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_color_led_sw_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_color_led_sw
    ui->smart_home_app_color_led_sw = lv_switch_create(ui->smart_home_app_color_led_sw_div);
    lv_obj_set_pos(ui->smart_home_app_color_led_sw, 114, 0);
    lv_obj_set_size(ui->smart_home_app_color_led_sw, 40, 20);

    //Write style for smart_home_app_color_led_sw, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->smart_home_app_color_led_sw, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->smart_home_app_color_led_sw, lv_color_hex(0xe6e2e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->smart_home_app_color_led_sw, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->smart_home_app_color_led_sw, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_color_led_sw, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_color_led_sw, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for smart_home_app_color_led_sw, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->smart_home_app_color_led_sw, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->smart_home_app_color_led_sw, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->smart_home_app_color_led_sw, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->smart_home_app_color_led_sw, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    //Write style for smart_home_app_color_led_sw, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->smart_home_app_color_led_sw, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->smart_home_app_color_led_sw, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->smart_home_app_color_led_sw, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->smart_home_app_color_led_sw, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_color_led_sw, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes smart_home_app_color_led_sw_text
    ui->smart_home_app_color_led_sw_text = lv_label_create(ui->smart_home_app_color_led_sw_div);
    lv_label_set_text(ui->smart_home_app_color_led_sw_text, "开关");
    lv_label_set_long_mode(ui->smart_home_app_color_led_sw_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_color_led_sw_text, 11, 0);
    lv_obj_set_size(ui->smart_home_app_color_led_sw_text, 62, 23);

    //Write style for smart_home_app_color_led_sw_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_color_led_sw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_color_led_sw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_color_led_sw_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_color_led_sw_text, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_color_led_sw_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_color_led_sw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_color_led_sw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_color_led_sw_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_color_led_sw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_color_led_sw_text, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_color_led_sw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_color_led_sw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_color_led_sw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_color_led_sw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_color_led_light_div
    ui->smart_home_app_color_led_light_div = lv_obj_create(ui->smart_home_app_color_led_page);
    lv_obj_set_pos(ui->smart_home_app_color_led_light_div, 30, 230);
    lv_obj_set_size(ui->smart_home_app_color_led_light_div, 208, 21);
    lv_obj_set_scrollbar_mode(ui->smart_home_app_color_led_light_div, LV_SCROLLBAR_MODE_OFF);

    //Write style for smart_home_app_color_led_light_div, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_color_led_light_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_color_led_light_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_color_led_light_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_color_led_light_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_color_led_light_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_color_led_light_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_color_led_light_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_color_led_light_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_color_led_light_text
    ui->smart_home_app_color_led_light_text = lv_label_create(ui->smart_home_app_color_led_light_div);
    lv_label_set_text(ui->smart_home_app_color_led_light_text, "亮度");
    lv_label_set_long_mode(ui->smart_home_app_color_led_light_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_color_led_light_text, 11, 0);
    lv_obj_set_size(ui->smart_home_app_color_led_light_text, 62, 23);

    //Write style for smart_home_app_color_led_light_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_color_led_light_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_color_led_light_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_color_led_light_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_color_led_light_text, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_color_led_light_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_color_led_light_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_color_led_light_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_color_led_light_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_color_led_light_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_color_led_light_text, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_color_led_light_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_color_led_light_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_color_led_light_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_color_led_light_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_color_led_light_div_slider
    ui->smart_home_app_color_led_light_div_slider = lv_slider_create(ui->smart_home_app_color_led_light_div);
    lv_slider_set_range(ui->smart_home_app_color_led_light_div_slider, 0, 100);
    lv_slider_set_mode(ui->smart_home_app_color_led_light_div_slider, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->smart_home_app_color_led_light_div_slider, 50, LV_ANIM_OFF);
    lv_obj_set_pos(ui->smart_home_app_color_led_light_div_slider, 65, 5);
    lv_obj_set_size(ui->smart_home_app_color_led_light_div_slider, 127, 11);

    //Write style for smart_home_app_color_led_light_div_slider, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->smart_home_app_color_led_light_div_slider, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->smart_home_app_color_led_light_div_slider, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->smart_home_app_color_led_light_div_slider, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_color_led_light_div_slider, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->smart_home_app_color_led_light_div_slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_color_led_light_div_slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for smart_home_app_color_led_light_div_slider, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->smart_home_app_color_led_light_div_slider, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->smart_home_app_color_led_light_div_slider, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->smart_home_app_color_led_light_div_slider, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_color_led_light_div_slider, 8, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for smart_home_app_color_led_light_div_slider, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->smart_home_app_color_led_light_div_slider, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->smart_home_app_color_led_light_div_slider, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->smart_home_app_color_led_light_div_slider, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_color_led_light_div_slider, 8, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes smart_home_app_btn_return1
    ui->smart_home_app_btn_return1 = lv_btn_create(ui->smart_home_app_color_led_page);
    ui->smart_home_app_btn_return1_label = lv_label_create(ui->smart_home_app_btn_return1);
    lv_label_set_text(ui->smart_home_app_btn_return1_label, "⬅");
    lv_label_set_long_mode(ui->smart_home_app_btn_return1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->smart_home_app_btn_return1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->smart_home_app_btn_return1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->smart_home_app_btn_return1_label, LV_PCT(100));
    lv_obj_set_pos(ui->smart_home_app_btn_return1, 15, 12);
    lv_obj_set_size(ui->smart_home_app_btn_return1, 34, 34);

    //Write style for smart_home_app_btn_return1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->smart_home_app_btn_return1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->smart_home_app_btn_return1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_btn_return1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_btn_return1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_btn_return1, lv_color_hex(0x5e5e5e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_btn_return1, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_btn_return1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_btn_return1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_led_green_page
    ui->smart_home_app_led_green_page = lv_obj_create(ui->smart_home_app);
    lv_obj_set_pos(ui->smart_home_app_led_green_page, 220, 16);
    lv_obj_set_size(ui->smart_home_app_led_green_page, 260, 304);
    lv_obj_set_scrollbar_mode(ui->smart_home_app_led_green_page, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->smart_home_app_led_green_page, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->smart_home_app_led_green_page, LV_OBJ_FLAG_HIDDEN);

    //Write style for smart_home_app_led_green_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_led_green_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_led_green_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_led_green_page, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->smart_home_app_led_green_page, lv_color_hex(0xededed), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->smart_home_app_led_green_page, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_led_green_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_led_green_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_led_green_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_led_green_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_led_green_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_led_green_sw_div
    ui->smart_home_app_led_green_sw_div = lv_obj_create(ui->smart_home_app_led_green_page);
    lv_obj_set_pos(ui->smart_home_app_led_green_sw_div, 50, 255);
    lv_obj_set_size(ui->smart_home_app_led_green_sw_div, 173, 21);
    lv_obj_set_scrollbar_mode(ui->smart_home_app_led_green_sw_div, LV_SCROLLBAR_MODE_OFF);

    //Write style for smart_home_app_led_green_sw_div, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_led_green_sw_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_led_green_sw_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_led_green_sw_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_led_green_sw_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_led_green_sw_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_led_green_sw_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_led_green_sw_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_led_green_sw_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_led_green_sw
    ui->smart_home_app_led_green_sw = lv_switch_create(ui->smart_home_app_led_green_sw_div);
    lv_obj_set_pos(ui->smart_home_app_led_green_sw, 114, 0);
    lv_obj_set_size(ui->smart_home_app_led_green_sw, 40, 20);

    //Write style for smart_home_app_led_green_sw, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->smart_home_app_led_green_sw, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->smart_home_app_led_green_sw, lv_color_hex(0xe6e2e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->smart_home_app_led_green_sw, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->smart_home_app_led_green_sw, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_led_green_sw, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_led_green_sw, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for smart_home_app_led_green_sw, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->smart_home_app_led_green_sw, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->smart_home_app_led_green_sw, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->smart_home_app_led_green_sw, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->smart_home_app_led_green_sw, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    //Write style for smart_home_app_led_green_sw, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->smart_home_app_led_green_sw, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->smart_home_app_led_green_sw, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->smart_home_app_led_green_sw, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->smart_home_app_led_green_sw, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_led_green_sw, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes smart_home_app_led_green_sw_text
    ui->smart_home_app_led_green_sw_text = lv_label_create(ui->smart_home_app_led_green_sw_div);
    lv_label_set_text(ui->smart_home_app_led_green_sw_text, "开关");
    lv_label_set_long_mode(ui->smart_home_app_led_green_sw_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_led_green_sw_text, 11, 0);
    lv_obj_set_size(ui->smart_home_app_led_green_sw_text, 62, 23);

    //Write style for smart_home_app_led_green_sw_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_led_green_sw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_led_green_sw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_led_green_sw_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_led_green_sw_text, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_led_green_sw_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_led_green_sw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_led_green_sw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_led_green_sw_text, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_led_green_sw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_led_green_sw_text, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_led_green_sw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_led_green_sw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_led_green_sw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_led_green_sw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_led_green_name
    ui->smart_home_app_led_green_name = lv_label_create(ui->smart_home_app_led_green_page);
    lv_label_set_text(ui->smart_home_app_led_green_name, "绿灯设备");
    lv_label_set_long_mode(ui->smart_home_app_led_green_name, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_led_green_name, 85, 20);
    lv_obj_set_size(ui->smart_home_app_led_green_name, 105, 20);

    //Write style for smart_home_app_led_green_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_led_green_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_led_green_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_led_green_name, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_led_green_name, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_led_green_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_led_green_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_led_green_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_led_green_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_led_green_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_led_green_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_led_green_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_led_green_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_led_green_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_led_green_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_btn_return2
    ui->smart_home_app_btn_return2 = lv_btn_create(ui->smart_home_app_led_green_page);
    ui->smart_home_app_btn_return2_label = lv_label_create(ui->smart_home_app_btn_return2);
    lv_label_set_text(ui->smart_home_app_btn_return2_label, "⬅");
    lv_label_set_long_mode(ui->smart_home_app_btn_return2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->smart_home_app_btn_return2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->smart_home_app_btn_return2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->smart_home_app_btn_return2_label, LV_PCT(100));
    lv_obj_set_pos(ui->smart_home_app_btn_return2, 15, 12);
    lv_obj_set_size(ui->smart_home_app_btn_return2, 34, 34);

    //Write style for smart_home_app_btn_return2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->smart_home_app_btn_return2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->smart_home_app_btn_return2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_btn_return2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_btn_return2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_btn_return2, lv_color_hex(0x5e5e5e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_btn_return2, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_btn_return2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_btn_return2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_lm75_page
    ui->smart_home_app_lm75_page = lv_obj_create(ui->smart_home_app);
    lv_obj_set_pos(ui->smart_home_app_lm75_page, 220, 16);
    lv_obj_set_size(ui->smart_home_app_lm75_page, 260, 304);
    lv_obj_set_scrollbar_mode(ui->smart_home_app_lm75_page, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->smart_home_app_lm75_page, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->smart_home_app_lm75_page, LV_OBJ_FLAG_HIDDEN);

    //Write style for smart_home_app_lm75_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_lm75_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_lm75_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_lm75_page, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->smart_home_app_lm75_page, lv_color_hex(0xededed), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->smart_home_app_lm75_page, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_lm75_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_lm75_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_lm75_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_lm75_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_lm75_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_temperature_div
    ui->smart_home_app_temperature_div = lv_obj_create(ui->smart_home_app_lm75_page);
    lv_obj_set_pos(ui->smart_home_app_temperature_div, 36, 255);
    lv_obj_set_size(ui->smart_home_app_temperature_div, 195, 22);
    lv_obj_set_scrollbar_mode(ui->smart_home_app_temperature_div, LV_SCROLLBAR_MODE_OFF);

    //Write style for smart_home_app_temperature_div, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_temperature_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_temperature_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_temperature_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_temperature_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_temperature_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_temperature_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_temperature_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_temperature_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_temperature_textt
    ui->smart_home_app_temperature_textt = lv_label_create(ui->smart_home_app_temperature_div);
    lv_label_set_text(ui->smart_home_app_temperature_textt, "当前温度值");
    lv_label_set_long_mode(ui->smart_home_app_temperature_textt, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_temperature_textt, 0, 0);
    lv_obj_set_size(ui->smart_home_app_temperature_textt, 83, 22);

    //Write style for smart_home_app_temperature_textt, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_temperature_textt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_temperature_textt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_temperature_textt, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_temperature_textt, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_temperature_textt, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_temperature_textt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_temperature_textt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_temperature_textt, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_temperature_textt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_temperature_textt, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_temperature_textt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_temperature_textt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_temperature_textt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_temperature_textt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_temperature_num
    ui->smart_home_app_temperature_num = lv_label_create(ui->smart_home_app_temperature_div);
    lv_label_set_text(ui->smart_home_app_temperature_num, "0°C");
    lv_label_set_long_mode(ui->smart_home_app_temperature_num, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_temperature_num, 100, 0);
    lv_obj_set_size(ui->smart_home_app_temperature_num, 100, 22);

    //Write style for smart_home_app_temperature_num, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_temperature_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_temperature_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_temperature_num, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_temperature_num, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_temperature_num, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_temperature_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_temperature_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_temperature_num, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_temperature_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_temperature_num, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_temperature_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_temperature_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_temperature_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_temperature_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_lm75_name
    ui->smart_home_app_lm75_name = lv_label_create(ui->smart_home_app_lm75_page);
    lv_label_set_text(ui->smart_home_app_lm75_name, "温度传感设备");
    lv_label_set_long_mode(ui->smart_home_app_lm75_name, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_lm75_name, 85, 20);
    lv_obj_set_size(ui->smart_home_app_lm75_name, 105, 20);

    //Write style for smart_home_app_lm75_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_lm75_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_lm75_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_lm75_name, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_lm75_name, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_lm75_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_lm75_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_lm75_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_lm75_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_lm75_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_lm75_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_lm75_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_lm75_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_lm75_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_lm75_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_btn_return3
    ui->smart_home_app_btn_return3 = lv_btn_create(ui->smart_home_app_lm75_page);
    ui->smart_home_app_btn_return3_label = lv_label_create(ui->smart_home_app_btn_return3);
    lv_label_set_text(ui->smart_home_app_btn_return3_label, "⬅");
    lv_label_set_long_mode(ui->smart_home_app_btn_return3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->smart_home_app_btn_return3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->smart_home_app_btn_return3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->smart_home_app_btn_return3_label, LV_PCT(100));
    lv_obj_set_pos(ui->smart_home_app_btn_return3, 15, 12);
    lv_obj_set_size(ui->smart_home_app_btn_return3, 34, 34);

    //Write style for smart_home_app_btn_return3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->smart_home_app_btn_return3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->smart_home_app_btn_return3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_btn_return3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_btn_return3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_btn_return3, lv_color_hex(0x5e5e5e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_btn_return3, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_btn_return3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_btn_return3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_ADC_page
    ui->smart_home_app_ADC_page = lv_obj_create(ui->smart_home_app);
    lv_obj_set_pos(ui->smart_home_app_ADC_page, 220, 16);
    lv_obj_set_size(ui->smart_home_app_ADC_page, 260, 304);
    lv_obj_set_scrollbar_mode(ui->smart_home_app_ADC_page, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->smart_home_app_ADC_page, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->smart_home_app_ADC_page, LV_OBJ_FLAG_HIDDEN);

    //Write style for smart_home_app_ADC_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_ADC_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_ADC_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_ADC_page, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->smart_home_app_ADC_page, lv_color_hex(0xededed), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->smart_home_app_ADC_page, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_ADC_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_ADC_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_ADC_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_ADC_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_ADC_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_ADC_name
    ui->smart_home_app_ADC_name = lv_label_create(ui->smart_home_app_ADC_page);
    lv_label_set_text(ui->smart_home_app_ADC_name, "电压传感器设备");
    lv_label_set_long_mode(ui->smart_home_app_ADC_name, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_ADC_name, 36, 20);
    lv_obj_set_size(ui->smart_home_app_ADC_name, 190, 20);

    //Write style for smart_home_app_ADC_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_ADC_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_ADC_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_ADC_name, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_ADC_name, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_ADC_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_ADC_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_ADC_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_ADC_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_ADC_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_ADC_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_ADC_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_ADC_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_ADC_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_ADC_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_ADC_div
    ui->smart_home_app_ADC_div = lv_obj_create(ui->smart_home_app_ADC_page);
    lv_obj_set_pos(ui->smart_home_app_ADC_div, 36, 255);
    lv_obj_set_size(ui->smart_home_app_ADC_div, 195, 22);
    lv_obj_set_scrollbar_mode(ui->smart_home_app_ADC_div, LV_SCROLLBAR_MODE_OFF);

    //Write style for smart_home_app_ADC_div, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_ADC_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_ADC_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_ADC_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_ADC_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_ADC_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_ADC_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_ADC_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_ADC_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_ADC_text
    ui->smart_home_app_ADC_text = lv_label_create(ui->smart_home_app_ADC_div);
    lv_label_set_text(ui->smart_home_app_ADC_text, "当前电压值");
    lv_label_set_long_mode(ui->smart_home_app_ADC_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_ADC_text, 0, 0);
    lv_obj_set_size(ui->smart_home_app_ADC_text, 83, 22);

    //Write style for smart_home_app_ADC_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_ADC_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_ADC_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_ADC_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_ADC_text, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_ADC_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_ADC_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_ADC_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_ADC_text, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_ADC_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_ADC_text, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_ADC_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_ADC_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_ADC_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_ADC_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_ADC_num
    ui->smart_home_app_ADC_num = lv_label_create(ui->smart_home_app_ADC_div);
    lv_label_set_text(ui->smart_home_app_ADC_num, "mV");
    lv_label_set_long_mode(ui->smart_home_app_ADC_num, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_ADC_num, 90, 0);
    lv_obj_set_size(ui->smart_home_app_ADC_num, 100, 22);

    //Write style for smart_home_app_ADC_num, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_ADC_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_ADC_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_ADC_num, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_ADC_num, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_ADC_num, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_ADC_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_ADC_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_ADC_num, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_ADC_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_ADC_num, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_ADC_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_ADC_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_ADC_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_ADC_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_btn_reutrn4
    ui->smart_home_app_btn_reutrn4 = lv_btn_create(ui->smart_home_app_ADC_page);
    ui->smart_home_app_btn_reutrn4_label = lv_label_create(ui->smart_home_app_btn_reutrn4);
    lv_label_set_text(ui->smart_home_app_btn_reutrn4_label, "⬅");
    lv_label_set_long_mode(ui->smart_home_app_btn_reutrn4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->smart_home_app_btn_reutrn4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->smart_home_app_btn_reutrn4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->smart_home_app_btn_reutrn4_label, LV_PCT(100));
    lv_obj_set_pos(ui->smart_home_app_btn_reutrn4, 15, 12);
    lv_obj_set_size(ui->smart_home_app_btn_reutrn4, 34, 34);

    //Write style for smart_home_app_btn_reutrn4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->smart_home_app_btn_reutrn4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->smart_home_app_btn_reutrn4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_btn_reutrn4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_btn_reutrn4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_btn_reutrn4, lv_color_hex(0x5e5e5e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_btn_reutrn4, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_btn_reutrn4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_btn_reutrn4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_MPU6050_page
    ui->smart_home_app_MPU6050_page = lv_obj_create(ui->smart_home_app);
    lv_obj_set_pos(ui->smart_home_app_MPU6050_page, 220, 16);
    lv_obj_set_size(ui->smart_home_app_MPU6050_page, 260, 304);
    lv_obj_set_scrollbar_mode(ui->smart_home_app_MPU6050_page, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->smart_home_app_MPU6050_page, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->smart_home_app_MPU6050_page, LV_OBJ_FLAG_HIDDEN);

    //Write style for smart_home_app_MPU6050_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_MPU6050_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_MPU6050_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_MPU6050_page, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->smart_home_app_MPU6050_page, lv_color_hex(0xededed), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->smart_home_app_MPU6050_page, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_MPU6050_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_MPU6050_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_MPU6050_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_MPU6050_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_MPU6050_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_MPU6050_name
    ui->smart_home_app_MPU6050_name = lv_label_create(ui->smart_home_app_MPU6050_page);
    lv_label_set_text(ui->smart_home_app_MPU6050_name, "姿态传感器设备");
    lv_label_set_long_mode(ui->smart_home_app_MPU6050_name, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_MPU6050_name, 50, 20);
    lv_obj_set_size(ui->smart_home_app_MPU6050_name, 165, 20);

    //Write style for smart_home_app_MPU6050_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_MPU6050_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_MPU6050_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_MPU6050_name, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_MPU6050_name, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_MPU6050_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_MPU6050_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_MPU6050_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_MPU6050_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_MPU6050_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_MPU6050_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_MPU6050_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_MPU6050_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_MPU6050_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_MPU6050_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_attitude_div
    ui->smart_home_app_attitude_div = lv_obj_create(ui->smart_home_app_MPU6050_page);
    lv_obj_set_pos(ui->smart_home_app_attitude_div, 36, 165);
    lv_obj_set_size(ui->smart_home_app_attitude_div, 195, 100);
    lv_obj_set_scrollbar_mode(ui->smart_home_app_attitude_div, LV_SCROLLBAR_MODE_OFF);

    //Write style for smart_home_app_attitude_div, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_attitude_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_attitude_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_attitude_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_attitude_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_attitude_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_attitude_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_attitude_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_attitude_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_attitude_text
    ui->smart_home_app_attitude_text = lv_label_create(ui->smart_home_app_attitude_div);
    lv_label_set_text(ui->smart_home_app_attitude_text, "当前陀螺仪");
    lv_label_set_long_mode(ui->smart_home_app_attitude_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_attitude_text, 0, 0);
    lv_obj_set_size(ui->smart_home_app_attitude_text, 83, 19);

    //Write style for smart_home_app_attitude_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_attitude_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_attitude_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_attitude_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_attitude_text, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_attitude_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_attitude_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_attitude_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_attitude_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_attitude_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_attitude_text, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_attitude_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_attitude_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_attitude_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_attitude_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_attitude_text_x
    ui->smart_home_app_attitude_text_x = lv_label_create(ui->smart_home_app_attitude_div);
    lv_label_set_text(ui->smart_home_app_attitude_text_x, "x");
    lv_label_set_long_mode(ui->smart_home_app_attitude_text_x, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_attitude_text_x, 19, 23);
    lv_obj_set_size(ui->smart_home_app_attitude_text_x, 83, 19);

    //Write style for smart_home_app_attitude_text_x, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_attitude_text_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_attitude_text_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_attitude_text_x, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_attitude_text_x, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_attitude_text_x, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_attitude_text_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_attitude_text_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_attitude_text_x, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_attitude_text_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_attitude_text_x, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_attitude_text_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_attitude_text_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_attitude_text_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_attitude_text_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_attitude_text_y
    ui->smart_home_app_attitude_text_y = lv_label_create(ui->smart_home_app_attitude_div);
    lv_label_set_text(ui->smart_home_app_attitude_text_y, "y");
    lv_label_set_long_mode(ui->smart_home_app_attitude_text_y, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_attitude_text_y, 19, 43);
    lv_obj_set_size(ui->smart_home_app_attitude_text_y, 83, 22);

    //Write style for smart_home_app_attitude_text_y, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_attitude_text_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_attitude_text_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_attitude_text_y, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_attitude_text_y, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_attitude_text_y, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_attitude_text_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_attitude_text_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_attitude_text_y, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_attitude_text_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_attitude_text_y, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_attitude_text_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_attitude_text_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_attitude_text_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_attitude_text_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_attitude_text_z
    ui->smart_home_app_attitude_text_z = lv_label_create(ui->smart_home_app_attitude_div);
    lv_label_set_text(ui->smart_home_app_attitude_text_z, "z");
    lv_label_set_long_mode(ui->smart_home_app_attitude_text_z, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_attitude_text_z, 19, 63);
    lv_obj_set_size(ui->smart_home_app_attitude_text_z, 83, 19);

    //Write style for smart_home_app_attitude_text_z, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_attitude_text_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_attitude_text_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_attitude_text_z, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_attitude_text_z, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_attitude_text_z, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_attitude_text_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_attitude_text_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_attitude_text_z, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_attitude_text_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_attitude_text_z, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_attitude_text_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_attitude_text_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_attitude_text_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_attitude_text_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_attitude_num_x
    ui->smart_home_app_attitude_num_x = lv_label_create(ui->smart_home_app_attitude_div);
    lv_label_set_text(ui->smart_home_app_attitude_num_x, "1");
    lv_label_set_long_mode(ui->smart_home_app_attitude_num_x, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_attitude_num_x, 91, 23);
    lv_obj_set_size(ui->smart_home_app_attitude_num_x, 83, 19);

    //Write style for smart_home_app_attitude_num_x, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_attitude_num_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_attitude_num_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_attitude_num_x, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_attitude_num_x, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_attitude_num_x, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_attitude_num_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_attitude_num_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_attitude_num_x, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_attitude_num_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_attitude_num_x, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_attitude_num_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_attitude_num_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_attitude_num_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_attitude_num_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_attitude_num_y
    ui->smart_home_app_attitude_num_y = lv_label_create(ui->smart_home_app_attitude_div);
    lv_label_set_text(ui->smart_home_app_attitude_num_y, "1");
    lv_label_set_long_mode(ui->smart_home_app_attitude_num_y, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_attitude_num_y, 90, 43);
    lv_obj_set_size(ui->smart_home_app_attitude_num_y, 83, 19);

    //Write style for smart_home_app_attitude_num_y, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_attitude_num_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_attitude_num_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_attitude_num_y, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_attitude_num_y, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_attitude_num_y, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_attitude_num_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_attitude_num_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_attitude_num_y, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_attitude_num_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_attitude_num_y, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_attitude_num_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_attitude_num_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_attitude_num_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_attitude_num_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_attitude_num_z
    ui->smart_home_app_attitude_num_z = lv_label_create(ui->smart_home_app_attitude_div);
    lv_label_set_text(ui->smart_home_app_attitude_num_z, "1");
    lv_label_set_long_mode(ui->smart_home_app_attitude_num_z, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_attitude_num_z, 90, 63);
    lv_obj_set_size(ui->smart_home_app_attitude_num_z, 83, 19);

    //Write style for smart_home_app_attitude_num_z, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_attitude_num_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_attitude_num_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_attitude_num_z, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_attitude_num_z, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_attitude_num_z, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_attitude_num_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_attitude_num_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_attitude_num_z, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_attitude_num_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_attitude_num_z, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_attitude_num_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_attitude_num_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_attitude_num_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_attitude_num_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_accelerated_speed_div
    ui->smart_home_app_accelerated_speed_div = lv_obj_create(ui->smart_home_app_MPU6050_page);
    lv_obj_set_pos(ui->smart_home_app_accelerated_speed_div, 36, 65);
    lv_obj_set_size(ui->smart_home_app_accelerated_speed_div, 195, 100);
    lv_obj_set_scrollbar_mode(ui->smart_home_app_accelerated_speed_div, LV_SCROLLBAR_MODE_OFF);

    //Write style for smart_home_app_accelerated_speed_div, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_accelerated_speed_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_accelerated_speed_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_accelerated_speed_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_accelerated_speed_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_accelerated_speed_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_accelerated_speed_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_accelerated_speed_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_accelerated_speed_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_accelerated_speed_text
    ui->smart_home_app_accelerated_speed_text = lv_label_create(ui->smart_home_app_accelerated_speed_div);
    lv_label_set_text(ui->smart_home_app_accelerated_speed_text, "当前加速度");
    lv_label_set_long_mode(ui->smart_home_app_accelerated_speed_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_accelerated_speed_text, 0, 0);
    lv_obj_set_size(ui->smart_home_app_accelerated_speed_text, 83, 22);

    //Write style for smart_home_app_accelerated_speed_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_accelerated_speed_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_accelerated_speed_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_accelerated_speed_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_accelerated_speed_text, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_accelerated_speed_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_accelerated_speed_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_accelerated_speed_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_accelerated_speed_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_accelerated_speed_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_accelerated_speed_text, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_accelerated_speed_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_accelerated_speed_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_accelerated_speed_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_accelerated_speed_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_accelerated_speed_text_x
    ui->smart_home_app_accelerated_speed_text_x = lv_label_create(ui->smart_home_app_accelerated_speed_div);
    lv_label_set_text(ui->smart_home_app_accelerated_speed_text_x, "x");
    lv_label_set_long_mode(ui->smart_home_app_accelerated_speed_text_x, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_accelerated_speed_text_x, 19, 22);
    lv_obj_set_size(ui->smart_home_app_accelerated_speed_text_x, 83, 19);

    //Write style for smart_home_app_accelerated_speed_text_x, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_accelerated_speed_text_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_accelerated_speed_text_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_accelerated_speed_text_x, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_accelerated_speed_text_x, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_accelerated_speed_text_x, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_accelerated_speed_text_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_accelerated_speed_text_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_accelerated_speed_text_x, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_accelerated_speed_text_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_accelerated_speed_text_x, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_accelerated_speed_text_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_accelerated_speed_text_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_accelerated_speed_text_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_accelerated_speed_text_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_accelerated_speed_text_y
    ui->smart_home_app_accelerated_speed_text_y = lv_label_create(ui->smart_home_app_accelerated_speed_div);
    lv_label_set_text(ui->smart_home_app_accelerated_speed_text_y, "y");
    lv_label_set_long_mode(ui->smart_home_app_accelerated_speed_text_y, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_accelerated_speed_text_y, 19, 44);
    lv_obj_set_size(ui->smart_home_app_accelerated_speed_text_y, 83, 25);

    //Write style for smart_home_app_accelerated_speed_text_y, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_accelerated_speed_text_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_accelerated_speed_text_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_accelerated_speed_text_y, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_accelerated_speed_text_y, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_accelerated_speed_text_y, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_accelerated_speed_text_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_accelerated_speed_text_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_accelerated_speed_text_y, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_accelerated_speed_text_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_accelerated_speed_text_y, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_accelerated_speed_text_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_accelerated_speed_text_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_accelerated_speed_text_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_accelerated_speed_text_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_accelerated_speed_text_z
    ui->smart_home_app_accelerated_speed_text_z = lv_label_create(ui->smart_home_app_accelerated_speed_div);
    lv_label_set_text(ui->smart_home_app_accelerated_speed_text_z, "z");
    lv_label_set_long_mode(ui->smart_home_app_accelerated_speed_text_z, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_accelerated_speed_text_z, 19, 69);
    lv_obj_set_size(ui->smart_home_app_accelerated_speed_text_z, 83, 19);

    //Write style for smart_home_app_accelerated_speed_text_z, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_accelerated_speed_text_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_accelerated_speed_text_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_accelerated_speed_text_z, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_accelerated_speed_text_z, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_accelerated_speed_text_z, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_accelerated_speed_text_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_accelerated_speed_text_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_accelerated_speed_text_z, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_accelerated_speed_text_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_accelerated_speed_text_z, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_accelerated_speed_text_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_accelerated_speed_text_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_accelerated_speed_text_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_accelerated_speed_text_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_accelerated_speed_num_x
    ui->smart_home_app_accelerated_speed_num_x = lv_label_create(ui->smart_home_app_accelerated_speed_div);
    lv_label_set_text(ui->smart_home_app_accelerated_speed_num_x, "1");
    lv_label_set_long_mode(ui->smart_home_app_accelerated_speed_num_x, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_accelerated_speed_num_x, 90, 24);
    lv_obj_set_size(ui->smart_home_app_accelerated_speed_num_x, 83, 19);

    //Write style for smart_home_app_accelerated_speed_num_x, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_accelerated_speed_num_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_accelerated_speed_num_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_accelerated_speed_num_x, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_accelerated_speed_num_x, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_accelerated_speed_num_x, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_accelerated_speed_num_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_accelerated_speed_num_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_accelerated_speed_num_x, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_accelerated_speed_num_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_accelerated_speed_num_x, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_accelerated_speed_num_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_accelerated_speed_num_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_accelerated_speed_num_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_accelerated_speed_num_x, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_accelerated_speed_num_y
    ui->smart_home_app_accelerated_speed_num_y = lv_label_create(ui->smart_home_app_accelerated_speed_div);
    lv_label_set_text(ui->smart_home_app_accelerated_speed_num_y, "1");
    lv_label_set_long_mode(ui->smart_home_app_accelerated_speed_num_y, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_accelerated_speed_num_y, 90, 44);
    lv_obj_set_size(ui->smart_home_app_accelerated_speed_num_y, 83, 19);

    //Write style for smart_home_app_accelerated_speed_num_y, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_accelerated_speed_num_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_accelerated_speed_num_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_accelerated_speed_num_y, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_accelerated_speed_num_y, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_accelerated_speed_num_y, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_accelerated_speed_num_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_accelerated_speed_num_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_accelerated_speed_num_y, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_accelerated_speed_num_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_accelerated_speed_num_y, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_accelerated_speed_num_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_accelerated_speed_num_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_accelerated_speed_num_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_accelerated_speed_num_y, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_accelerated_speed_num_z
    ui->smart_home_app_accelerated_speed_num_z = lv_label_create(ui->smart_home_app_accelerated_speed_div);
    lv_label_set_text(ui->smart_home_app_accelerated_speed_num_z, "1");
    lv_label_set_long_mode(ui->smart_home_app_accelerated_speed_num_z, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_accelerated_speed_num_z, 90, 64);
    lv_obj_set_size(ui->smart_home_app_accelerated_speed_num_z, 83, 19);

    //Write style for smart_home_app_accelerated_speed_num_z, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_accelerated_speed_num_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_accelerated_speed_num_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_accelerated_speed_num_z, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_accelerated_speed_num_z, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_accelerated_speed_num_z, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_accelerated_speed_num_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_accelerated_speed_num_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_accelerated_speed_num_z, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_accelerated_speed_num_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_accelerated_speed_num_z, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_accelerated_speed_num_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_accelerated_speed_num_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_accelerated_speed_num_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_accelerated_speed_num_z, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_mpu6050_temp
    ui->smart_home_app_mpu6050_temp = lv_obj_create(ui->smart_home_app_MPU6050_page);
    lv_obj_set_pos(ui->smart_home_app_mpu6050_temp, 36, 255);
    lv_obj_set_size(ui->smart_home_app_mpu6050_temp, 195, 22);
    lv_obj_set_scrollbar_mode(ui->smart_home_app_mpu6050_temp, LV_SCROLLBAR_MODE_OFF);

    //Write style for smart_home_app_mpu6050_temp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_mpu6050_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_mpu6050_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_mpu6050_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_mpu6050_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_mpu6050_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_mpu6050_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_mpu6050_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_mpu6050_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_mpu6050_teemp_text
    ui->smart_home_app_mpu6050_teemp_text = lv_label_create(ui->smart_home_app_mpu6050_temp);
    lv_label_set_text(ui->smart_home_app_mpu6050_teemp_text, "当前温度值");
    lv_label_set_long_mode(ui->smart_home_app_mpu6050_teemp_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_mpu6050_teemp_text, 0, 0);
    lv_obj_set_size(ui->smart_home_app_mpu6050_teemp_text, 83, 22);

    //Write style for smart_home_app_mpu6050_teemp_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_mpu6050_teemp_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_mpu6050_teemp_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_mpu6050_teemp_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_mpu6050_teemp_text, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_mpu6050_teemp_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_mpu6050_teemp_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_mpu6050_teemp_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_mpu6050_teemp_text, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_mpu6050_teemp_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_mpu6050_teemp_text, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_mpu6050_teemp_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_mpu6050_teemp_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_mpu6050_teemp_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_mpu6050_teemp_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_mpu6050_teemp_num
    ui->smart_home_app_mpu6050_teemp_num = lv_label_create(ui->smart_home_app_mpu6050_temp);
    lv_label_set_text(ui->smart_home_app_mpu6050_teemp_num, "0°C");
    lv_label_set_long_mode(ui->smart_home_app_mpu6050_teemp_num, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_mpu6050_teemp_num, 92, 0);
    lv_obj_set_size(ui->smart_home_app_mpu6050_teemp_num, 100, 22);

    //Write style for smart_home_app_mpu6050_teemp_num, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_mpu6050_teemp_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_mpu6050_teemp_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_mpu6050_teemp_num, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_mpu6050_teemp_num, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_mpu6050_teemp_num, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_mpu6050_teemp_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_mpu6050_teemp_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_mpu6050_teemp_num, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_mpu6050_teemp_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_mpu6050_teemp_num, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_mpu6050_teemp_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_mpu6050_teemp_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_mpu6050_teemp_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_mpu6050_teemp_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_btn_return5
    ui->smart_home_app_btn_return5 = lv_btn_create(ui->smart_home_app_MPU6050_page);
    ui->smart_home_app_btn_return5_label = lv_label_create(ui->smart_home_app_btn_return5);
    lv_label_set_text(ui->smart_home_app_btn_return5_label, "⬅");
    lv_label_set_long_mode(ui->smart_home_app_btn_return5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->smart_home_app_btn_return5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->smart_home_app_btn_return5, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->smart_home_app_btn_return5_label, LV_PCT(100));
    lv_obj_set_pos(ui->smart_home_app_btn_return5, 15, 12);
    lv_obj_set_size(ui->smart_home_app_btn_return5, 34, 34);

    //Write style for smart_home_app_btn_return5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->smart_home_app_btn_return5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->smart_home_app_btn_return5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_btn_return5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_btn_return5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_btn_return5, lv_color_hex(0x5e5e5e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_btn_return5, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_btn_return5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_btn_return5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_key_page
    ui->smart_home_app_key_page = lv_obj_create(ui->smart_home_app);
    lv_obj_set_pos(ui->smart_home_app_key_page, 220, 16);
    lv_obj_set_size(ui->smart_home_app_key_page, 260, 304);
    lv_obj_set_scrollbar_mode(ui->smart_home_app_key_page, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->smart_home_app_key_page, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->smart_home_app_key_page, LV_OBJ_FLAG_HIDDEN);

    //Write style for smart_home_app_key_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_key_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_key_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_key_page, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->smart_home_app_key_page, lv_color_hex(0xededed), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->smart_home_app_key_page, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_key_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_key_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_key_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_key_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_key_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_key_name
    ui->smart_home_app_key_name = lv_label_create(ui->smart_home_app_key_page);
    lv_label_set_text(ui->smart_home_app_key_name, "按键设备");
    lv_label_set_long_mode(ui->smart_home_app_key_name, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->smart_home_app_key_name, 59, 20);
    lv_obj_set_size(ui->smart_home_app_key_name, 152, 20);

    //Write style for smart_home_app_key_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->smart_home_app_key_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_key_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_key_name, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_key_name, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_key_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->smart_home_app_key_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->smart_home_app_key_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_key_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->smart_home_app_key_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->smart_home_app_key_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->smart_home_app_key_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->smart_home_app_key_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->smart_home_app_key_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_key_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_btn_7
    ui->smart_home_app_btn_7 = lv_btn_create(ui->smart_home_app_key_page);
    ui->smart_home_app_btn_7_label = lv_label_create(ui->smart_home_app_btn_7);
    lv_label_set_text(ui->smart_home_app_btn_7_label, "按钮7");
    lv_label_set_long_mode(ui->smart_home_app_btn_7_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->smart_home_app_btn_7_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->smart_home_app_btn_7, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->smart_home_app_btn_7_label, LV_PCT(100));
    lv_obj_set_pos(ui->smart_home_app_btn_7, 15, 90);
    lv_obj_set_size(ui->smart_home_app_btn_7, 40, 35);

    //Write style for smart_home_app_btn_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->smart_home_app_btn_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->smart_home_app_btn_7, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->smart_home_app_btn_7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->smart_home_app_btn_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_btn_7, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_btn_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_btn_7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_btn_7, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_btn_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_btn_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_btn_5
    ui->smart_home_app_btn_5 = lv_btn_create(ui->smart_home_app_key_page);
    ui->smart_home_app_btn_5_label = lv_label_create(ui->smart_home_app_btn_5);
    lv_label_set_text(ui->smart_home_app_btn_5_label, "按钮5");
    lv_label_set_long_mode(ui->smart_home_app_btn_5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->smart_home_app_btn_5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->smart_home_app_btn_5, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->smart_home_app_btn_5_label, LV_PCT(100));
    lv_obj_set_pos(ui->smart_home_app_btn_5, 80, 90);
    lv_obj_set_size(ui->smart_home_app_btn_5, 40, 35);

    //Write style for smart_home_app_btn_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->smart_home_app_btn_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->smart_home_app_btn_5, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->smart_home_app_btn_5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->smart_home_app_btn_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_btn_5, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_btn_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_btn_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_btn_5, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_btn_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_btn_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_btn_8
    ui->smart_home_app_btn_8 = lv_btn_create(ui->smart_home_app_key_page);
    ui->smart_home_app_btn_8_label = lv_label_create(ui->smart_home_app_btn_8);
    lv_label_set_text(ui->smart_home_app_btn_8_label, "按钮8");
    lv_label_set_long_mode(ui->smart_home_app_btn_8_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->smart_home_app_btn_8_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->smart_home_app_btn_8, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->smart_home_app_btn_8_label, LV_PCT(100));
    lv_obj_set_pos(ui->smart_home_app_btn_8, 15, 145);
    lv_obj_set_size(ui->smart_home_app_btn_8, 40, 35);

    //Write style for smart_home_app_btn_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->smart_home_app_btn_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->smart_home_app_btn_8, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->smart_home_app_btn_8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->smart_home_app_btn_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_btn_8, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_btn_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_btn_8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_btn_8, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_btn_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_btn_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_btn_6
    ui->smart_home_app_btn_6 = lv_btn_create(ui->smart_home_app_key_page);
    ui->smart_home_app_btn_6_label = lv_label_create(ui->smart_home_app_btn_6);
    lv_label_set_text(ui->smart_home_app_btn_6_label, "按钮6");
    lv_label_set_long_mode(ui->smart_home_app_btn_6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->smart_home_app_btn_6_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->smart_home_app_btn_6, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->smart_home_app_btn_6_label, LV_PCT(100));
    lv_obj_set_pos(ui->smart_home_app_btn_6, 80, 145);
    lv_obj_set_size(ui->smart_home_app_btn_6, 40, 35);

    //Write style for smart_home_app_btn_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->smart_home_app_btn_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->smart_home_app_btn_6, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->smart_home_app_btn_6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->smart_home_app_btn_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_btn_6, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_btn_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_btn_6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_btn_6, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_btn_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_btn_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_btn_1
    ui->smart_home_app_btn_1 = lv_btn_create(ui->smart_home_app_key_page);
    ui->smart_home_app_btn_1_label = lv_label_create(ui->smart_home_app_btn_1);
    lv_label_set_text(ui->smart_home_app_btn_1_label, "按钮1");
    lv_label_set_long_mode(ui->smart_home_app_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->smart_home_app_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->smart_home_app_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->smart_home_app_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->smart_home_app_btn_1, 170, 80);
    lv_obj_set_size(ui->smart_home_app_btn_1, 40, 35);

    //Write style for smart_home_app_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->smart_home_app_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->smart_home_app_btn_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->smart_home_app_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->smart_home_app_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_btn_1, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_btn_4
    ui->smart_home_app_btn_4 = lv_btn_create(ui->smart_home_app_key_page);
    ui->smart_home_app_btn_4_label = lv_label_create(ui->smart_home_app_btn_4);
    lv_label_set_text(ui->smart_home_app_btn_4_label, "按钮4");
    lv_label_set_long_mode(ui->smart_home_app_btn_4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->smart_home_app_btn_4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->smart_home_app_btn_4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->smart_home_app_btn_4_label, LV_PCT(100));
    lv_obj_set_pos(ui->smart_home_app_btn_4, 130, 120);
    lv_obj_set_size(ui->smart_home_app_btn_4, 40, 35);

    //Write style for smart_home_app_btn_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->smart_home_app_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->smart_home_app_btn_4, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->smart_home_app_btn_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->smart_home_app_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_btn_4, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_btn_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_btn_4, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_btn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_btn_2
    ui->smart_home_app_btn_2 = lv_btn_create(ui->smart_home_app_key_page);
    ui->smart_home_app_btn_2_label = lv_label_create(ui->smart_home_app_btn_2);
    lv_label_set_text(ui->smart_home_app_btn_2_label, "按钮2");
    lv_label_set_long_mode(ui->smart_home_app_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->smart_home_app_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->smart_home_app_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->smart_home_app_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->smart_home_app_btn_2, 210, 120);
    lv_obj_set_size(ui->smart_home_app_btn_2, 40, 35);

    //Write style for smart_home_app_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->smart_home_app_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->smart_home_app_btn_2, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->smart_home_app_btn_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->smart_home_app_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_btn_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_btn_2, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_btn_3
    ui->smart_home_app_btn_3 = lv_btn_create(ui->smart_home_app_key_page);
    ui->smart_home_app_btn_3_label = lv_label_create(ui->smart_home_app_btn_3);
    lv_label_set_text(ui->smart_home_app_btn_3_label, "按钮3");
    lv_label_set_long_mode(ui->smart_home_app_btn_3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->smart_home_app_btn_3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->smart_home_app_btn_3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->smart_home_app_btn_3_label, LV_PCT(100));
    lv_obj_set_pos(ui->smart_home_app_btn_3, 171, 160);
    lv_obj_set_size(ui->smart_home_app_btn_3, 40, 35);

    //Write style for smart_home_app_btn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->smart_home_app_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->smart_home_app_btn_3, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->smart_home_app_btn_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->smart_home_app_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_btn_3, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_btn_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_btn_3, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_btn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_btn_return6
    ui->smart_home_app_btn_return6 = lv_btn_create(ui->smart_home_app_key_page);
    ui->smart_home_app_btn_return6_label = lv_label_create(ui->smart_home_app_btn_return6);
    lv_label_set_text(ui->smart_home_app_btn_return6_label, "⬅");
    lv_label_set_long_mode(ui->smart_home_app_btn_return6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->smart_home_app_btn_return6_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->smart_home_app_btn_return6, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->smart_home_app_btn_return6_label, LV_PCT(100));
    lv_obj_set_pos(ui->smart_home_app_btn_return6, 15, 12);
    lv_obj_set_size(ui->smart_home_app_btn_return6, 34, 34);

    //Write style for smart_home_app_btn_return6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->smart_home_app_btn_return6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->smart_home_app_btn_return6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_btn_return6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_btn_return6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_btn_return6, lv_color_hex(0x5e5e5e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_btn_return6, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_btn_return6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_btn_return6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes smart_home_app_back_btn
    ui->smart_home_app_back_btn = lv_btn_create(ui->smart_home_app);
    ui->smart_home_app_back_btn_label = lv_label_create(ui->smart_home_app_back_btn);
    lv_label_set_text(ui->smart_home_app_back_btn_label, "⬅");
    lv_label_set_long_mode(ui->smart_home_app_back_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->smart_home_app_back_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->smart_home_app_back_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->smart_home_app_back_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->smart_home_app_back_btn, 29, 24);
    lv_obj_set_size(ui->smart_home_app_back_btn, 28, 23);

    //Write style for smart_home_app_back_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->smart_home_app_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->smart_home_app_back_btn, lv_color_hex(0x9a9a9a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->smart_home_app_back_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->smart_home_app_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->smart_home_app_back_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->smart_home_app_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->smart_home_app_back_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->smart_home_app_back_btn, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->smart_home_app_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->smart_home_app_back_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of smart_home_app.
    // IoT页面图标可点击并不向父容器冒泡
    lv_obj_add_flag(ui->smart_home_app_IoT_color_led, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(ui->smart_home_app_IoT_color_led, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui->smart_home_app_IoT_led_green, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(ui->smart_home_app_IoT_led_green, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui->smart_home_app_IoT_ADC, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(ui->smart_home_app_IoT_ADC, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui->smart_home_app_IoT_MPU6050, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(ui->smart_home_app_IoT_MPU6050, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui->smart_home_app_IoT_lm75, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(ui->smart_home_app_IoT_lm75, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui->smart_home_app_IoT_8key, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(ui->smart_home_app_IoT_8key, LV_OBJ_FLAG_EVENT_BUBBLE);

    // IoT页面图标事件
    lv_obj_add_event_cb(ui->smart_home_app_IoT_color_led, smart_home_iot_color_led_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->smart_home_app_IoT_led_green, smart_home_iot_led_green_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->smart_home_app_IoT_ADC, smart_home_iot_adc_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->smart_home_app_IoT_MPU6050, smart_home_iot_mpu6050_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->smart_home_app_IoT_lm75, smart_home_iot_lm75_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->smart_home_app_IoT_8key, smart_home_iot_8key_event_handler, LV_EVENT_ALL, ui);
    // 彩灯控制事件
#ifdef KEIL_COMPILE
    lv_obj_add_event_cb(ui->smart_home_app_color_led_sw, smart_home_color_led_sw_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->smart_home_app_color_led_cpicker, smart_home_color_led_cpicker_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->smart_home_app_color_led_light_div_slider, smart_home_color_led_light_slider_event_handler, LV_EVENT_ALL, ui);
    // 绿灯控制事件
    lv_obj_add_event_cb(ui->smart_home_app_led_green_sw, smart_home_led_green_sw_event_handler, LV_EVENT_ALL, ui);
#endif

    //Update current screen layout.
    lv_obj_update_layout(ui->smart_home_app);

    //Init events for screen.
    events_init_smart_home_app(ui);
}
