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



void setup_scr_drawing_board_app(lv_ui *ui)
{
    //Write codes drawing_board_app
    ui->drawing_board_app = lv_obj_create(NULL);
    lv_obj_set_size(ui->drawing_board_app, 480, 320);
    lv_obj_set_scrollbar_mode(ui->drawing_board_app, LV_SCROLLBAR_MODE_OFF);

    //Write style for drawing_board_app, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->drawing_board_app, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes drawing_board_app_tools_panel
    ui->drawing_board_app_tools_panel = lv_obj_create(ui->drawing_board_app);
    lv_obj_set_pos(ui->drawing_board_app_tools_panel, 320, 16);
    lv_obj_set_size(ui->drawing_board_app_tools_panel, 160, 304);
    lv_obj_set_scrollbar_mode(ui->drawing_board_app_tools_panel, LV_SCROLLBAR_MODE_OFF);

    //Write style for drawing_board_app_tools_panel, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->drawing_board_app_tools_panel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->drawing_board_app_tools_panel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->drawing_board_app_tools_panel, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->drawing_board_app_tools_panel, lv_color_hex(0x202020), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->drawing_board_app_tools_panel, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->drawing_board_app_tools_panel, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->drawing_board_app_tools_panel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->drawing_board_app_tools_panel, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->drawing_board_app_tools_panel, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->drawing_board_app_tools_panel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes drawing_board_app_colorwheel
    ui->drawing_board_app_colorwheel = lv_colorwheel_create(ui->drawing_board_app_tools_panel, true);
    lv_obj_set_pos(ui->drawing_board_app_colorwheel, 25, 9);
    lv_obj_set_size(ui->drawing_board_app_colorwheel, 100, 100);

    //Write style for drawing_board_app_colorwheel, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(ui->drawing_board_app_colorwheel, 10, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes drawing_board_app_width_slider
    ui->drawing_board_app_width_slider = lv_slider_create(ui->drawing_board_app_tools_panel);
    lv_slider_set_range(ui->drawing_board_app_width_slider, 1, 30);
    lv_slider_set_mode(ui->drawing_board_app_width_slider, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->drawing_board_app_width_slider, 4, LV_ANIM_OFF);
    lv_obj_set_pos(ui->drawing_board_app_width_slider, 7, 148);
    lv_obj_set_size(ui->drawing_board_app_width_slider, 130, 16);

    //Write style for drawing_board_app_width_slider, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->drawing_board_app_width_slider, 81, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->drawing_board_app_width_slider, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->drawing_board_app_width_slider, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->drawing_board_app_width_slider, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->drawing_board_app_width_slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->drawing_board_app_width_slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for drawing_board_app_width_slider, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->drawing_board_app_width_slider, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->drawing_board_app_width_slider, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->drawing_board_app_width_slider, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->drawing_board_app_width_slider, 8, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for drawing_board_app_width_slider, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->drawing_board_app_width_slider, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->drawing_board_app_width_slider, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->drawing_board_app_width_slider, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->drawing_board_app_width_slider, 8, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes drawing_board_app_btn_clear
    ui->drawing_board_app_btn_clear = lv_btn_create(ui->drawing_board_app_tools_panel);
    ui->drawing_board_app_btn_clear_label = lv_label_create(ui->drawing_board_app_btn_clear);
    lv_label_set_text(ui->drawing_board_app_btn_clear_label, "清空");
    lv_label_set_long_mode(ui->drawing_board_app_btn_clear_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->drawing_board_app_btn_clear_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->drawing_board_app_btn_clear, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->drawing_board_app_btn_clear_label, LV_PCT(100));
    lv_obj_set_pos(ui->drawing_board_app_btn_clear, 45, 192);
    lv_obj_set_size(ui->drawing_board_app_btn_clear, 58, 27);

    //Write style for drawing_board_app_btn_clear, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->drawing_board_app_btn_clear, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->drawing_board_app_btn_clear, lv_color_hex(0x797979), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->drawing_board_app_btn_clear, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->drawing_board_app_btn_clear, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->drawing_board_app_btn_clear, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->drawing_board_app_btn_clear, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->drawing_board_app_btn_clear, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->drawing_board_app_btn_clear, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->drawing_board_app_btn_clear, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->drawing_board_app_btn_clear, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes drawing_board_app_btn_nav_back
    ui->drawing_board_app_btn_nav_back = lv_btn_create(ui->drawing_board_app_tools_panel);
    ui->drawing_board_app_btn_nav_back_label = lv_label_create(ui->drawing_board_app_btn_nav_back);
    lv_label_set_text(ui->drawing_board_app_btn_nav_back_label, "返回");
    lv_label_set_long_mode(ui->drawing_board_app_btn_nav_back_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->drawing_board_app_btn_nav_back_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->drawing_board_app_btn_nav_back, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->drawing_board_app_btn_nav_back_label, LV_PCT(100));
    lv_obj_set_pos(ui->drawing_board_app_btn_nav_back, 45, 248);
    lv_obj_set_size(ui->drawing_board_app_btn_nav_back, 58, 27);

    //Write style for drawing_board_app_btn_nav_back, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->drawing_board_app_btn_nav_back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->drawing_board_app_btn_nav_back, lv_color_hex(0x797979), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->drawing_board_app_btn_nav_back, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->drawing_board_app_btn_nav_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->drawing_board_app_btn_nav_back, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->drawing_board_app_btn_nav_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->drawing_board_app_btn_nav_back, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->drawing_board_app_btn_nav_back, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->drawing_board_app_btn_nav_back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->drawing_board_app_btn_nav_back, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes drawing_board_app_canvas_container
    ui->drawing_board_app_canvas_container = lv_obj_create(ui->drawing_board_app);
    lv_obj_set_pos(ui->drawing_board_app_canvas_container, 0, 16);
    lv_obj_set_size(ui->drawing_board_app_canvas_container, 320, 304);
    lv_obj_set_scrollbar_mode(ui->drawing_board_app_canvas_container, LV_SCROLLBAR_MODE_OFF);

    //Write style for drawing_board_app_canvas_container, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->drawing_board_app_canvas_container, 9, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->drawing_board_app_canvas_container, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->drawing_board_app_canvas_container, lv_color_hex(0x2b2b2b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->drawing_board_app_canvas_container, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->drawing_board_app_canvas_container, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->drawing_board_app_canvas_container, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->drawing_board_app_canvas_container, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->drawing_board_app_canvas_container, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->drawing_board_app_canvas_container, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->drawing_board_app_canvas_container, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->drawing_board_app_canvas_container, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->drawing_board_app_canvas_container, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->drawing_board_app_canvas_container, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of drawing_board_app.
    drawing_board_ctx_t *ctx = &s_drawing_ctx;
    ctx->last_valid = false;
    ctx->seg_count = 0;

    // 屏幕删除时释放画布缓冲
    lv_obj_add_event_cb(ui->drawing_board_app, drawing_board_app_delete_cb, LV_EVENT_DELETE, ctx);

    // 画布（左侧）
    ctx->canvas = lv_obj_create(ui->drawing_board_app_canvas_container);
    lv_obj_set_pos(ctx->canvas, 0, 0);
    lv_obj_set_style_border_width(ctx->canvas, 0, 0);
    lv_obj_set_size(ctx->canvas, DRAW_CANVAS_W, DRAW_CANVAS_H);
    lv_obj_add_flag(ctx->canvas, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ctx->canvas, drawing_board_paint_draw_event_cb, LV_EVENT_DRAW_MAIN, ctx);
    lv_obj_set_style_border_width(ctx->canvas, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ctx->canvas, lv_color_hex(0x888888), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ctx->canvas, 0, LV_PART_MAIN | LV_STATE_DEFAULT); // 取消圆角

    // 颜色选择器
    lv_obj_add_event_cb(ui->drawing_board_app_colorwheel, drawing_board_color_event_cb, LV_EVENT_VALUE_CHANGED, ctx);
    // 笔宽滑条
    lv_obj_add_event_cb(ui->drawing_board_app_width_slider, drawing_board_width_event_cb, LV_EVENT_VALUE_CHANGED, ctx);
    // 清空按钮
    lv_obj_add_event_cb(ui->drawing_board_app_btn_clear, drawing_board_clear_event_cb, LV_EVENT_CLICKED, ctx);
    // 绑定画布触控绘图事件
    lv_obj_add_event_cb(ctx->canvas, drawing_board_canvas_event_cb, LV_EVENT_PRESSED, ctx);
    lv_obj_add_event_cb(ctx->canvas, drawing_board_canvas_event_cb, LV_EVENT_PRESSING, ctx);
    lv_obj_add_event_cb(ctx->canvas, drawing_board_canvas_event_cb, LV_EVENT_RELEASED, ctx);

    //Update current screen layout.
    lv_obj_update_layout(ui->drawing_board_app);

    //Init events for screen.
    events_init_drawing_board_app(ui);
}
