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



void setup_scr_minecraft_app(lv_ui *ui)
{
    //Write codes minecraft_app
    ui->minecraft_app = lv_obj_create(NULL);
    lv_obj_set_size(ui->minecraft_app, 480, 320);
    lv_obj_set_scrollbar_mode(ui->minecraft_app, LV_SCROLLBAR_MODE_OFF);

    //Write style for minecraft_app, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->minecraft_app, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes minecraft_app_back_btn
    ui->minecraft_app_back_btn = lv_btn_create(ui->minecraft_app);
    ui->minecraft_app_back_btn_label = lv_label_create(ui->minecraft_app_back_btn);
    lv_label_set_text(ui->minecraft_app_back_btn_label, "⬅");
    lv_label_set_long_mode(ui->minecraft_app_back_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->minecraft_app_back_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->minecraft_app_back_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->minecraft_app_back_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->minecraft_app_back_btn, 29, 24);
    lv_obj_set_size(ui->minecraft_app_back_btn, 28, 23);

    //Write style for minecraft_app_back_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->minecraft_app_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->minecraft_app_back_btn, lv_color_hex(0x9a9a9a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->minecraft_app_back_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->minecraft_app_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->minecraft_app_back_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->minecraft_app_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->minecraft_app_back_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->minecraft_app_back_btn, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->minecraft_app_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->minecraft_app_back_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of minecraft_app.
#ifdef KEIL_COMPILE
    lv_obj_add_event_cb(ui->minecraft_app, minecraft_app_screen_delete_event_handler, LV_EVENT_DELETE, ui);
    minecraft_init();
    const uint8_t *fb = (const uint8_t *)minecraft_get_framebuffer();
    if (fb == NULL) {
        lv_obj_t *err = lv_label_create(ui->minecraft_app);
        lv_label_set_text(err, "Minecraft初始化失败：内存不足");
        lv_obj_center(err);
    } else {
        static lv_img_dsc_t mc_img_dsc;
        mc_img_dsc.header.always_zero = 0;
        mc_img_dsc.header.w = SCREEN_WIDTH;
        mc_img_dsc.header.h = SCREEN_HEIGHT;
        mc_img_dsc.header.cf = LV_IMG_CF_TRUE_COLOR;
        mc_img_dsc.data_size = SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(lv_color_t);
        mc_img_dsc.data = fb;
        minecraft_img = lv_img_create(ui->minecraft_app);
        lv_img_set_src(minecraft_img, &mc_img_dsc);
        lv_img_set_pivot(minecraft_img, 0, 0); // 缩放锚点设为左上角
        lv_img_set_zoom(minecraft_img, 1024);
        lv_obj_align(minecraft_img, LV_ALIGN_TOP_LEFT, 1, 17);

        minecraft_timer = lv_timer_create(minecraft_timer_cb, 33, NULL);
    }
#endif
    lv_obj_move_foreground(ui->minecraft_app_back_btn);

    //Update current screen layout.
    lv_obj_update_layout(ui->minecraft_app);

    //Init events for screen.
    events_init_minecraft_app(ui);
}
