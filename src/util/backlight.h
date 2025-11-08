/**
 * @brief 背光控制接口
 */
#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// 设置背光亮度百分比（0..100）。当前硬件为数字开关：0=关闭，其它=打开。
void backlight_set_percent(uint8_t percent);

#ifdef __cplusplus
}
#endif