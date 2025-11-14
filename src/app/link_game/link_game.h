#pragma once

#include "lvgl.h"
#include "gui_guider.h"

#define LINK_ROWS 8
#define LINK_COLS 10
#define LINK_MAX_TURNS 2

static int *board;
static lv_obj_t **tiles;
static int sel_r = -1, sel_c = -1;
static lv_obj_t *link_root;
static lv_obj_t *grid_container;

#define BR(r, c) board[(r) * (LINK_COLS + 2) + (c)]
#define TL(r, c) tiles[((r) - 1) * LINK_COLS + ((c) - 1)]

#ifdef __cplusplus
extern "C" {
#endif

extern void link_init_board(uint32_t seed);
extern void link_create_grid(lv_ui *ui);
extern void reset_event_cb(lv_event_t *e);
extern void root_delete_cb(lv_event_t *e);

#ifdef __cplusplus
}
#endif
