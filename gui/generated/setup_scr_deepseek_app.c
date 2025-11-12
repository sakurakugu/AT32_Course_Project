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

    //Write codes deepseek_app_input_div
    ui->deepseek_app_input_div = lv_obj_create(ui->deepseek_app);
    lv_obj_set_pos(ui->deepseek_app_input_div, 16, 263);
    lv_obj_set_size(ui->deepseek_app_input_div, 456, 39);
    lv_obj_set_scrollbar_mode(ui->deepseek_app_input_div, LV_SCROLLBAR_MODE_OFF);

    //Write style for deepseek_app_input_div, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->deepseek_app_input_div, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->deepseek_app_input_div, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->deepseek_app_input_div, lv_color_hex(0xff0050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->deepseek_app_input_div, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->deepseek_app_input_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->deepseek_app_input_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->deepseek_app_input_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->deepseek_app_input_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->deepseek_app_input_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->deepseek_app_input_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->deepseek_app_input_div, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes deepseek_app_send_btn
    ui->deepseek_app_send_btn = lv_btn_create(ui->deepseek_app_input_div);
    ui->deepseek_app_send_btn_label = lv_label_create(ui->deepseek_app_send_btn);
    lv_label_set_text(ui->deepseek_app_send_btn_label, "发送");
    lv_label_set_long_mode(ui->deepseek_app_send_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->deepseek_app_send_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->deepseek_app_send_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->deepseek_app_send_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->deepseek_app_send_btn, 392, 3);
    lv_obj_set_size(ui->deepseek_app_send_btn, 58, 29);

    //Write style for deepseek_app_send_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->deepseek_app_send_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->deepseek_app_send_btn, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->deepseek_app_send_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->deepseek_app_send_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->deepseek_app_send_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->deepseek_app_send_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->deepseek_app_send_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->deepseek_app_send_btn, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->deepseek_app_send_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->deepseek_app_send_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes deepseek_app_input_box
    ui->deepseek_app_input_box = lv_textarea_create(ui->deepseek_app_input_div);
    lv_textarea_set_text(ui->deepseek_app_input_box, "");
    lv_textarea_set_placeholder_text(ui->deepseek_app_input_box, "");
    lv_textarea_set_password_bullet(ui->deepseek_app_input_box, "*");
    lv_textarea_set_password_mode(ui->deepseek_app_input_box, false);
    lv_textarea_set_one_line(ui->deepseek_app_input_box, false);
    lv_textarea_set_accepted_chars(ui->deepseek_app_input_box, "");
    lv_textarea_set_max_length(ui->deepseek_app_input_box, 112);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->deepseek_app_input_box, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->deepseek_app_input_box, 0, 0);
    lv_obj_set_size(ui->deepseek_app_input_box, 378, 36);

    //Write style for deepseek_app_input_box, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->deepseek_app_input_box, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->deepseek_app_input_box, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->deepseek_app_input_box, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->deepseek_app_input_box, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->deepseek_app_input_box, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->deepseek_app_input_box, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->deepseek_app_input_box, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->deepseek_app_input_box, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->deepseek_app_input_box, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->deepseek_app_input_box, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->deepseek_app_input_box, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->deepseek_app_input_box, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->deepseek_app_input_box, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->deepseek_app_input_box, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->deepseek_app_input_box, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->deepseek_app_input_box, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->deepseek_app_input_box, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for deepseek_app_input_box, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->deepseek_app_input_box, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->deepseek_app_input_box, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->deepseek_app_input_box, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->deepseek_app_input_box, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //The custom code of deepseek_app.


    //Update current screen layout.
    lv_obj_update_layout(ui->deepseek_app);

    //Init events for screen.
    events_init_deepseek_app(ui);
}
