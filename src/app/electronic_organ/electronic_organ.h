#pragma once

#include "gui_guider.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
// 电子琴：按钮矩阵事件（点击后按音发声）
extern void electronic_organ_btnm_event_handler(lv_event_t *e);
#ifdef __cplusplus
}
#endif
