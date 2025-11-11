/**
 * @brief 蜂鸣器类
 *
 * 该类用于控制无源蜂鸣器的发声和停止。
 */

#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void beep_setFreq(int freq);
extern void beep_start(uint16_t beepTime, uint16_t stopTime, uint16_t cycle);

#ifdef __cplusplus
}
#endif
