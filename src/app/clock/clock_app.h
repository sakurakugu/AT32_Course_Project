// _app 是为了防止与clock.h冲突
#pragma once

#include "gui_guider.h"

// ===============================
// 时钟实现
// ===============================

extern void clock_app_start_or_pausing_btn_event_handler(lv_event_t *e);
extern void clock_app_reset_btn_event_handler(lv_event_t *e);
extern void clock_app_timer_SPC_btn_event_handler(lv_event_t *e);
extern void clock_app_timer_reset_btn_event_handler(lv_event_t *e);
extern void clock_app_timer_bell_btn_event_handler(lv_event_t *e);
extern void clock_app_init_customize(lv_ui *ui);