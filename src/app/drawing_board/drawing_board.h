#pragma once

#include "lvgl.h"

// 画布

// 画板实现：绘图画布 + 颜色选择 + 笔宽设置 + 清空
// 注：为支持 lv_canvas_draw_line/rect，需要使用 TRUE_COLOR 画布缓冲。
// 缓冲类型统一按字节指针管理。
#define DRAW_CANVAS_W 302
#define DRAW_CANVAS_H 286
#define DRAW_MAX_SEGMENTS 1024
typedef struct draw_seg_s {
    lv_color_t color;
    uint16_t width;
    lv_point_t p1;
    lv_point_t p2;
} draw_seg_t;
typedef struct drawing_board_ctx_s {
    lv_obj_t *canvas;
    lv_point_t last_pt;
    bool last_valid;
    uint16_t seg_count;
    draw_seg_t segs[DRAW_MAX_SEGMENTS];
} drawing_board_ctx_t;

extern drawing_board_ctx_t s_drawing_ctx;

void drawing_board_app_delete_cb(lv_event_t *e);   // 删除画布
void drawing_board_canvas_event_cb(lv_event_t *e); // 画布点击事件
void drawing_board_clear_event_cb(lv_event_t *e);  // 清空画布
void drawing_board_width_event_cb(lv_event_t *e);  // 笔宽选择事件
void drawing_board_color_event_cb(lv_event_t *e);  // 颜色选择事件
void drawing_board_paint_draw_event_cb(lv_event_t *e);