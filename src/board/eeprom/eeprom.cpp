#include "eeprom.h"
#include "at32f435_437_clock.h"
#include "util/mutex.h"

i2c_handle_type hi2cx;
uint8_t eep_write[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
uint8_t eep_read_buf[32];

static mutex g_i2c_mutex;


void I2C_Init(void) {
    hi2cx.i2cx = I2Cx_PORT;
    /* i2c config */
    i2c_config(&hi2cx);
}

/**
 * @brief  initializes peripherals used by the i2c.
 * @param  none
 * @retval none
 */
void i2c_lowlevel_init(i2c_handle_type *hi2c) {
    gpio_init_type gpio_init_structure;

    if (hi2c->i2cx == I2Cx_PORT) {
        /* i2c periph clock enable */
        crm_periph_clock_enable(I2Cx_CLK, TRUE);
        crm_periph_clock_enable(I2Cx_SCL_GPIO_CLK, TRUE);
        crm_periph_clock_enable(I2Cx_SDA_GPIO_CLK, TRUE);

        /* gpio configuration */
        gpio_pin_mux_config(I2Cx_SCL_GPIO_PORT, I2Cx_SCL_GPIO_PinsSource, I2Cx_SCL_GPIO_MUX);

        gpio_pin_mux_config(I2Cx_SDA_GPIO_PORT, I2Cx_SDA_GPIO_PinsSource, I2Cx_SDA_GPIO_MUX);

        /* configure i2c pins: scl */
        gpio_init_structure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
        gpio_init_structure.gpio_mode = GPIO_MODE_MUX;
        gpio_init_structure.gpio_out_type = GPIO_OUTPUT_OPEN_DRAIN;
        gpio_init_structure.gpio_pull = GPIO_PULL_NONE;

        gpio_init_structure.gpio_pins = I2Cx_SCL_GPIO_PIN;
        gpio_init(I2Cx_SCL_GPIO_PORT, &gpio_init_structure);

        /* configure i2c pins: sda */
        gpio_init_structure.gpio_pins = I2Cx_SDA_GPIO_PIN;
        gpio_init(I2Cx_SDA_GPIO_PORT, &gpio_init_structure);

        /* config i2c */
        i2c_init(hi2c->i2cx, 0x0F, I2Cx_CLKCTRL);

        i2c_own_address1_set(hi2c->i2cx, I2C_ADDRESS_MODE_7BIT, I2Cx_ADDRESS);
    }
}
//
void I2C_BusLock(void) { g_i2c_mutex.lock(); }
void I2C_BusUnlock(void) { g_i2c_mutex.unlock(); }

void EEP_Write(uint16_t mem_address, uint8_t *pdata, uint16_t size) {
    I2C_BusLock();
    i2c_memory_write(&hi2cx, I2C_MEM_ADDR_WIDIH_16, 0xA0, mem_address, pdata, size, I2C_TIMEOUT);
    I2C_BusUnlock();
}

void EEP_Read(uint16_t mem_address, uint8_t *pdata, uint16_t size) {
    I2C_BusLock();
    i2c_memory_read(&hi2cx, I2C_MEM_ADDR_WIDIH_16, 0xA0, mem_address, pdata, size, I2C_TIMEOUT);
    I2C_BusUnlock();
}
