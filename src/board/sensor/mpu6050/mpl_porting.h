#ifndef MPL_PORTING_H
#define MPL_PORTING_H

/*
 * Target/platform selection for the InvenSense eMPL drivers.
 * This header also exposes the platform helper APIs used by the
 * motion driver and DMP firmware glue code.
 */
#ifndef EMPL_TARGET_AT32F435
#define EMPL_TARGET_AT32F435
#endif

#ifndef MPU6050
#define MPU6050
#endif

#include <stdint.h>
#include "bsp.h"

#ifdef __cplusplus
extern "C" {
#endif

int mpl_i2c_write(uint8_t slave_addr, uint8_t reg_addr, uint8_t length, const uint8_t *data);
int mpl_i2c_read(uint8_t slave_addr, uint8_t reg_addr, uint8_t length, uint8_t *data);
void mpl_delay_ms(unsigned long num_ms);
void mpl_get_ms(unsigned long *count);

#ifdef __cplusplus
}
#endif

#endif /* MPL_PORTING_H */
