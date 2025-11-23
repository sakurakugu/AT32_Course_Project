/**
 * @brief 蜂鸣器类
 *
 * 该类用于控制无源蜂鸣器的发声和停止。
 */

#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void Beep_SetMute(bool mute);

#ifdef __cplusplus
}
#endif
