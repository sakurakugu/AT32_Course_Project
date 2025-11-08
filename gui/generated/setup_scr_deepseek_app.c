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



void setup_scr_deepseek_app(lv_ui *ui)
{
    //Write codes deepseek_app
    ui->deepseek_app = lv_obj_create(NULL);
    lv_obj_set_size(ui->deepseek_app, 480, 320);
    lv_obj_set_scrollbar_mode(ui->deepseek_app, LV_SCROLLBAR_MODE_OFF);

    //Write style for deepseek_app, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->deepseek_app, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes deepseek_app_ta_1
    ui->deepseek_app_ta_1 = lv_textarea_create(ui->deepseek_app);
    lv_textarea_set_text(ui->deepseek_app_ta_1, "Hello World");
    lv_textarea_set_placeholder_text(ui->deepseek_app_ta_1, "");
    lv_textarea_set_password_bullet(ui->deepseek_app_ta_1, "*");
    lv_textarea_set_password_mode(ui->deepseek_app_ta_1, false);
    lv_textarea_set_one_line(ui->deepseek_app_ta_1, false);
    lv_textarea_set_accepted_chars(ui->deepseek_app_ta_1, "");
    lv_textarea_set_max_length(ui->deepseek_app_ta_1, 32);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->deepseek_app_ta_1, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->deepseek_app_ta_1, 21, 242);
    lv_obj_set_size(ui->deepseek_app_ta_1, 422, 52);

    //Write style for deepseek_app_ta_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->deepseek_app_ta_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->deepseek_app_ta_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->deepseek_app_ta_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->deepseek_app_ta_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->deepseek_app_ta_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->deepseek_app_ta_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->deepseek_app_ta_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->deepseek_app_ta_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->deepseek_app_ta_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->deepseek_app_ta_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->deepseek_app_ta_1, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->deepseek_app_ta_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->deepseek_app_ta_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->deepseek_app_ta_1, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->deepseek_app_ta_1, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->deepseek_app_ta_1, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->deepseek_app_ta_1, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for deepseek_app_ta_1, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->deepseek_app_ta_1, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->deepseek_app_ta_1, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->deepseek_app_ta_1, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->deepseek_app_ta_1, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes deepseek_app_spangroup_1
    ui->deepseek_app_spangroup_1 = lv_spangroup_create(ui->deepseek_app);
    lv_spangroup_set_align(ui->deepseek_app_spangroup_1, LV_TEXT_ALIGN_LEFT);
    lv_spangroup_set_overflow(ui->deepseek_app_spangroup_1, LV_SPAN_OVERFLOW_CLIP);
    lv_spangroup_set_mode(ui->deepseek_app_spangroup_1, LV_SPAN_MODE_BREAK);
    //create span
    ui->deepseek_app_spangroup_1_span = lv_spangroup_new_span(ui->deepseek_app_spangroup_1);
    lv_span_set_text(ui->deepseek_app_spangroup_1_span, "hello");
    lv_style_set_text_color(&ui->deepseek_app_spangroup_1_span->style, lv_color_hex(0x000000));
    lv_style_set_text_decor(&ui->deepseek_app_spangroup_1_span->style, LV_TEXT_DECOR_NONE);
    lv_style_set_text_font(&ui->deepseek_app_spangroup_1_span->style, &lv_font_montserratMedium_12);
    lv_obj_set_pos(ui->deepseek_app_spangroup_1, 237, 48);
    lv_obj_set_size(ui->deepseek_app_spangroup_1, 186, 20);

    //Write style state: LV_STATE_DEFAULT for &style_deepseek_app_spangroup_1_main_main_default
    static lv_style_t style_deepseek_app_spangroup_1_main_main_default;
    ui_init_style(&style_deepseek_app_spangroup_1_main_main_default);

    lv_style_set_border_width(&style_deepseek_app_spangroup_1_main_main_default, 0);
    lv_style_set_radius(&style_deepseek_app_spangroup_1_main_main_default, 0);
    lv_style_set_bg_opa(&style_deepseek_app_spangroup_1_main_main_default, 0);
    lv_style_set_pad_top(&style_deepseek_app_spangroup_1_main_main_default, 0);
    lv_style_set_pad_right(&style_deepseek_app_spangroup_1_main_main_default, 0);
    lv_style_set_pad_bottom(&style_deepseek_app_spangroup_1_main_main_default, 0);
    lv_style_set_pad_left(&style_deepseek_app_spangroup_1_main_main_default, 0);
    lv_style_set_shadow_width(&style_deepseek_app_spangroup_1_main_main_default, 0);
    lv_obj_add_style(ui->deepseek_app_spangroup_1, &style_deepseek_app_spangroup_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_spangroup_refr_mode(ui->deepseek_app_spangroup_1);

    //Write codes deepseek_app_spangroup_2
    ui->deepseek_app_spangroup_2 = lv_spangroup_create(ui->deepseek_app);
    lv_spangroup_set_align(ui->deepseek_app_spangroup_2, LV_TEXT_ALIGN_LEFT);
    lv_spangroup_set_overflow(ui->deepseek_app_spangroup_2, LV_SPAN_OVERFLOW_CLIP);
    lv_spangroup_set_mode(ui->deepseek_app_spangroup_2, LV_SPAN_MODE_BREAK);
    //create span
    ui->deepseek_app_spangroup_2_span = lv_spangroup_new_span(ui->deepseek_app_spangroup_2);
    lv_span_set_text(ui->deepseek_app_spangroup_2_span, "hello");
    lv_style_set_text_color(&ui->deepseek_app_spangroup_2_span->style, lv_color_hex(0x000000));
    lv_style_set_text_decor(&ui->deepseek_app_spangroup_2_span->style, LV_TEXT_DECOR_NONE);
    lv_style_set_text_font(&ui->deepseek_app_spangroup_2_span->style, &lv_font_montserratMedium_12);
    lv_obj_set_pos(ui->deepseek_app_spangroup_2, 45, 99);
    lv_obj_set_size(ui->deepseek_app_spangroup_2, 186, 20);

    //Write style state: LV_STATE_DEFAULT for &style_deepseek_app_spangroup_2_main_main_default
    static lv_style_t style_deepseek_app_spangroup_2_main_main_default;
    ui_init_style(&style_deepseek_app_spangroup_2_main_main_default);

    lv_style_set_border_width(&style_deepseek_app_spangroup_2_main_main_default, 0);
    lv_style_set_radius(&style_deepseek_app_spangroup_2_main_main_default, 0);
    lv_style_set_bg_opa(&style_deepseek_app_spangroup_2_main_main_default, 0);
    lv_style_set_pad_top(&style_deepseek_app_spangroup_2_main_main_default, 0);
    lv_style_set_pad_right(&style_deepseek_app_spangroup_2_main_main_default, 0);
    lv_style_set_pad_bottom(&style_deepseek_app_spangroup_2_main_main_default, 0);
    lv_style_set_pad_left(&style_deepseek_app_spangroup_2_main_main_default, 0);
    lv_style_set_shadow_width(&style_deepseek_app_spangroup_2_main_main_default, 0);
    lv_obj_add_style(ui->deepseek_app_spangroup_2, &style_deepseek_app_spangroup_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_spangroup_refr_mode(ui->deepseek_app_spangroup_2);

    //The custom code of deepseek_app.


    //Update current screen layout.
    lv_obj_update_layout(ui->deepseek_app);

    //Init events for screen.
    events_init_deepseek_app(ui);
}
