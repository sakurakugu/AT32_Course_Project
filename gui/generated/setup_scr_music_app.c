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



int music_app_time_min_value = 25;
int music_app_time_hour_value = 11;
int music_app_time_sec_value = 50;
void setup_scr_music_app(lv_ui *ui)
{
    //Write codes music_app
    ui->music_app = lv_obj_create(NULL);
    lv_obj_set_size(ui->music_app, 480, 320);
    lv_obj_set_scrollbar_mode(ui->music_app, LV_SCROLLBAR_MODE_OFF);

    //Write style for music_app, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->music_app, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes music_app_status_bar
    ui->music_app_status_bar = lv_obj_create(ui->music_app);
    lv_obj_set_pos(ui->music_app_status_bar, 0, 0);
    lv_obj_set_size(ui->music_app_status_bar, 480, 16);
    lv_obj_set_scrollbar_mode(ui->music_app_status_bar, LV_SCROLLBAR_MODE_OFF);

    //Write style for music_app_status_bar, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->music_app_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->music_app_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->music_app_status_bar, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->music_app_status_bar, lv_color_hex(0x333333), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->music_app_status_bar, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->music_app_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->music_app_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->music_app_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->music_app_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->music_app_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes music_app_wifi
    ui->music_app_wifi = lv_img_create(ui->music_app_status_bar);
    lv_obj_add_flag(ui->music_app_wifi, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->music_app_wifi, &_wifi_alpha_16x16);
    lv_img_set_pivot(ui->music_app_wifi, 50,50);
    lv_img_set_angle(ui->music_app_wifi, 0);
    lv_obj_set_pos(ui->music_app_wifi, 456, 0);
    lv_obj_set_size(ui->music_app_wifi, 16, 16);

    //Write style for music_app_wifi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->music_app_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->music_app_wifi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->music_app_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->music_app_wifi, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes music_app_voice_on
    ui->music_app_voice_on = lv_img_create(ui->music_app_status_bar);
    lv_obj_add_flag(ui->music_app_voice_on, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->music_app_voice_on, &_voice_on_alpha_16x16);
    lv_img_set_pivot(ui->music_app_voice_on, 50,50);
    lv_img_set_angle(ui->music_app_voice_on, 0);
    lv_obj_set_pos(ui->music_app_voice_on, 434, 0);
    lv_obj_set_size(ui->music_app_voice_on, 16, 16);
    lv_obj_add_flag(ui->music_app_voice_on, LV_OBJ_FLAG_HIDDEN);

    //Write style for music_app_voice_on, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->music_app_voice_on, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->music_app_voice_on, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->music_app_voice_on, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->music_app_voice_on, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes music_app_voice_off
    ui->music_app_voice_off = lv_img_create(ui->music_app_status_bar);
    lv_obj_add_flag(ui->music_app_voice_off, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->music_app_voice_off, &_voice_off_alpha_16x16);
    lv_img_set_pivot(ui->music_app_voice_off, 50,50);
    lv_img_set_angle(ui->music_app_voice_off, 0);
    lv_obj_set_pos(ui->music_app_voice_off, 434, 0);
    lv_obj_set_size(ui->music_app_voice_off, 16, 16);

    //Write style for music_app_voice_off, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->music_app_voice_off, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->music_app_voice_off, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->music_app_voice_off, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->music_app_voice_off, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes music_app_time
    static bool music_app_time_timer_enabled = false;
    ui->music_app_time = lv_dclock_create(ui->music_app_status_bar, "11:25");
    if (!music_app_time_timer_enabled) {
        lv_timer_create(music_app_time_timer, 1000, NULL);
        music_app_time_timer_enabled = true;
    }
    lv_obj_set_pos(ui->music_app_time, 220, 0);
    lv_obj_set_size(ui->music_app_time, 46, 16);

    //Write style for music_app_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->music_app_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->music_app_time, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->music_app_time, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->music_app_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->music_app_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->music_app_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->music_app_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->music_app_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->music_app_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->music_app_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->music_app_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->music_app_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes music_app_date
    ui->music_app_date = lv_label_create(ui->music_app_status_bar);
    lv_label_set_text(ui->music_app_date, "2023/07/31");
    lv_obj_set_style_text_align(ui->music_app_date, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_add_flag(ui->music_app_date, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ui->music_app_date, music_app_date_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_set_pos(ui->music_app_date, 0, 1);
    lv_obj_set_size(ui->music_app_date, 112, 16);

    //Write style for music_app_date, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->music_app_date, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->music_app_date, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->music_app_date, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->music_app_date, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->music_app_date, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->music_app_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->music_app_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->music_app_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->music_app_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->music_app_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->music_app_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->music_app_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes music_app_music_list
    ui->music_app_music_list = lv_obj_create(ui->music_app);
    lv_obj_set_pos(ui->music_app_music_list, 0, 16);
    lv_obj_set_size(ui->music_app_music_list, 240, 304);
    lv_obj_set_scrollbar_mode(ui->music_app_music_list, LV_SCROLLBAR_MODE_OFF);

    //Write style for music_app_music_list, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->music_app_music_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->music_app_music_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->music_app_music_list, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->music_app_music_list, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->music_app_music_list, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->music_app_music_list, lv_color_hex(0x91ed74), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->music_app_music_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->music_app_music_list, 121, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->music_app_music_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->music_app_music_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->music_app_music_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->music_app_music_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->music_app_music_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes music_app_music_play
    ui->music_app_music_play = lv_obj_create(ui->music_app);
    lv_obj_set_pos(ui->music_app_music_play, 240, 16);
    lv_obj_set_size(ui->music_app_music_play, 240, 304);
    lv_obj_set_scrollbar_mode(ui->music_app_music_play, LV_SCROLLBAR_MODE_OFF);

    //Write style for music_app_music_play, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->music_app_music_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->music_app_music_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->music_app_music_play, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->music_app_music_play, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->music_app_music_play, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->music_app_music_play, lv_color_hex(0x91ed74), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->music_app_music_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->music_app_music_play, 121, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->music_app_music_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->music_app_music_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->music_app_music_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->music_app_music_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->music_app_music_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes music_app_img_1
    ui->music_app_img_1 = lv_img_create(ui->music_app);
    lv_obj_add_flag(ui->music_app_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_pivot(ui->music_app_img_1, 50,50);
    lv_img_set_angle(ui->music_app_img_1, 0);
    lv_obj_set_pos(ui->music_app_img_1, 293, 78);
    lv_obj_set_size(ui->music_app_img_1, 100, 100);

    //Write style for music_app_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->music_app_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->music_app_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->music_app_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->music_app_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes music_app_list_1
    ui->music_app_list_1 = lv_list_create(ui->music_app);
    ui->music_app_list_1_item0 = lv_list_add_btn(ui->music_app_list_1, LV_SYMBOL_SAVE, "save");
    ui->music_app_list_1_item1 = lv_list_add_btn(ui->music_app_list_1, LV_SYMBOL_SAVE, "save_1");
    ui->music_app_list_1_item2 = lv_list_add_btn(ui->music_app_list_1, LV_SYMBOL_SAVE, "save_2");
    lv_obj_set_pos(ui->music_app_list_1, 26, 46);
    lv_obj_set_size(ui->music_app_list_1, 175, 232);
    lv_obj_set_scrollbar_mode(ui->music_app_list_1, LV_SCROLLBAR_MODE_OFF);

    //Write style state: LV_STATE_DEFAULT for &style_music_app_list_1_main_main_default
    static lv_style_t style_music_app_list_1_main_main_default;
    ui_init_style(&style_music_app_list_1_main_main_default);

    lv_style_set_pad_top(&style_music_app_list_1_main_main_default, 5);
    lv_style_set_pad_left(&style_music_app_list_1_main_main_default, 5);
    lv_style_set_pad_right(&style_music_app_list_1_main_main_default, 5);
    lv_style_set_pad_bottom(&style_music_app_list_1_main_main_default, 5);
    lv_style_set_bg_opa(&style_music_app_list_1_main_main_default, 255);
    lv_style_set_bg_color(&style_music_app_list_1_main_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_music_app_list_1_main_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_music_app_list_1_main_main_default, 1);
    lv_style_set_border_opa(&style_music_app_list_1_main_main_default, 255);
    lv_style_set_border_color(&style_music_app_list_1_main_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_music_app_list_1_main_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_music_app_list_1_main_main_default, 3);
    lv_style_set_shadow_width(&style_music_app_list_1_main_main_default, 0);
    lv_obj_add_style(ui->music_app_list_1, &style_music_app_list_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_music_app_list_1_main_scrollbar_default
    static lv_style_t style_music_app_list_1_main_scrollbar_default;
    ui_init_style(&style_music_app_list_1_main_scrollbar_default);

    lv_style_set_radius(&style_music_app_list_1_main_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_music_app_list_1_main_scrollbar_default, 255);
    lv_style_set_bg_color(&style_music_app_list_1_main_scrollbar_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_music_app_list_1_main_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->music_app_list_1, &style_music_app_list_1_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_music_app_list_1_extra_btns_main_default
    static lv_style_t style_music_app_list_1_extra_btns_main_default;
    ui_init_style(&style_music_app_list_1_extra_btns_main_default);

    lv_style_set_pad_top(&style_music_app_list_1_extra_btns_main_default, 5);
    lv_style_set_pad_left(&style_music_app_list_1_extra_btns_main_default, 5);
    lv_style_set_pad_right(&style_music_app_list_1_extra_btns_main_default, 5);
    lv_style_set_pad_bottom(&style_music_app_list_1_extra_btns_main_default, 5);
    lv_style_set_border_width(&style_music_app_list_1_extra_btns_main_default, 0);
    lv_style_set_text_color(&style_music_app_list_1_extra_btns_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_music_app_list_1_extra_btns_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_music_app_list_1_extra_btns_main_default, 255);
    lv_style_set_radius(&style_music_app_list_1_extra_btns_main_default, 3);
    lv_style_set_bg_opa(&style_music_app_list_1_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_music_app_list_1_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_music_app_list_1_extra_btns_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->music_app_list_1_item2, &style_music_app_list_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->music_app_list_1_item1, &style_music_app_list_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->music_app_list_1_item0, &style_music_app_list_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_music_app_list_1_extra_texts_main_default
    static lv_style_t style_music_app_list_1_extra_texts_main_default;
    ui_init_style(&style_music_app_list_1_extra_texts_main_default);

    lv_style_set_pad_top(&style_music_app_list_1_extra_texts_main_default, 5);
    lv_style_set_pad_left(&style_music_app_list_1_extra_texts_main_default, 5);
    lv_style_set_pad_right(&style_music_app_list_1_extra_texts_main_default, 5);
    lv_style_set_pad_bottom(&style_music_app_list_1_extra_texts_main_default, 5);
    lv_style_set_border_width(&style_music_app_list_1_extra_texts_main_default, 0);
    lv_style_set_text_color(&style_music_app_list_1_extra_texts_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_music_app_list_1_extra_texts_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_music_app_list_1_extra_texts_main_default, 255);
    lv_style_set_radius(&style_music_app_list_1_extra_texts_main_default, 3);
    lv_style_set_transform_width(&style_music_app_list_1_extra_texts_main_default, 0);
    lv_style_set_bg_opa(&style_music_app_list_1_extra_texts_main_default, 255);
    lv_style_set_bg_color(&style_music_app_list_1_extra_texts_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_music_app_list_1_extra_texts_main_default, LV_GRAD_DIR_NONE);

    //The custom code of music_app.


    //Update current screen layout.
    lv_obj_update_layout(ui->music_app);

    //Init events for screen.
    events_init_music_app(ui);
}
