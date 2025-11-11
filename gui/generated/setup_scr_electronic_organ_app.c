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



void setup_scr_electronic_organ_app(lv_ui *ui)
{
    //Write codes electronic_organ_app
    ui->electronic_organ_app = lv_obj_create(NULL);
    lv_obj_set_size(ui->electronic_organ_app, 480, 320);
    lv_obj_set_scrollbar_mode(ui->electronic_organ_app, LV_SCROLLBAR_MODE_OFF);

    //Write style for electronic_organ_app, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->electronic_organ_app, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes electronic_organ_app_e_organ_btnm
    ui->electronic_organ_app_e_organ_btnm = lv_btnmatrix_create(ui->electronic_organ_app);
    static const char *electronic_organ_app_e_organ_btnm_text_map[] = {"L1", "L2", "L3", "L4", "L5", "L6", "L7", "\n", "M1", "M2", "M3", "M4", "M5", "M6", "M7", "\n", "H1", "H2", "H3", "H4", "H5", "H6", "H7", "",};
    lv_btnmatrix_set_map(ui->electronic_organ_app_e_organ_btnm, electronic_organ_app_e_organ_btnm_text_map);
    lv_obj_set_pos(ui->electronic_organ_app_e_organ_btnm, 0, 95);
    lv_obj_set_size(ui->electronic_organ_app_e_organ_btnm, 480, 225);

    //Write style for electronic_organ_app_e_organ_btnm, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->electronic_organ_app_e_organ_btnm, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->electronic_organ_app_e_organ_btnm, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->electronic_organ_app_e_organ_btnm, lv_color_hex(0xc9c9c9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->electronic_organ_app_e_organ_btnm, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->electronic_organ_app_e_organ_btnm, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->electronic_organ_app_e_organ_btnm, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->electronic_organ_app_e_organ_btnm, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->electronic_organ_app_e_organ_btnm, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui->electronic_organ_app_e_organ_btnm, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui->electronic_organ_app_e_organ_btnm, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->electronic_organ_app_e_organ_btnm, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->electronic_organ_app_e_organ_btnm, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->electronic_organ_app_e_organ_btnm, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->electronic_organ_app_e_organ_btnm, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for electronic_organ_app_e_organ_btnm, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->electronic_organ_app_e_organ_btnm, 1, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->electronic_organ_app_e_organ_btnm, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->electronic_organ_app_e_organ_btnm, lv_color_hex(0xc9c9c9), LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->electronic_organ_app_e_organ_btnm, LV_BORDER_SIDE_FULL, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->electronic_organ_app_e_organ_btnm, lv_color_hex(0xffffff), LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->electronic_organ_app_e_organ_btnm, &lv_font_montserratMedium_16, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->electronic_organ_app_e_organ_btnm, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->electronic_organ_app_e_organ_btnm, 4, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->electronic_organ_app_e_organ_btnm, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->electronic_organ_app_e_organ_btnm, lv_color_hex(0x2195f6), LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->electronic_organ_app_e_organ_btnm, LV_GRAD_DIR_NONE, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->electronic_organ_app_e_organ_btnm, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //The custom code of electronic_organ_app.
    // 电子琴按钮矩阵：点击后按音发声
    lv_obj_add_event_cb(guider_ui.electronic_organ_app_e_organ_btnm, electronic_organ_btnm_event_handler, LV_EVENT_VALUE_CHANGED, &guider_ui);

    //Update current screen layout.
    lv_obj_update_layout(ui->electronic_organ_app);

    //Init events for screen.
    events_init_electronic_organ_app(ui);
}
