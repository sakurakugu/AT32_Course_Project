#pragma once
#include <stdint.h>
#include "i2c_application.h"

#define I2C_TIMEOUT 10000

// #define I2Cx_CLKCTRL                   0xB170FFFF   //10K
// #define I2Cx_CLKCTRL                   0xC0E06969   //50K
#define I2Cx_CLKCTRL 0x80504C4E // 100K
// #define I2Cx_CLKCTRL                   0x30F03C6B   //200K

#define I2Cx_ADDRESS 0xA0

#define I2Cx_PORT I2C2
#define I2Cx_CLK CRM_I2C2_PERIPH_CLOCK
#define I2Cx_DMA DMA1
#define I2Cx_DMA_CLK CRM_DMA1_PERIPH_CLOCK

#define I2Cx_SCL_GPIO_CLK CRM_GPIOB_PERIPH_CLOCK
#define I2Cx_SCL_GPIO_PIN GPIO_PINS_10
#define I2Cx_SCL_GPIO_PinsSource GPIO_PINS_SOURCE10
#define I2Cx_SCL_GPIO_PORT GPIOB
#define I2Cx_SCL_GPIO_MUX GPIO_MUX_4

#define I2Cx_SDA_GPIO_CLK CRM_GPIOB_PERIPH_CLOCK
#define I2Cx_SDA_GPIO_PIN GPIO_PINS_11
#define I2Cx_SDA_GPIO_PinsSource GPIO_PINS_SOURCE11
#define I2Cx_SDA_GPIO_PORT GPIOB
#define I2Cx_SDA_GPIO_MUX GPIO_MUX_4

#ifdef __cplusplus
extern "C" {
#endif
void I2C_Init(void);
void EEP_Write(uint16_t mem_address, uint8_t *pdata, uint16_t size);
void EEP_Read(uint16_t mem_address, uint8_t *pdata, uint16_t size);

/**
 * @brief 提供公共的I2C缓冲区，用于应用程序使用
 */
extern uint8_t eep_write[16];
extern uint8_t eep_read_buf[32];
extern uint8_t lm75_buf[2];
extern i2c_handle_type hi2cx;
/**
 * @brief I2C总线守卫API
 *        用于在多任务环境下保护I2C总线不被同时访问
 */
void I2C_BusLock(void);
void I2C_BusUnlock(void);

#ifdef __cplusplus
}
#endif
