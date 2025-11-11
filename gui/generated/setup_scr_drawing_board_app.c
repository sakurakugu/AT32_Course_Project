/*
 * Copyright 2025 NXP
 * NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */

#include "custom.h"
#include "events_init.h"
#include "gui_guider.h"
#include "lvgl.h"
#include "widgets_init.h"
#include <stdio.h>

// 画板实现：绘图画布 + 颜色选择 + 笔宽设置 + 清空
#define DRAW_CANVAS_W 360
#define DRAW_CANVAS_H 320

typedef struct drawing_board_ctx_s {
    lv_obj_t *canvas;       // 绘图画布
    lv_obj_t *tools_panel;  // 工具面板
    lv_obj_t *colorwheel;   // 颜色选择器
    lv_obj_t *width_slider; // 笔宽滑条
    lv_obj_t *clear_btn;    // 清空按钮

    lv_color_t *canvas_buf; // 运行时分配的画布缓冲

    lv_point_t last_pt; // 上一个绘图点
    bool last_valid;    // 上一个点是否有效
} drawing_board_ctx_t;

static drawing_board_ctx_t s_drawing_ctx; // 单屏上下文

// 屏幕删除时释放画布缓冲
static void drawing_board_app_delete_cb(lv_event_t *e) {
    drawing_board_ctx_t *ctx = (drawing_board_ctx_t *)lv_event_get_user_data(e);
    if (ctx && ctx->canvas_buf) {
        lv_mem_free(ctx->canvas_buf);
        ctx->canvas_buf = NULL;
    }
}

static void drawing_board_canvas_event_cb(lv_event_t *e) {
    drawing_board_ctx_t *ctx = (drawing_board_ctx_t *)lv_event_get_user_data(e);
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *canvas = lv_event_get_target(e);

    lv_indev_t *indev = lv_indev_get_act();
    if (!indev)
        return;

    lv_point_t p;
    lv_indev_get_point(indev, &p);

    // 转换为画布局部坐标
    lv_area_t a;
    lv_obj_get_coords(canvas, &a);
    int32_t x = p.x - a.x1;
    int32_t y = p.y - a.y1;

    // 越界保护
    if (x < 0)
        x = 0;
    else if (x >= DRAW_CANVAS_W)
        x = DRAW_CANVAS_W - 1;
    if (y < 0)
        y = 0;
    else if (y >= DRAW_CANVAS_H)
        y = DRAW_CANVAS_H - 1;

    switch (code) {
    case LV_EVENT_PRESSED: {
        ctx->last_pt.x = x;
        ctx->last_pt.y = y;
        ctx->last_valid = true;

        // 画一个圆点，作为起笔
        lv_draw_rect_dsc_t rect_dsc;
        lv_draw_rect_dsc_init(&rect_dsc);
        rect_dsc.bg_color = lv_colorwheel_get_rgb(ctx->colorwheel);
        rect_dsc.radius = lv_slider_get_value(ctx->width_slider) / 2;
        rect_dsc.bg_opa = LV_OPA_COVER;
        int32_t r = rect_dsc.radius;
        if (r < 1)
            r = 1;
        lv_canvas_draw_rect(ctx->canvas, x - r, y - r, r * 2, r * 2, &rect_dsc);
        break;
    }
    case LV_EVENT_PRESSING: {
        if (!ctx->last_valid)
            break;
        // 画上一个点到当前点的线段
        lv_draw_line_dsc_t line_dsc;
        lv_draw_line_dsc_init(&line_dsc);
        line_dsc.color = lv_colorwheel_get_rgb(ctx->colorwheel);
        line_dsc.width = lv_slider_get_value(ctx->width_slider);
        line_dsc.round_start = 1;
        line_dsc.round_end = 1;

        lv_point_t p1 = ctx->last_pt;
        lv_point_t p2 = {(lv_coord_t)x, (lv_coord_t)y};

        // 使用 LVGL 画线 API（传入点数组与点数）
        lv_point_t pts[2] = {p1, p2};
        lv_canvas_draw_line(ctx->canvas, pts, 2, &line_dsc);

        ctx->last_pt = p2;
        break;
    }
    case LV_EVENT_RELEASED: {
        ctx->last_valid = false;
        break;
    }
    default:
        break;
    }
}

static void drawing_board_clear_event_cb(lv_event_t *e) {
    drawing_board_ctx_t *ctx = (drawing_board_ctx_t *)lv_event_get_user_data(e);
    // 清空为白色背景
    lv_canvas_fill_bg(ctx->canvas, lv_color_white(), LV_OPA_COVER);
}

static void drawing_board_width_event_cb(lv_event_t *e) {
    // 这里无需立即作画，仅在按压时读取值即可；此处可更新显示或做范围保护
    LV_UNUSED(e);
}

static void drawing_board_color_event_cb(lv_event_t *e) {
    // 颜色变化同样在作画事件中实时读取；保留回调以备扩展
    LV_UNUSED(e);
}

void setup_scr_drawing_board_app(lv_ui *ui) {
    // Write codes drawing_board_app
    ui->drawing_board_app = lv_obj_create(NULL);
    lv_obj_set_size(ui->drawing_board_app, 480, 320);
    lv_obj_set_scrollbar_mode(ui->drawing_board_app, LV_SCROLLBAR_MODE_OFF);

    // Write style for drawing_board_app, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->drawing_board_app, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // The custom code of drawing_board_app.
    drawing_board_ctx_t *ctx = &s_drawing_ctx;
    ctx->last_valid = false;
    ctx->canvas_buf = NULL;

    // 屏幕删除时释放画布缓冲
    lv_obj_add_event_cb(ui->drawing_board_app, drawing_board_app_delete_cb, LV_EVENT_DELETE, ctx);

    // 工具面板（右侧）
    ctx->tools_panel = lv_obj_create(ui->drawing_board_app);
    lv_obj_set_pos(ctx->tools_panel, 480 - (480 - DRAW_CANVAS_W), 0); // 放在画布右侧
    lv_obj_set_size(ctx->tools_panel, 480 - DRAW_CANVAS_W, 320);
    lv_obj_set_scrollbar_mode(ctx->tools_panel, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_width(ctx->tools_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ctx->tools_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ctx->tools_panel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ctx->tools_panel, lv_color_hex(0x2b2b2b), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ctx->tools_panel, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ctx->tools_panel, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ctx->tools_panel, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    // 画布（左侧）
    ctx->canvas = lv_canvas_create(ui->drawing_board_app);
    lv_obj_set_pos(ctx->canvas, 0, 0);
    lv_obj_set_size(ctx->canvas, DRAW_CANVAS_W, DRAW_CANVAS_H);
    lv_obj_add_flag(ctx->canvas, LV_OBJ_FLAG_CLICKABLE);
    // 运行时分配画布缓冲
    ctx->canvas_buf = (lv_color_t *)lv_mem_alloc(DRAW_CANVAS_W * DRAW_CANVAS_H * sizeof(lv_color_t));
    if (ctx->canvas_buf) {
        lv_canvas_set_buffer(ctx->canvas, ctx->canvas_buf, DRAW_CANVAS_W, DRAW_CANVAS_H, LV_IMG_CF_TRUE_COLOR);
        lv_canvas_fill_bg(ctx->canvas, lv_color_white(), LV_OPA_COVER);
    } else {
        // 分配失败时给出提示并禁止绘图
        lv_obj_add_flag(ctx->canvas, LV_OBJ_FLAG_HIDDEN);
        lv_obj_t *warn = lv_label_create(ui->drawing_board_app);
        lv_label_set_text(warn, "内存不足，无法创建画布");
        lv_obj_align(warn, LV_ALIGN_TOP_LEFT, 6, 6);
    }
    lv_obj_set_style_border_width(ctx->canvas, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ctx->canvas, lv_color_hex(0x888888), LV_PART_MAIN | LV_STATE_DEFAULT);

    // 颜色选择器
    ctx->colorwheel = lv_colorwheel_create(ctx->tools_panel, true);
    lv_obj_set_size(ctx->colorwheel, 100, 100);
    lv_obj_align(ctx->colorwheel, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_add_event_cb(ctx->colorwheel, drawing_board_color_event_cb, LV_EVENT_VALUE_CHANGED, ctx);

    // 笔宽滑条
    ctx->width_slider = lv_slider_create(ctx->tools_panel);
    lv_obj_set_size(ctx->width_slider, 100, 14);
    lv_obj_align_to(ctx->width_slider, ctx->colorwheel, LV_ALIGN_OUT_BOTTOM_MID, 0, 12);
    lv_slider_set_range(ctx->width_slider, 1, 30);
    lv_slider_set_value(ctx->width_slider, 4, LV_ANIM_OFF);
    lv_obj_add_event_cb(ctx->width_slider, drawing_board_width_event_cb, LV_EVENT_VALUE_CHANGED, ctx);

    // 清空按钮
    ctx->clear_btn = lv_btn_create(ctx->tools_panel);
    lv_obj_set_size(ctx->clear_btn, 100, 36);
    lv_obj_align_to(ctx->clear_btn, ctx->width_slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 16);
    lv_obj_add_event_cb(ctx->clear_btn, drawing_board_clear_event_cb, LV_EVENT_CLICKED, ctx);
    lv_obj_t *clear_label = lv_label_create(ctx->clear_btn);
    lv_label_set_text(clear_label, "清空");
    lv_obj_center(clear_label);

    // 绑定画布触控绘图事件
    lv_obj_add_event_cb(ctx->canvas, drawing_board_canvas_event_cb, LV_EVENT_PRESSED, ctx);
    lv_obj_add_event_cb(ctx->canvas, drawing_board_canvas_event_cb, LV_EVENT_PRESSING, ctx);
    lv_obj_add_event_cb(ctx->canvas, drawing_board_canvas_event_cb, LV_EVENT_RELEASED, ctx);

    // Update current screen layout.
    lv_obj_update_layout(ui->drawing_board_app);

    // Init events for screen.
    events_init_drawing_board_app(ui);
}
