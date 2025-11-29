#include "mpl_porting.h"
#include "i2c_application.h"

#include <stddef.h>

int mpl_i2c_write(uint8_t slave_addr, uint8_t reg_addr, uint8_t length, const uint8_t *data)
{
    if ((length > 0U) && (data == NULL)) {
        return -1;
    }

    uint16_t device_addr = ((uint16_t)slave_addr) << 1;
    uint8_t *tx_buf = (uint8_t *)data;
    if (i2c_memory_write(&hi2cx, I2C_MEM_ADDR_WIDIH_8, device_addr, reg_addr, tx_buf, length, I2C_TIMEOUT) != I2C_OK) {
        return -1;
    }
    return 0;
}

int mpl_i2c_read(uint8_t slave_addr, uint8_t reg_addr, uint8_t length, uint8_t *data)
{
    if ((length > 0U) && (data == NULL)) {
        return -1;
    }

    uint16_t device_addr = ((uint16_t)slave_addr) << 1;
    if (i2c_memory_read(&hi2cx, I2C_MEM_ADDR_WIDIH_8, device_addr, reg_addr, data, length, I2C_TIMEOUT) != I2C_OK) {
        return -1;
    }
    return 0;
}

void mpl_delay_ms(unsigned long num_ms)
{
    while (num_ms != 0UL) {
        uint16_t chunk = (num_ms > 0xFFFFUL) ? 0xFFFFU : (uint16_t)num_ms;
        delay_ms(chunk);
        num_ms -= chunk;
    }
}

void mpl_get_ms(unsigned long *count)
{
    if (count == NULL) {
        return;
    }
    *count = (unsigned long)Timer_GetTickCount();
}
