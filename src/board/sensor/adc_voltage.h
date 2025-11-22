#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void ADC_Config(void);
uint16_t AnalogRead(void);

#ifdef __cplusplus
}
#endif
