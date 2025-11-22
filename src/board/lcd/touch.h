/**
 **************************************************************************
 * @file     at_surf_f437_board_touch.h
 * @version  v2.0.0
 * @date     2020-11-02
 * @brief    touch application libray header file.
 **************************************************************************
 *                       Copyright notice & Disclaimer
 *
 * The software Board Support Package (BSP) that is made available to
 * download from Artery official website is the copyrighted work of Artery.
 * Artery authorizes customers to use, copy, and distribute the BSP
 * software and its related documentation for the purpose of design and
 * development in conjunction with Artery microcontrollers. Use of the
 * software is governed by this copyright notice and the following disclaimer.
 *
 * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
 * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
 * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
 * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
 * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
 *
 **************************************************************************
 */

/* define to prevent recursive inclusion -------------------------------------*/
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "i2c_application.h"
#include <stdbool.h>

/**
 * @brief touch register definition
 */
#define TOUCH_CTRL_REG 0x8040  /* control register */
#define TOUCH_CFG_REG 0x8047   /* config version */
#define TOUCH_CHECK_REG 0x80FF /* config check sum */
#define TOUCH_PID_REG 0x8140   /* product ID */
#define TOUCH_STS_REG 0x814E   /* touch status register */
#define TOUCH_TP1_REG 0x8150   /* point 1 coordinate */
#define TOUCH_TP2_REG 0x8158   /* point 2 coordinate */
#define TOUCH_TP3_REG 0x8160   /* point 3 coordinate */
#define TOUCH_TP4_REG 0x8168   /* point 4 coordinate */
#define TOUCH_TP5_REG 0x8170   /* point 5 coordinate */

/**
 * @brief touch scan direction
 */
typedef enum {
    TOUCH_SCAN_VERTICAL = 0x00,      /*!< vertical display */
    TOUCH_SCAN_HORIZONTAL = 0x01,    /*!< horizontal display */
    TOUCH_SCAN_VERTICAL_180 = 0x02,  /*!< vertical display 180 deg */
    TOUCH_SCAN_HORIZONTAL_180 = 0x03 /*!< horizontal display 180 deg */
} touch_scan_type;


/**
 * @brief io definition
 */
#define TOUCH_I2C_TIMEOUT 0xFFFFFFF

#define TOUCH_I2C_CLKCTRL_100K 0x80504C4E
#define TOUCH_I2C_CLKCTRL_200K 0x30F03C6B

#define TOUCH_I2C_ADDRESS 0xBA

#define TOUCH_I2C_PORT I2C2
#define TOUCH_I2C_CLK CRM_I2C2_PERIPH_CLOCK

#define TOUCH_SCL_GPIO_CLK CRM_GPIOB_PERIPH_CLOCK
#define TOUCH_SCL_GPIO_PIN GPIO_PINS_10
#define TOUCH_SCL_GPIO_PINS_SOURCE GPIO_PINS_SOURCE10
#define TOUCH_SCL_GPIO_PORT GPIOB
#define TOUCH_SCL_GPIO_MUX GPIO_MUX_4

#define TOUCH_SDA_GPIO_CLK CRM_GPIOB_PERIPH_CLOCK
#define TOUCH_SDA_GPIO_PIN GPIO_PINS_11
#define TOUCH_SDA_GPIO_PINS_SOURCE GPIO_PINS_SOURCE11
#define TOUCH_SDA_GPIO_PORT GPIOB
#define TOUCH_SDA_GPIO_MUX GPIO_MUX_4

#define TOUCH_RST_GPIO_CLK CRM_GPIOB_PERIPH_CLOCK
#define TOUCH_RST_GPIO_PIN GPIO_PINS_9
#define TOUCH_RST_GPIO_PORT GPIOB

#define TOUCH_INT_GPIO_CLK CRM_GPIOE_PERIPH_CLOCK
#define TOUCH_INT_GPIO_PIN GPIO_PINS_3
#define TOUCH_INT_GPIO_PORT GPIOE

#define TOUCH_RST_LOW() gpio_bits_reset(TOUCH_RST_GPIO_PORT, TOUCH_RST_GPIO_PIN)
#define TOUCH_RST_HIGH() gpio_bits_set(TOUCH_RST_GPIO_PORT, TOUCH_RST_GPIO_PIN)

#define TOUCH_INT_LOW() gpio_bits_reset(TOUCH_INT_GPIO_PORT, TOUCH_INT_GPIO_PIN)
#define TOUCH_INT_HIGH() gpio_bits_set(TOUCH_INT_GPIO_PORT, TOUCH_INT_GPIO_PIN)
#define TOUCH_INT_READ() gpio_input_data_bit_read(TOUCH_INT_GPIO_PORT, TOUCH_INT_GPIO_PIN)

/**
 * @brief touch exported functions
 */
bool Touch_ReadXY(uint16_t *x, uint16_t *y);

#ifdef __cplusplus
}
#endif
