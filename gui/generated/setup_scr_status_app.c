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



void setup_scr_status_app(lv_ui *ui)
{
    //Write codes status_app
    ui->status_app = lv_obj_create(NULL);
    lv_obj_set_size(ui->status_app, 480, 320);
    lv_obj_set_scrollbar_mode(ui->status_app, LV_SCROLLBAR_MODE_OFF);

    //Write style for status_app, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->status_app, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->status_app, lv_color_hex(0x333333), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->status_app, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);


    //The custom code of status_app.


    //Update current screen layout.
    lv_obj_update_layout(ui->status_app);

    //Init events for screen.
    events_init_status_app(ui);
}
