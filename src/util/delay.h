#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
void delay_init();
void delay_us(uint32_t nus);
void delay_ms(uint16_t nms);
void delay_sec(uint16_t sec);
#ifdef __cplusplus
}
#endif
