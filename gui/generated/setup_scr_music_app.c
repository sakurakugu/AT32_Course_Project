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



void setup_scr_music_app(lv_ui *ui)
{
    //Write codes music_app
    ui->music_app = lv_obj_create(NULL);
    lv_obj_set_size(ui->music_app, 480, 320);
    lv_obj_set_scrollbar_mode(ui->music_app, LV_SCROLLBAR_MODE_OFF);

    //Write style for music_app, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->music_app, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes music_app_music_page
    ui->music_app_music_page = lv_obj_create(ui->music_app);
    lv_obj_set_pos(ui->music_app_music_page, 0, 16);
    lv_obj_set_size(ui->music_app_music_page, 480, 304);
    lv_obj_set_scrollbar_mode(ui->music_app_music_page, LV_SCROLLBAR_MODE_OFF);

    //Write style for music_app_music_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->music_app_music_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->music_app_music_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->music_app_music_page, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->music_app_music_page, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->music_app_music_page, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->music_app_music_page, lv_color_hex(0x91ed74), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->music_app_music_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->music_app_music_page, 121, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->music_app_music_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->music_app_music_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->music_app_music_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->music_app_music_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->music_app_music_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes music_app_music_list
    ui->music_app_music_list = lv_list_create(ui->music_app_music_page);
    ui->music_app_music_list_item0 = lv_list_add_btn(ui->music_app_music_list, LV_SYMBOL_SAVE, "红尘情歌");
    ui->music_app_music_list_item1 = lv_list_add_btn(ui->music_app_music_list, LV_SYMBOL_SAVE, "荷塘月色");
    ui->music_app_music_list_item2 = lv_list_add_btn(ui->music_app_music_list, LV_SYMBOL_SAVE, "沉默是金");
    lv_obj_set_pos(ui->music_app_music_list, 26, 31);
    lv_obj_set_size(ui->music_app_music_list, 175, 247);
    lv_obj_set_scrollbar_mode(ui->music_app_music_list, LV_SCROLLBAR_MODE_OFF);

    //Write style state: LV_STATE_DEFAULT for &style_music_app_music_list_main_main_default
    static lv_style_t style_music_app_music_list_main_main_default;
    ui_init_style(&style_music_app_music_list_main_main_default);

    lv_style_set_pad_top(&style_music_app_music_list_main_main_default, 5);
    lv_style_set_pad_left(&style_music_app_music_list_main_main_default, 5);
    lv_style_set_pad_right(&style_music_app_music_list_main_main_default, 5);
    lv_style_set_pad_bottom(&style_music_app_music_list_main_main_default, 5);
    lv_style_set_bg_opa(&style_music_app_music_list_main_main_default, 255);
    lv_style_set_bg_color(&style_music_app_music_list_main_main_default, lv_color_hex(0xeeffbd));
    lv_style_set_bg_grad_dir(&style_music_app_music_list_main_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_music_app_music_list_main_main_default, 1);
    lv_style_set_border_opa(&style_music_app_music_list_main_main_default, 255);
    lv_style_set_border_color(&style_music_app_music_list_main_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_music_app_music_list_main_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_music_app_music_list_main_main_default, 3);
    lv_style_set_shadow_width(&style_music_app_music_list_main_main_default, 0);
    lv_obj_add_style(ui->music_app_music_list, &style_music_app_music_list_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_music_app_music_list_main_scrollbar_default
    static lv_style_t style_music_app_music_list_main_scrollbar_default;
    ui_init_style(&style_music_app_music_list_main_scrollbar_default);

    lv_style_set_radius(&style_music_app_music_list_main_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_music_app_music_list_main_scrollbar_default, 255);
    lv_style_set_bg_color(&style_music_app_music_list_main_scrollbar_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_music_app_music_list_main_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->music_app_music_list, &style_music_app_music_list_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_music_app_music_list_extra_btns_main_default
    static lv_style_t style_music_app_music_list_extra_btns_main_default;
    ui_init_style(&style_music_app_music_list_extra_btns_main_default);

    lv_style_set_pad_top(&style_music_app_music_list_extra_btns_main_default, 5);
    lv_style_set_pad_left(&style_music_app_music_list_extra_btns_main_default, 5);
    lv_style_set_pad_right(&style_music_app_music_list_extra_btns_main_default, 5);
    lv_style_set_pad_bottom(&style_music_app_music_list_extra_btns_main_default, 5);
    lv_style_set_border_width(&style_music_app_music_list_extra_btns_main_default, 0);
    lv_style_set_text_color(&style_music_app_music_list_extra_btns_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_music_app_music_list_extra_btns_main_default, &lv_font_SourceHanSerifSC_Regular_12);
    lv_style_set_text_opa(&style_music_app_music_list_extra_btns_main_default, 255);
    lv_style_set_radius(&style_music_app_music_list_extra_btns_main_default, 3);
    lv_style_set_bg_opa(&style_music_app_music_list_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_music_app_music_list_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_music_app_music_list_extra_btns_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->music_app_music_list_item2, &style_music_app_music_list_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->music_app_music_list_item1, &style_music_app_music_list_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->music_app_music_list_item0, &style_music_app_music_list_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_music_app_music_list_extra_texts_main_default
    static lv_style_t style_music_app_music_list_extra_texts_main_default;
    ui_init_style(&style_music_app_music_list_extra_texts_main_default);

    lv_style_set_pad_top(&style_music_app_music_list_extra_texts_main_default, 5);
    lv_style_set_pad_left(&style_music_app_music_list_extra_texts_main_default, 5);
    lv_style_set_pad_right(&style_music_app_music_list_extra_texts_main_default, 5);
    lv_style_set_pad_bottom(&style_music_app_music_list_extra_texts_main_default, 5);
    lv_style_set_border_width(&style_music_app_music_list_extra_texts_main_default, 0);
    lv_style_set_text_color(&style_music_app_music_list_extra_texts_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_music_app_music_list_extra_texts_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_music_app_music_list_extra_texts_main_default, 255);
    lv_style_set_radius(&style_music_app_music_list_extra_texts_main_default, 3);
    lv_style_set_transform_width(&style_music_app_music_list_extra_texts_main_default, 0);
    lv_style_set_bg_opa(&style_music_app_music_list_extra_texts_main_default, 255);
    lv_style_set_bg_color(&style_music_app_music_list_extra_texts_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_music_app_music_list_extra_texts_main_default, LV_GRAD_DIR_NONE);

    //Write codes music_app_music_recode
    ui->music_app_music_recode = lv_img_create(ui->music_app_music_page);
    lv_obj_add_flag(ui->music_app_music_recode, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->music_app_music_recode, &_music_record_alpha_160x160);
    lv_img_set_pivot(ui->music_app_music_recode, 80,80);
    lv_img_set_angle(ui->music_app_music_recode, 0);
    lv_obj_set_pos(ui->music_app_music_recode, 267, 61);
    lv_obj_set_size(ui->music_app_music_recode, 160, 160);

    //Write style for music_app_music_recode, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->music_app_music_recode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->music_app_music_recode, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->music_app_music_recode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->music_app_music_recode, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes music_app_music_stylus
    ui->music_app_music_stylus = lv_img_create(ui->music_app_music_page);
    lv_obj_add_flag(ui->music_app_music_stylus, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->music_app_music_stylus, &_music_stylus_alpha_26x126);
    lv_img_set_pivot(ui->music_app_music_stylus, 16,11);
    lv_img_set_angle(ui->music_app_music_stylus, -240);
    lv_obj_set_pos(ui->music_app_music_stylus, 394, 23);
    lv_obj_set_size(ui->music_app_music_stylus, 26, 126);

    //Write style for music_app_music_stylus, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->music_app_music_stylus, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->music_app_music_stylus, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->music_app_music_stylus, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->music_app_music_stylus, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes music_app_player_div
    ui->music_app_player_div = lv_obj_create(ui->music_app_music_page);
    lv_obj_set_pos(ui->music_app_player_div, 245, 253);
    lv_obj_set_size(ui->music_app_player_div, 200, 21);
    lv_obj_set_scrollbar_mode(ui->music_app_player_div, LV_SCROLLBAR_MODE_OFF);

    //Write style for music_app_player_div, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->music_app_player_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->music_app_player_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->music_app_player_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->music_app_player_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->music_app_player_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->music_app_player_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->music_app_player_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->music_app_player_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes music_app_music_next_song_btn
    ui->music_app_music_next_song_btn = lv_imgbtn_create(ui->music_app_player_div);
    lv_obj_add_flag(ui->music_app_music_next_song_btn, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->music_app_music_next_song_btn, LV_IMGBTN_STATE_RELEASED, NULL, &_music_next_song_alpha_16x16, NULL);
    ui->music_app_music_next_song_btn_label = lv_label_create(ui->music_app_music_next_song_btn);
    lv_label_set_text(ui->music_app_music_next_song_btn_label, "");
    lv_label_set_long_mode(ui->music_app_music_next_song_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->music_app_music_next_song_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->music_app_music_next_song_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->music_app_music_next_song_btn, 174, -1);
    lv_obj_set_size(ui->music_app_music_next_song_btn, 16, 16);

    //Write style for music_app_music_next_song_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->music_app_music_next_song_btn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->music_app_music_next_song_btn, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->music_app_music_next_song_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->music_app_music_next_song_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->music_app_music_next_song_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->music_app_music_next_song_btn, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->music_app_music_next_song_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for music_app_music_next_song_btn, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->music_app_music_next_song_btn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->music_app_music_next_song_btn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->music_app_music_next_song_btn, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->music_app_music_next_song_btn, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->music_app_music_next_song_btn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->music_app_music_next_song_btn, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for music_app_music_next_song_btn, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->music_app_music_next_song_btn, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->music_app_music_next_song_btn, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->music_app_music_next_song_btn, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->music_app_music_next_song_btn, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->music_app_music_next_song_btn, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->music_app_music_next_song_btn, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for music_app_music_next_song_btn, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->music_app_music_next_song_btn, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->music_app_music_next_song_btn, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes music_app_music_player_or_pause_btn
    ui->music_app_music_player_or_pause_btn = lv_imgbtn_create(ui->music_app_player_div);
    lv_obj_add_flag(ui->music_app_music_player_or_pause_btn, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->music_app_music_player_or_pause_btn, LV_IMGBTN_STATE_RELEASED, NULL, &_music_player_alpha_16x16, NULL);
    lv_imgbtn_set_src(ui->music_app_music_player_or_pause_btn, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_music_pause_alpha_16x16, NULL);
    ui->music_app_music_player_or_pause_btn_label = lv_label_create(ui->music_app_music_player_or_pause_btn);
    lv_label_set_text(ui->music_app_music_player_or_pause_btn_label, "");
    lv_label_set_long_mode(ui->music_app_music_player_or_pause_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->music_app_music_player_or_pause_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->music_app_music_player_or_pause_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->music_app_music_player_or_pause_btn, 96, 0);
    lv_obj_set_size(ui->music_app_music_player_or_pause_btn, 16, 16);

    //Write style for music_app_music_player_or_pause_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->music_app_music_player_or_pause_btn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->music_app_music_player_or_pause_btn, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->music_app_music_player_or_pause_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->music_app_music_player_or_pause_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->music_app_music_player_or_pause_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->music_app_music_player_or_pause_btn, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->music_app_music_player_or_pause_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for music_app_music_player_or_pause_btn, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->music_app_music_player_or_pause_btn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->music_app_music_player_or_pause_btn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->music_app_music_player_or_pause_btn, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->music_app_music_player_or_pause_btn, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->music_app_music_player_or_pause_btn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->music_app_music_player_or_pause_btn, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for music_app_music_player_or_pause_btn, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->music_app_music_player_or_pause_btn, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->music_app_music_player_or_pause_btn, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->music_app_music_player_or_pause_btn, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->music_app_music_player_or_pause_btn, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->music_app_music_player_or_pause_btn, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->music_app_music_player_or_pause_btn, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for music_app_music_player_or_pause_btn, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->music_app_music_player_or_pause_btn, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->music_app_music_player_or_pause_btn, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes music_app_music_prev_song_btn
    ui->music_app_music_prev_song_btn = lv_imgbtn_create(ui->music_app_player_div);
    lv_obj_add_flag(ui->music_app_music_prev_song_btn, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->music_app_music_prev_song_btn, LV_IMGBTN_STATE_RELEASED, NULL, &_music_prev_song_alpha_16x16, NULL);
    ui->music_app_music_prev_song_btn_label = lv_label_create(ui->music_app_music_prev_song_btn);
    lv_label_set_text(ui->music_app_music_prev_song_btn_label, "");
    lv_label_set_long_mode(ui->music_app_music_prev_song_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->music_app_music_prev_song_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->music_app_music_prev_song_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->music_app_music_prev_song_btn, 17, 0);
    lv_obj_set_size(ui->music_app_music_prev_song_btn, 16, 16);

    //Write style for music_app_music_prev_song_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->music_app_music_prev_song_btn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->music_app_music_prev_song_btn, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->music_app_music_prev_song_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->music_app_music_prev_song_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->music_app_music_prev_song_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->music_app_music_prev_song_btn, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->music_app_music_prev_song_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for music_app_music_prev_song_btn, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->music_app_music_prev_song_btn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->music_app_music_prev_song_btn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->music_app_music_prev_song_btn, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->music_app_music_prev_song_btn, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->music_app_music_prev_song_btn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->music_app_music_prev_song_btn, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for music_app_music_prev_song_btn, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->music_app_music_prev_song_btn, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->music_app_music_prev_song_btn, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->music_app_music_prev_song_btn, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->music_app_music_prev_song_btn, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->music_app_music_prev_song_btn, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->music_app_music_prev_song_btn, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for music_app_music_prev_song_btn, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->music_app_music_prev_song_btn, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->music_app_music_prev_song_btn, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //The custom code of music_app.
    // 绑定音乐列表与控制按钮事件
    lv_obj_add_event_cb(guider_ui.music_app_music_list_item0, music_list_item_event_handler, LV_EVENT_CLICKED, &guider_ui);
    lv_obj_add_event_cb(guider_ui.music_app_music_list_item1, music_list_item_event_handler, LV_EVENT_CLICKED, &guider_ui);
    lv_obj_add_event_cb(guider_ui.music_app_music_list_item2, music_list_item_event_handler, LV_EVENT_CLICKED, &guider_ui);
    lv_obj_add_event_cb(guider_ui.music_app_music_prev_song_btn, music_prev_btn_event_handler, LV_EVENT_CLICKED, &guider_ui);
    lv_obj_add_event_cb(guider_ui.music_app_music_next_song_btn, music_next_btn_event_handler, LV_EVENT_CLICKED, &guider_ui);
    lv_obj_add_event_cb(guider_ui.music_app_music_player_or_pause_btn, music_play_pause_btn_event_handler, LV_EVENT_VALUE_CHANGED, &guider_ui);

    //Update current screen layout.
    lv_obj_update_layout(ui->music_app);

    //Init events for screen.
    events_init_music_app(ui);
}
