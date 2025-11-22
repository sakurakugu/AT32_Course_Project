
// PanYanWei 潘彦玮 2023030103024

#include "lm75.h"
#include "eeprom.h"

uint8_t lm75_buf[2];

uint8_t LM75::Read() {
    I2C_BusLock();
    i2c_memory_read(&hi2cx, I2C_MEM_ADDR_WIDIH_8, 0x92, 0, lm75_buf, 2, I2C_TIMEOUT);
    I2C_BusUnlock();
    return lm75_buf[0];
}
