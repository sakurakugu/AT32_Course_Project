#include "drawing_board.h"
#include "gui_guider.h"

drawing_board_ctx_t s_drawing_ctx; // 单屏上下文

// 屏幕删除时释放画布缓冲
void drawing_board_app_delete_cb(lv_event_t *e) {
    drawing_board_ctx_t *ctx = (drawing_board_ctx_t *)lv_event_get_user_data(e);
    if (!ctx)
        return;
    ctx->seg_count = 0;
    ctx->last_valid = false;
}

void drawing_board_canvas_event_cb(lv_event_t *e) {
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
    lv_coord_t obj_w = lv_obj_get_width(canvas);
    lv_coord_t obj_h = lv_obj_get_height(canvas);

    // 越界保护
    if (x < 0)
        x = 0;
    else if (x >= obj_w)
        x = obj_w - 1;
    if (y < 0)
        y = 0;
    else if (y >= obj_h)
        y = obj_h - 1;

    switch (code) {
    case LV_EVENT_PRESSED: {
        ctx->last_pt.x = x;
        ctx->last_pt.y = y;
        ctx->last_valid = true;
        if (ctx->seg_count < DRAW_MAX_SEGMENTS) {
            draw_seg_t *s = &ctx->segs[ctx->seg_count++];
            s->color = lv_colorwheel_get_rgb(guider_ui.drawing_board_app_colorwheel);
            uint16_t w = (uint16_t)lv_slider_get_value(guider_ui.drawing_board_app_width_slider);
            if (w == 0)
                w = 1;
            s->width = w;
            s->p1.x = (lv_coord_t)x;
            s->p1.y = (lv_coord_t)y;
            s->p2 = s->p1;
        }
        lv_obj_invalidate(canvas);
        break;
    }
    case LV_EVENT_PRESSING: {
        if (!ctx->last_valid)
            break;
        if (ctx->seg_count < DRAW_MAX_SEGMENTS) {
            draw_seg_t *s = &ctx->segs[ctx->seg_count++];
            s->color = lv_colorwheel_get_rgb(guider_ui.drawing_board_app_colorwheel);
            uint16_t w = (uint16_t)lv_slider_get_value(guider_ui.drawing_board_app_width_slider);
            if (w == 0)
                w = 1;
            s->width = w;
            s->p1 = ctx->last_pt;
            s->p2.x = (lv_coord_t)x;
            s->p2.y = (lv_coord_t)y;
            ctx->last_pt = s->p2;
        }
        lv_obj_invalidate(canvas);
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

void drawing_board_clear_event_cb(lv_event_t *e) {
    drawing_board_ctx_t *ctx = (drawing_board_ctx_t *)lv_event_get_user_data(e);
    if (!ctx)
        return;
    ctx->seg_count = 0;
    lv_obj_invalidate(ctx->canvas);
}

void drawing_board_width_event_cb(lv_event_t *e) {
    // 这里无需立即作画，仅在按压时读取值即可；此处可更新显示或做范围保护
    LV_UNUSED(e);
}

void drawing_board_color_event_cb(lv_event_t *e) {
    // 颜色变化同样在作画事件中实时读取；保留回调以备扩展
    LV_UNUSED(e);
}

void drawing_board_paint_draw_event_cb(lv_event_t *e) {
    drawing_board_ctx_t *ctx = (drawing_board_ctx_t *)lv_event_get_user_data(e);
    lv_obj_t *obj = lv_event_get_target(e);
    lv_draw_ctx_t *draw_ctx = lv_event_get_draw_ctx(e);
    lv_area_t area;
    lv_obj_get_content_coords(obj, &area);
    lv_draw_rect_dsc_t rd;
    lv_draw_rect_dsc_init(&rd);
    rd.bg_color = lv_color_white();
    rd.bg_opa = LV_OPA_COVER;
    lv_draw_rect(draw_ctx, &rd, &area);
    for (uint16_t i = 0; i < ctx->seg_count; i++) {
        draw_seg_t *s = &ctx->segs[i];
        lv_draw_line_dsc_t ld;
        lv_draw_line_dsc_init(&ld);
        ld.color = s->color;
        ld.width = s->width;
        ld.round_start = 1;
        ld.round_end = 1;
        lv_draw_line(draw_ctx, &ld, &s->p1, &s->p2);
    }
}
