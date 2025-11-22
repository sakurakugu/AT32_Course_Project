#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void ColorLed_SetColor(uint8_t r, uint8_t g, uint8_t b);
extern void ColorLed_TurnOn();
extern void ColorLed_TurnOff();

#ifdef __cplusplus
}
#endif