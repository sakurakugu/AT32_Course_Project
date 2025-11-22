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

extern void Beep_SetFreq(int freq);
extern void Beep_Start(uint16_t beepTime, uint16_t stopTime, uint16_t cycle);
extern void Beep_Stop(void);

#ifdef __cplusplus
}
#endif
