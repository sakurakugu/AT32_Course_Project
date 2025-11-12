#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void adc_config(void);
uint16_t analogRead(void);

#ifdef __cplusplus
}
#endif
