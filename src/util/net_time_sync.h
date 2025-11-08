/**
 * @brief 网络时间同步接口
 */
#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// 触发一次网络时间同步（成功返回 true）。将更新各屏幕的时钟与日期。
bool sync_network_time(void);

#ifdef __cplusplus
}
#endif