#pragma once

#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif

// 触发天气更新（从网络获取并更新到 LVGL 天气页面）
bool Weather_UpdateUI(void);

#ifdef __cplusplus
}
#endif