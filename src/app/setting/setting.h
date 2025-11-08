#pragma once
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// 网络时间同步接口
bool sync_network_time(bool sync);
// 设置背光亮度百分比（0..100）。当前硬件为数字开关：0=关闭，其它=打开。
void backlight_set_percent(uint8_t percent);

#ifdef __cplusplus
}
#endif