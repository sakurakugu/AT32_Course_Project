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



int clock_app_analog_clock_1_hour_value = 3;
int clock_app_analog_clock_1_min_value = 20;
int clock_app_analog_clock_1_sec_value = 50;
lv_calendar_date_t clock_app_calendar_today;
lv_calendar_date_t clock_app_calendar_highlihted_days[1];
void setup_scr_clock_app(lv_ui *ui)
{
    //Write codes clock_app
    ui->clock_app = lv_obj_create(NULL);
    lv_obj_set_size(ui->clock_app, 480, 320);
    lv_obj_set_scrollbar_mode(ui->clock_app, LV_SCROLLBAR_MODE_OFF);

    //Write style for clock_app, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->clock_app, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes clock_app_clock_page
    ui->clock_app_clock_page = lv_menu_create(ui->clock_app);

    //Create sidebar page for menu clock_app_clock_page
    ui->clock_app_clock_page_sidebar_page = lv_menu_page_create(ui->clock_app_clock_page, "时间");
    lv_menu_set_sidebar_page(ui->clock_app_clock_page, ui->clock_app_clock_page_sidebar_page);
    lv_obj_set_scrollbar_mode(ui->clock_app_clock_page_sidebar_page, LV_SCROLLBAR_MODE_OFF);

    //Create subpage for clock_app_clock_page
    ui->clock_app_clock_page_subpage_1 = lv_menu_page_create(ui->clock_app_clock_page, NULL);
    ui->clock_app_clock_page_cont_1 = lv_menu_cont_create(ui->clock_app_clock_page_sidebar_page);
    ui->clock_app_clock_page_label_1 = lv_label_create(ui->clock_app_clock_page_cont_1);
    lv_label_set_text(ui->clock_app_clock_page_label_1, "时钟");
    lv_obj_set_size(ui->clock_app_clock_page_label_1, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_scrollbar_mode(ui->clock_app_clock_page_subpage_1, LV_SCROLLBAR_MODE_OFF);
    lv_menu_set_load_page_event(ui->clock_app_clock_page, ui->clock_app_clock_page_cont_1, ui->clock_app_clock_page_subpage_1);

    //Create subpage for clock_app_clock_page
    ui->clock_app_clock_page_subpage_2 = lv_menu_page_create(ui->clock_app_clock_page, NULL);
    ui->clock_app_clock_page_cont_2 = lv_menu_cont_create(ui->clock_app_clock_page_sidebar_page);
    ui->clock_app_clock_page_label_2 = lv_label_create(ui->clock_app_clock_page_cont_2);
    lv_label_set_text(ui->clock_app_clock_page_label_2, "秒表");
    lv_obj_set_size(ui->clock_app_clock_page_label_2, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_scrollbar_mode(ui->clock_app_clock_page_subpage_2, LV_SCROLLBAR_MODE_OFF);
    lv_menu_set_load_page_event(ui->clock_app_clock_page, ui->clock_app_clock_page_cont_2, ui->clock_app_clock_page_subpage_2);

    //Create subpage for clock_app_clock_page
    ui->clock_app_clock_page_subpage_3 = lv_menu_page_create(ui->clock_app_clock_page, NULL);
    ui->clock_app_clock_page_cont_3 = lv_menu_cont_create(ui->clock_app_clock_page_sidebar_page);
    ui->clock_app_clock_page_label_3 = lv_label_create(ui->clock_app_clock_page_cont_3);
    lv_label_set_text(ui->clock_app_clock_page_label_3, "计时器");
    lv_obj_set_size(ui->clock_app_clock_page_label_3, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_scrollbar_mode(ui->clock_app_clock_page_subpage_3, LV_SCROLLBAR_MODE_OFF);
    lv_menu_set_load_page_event(ui->clock_app_clock_page, ui->clock_app_clock_page_cont_3, ui->clock_app_clock_page_subpage_3);

    //Create subpage for clock_app_clock_page
    ui->clock_app_clock_page_subpage_4 = lv_menu_page_create(ui->clock_app_clock_page, NULL);
    ui->clock_app_clock_page_cont_4 = lv_menu_cont_create(ui->clock_app_clock_page_sidebar_page);
    ui->clock_app_clock_page_label_4 = lv_label_create(ui->clock_app_clock_page_cont_4);
    lv_label_set_text(ui->clock_app_clock_page_label_4, "日历");
    lv_obj_set_size(ui->clock_app_clock_page_label_4, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_scrollbar_mode(ui->clock_app_clock_page_subpage_4, LV_SCROLLBAR_MODE_OFF);
    lv_menu_set_load_page_event(ui->clock_app_clock_page, ui->clock_app_clock_page_cont_4, ui->clock_app_clock_page_subpage_4);
    lv_event_send(ui->clock_app_clock_page_cont_1, LV_EVENT_CLICKED, NULL);
    lv_obj_set_pos(ui->clock_app_clock_page, 0, 16);
    lv_obj_set_size(ui->clock_app_clock_page, 480, 304);
    lv_obj_set_scrollbar_mode(ui->clock_app_clock_page, LV_SCROLLBAR_MODE_OFF);

    //Write style for clock_app_clock_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->clock_app_clock_page, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->clock_app_clock_page, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->clock_app_clock_page, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->clock_app_clock_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->clock_app_clock_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_clock_app_clock_page_extra_sidebar_page_main_default
    static lv_style_t style_clock_app_clock_page_extra_sidebar_page_main_default;
    ui_init_style(&style_clock_app_clock_page_extra_sidebar_page_main_default);

    lv_style_set_bg_opa(&style_clock_app_clock_page_extra_sidebar_page_main_default, 255);
    lv_style_set_bg_color(&style_clock_app_clock_page_extra_sidebar_page_main_default, lv_color_hex(0xdaf2f8));
    lv_style_set_bg_grad_dir(&style_clock_app_clock_page_extra_sidebar_page_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_radius(&style_clock_app_clock_page_extra_sidebar_page_main_default, 0);
    lv_obj_add_style(ui->clock_app_clock_page_sidebar_page, &style_clock_app_clock_page_extra_sidebar_page_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_clock_app_clock_page_extra_option_btns_main_default
    static lv_style_t style_clock_app_clock_page_extra_option_btns_main_default;
    ui_init_style(&style_clock_app_clock_page_extra_option_btns_main_default);

    lv_style_set_text_color(&style_clock_app_clock_page_extra_option_btns_main_default, lv_color_hex(0x151212));
    lv_style_set_text_font(&style_clock_app_clock_page_extra_option_btns_main_default, &lv_font_SourceHanSerifSC_Regular_12);
    lv_style_set_text_opa(&style_clock_app_clock_page_extra_option_btns_main_default, 255);
    lv_style_set_text_align(&style_clock_app_clock_page_extra_option_btns_main_default, LV_TEXT_ALIGN_CENTER);
    lv_style_set_pad_top(&style_clock_app_clock_page_extra_option_btns_main_default, 10);
    lv_style_set_pad_bottom(&style_clock_app_clock_page_extra_option_btns_main_default, 10);
    lv_obj_add_style(ui->clock_app_clock_page_cont_4, &style_clock_app_clock_page_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->clock_app_clock_page_cont_3, &style_clock_app_clock_page_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->clock_app_clock_page_cont_2, &style_clock_app_clock_page_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->clock_app_clock_page_cont_1, &style_clock_app_clock_page_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_clock_app_clock_page_extra_option_btns_main_checked
    static lv_style_t style_clock_app_clock_page_extra_option_btns_main_checked;
    ui_init_style(&style_clock_app_clock_page_extra_option_btns_main_checked);

    lv_style_set_text_color(&style_clock_app_clock_page_extra_option_btns_main_checked, lv_color_hex(0x9ab700));
    lv_style_set_text_font(&style_clock_app_clock_page_extra_option_btns_main_checked, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_clock_app_clock_page_extra_option_btns_main_checked, 255);
    lv_style_set_text_align(&style_clock_app_clock_page_extra_option_btns_main_checked, LV_TEXT_ALIGN_CENTER);
    lv_style_set_border_width(&style_clock_app_clock_page_extra_option_btns_main_checked, 0);
    lv_style_set_radius(&style_clock_app_clock_page_extra_option_btns_main_checked, 0);
    lv_style_set_bg_opa(&style_clock_app_clock_page_extra_option_btns_main_checked, 60);
    lv_style_set_bg_color(&style_clock_app_clock_page_extra_option_btns_main_checked, lv_color_hex(0x00e0b8));
    lv_style_set_bg_grad_dir(&style_clock_app_clock_page_extra_option_btns_main_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->clock_app_clock_page_cont_4, &style_clock_app_clock_page_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_add_style(ui->clock_app_clock_page_cont_3, &style_clock_app_clock_page_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_add_style(ui->clock_app_clock_page_cont_2, &style_clock_app_clock_page_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_add_style(ui->clock_app_clock_page_cont_1, &style_clock_app_clock_page_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style state: LV_STATE_DEFAULT for &style_clock_app_clock_page_extra_main_title_main_default
    static lv_style_t style_clock_app_clock_page_extra_main_title_main_default;
    ui_init_style(&style_clock_app_clock_page_extra_main_title_main_default);

    lv_style_set_text_color(&style_clock_app_clock_page_extra_main_title_main_default, lv_color_hex(0x41485a));
    lv_style_set_text_font(&style_clock_app_clock_page_extra_main_title_main_default, &lv_font_SourceHanSerifSC_Regular_12);
    lv_style_set_text_opa(&style_clock_app_clock_page_extra_main_title_main_default, 255);
    lv_style_set_text_align(&style_clock_app_clock_page_extra_main_title_main_default, LV_TEXT_ALIGN_CENTER);
    lv_style_set_bg_opa(&style_clock_app_clock_page_extra_main_title_main_default, 255);
    lv_style_set_bg_color(&style_clock_app_clock_page_extra_main_title_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_clock_app_clock_page_extra_main_title_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_pad_top(&style_clock_app_clock_page_extra_main_title_main_default, 0);
    lv_style_set_pad_bottom(&style_clock_app_clock_page_extra_main_title_main_default, 0);
    lv_menu_t * clock_app_clock_page_menu= (lv_menu_t *)ui->clock_app_clock_page;
    lv_obj_t * clock_app_clock_page_title = clock_app_clock_page_menu->sidebar_header_title;
    lv_obj_set_size(clock_app_clock_page_title, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_add_style(lv_menu_get_sidebar_header(ui->clock_app_clock_page), &style_clock_app_clock_page_extra_main_title_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);



    //Write codes clock_app_placeholder_div1
    ui->clock_app_placeholder_div1 = lv_obj_create(ui->clock_app_clock_page_subpage_1);
    lv_obj_set_pos(ui->clock_app_placeholder_div1, 113, 94);
    lv_obj_set_size(ui->clock_app_placeholder_div1, 10, 40);
    lv_obj_set_scrollbar_mode(ui->clock_app_placeholder_div1, LV_SCROLLBAR_MODE_OFF);

    //Write style for clock_app_placeholder_div1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->clock_app_placeholder_div1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->clock_app_placeholder_div1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->clock_app_placeholder_div1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->clock_app_placeholder_div1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->clock_app_placeholder_div1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->clock_app_placeholder_div1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->clock_app_placeholder_div1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->clock_app_placeholder_div1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->clock_app_placeholder_div1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->clock_app_placeholder_div1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes clock_app_analog_clock_1
    static bool clock_app_analog_clock_1_timer_enabled = false;
    ui->clock_app_analog_clock_1 = lv_analogclock_create(ui->clock_app_clock_page_subpage_1);
    lv_analogclock_hide_digits(ui->clock_app_analog_clock_1, false);
    lv_analogclock_set_major_ticks(ui->clock_app_analog_clock_1, 2, 10, lv_color_hex(0x555555), 10);
    lv_analogclock_set_ticks(ui->clock_app_analog_clock_1, 2, 5, lv_color_hex(0x333333));
    lv_analogclock_set_hour_needle_line(ui->clock_app_analog_clock_1, 2, lv_color_hex(0x00ff00), -40);
    lv_analogclock_set_min_needle_line(ui->clock_app_analog_clock_1, 2, lv_color_hex(0xE1FF00), -30);
    lv_analogclock_set_sec_needle_line(ui->clock_app_analog_clock_1, 2, lv_color_hex(0x6600FF), -10);
    lv_analogclock_set_time(ui->clock_app_analog_clock_1, clock_app_analog_clock_1_hour_value, clock_app_analog_clock_1_min_value,clock_app_analog_clock_1_sec_value);
    // create timer
    if (!clock_app_analog_clock_1_timer_enabled) {
        lv_timer_create(clock_app_analog_clock_1_timer, 1000, NULL);
        clock_app_analog_clock_1_timer_enabled = true;
    }
    lv_obj_set_pos(ui->clock_app_analog_clock_1, 140, 60);
    lv_obj_set_size(ui->clock_app_analog_clock_1, 200, 200);

    //Write style for clock_app_analog_clock_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->clock_app_analog_clock_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->clock_app_analog_clock_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->clock_app_analog_clock_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->clock_app_analog_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->clock_app_analog_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for clock_app_analog_clock_1, Part: LV_PART_TICKS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->clock_app_analog_clock_1, lv_color_hex(0xff0000), LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->clock_app_analog_clock_1, &lv_font_montserratMedium_12, LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->clock_app_analog_clock_1, 255, LV_PART_TICKS|LV_STATE_DEFAULT);

    //Write style for clock_app_analog_clock_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->clock_app_analog_clock_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->clock_app_analog_clock_1, lv_color_hex(0x000000), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->clock_app_analog_clock_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);







    //Write codes clock_app_placeholder_div2
    ui->clock_app_placeholder_div2 = lv_obj_create(ui->clock_app_clock_page_subpage_4);
    lv_obj_set_pos(ui->clock_app_placeholder_div2, 90, 60);
    lv_obj_set_size(ui->clock_app_placeholder_div2, 10, 40);
    lv_obj_set_scrollbar_mode(ui->clock_app_placeholder_div2, LV_SCROLLBAR_MODE_OFF);

    //Write style for clock_app_placeholder_div2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->clock_app_placeholder_div2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->clock_app_placeholder_div2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->clock_app_placeholder_div2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->clock_app_placeholder_div2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->clock_app_placeholder_div2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->clock_app_placeholder_div2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->clock_app_placeholder_div2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->clock_app_placeholder_div2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->clock_app_placeholder_div2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->clock_app_placeholder_div2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes clock_app_calendar
    ui->clock_app_calendar = lv_calendar_create(ui->clock_app_clock_page_subpage_4);
    clock_app_calendar_today.year = 2025;
    clock_app_calendar_today.month = 11;
    clock_app_calendar_today.day = 20;
    lv_calendar_set_today_date(ui->clock_app_calendar, clock_app_calendar_today.year, clock_app_calendar_today.month, clock_app_calendar_today.day);
    lv_calendar_set_showed_date(ui->clock_app_calendar, clock_app_calendar_today.year, clock_app_calendar_today.month);
    clock_app_calendar_highlihted_days[0].year = 2025;
    clock_app_calendar_highlihted_days[0].month = 11;
    clock_app_calendar_highlihted_days[0].day = 21;
    lv_calendar_set_highlighted_dates(ui->clock_app_calendar, clock_app_calendar_highlihted_days, 1);
    lv_obj_t *clock_app_calendar_header = lv_calendar_header_arrow_create(ui->clock_app_calendar);
    lv_calendar_t *clock_app_calendar = (lv_calendar_t *)ui->clock_app_calendar;
    lv_obj_add_event_cb(clock_app_calendar->btnm, clock_app_calendar_draw_part_begin_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);
    lv_obj_add_event_cb(ui->clock_app_calendar, clock_app_calendar_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_set_pos(ui->clock_app_calendar, 28, 30);
    lv_obj_set_size(ui->clock_app_calendar, 280, 210);

    //Write style state: LV_STATE_DEFAULT for &style_clock_app_calendar_main_main_default
    static lv_style_t style_clock_app_calendar_main_main_default;
    ui_init_style(&style_clock_app_calendar_main_main_default);

    lv_style_set_border_width(&style_clock_app_calendar_main_main_default, 1);
    lv_style_set_border_opa(&style_clock_app_calendar_main_main_default, 255);
    lv_style_set_border_color(&style_clock_app_calendar_main_main_default, lv_color_hex(0xc0c0c0));
    lv_style_set_border_side(&style_clock_app_calendar_main_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_bg_opa(&style_clock_app_calendar_main_main_default, 255);
    lv_style_set_bg_color(&style_clock_app_calendar_main_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_clock_app_calendar_main_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_shadow_width(&style_clock_app_calendar_main_main_default, 0);
    lv_style_set_radius(&style_clock_app_calendar_main_main_default, 0);
    lv_obj_add_style(ui->clock_app_calendar, &style_clock_app_calendar_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_clock_app_calendar_extra_header_main_default
    static lv_style_t style_clock_app_calendar_extra_header_main_default;
    ui_init_style(&style_clock_app_calendar_extra_header_main_default);

    lv_style_set_text_color(&style_clock_app_calendar_extra_header_main_default, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_clock_app_calendar_extra_header_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_clock_app_calendar_extra_header_main_default, 255);
    lv_style_set_bg_opa(&style_clock_app_calendar_extra_header_main_default, 255);
    lv_style_set_bg_color(&style_clock_app_calendar_extra_header_main_default, lv_color_hex(0x2195f6));
    lv_style_set_bg_grad_dir(&style_clock_app_calendar_extra_header_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(clock_app_calendar_header, &style_clock_app_calendar_extra_header_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_clock_app_calendar_main_items_default
    static lv_style_t style_clock_app_calendar_main_items_default;
    ui_init_style(&style_clock_app_calendar_main_items_default);

    lv_style_set_bg_opa(&style_clock_app_calendar_main_items_default, 0);
    lv_style_set_border_width(&style_clock_app_calendar_main_items_default, 1);
    lv_style_set_border_opa(&style_clock_app_calendar_main_items_default, 255);
    lv_style_set_border_color(&style_clock_app_calendar_main_items_default, lv_color_hex(0xc0c0c0));
    lv_style_set_border_side(&style_clock_app_calendar_main_items_default, LV_BORDER_SIDE_FULL);
    lv_style_set_text_color(&style_clock_app_calendar_main_items_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_clock_app_calendar_main_items_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_clock_app_calendar_main_items_default, 255);
    lv_obj_add_style(lv_calendar_get_btnmatrix(ui->clock_app_calendar), &style_clock_app_calendar_main_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //The custom code of clock_app.


    //Update current screen layout.
    lv_obj_update_layout(ui->clock_app);

    //Init events for screen.
    events_init_clock_app(ui);
}
