#pragma once

#include "i2c_application.h"
#include "touch.h"
#include <at32f435_437.h>
#include <stdint.h>

/**
 * @brief 触摸屏寄存器定义
 */
#define TOUCH_CTRL_REG 0x8040  /* 控制寄存器 */
#define TOUCH_CFG_REG 0x8047   /* 配置版本寄存器 */
#define TOUCH_CHECK_REG 0x80FF /* 配置校验和寄存器 */
#define TOUCH_PID_REG 0x8140   /* 产品ID寄存器 */
#define TOUCH_STS_REG 0x814E   /* 触摸状态寄存器 */
#define TOUCH_TP1_REG 0x8150   /* 点1坐标寄存器 */
#define TOUCH_TP2_REG 0x8158   /* 点2坐标寄存器 */
#define TOUCH_TP3_REG 0x8160   /* 点3坐标寄存器 */
#define TOUCH_TP4_REG 0x8168   /* 点4坐标寄存器 */
#define TOUCH_TP5_REG 0x8170   /* 点5坐标寄存器 */

/**
 * @brief 触摸屏扫描方向定义
 */
typedef enum {
    TOUCH_SCAN_VERTICAL = 0x00,      /*!< 垂直扫描方向 */
    TOUCH_SCAN_HORIZONTAL = 0x01,    /*!< 水平扫描方向 */
    TOUCH_SCAN_VERTICAL_180 = 0x02,  /*!< 垂直扫描方向180度 */
    TOUCH_SCAN_HORIZONTAL_180 = 0x03 /*!< 水平扫描方向180度 */
} touch_scan_type;

/**
 * @brief 触摸屏IO定义
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

class Touch {
  public:
    static Touch &GetInstance() {
        static Touch instance;
        return instance;
    }
    Touch(const Touch &) = delete;
    Touch &operator=(const Touch &) = delete;

    bool Init(touch_scan_type direction);
    bool Read(uint16_t &x, uint16_t &y);
    bool Adjust();

  private:
    Touch() {}
    ~Touch() {}

    touch_scan_type m_direction = TOUCH_SCAN_VERTICAL; /* 触摸扫描方向 */
    // uint16_t x_p[6];                                 // 保存x坐标
    // uint16_t y_p[6];                                 // 保存y坐标
};