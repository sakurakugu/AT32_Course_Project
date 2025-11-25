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



void setup_scr_setting_app(lv_ui *ui)
{
    //Write codes setting_app
    ui->setting_app = lv_obj_create(NULL);
    lv_obj_set_size(ui->setting_app, 480, 320);
    lv_obj_set_scrollbar_mode(ui->setting_app, LV_SCROLLBAR_MODE_OFF);

    //Write style for setting_app, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->setting_app, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_app_setting_page
    ui->setting_app_setting_page = lv_menu_create(ui->setting_app);

    //Create sidebar page for menu setting_app_setting_page
    ui->setting_app_setting_page_sidebar_page = lv_menu_page_create(ui->setting_app_setting_page, "设置");
    lv_menu_set_sidebar_page(ui->setting_app_setting_page, ui->setting_app_setting_page_sidebar_page);
    lv_obj_set_scrollbar_mode(ui->setting_app_setting_page_sidebar_page, LV_SCROLLBAR_MODE_OFF);

    //Create subpage for setting_app_setting_page
    ui->setting_app_setting_page_subpage_1 = lv_menu_page_create(ui->setting_app_setting_page, NULL);
    ui->setting_app_setting_page_cont_1 = lv_menu_cont_create(ui->setting_app_setting_page_sidebar_page);
    ui->setting_app_setting_page_label_1 = lv_label_create(ui->setting_app_setting_page_cont_1);
    lv_label_set_text(ui->setting_app_setting_page_label_1, "网络");
    lv_obj_set_size(ui->setting_app_setting_page_label_1, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_scrollbar_mode(ui->setting_app_setting_page_subpage_1, LV_SCROLLBAR_MODE_OFF);
    lv_menu_set_load_page_event(ui->setting_app_setting_page, ui->setting_app_setting_page_cont_1, ui->setting_app_setting_page_subpage_1);

    //Create subpage for setting_app_setting_page
    ui->setting_app_setting_page_subpage_2 = lv_menu_page_create(ui->setting_app_setting_page, NULL);
    ui->setting_app_setting_page_cont_2 = lv_menu_cont_create(ui->setting_app_setting_page_sidebar_page);
    ui->setting_app_setting_page_label_2 = lv_label_create(ui->setting_app_setting_page_cont_2);
    lv_label_set_text(ui->setting_app_setting_page_label_2, "显示");
    lv_obj_set_size(ui->setting_app_setting_page_label_2, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_scrollbar_mode(ui->setting_app_setting_page_subpage_2, LV_SCROLLBAR_MODE_OFF);
    lv_menu_set_load_page_event(ui->setting_app_setting_page, ui->setting_app_setting_page_cont_2, ui->setting_app_setting_page_subpage_2);

    //Create subpage for setting_app_setting_page
    ui->setting_app_setting_page_subpage_3 = lv_menu_page_create(ui->setting_app_setting_page, NULL);
    ui->setting_app_setting_page_cont_3 = lv_menu_cont_create(ui->setting_app_setting_page_sidebar_page);
    ui->setting_app_setting_page_label_3 = lv_label_create(ui->setting_app_setting_page_cont_3);
    lv_label_set_text(ui->setting_app_setting_page_label_3, "时间");
    lv_obj_set_size(ui->setting_app_setting_page_label_3, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_scrollbar_mode(ui->setting_app_setting_page_subpage_3, LV_SCROLLBAR_MODE_OFF);
    lv_menu_set_load_page_event(ui->setting_app_setting_page, ui->setting_app_setting_page_cont_3, ui->setting_app_setting_page_subpage_3);

    //Create subpage for setting_app_setting_page
    ui->setting_app_setting_page_subpage_4 = lv_menu_page_create(ui->setting_app_setting_page, NULL);
    ui->setting_app_setting_page_cont_4 = lv_menu_cont_create(ui->setting_app_setting_page_sidebar_page);
    ui->setting_app_setting_page_label_4 = lv_label_create(ui->setting_app_setting_page_cont_4);
    lv_label_set_text(ui->setting_app_setting_page_label_4, "声音");
    lv_obj_set_size(ui->setting_app_setting_page_label_4, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_scrollbar_mode(ui->setting_app_setting_page_subpage_4, LV_SCROLLBAR_MODE_OFF);
    lv_menu_set_load_page_event(ui->setting_app_setting_page, ui->setting_app_setting_page_cont_4, ui->setting_app_setting_page_subpage_4);
    lv_event_send(ui->setting_app_setting_page_cont_1, LV_EVENT_CLICKED, NULL);
    lv_obj_set_pos(ui->setting_app_setting_page, 0, 16);
    lv_obj_set_size(ui->setting_app_setting_page, 480, 304);
    lv_obj_set_scrollbar_mode(ui->setting_app_setting_page, LV_SCROLLBAR_MODE_OFF);

    //Write style for setting_app_setting_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->setting_app_setting_page, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->setting_app_setting_page, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->setting_app_setting_page, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_app_setting_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_app_setting_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_setting_app_setting_page_extra_sidebar_page_main_default
    static lv_style_t style_setting_app_setting_page_extra_sidebar_page_main_default;
    ui_init_style(&style_setting_app_setting_page_extra_sidebar_page_main_default);

    lv_style_set_bg_opa(&style_setting_app_setting_page_extra_sidebar_page_main_default, 255);
    lv_style_set_bg_color(&style_setting_app_setting_page_extra_sidebar_page_main_default, lv_color_hex(0xdaf2f8));
    lv_style_set_bg_grad_dir(&style_setting_app_setting_page_extra_sidebar_page_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_radius(&style_setting_app_setting_page_extra_sidebar_page_main_default, 0);
    lv_obj_add_style(ui->setting_app_setting_page_sidebar_page, &style_setting_app_setting_page_extra_sidebar_page_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_setting_app_setting_page_extra_option_btns_main_default
    static lv_style_t style_setting_app_setting_page_extra_option_btns_main_default;
    ui_init_style(&style_setting_app_setting_page_extra_option_btns_main_default);

    lv_style_set_text_color(&style_setting_app_setting_page_extra_option_btns_main_default, lv_color_hex(0x151212));
    lv_style_set_text_font(&style_setting_app_setting_page_extra_option_btns_main_default, &lv_font_SourceHanSerifSC_Regular_16);
    lv_style_set_text_opa(&style_setting_app_setting_page_extra_option_btns_main_default, 255);
    lv_style_set_text_align(&style_setting_app_setting_page_extra_option_btns_main_default, LV_TEXT_ALIGN_CENTER);
    lv_style_set_pad_top(&style_setting_app_setting_page_extra_option_btns_main_default, 10);
    lv_style_set_pad_bottom(&style_setting_app_setting_page_extra_option_btns_main_default, 10);
    lv_obj_add_style(ui->setting_app_setting_page_cont_4, &style_setting_app_setting_page_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->setting_app_setting_page_cont_3, &style_setting_app_setting_page_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->setting_app_setting_page_cont_2, &style_setting_app_setting_page_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->setting_app_setting_page_cont_1, &style_setting_app_setting_page_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_setting_app_setting_page_extra_option_btns_main_checked
    static lv_style_t style_setting_app_setting_page_extra_option_btns_main_checked;
    ui_init_style(&style_setting_app_setting_page_extra_option_btns_main_checked);

    lv_style_set_text_color(&style_setting_app_setting_page_extra_option_btns_main_checked, lv_color_hex(0x9ab700));
    lv_style_set_text_font(&style_setting_app_setting_page_extra_option_btns_main_checked, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_setting_app_setting_page_extra_option_btns_main_checked, 255);
    lv_style_set_text_align(&style_setting_app_setting_page_extra_option_btns_main_checked, LV_TEXT_ALIGN_CENTER);
    lv_style_set_border_width(&style_setting_app_setting_page_extra_option_btns_main_checked, 0);
    lv_style_set_radius(&style_setting_app_setting_page_extra_option_btns_main_checked, 0);
    lv_style_set_bg_opa(&style_setting_app_setting_page_extra_option_btns_main_checked, 60);
    lv_style_set_bg_color(&style_setting_app_setting_page_extra_option_btns_main_checked, lv_color_hex(0x00e0b8));
    lv_style_set_bg_grad_dir(&style_setting_app_setting_page_extra_option_btns_main_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->setting_app_setting_page_cont_4, &style_setting_app_setting_page_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_add_style(ui->setting_app_setting_page_cont_3, &style_setting_app_setting_page_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_add_style(ui->setting_app_setting_page_cont_2, &style_setting_app_setting_page_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_add_style(ui->setting_app_setting_page_cont_1, &style_setting_app_setting_page_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style state: LV_STATE_DEFAULT for &style_setting_app_setting_page_extra_main_title_main_default
    static lv_style_t style_setting_app_setting_page_extra_main_title_main_default;
    ui_init_style(&style_setting_app_setting_page_extra_main_title_main_default);

    lv_style_set_text_color(&style_setting_app_setting_page_extra_main_title_main_default, lv_color_hex(0x41485a));
    lv_style_set_text_font(&style_setting_app_setting_page_extra_main_title_main_default, &lv_font_SourceHanSerifSC_Regular_16);
    lv_style_set_text_opa(&style_setting_app_setting_page_extra_main_title_main_default, 255);
    lv_style_set_text_align(&style_setting_app_setting_page_extra_main_title_main_default, LV_TEXT_ALIGN_CENTER);
    lv_style_set_bg_opa(&style_setting_app_setting_page_extra_main_title_main_default, 255);
    lv_style_set_bg_color(&style_setting_app_setting_page_extra_main_title_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_setting_app_setting_page_extra_main_title_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_pad_top(&style_setting_app_setting_page_extra_main_title_main_default, 0);
    lv_style_set_pad_bottom(&style_setting_app_setting_page_extra_main_title_main_default, 0);
    lv_menu_t * setting_app_setting_page_menu= (lv_menu_t *)ui->setting_app_setting_page;
    lv_obj_t * setting_app_setting_page_title = setting_app_setting_page_menu->sidebar_header_title;
    lv_obj_set_size(setting_app_setting_page_title, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_add_style(lv_menu_get_sidebar_header(ui->setting_app_setting_page), &style_setting_app_setting_page_extra_main_title_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);



    //Write codes setting_app_placeholder_1
    ui->setting_app_placeholder_1 = lv_obj_create(ui->setting_app_setting_page_subpage_1);
    lv_obj_set_pos(ui->setting_app_placeholder_1, 46, -1);
    lv_obj_set_size(ui->setting_app_placeholder_1, 246, 20);
    lv_obj_set_scrollbar_mode(ui->setting_app_placeholder_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for setting_app_placeholder_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->setting_app_placeholder_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_app_placeholder_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->setting_app_placeholder_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->setting_app_placeholder_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->setting_app_placeholder_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->setting_app_placeholder_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->setting_app_placeholder_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_app_placeholder_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_app_wifi_name_text
    ui->setting_app_wifi_name_text = lv_label_create(ui->setting_app_setting_page_subpage_1);
    lv_label_set_text(ui->setting_app_wifi_name_text, "Wifi名称:");
    lv_label_set_long_mode(ui->setting_app_wifi_name_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->setting_app_wifi_name_text, 45, -1);
    lv_obj_set_size(ui->setting_app_wifi_name_text, 246, 20);

    //Write style for setting_app_wifi_name_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->setting_app_wifi_name_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_app_wifi_name_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->setting_app_wifi_name_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->setting_app_wifi_name_text, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->setting_app_wifi_name_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->setting_app_wifi_name_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->setting_app_wifi_name_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->setting_app_wifi_name_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->setting_app_wifi_name_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->setting_app_wifi_name_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->setting_app_wifi_name_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->setting_app_wifi_name_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->setting_app_wifi_name_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_app_wifi_name_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_app_wifi_name_input
    ui->setting_app_wifi_name_input = lv_textarea_create(ui->setting_app_setting_page_subpage_1);
    lv_textarea_set_text(ui->setting_app_wifi_name_input, "");
    lv_textarea_set_placeholder_text(ui->setting_app_wifi_name_input, "");
    lv_textarea_set_password_bullet(ui->setting_app_wifi_name_input, "*");
    lv_textarea_set_password_mode(ui->setting_app_wifi_name_input, false);
    lv_textarea_set_one_line(ui->setting_app_wifi_name_input, true);
    lv_textarea_set_accepted_chars(ui->setting_app_wifi_name_input, "");
    lv_textarea_set_max_length(ui->setting_app_wifi_name_input, 32);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->setting_app_wifi_name_input, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->setting_app_wifi_name_input, 45, 0);
    lv_obj_set_size(ui->setting_app_wifi_name_input, 246, 32);

    //Write style for setting_app_wifi_name_input, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->setting_app_wifi_name_input, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->setting_app_wifi_name_input, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->setting_app_wifi_name_input, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->setting_app_wifi_name_input, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->setting_app_wifi_name_input, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->setting_app_wifi_name_input, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->setting_app_wifi_name_input, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->setting_app_wifi_name_input, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->setting_app_wifi_name_input, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->setting_app_wifi_name_input, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->setting_app_wifi_name_input, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->setting_app_wifi_name_input, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_app_wifi_name_input, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->setting_app_wifi_name_input, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->setting_app_wifi_name_input, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->setting_app_wifi_name_input, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_app_wifi_name_input, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for setting_app_wifi_name_input, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->setting_app_wifi_name_input, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->setting_app_wifi_name_input, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->setting_app_wifi_name_input, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_app_wifi_name_input, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes setting_app_wifi_password_text
    ui->setting_app_wifi_password_text = lv_label_create(ui->setting_app_setting_page_subpage_1);
    lv_label_set_text(ui->setting_app_wifi_password_text, "Wifi密码:");
    lv_label_set_long_mode(ui->setting_app_wifi_password_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->setting_app_wifi_password_text, 225, 92);
    lv_obj_set_size(ui->setting_app_wifi_password_text, 246, 40);

    //Write style for setting_app_wifi_password_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->setting_app_wifi_password_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_app_wifi_password_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->setting_app_wifi_password_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->setting_app_wifi_password_text, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->setting_app_wifi_password_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->setting_app_wifi_password_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->setting_app_wifi_password_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->setting_app_wifi_password_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->setting_app_wifi_password_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->setting_app_wifi_password_text, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->setting_app_wifi_password_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->setting_app_wifi_password_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->setting_app_wifi_password_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_app_wifi_password_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_app_wifi_password_input
    ui->setting_app_wifi_password_input = lv_textarea_create(ui->setting_app_setting_page_subpage_1);
    lv_textarea_set_text(ui->setting_app_wifi_password_input, "");
    lv_textarea_set_placeholder_text(ui->setting_app_wifi_password_input, "");
    lv_textarea_set_password_bullet(ui->setting_app_wifi_password_input, "*");
    lv_textarea_set_password_mode(ui->setting_app_wifi_password_input, true);
    lv_textarea_set_one_line(ui->setting_app_wifi_password_input, true);
    lv_textarea_set_accepted_chars(ui->setting_app_wifi_password_input, "");
    lv_textarea_set_max_length(ui->setting_app_wifi_password_input, 32);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->setting_app_wifi_password_input, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->setting_app_wifi_password_input, 58, 2);
    lv_obj_set_size(ui->setting_app_wifi_password_input, 246, 32);

    //Write style for setting_app_wifi_password_input, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->setting_app_wifi_password_input, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->setting_app_wifi_password_input, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->setting_app_wifi_password_input, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->setting_app_wifi_password_input, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->setting_app_wifi_password_input, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->setting_app_wifi_password_input, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->setting_app_wifi_password_input, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->setting_app_wifi_password_input, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->setting_app_wifi_password_input, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->setting_app_wifi_password_input, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->setting_app_wifi_password_input, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->setting_app_wifi_password_input, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_app_wifi_password_input, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->setting_app_wifi_password_input, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->setting_app_wifi_password_input, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->setting_app_wifi_password_input, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_app_wifi_password_input, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for setting_app_wifi_password_input, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->setting_app_wifi_password_input, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->setting_app_wifi_password_input, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->setting_app_wifi_password_input, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_app_wifi_password_input, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes setting_app_placeholder_2
    ui->setting_app_placeholder_2 = lv_obj_create(ui->setting_app_setting_page_subpage_1);
    lv_obj_set_pos(ui->setting_app_placeholder_2, 95, 281);
    lv_obj_set_size(ui->setting_app_placeholder_2, 246, 60);
    lv_obj_set_scrollbar_mode(ui->setting_app_placeholder_2, LV_SCROLLBAR_MODE_OFF);

    //Write style for setting_app_placeholder_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->setting_app_placeholder_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_app_placeholder_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->setting_app_placeholder_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->setting_app_placeholder_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->setting_app_placeholder_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->setting_app_placeholder_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->setting_app_placeholder_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_app_placeholder_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_app_wifi_link_btn
    ui->setting_app_wifi_link_btn = lv_btn_create(ui->setting_app_setting_page_subpage_1);
    ui->setting_app_wifi_link_btn_label = lv_label_create(ui->setting_app_wifi_link_btn);
    lv_label_set_text(ui->setting_app_wifi_link_btn_label, "连接");
    lv_label_set_long_mode(ui->setting_app_wifi_link_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->setting_app_wifi_link_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->setting_app_wifi_link_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->setting_app_wifi_link_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->setting_app_wifi_link_btn, 190, 135);
    lv_obj_set_size(ui->setting_app_wifi_link_btn, 246, 40);

    //Write style for setting_app_wifi_link_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->setting_app_wifi_link_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->setting_app_wifi_link_btn, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->setting_app_wifi_link_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->setting_app_wifi_link_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_app_wifi_link_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_app_wifi_link_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->setting_app_wifi_link_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->setting_app_wifi_link_btn, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->setting_app_wifi_link_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->setting_app_wifi_link_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);



    //Write codes setting_app_light_text
    ui->setting_app_light_text = lv_label_create(ui->setting_app_setting_page_subpage_2);
    lv_label_set_text(ui->setting_app_light_text, "亮度:");
    lv_label_set_long_mode(ui->setting_app_light_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->setting_app_light_text, 67, 5);
    lv_obj_set_size(ui->setting_app_light_text, 246, 60);

    //Write style for setting_app_light_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->setting_app_light_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_app_light_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->setting_app_light_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->setting_app_light_text, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->setting_app_light_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->setting_app_light_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->setting_app_light_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->setting_app_light_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->setting_app_light_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->setting_app_light_text, 30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->setting_app_light_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->setting_app_light_text, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->setting_app_light_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_app_light_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_app_light_slider
    ui->setting_app_light_slider = lv_slider_create(ui->setting_app_setting_page_subpage_2);
    lv_slider_set_range(ui->setting_app_light_slider, 0, 100);
    lv_slider_set_mode(ui->setting_app_light_slider, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->setting_app_light_slider, 50, LV_ANIM_OFF);
    lv_obj_set_pos(ui->setting_app_light_slider, 26, 156);
    lv_obj_set_size(ui->setting_app_light_slider, 253, 19);

    //Write style for setting_app_light_slider, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->setting_app_light_slider, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->setting_app_light_slider, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->setting_app_light_slider, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_app_light_slider, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->setting_app_light_slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_app_light_slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for setting_app_light_slider, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->setting_app_light_slider, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->setting_app_light_slider, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->setting_app_light_slider, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_app_light_slider, 8, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for setting_app_light_slider, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->setting_app_light_slider, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->setting_app_light_slider, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->setting_app_light_slider, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_app_light_slider, 8, LV_PART_KNOB|LV_STATE_DEFAULT);



    //Write codes setting_app_sync_net_time_text
    ui->setting_app_sync_net_time_text = lv_label_create(ui->setting_app_setting_page_subpage_3);
    lv_label_set_text(ui->setting_app_sync_net_time_text, "是否同步网络时间:");
    lv_label_set_long_mode(ui->setting_app_sync_net_time_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->setting_app_sync_net_time_text, 106, 24);
    lv_obj_set_size(ui->setting_app_sync_net_time_text, 246, 57);

    //Write style for setting_app_sync_net_time_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->setting_app_sync_net_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_app_sync_net_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->setting_app_sync_net_time_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->setting_app_sync_net_time_text, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->setting_app_sync_net_time_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->setting_app_sync_net_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->setting_app_sync_net_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->setting_app_sync_net_time_text, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->setting_app_sync_net_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->setting_app_sync_net_time_text, 30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->setting_app_sync_net_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->setting_app_sync_net_time_text, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->setting_app_sync_net_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_app_sync_net_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_app_sync_net_time_sw
    ui->setting_app_sync_net_time_sw = lv_switch_create(ui->setting_app_setting_page_subpage_3);
    lv_obj_set_pos(ui->setting_app_sync_net_time_sw, 148, 57);
    lv_obj_set_size(ui->setting_app_sync_net_time_sw, 40, 20);

    //Write style for setting_app_sync_net_time_sw, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->setting_app_sync_net_time_sw, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->setting_app_sync_net_time_sw, lv_color_hex(0xe6e2e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->setting_app_sync_net_time_sw, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->setting_app_sync_net_time_sw, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_app_sync_net_time_sw, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_app_sync_net_time_sw, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for setting_app_sync_net_time_sw, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->setting_app_sync_net_time_sw, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->setting_app_sync_net_time_sw, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->setting_app_sync_net_time_sw, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->setting_app_sync_net_time_sw, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    //Write style for setting_app_sync_net_time_sw, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->setting_app_sync_net_time_sw, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->setting_app_sync_net_time_sw, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->setting_app_sync_net_time_sw, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->setting_app_sync_net_time_sw, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_app_sync_net_time_sw, 10, LV_PART_KNOB|LV_STATE_DEFAULT);



    //Write codes setting_app_sound_text
    ui->setting_app_sound_text = lv_label_create(ui->setting_app_setting_page_subpage_4);
    lv_label_set_text(ui->setting_app_sound_text, "是否打开声音:");
    lv_label_set_long_mode(ui->setting_app_sound_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->setting_app_sound_text, 110, 60);
    lv_obj_set_size(ui->setting_app_sound_text, 246, 57);

    //Write style for setting_app_sound_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->setting_app_sound_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_app_sound_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->setting_app_sound_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->setting_app_sound_text, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->setting_app_sound_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->setting_app_sound_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->setting_app_sound_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->setting_app_sound_text, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->setting_app_sound_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->setting_app_sound_text, 30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->setting_app_sound_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->setting_app_sound_text, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->setting_app_sound_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_app_sound_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_app_sound_sw
    ui->setting_app_sound_sw = lv_switch_create(ui->setting_app_setting_page_subpage_4);
    lv_obj_set_pos(ui->setting_app_sound_sw, 73, 65);
    lv_obj_set_size(ui->setting_app_sound_sw, 40, 20);

    //Write style for setting_app_sound_sw, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->setting_app_sound_sw, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->setting_app_sound_sw, lv_color_hex(0xe6e2e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->setting_app_sound_sw, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->setting_app_sound_sw, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_app_sound_sw, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_app_sound_sw, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for setting_app_sound_sw, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->setting_app_sound_sw, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->setting_app_sound_sw, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->setting_app_sound_sw, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->setting_app_sound_sw, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    //Write style for setting_app_sound_sw, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->setting_app_sound_sw, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->setting_app_sound_sw, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->setting_app_sound_sw, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->setting_app_sound_sw, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_app_sound_sw, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //The custom code of setting_app.
#ifdef KEIL_COMPILE
    // 绑定设置页“连接”按钮事件（读取输入并异步连接Wi‑Fi）
    lv_obj_add_event_cb(guider_ui.setting_app_wifi_link_btn, setting_app_wifi_link_btn_event_handler, LV_EVENT_CLICKED, &guider_ui);
    // 绑定亮度滑块事件
    lv_obj_add_event_cb(guider_ui.setting_app_light_slider, setting_app_light_slider_event_handler, LV_EVENT_VALUE_CHANGED, &guider_ui);
    // 绑定“同步网络时间”开关事件
    lv_obj_add_event_cb(guider_ui.setting_app_sync_net_time_sw, setting_app_sync_net_time_sw_event_handler, LV_EVENT_VALUE_CHANGED, &guider_ui);
    // 绑定“声音开关”事件
    lv_obj_add_event_cb(guider_ui.setting_app_sound_sw, setting_app_sound_sw_event_handler, LV_EVENT_VALUE_CHANGED, &guider_ui);
    lv_obj_add_state(ui->setting_app_sound_sw, LV_STATE_CHECKED);
    // 修复字体错误
    lv_style_set_text_font(&style_setting_app_setting_page_extra_option_btns_main_checked, &lv_font_SourceHanSerifSC_Regular_16);
#endif

    //Update current screen layout.
    lv_obj_update_layout(ui->setting_app);

    //Init events for screen.
    events_init_setting_app(ui);
}
