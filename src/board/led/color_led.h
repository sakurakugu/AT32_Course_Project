#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void Color_Led_SetColor(uint8_t r, uint8_t g, uint8_t b);
extern void Color_Led_TurnOn();
extern void Color_Led_TurnOff();

#ifdef __cplusplus
}
#endif