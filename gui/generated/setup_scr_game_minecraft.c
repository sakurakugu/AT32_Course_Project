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



void setup_scr_game_minecraft(lv_ui *ui)
{
    //Write codes game_minecraft
    ui->game_minecraft = lv_obj_create(NULL);
    lv_obj_set_size(ui->game_minecraft, 480, 320);
    lv_obj_set_scrollbar_mode(ui->game_minecraft, LV_SCROLLBAR_MODE_OFF);

    //Write style for game_minecraft, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->game_minecraft, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes game_minecraft_back_btn
    ui->game_minecraft_back_btn = lv_btn_create(ui->game_minecraft);
    ui->game_minecraft_back_btn_label = lv_label_create(ui->game_minecraft_back_btn);
    lv_label_set_text(ui->game_minecraft_back_btn_label, "⬅");
    lv_label_set_long_mode(ui->game_minecraft_back_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->game_minecraft_back_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->game_minecraft_back_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->game_minecraft_back_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->game_minecraft_back_btn, 29, 24);
    lv_obj_set_size(ui->game_minecraft_back_btn, 28, 23);

    //Write style for game_minecraft_back_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->game_minecraft_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->game_minecraft_back_btn, lv_color_hex(0x9a9a9a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->game_minecraft_back_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->game_minecraft_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->game_minecraft_back_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->game_minecraft_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->game_minecraft_back_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->game_minecraft_back_btn, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->game_minecraft_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->game_minecraft_back_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of game_minecraft.


    //Update current screen layout.
    lv_obj_update_layout(ui->game_minecraft);

    //Init events for screen.
    events_init_game_minecraft(ui);
}
