#pragma once

#include "gui_guider.h"
#include "lvgl.h"

#define LINKGAME_ROWS 8
#define LINKGAME_COLS 10
#define LINKGAME_MAX_TURNS 2

static int *board;
static lv_obj_t **tiles;
static int sel_r = -1, sel_c = -1;
static lv_obj_t *link_root;
static lv_obj_t *grid_container;

#ifdef __cplusplus
extern "C" {
#endif

extern void LinkGame_InitBoard(uint32_t seed);
extern void LinkGame_CreateGrid(lv_ui *ui);
extern void LinkGame_ResetEventCb(lv_event_t *e);
extern void LinkGame_RootDeleteCb(lv_event_t *e);

#ifdef __cplusplus
}
#endif
