/**
 * @file     lcd.h
 * @brief     LCD类 的 C接口, 为LVGL和C模块提供.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "at32f435_437.h"

// lcd 颜色定义
#define WHITE 0xFFFF
#define BLACK 0x0000
#define BLUE 0x001F
#define BRED 0xF81F
#define GRED 0xFFE0
#define GBLUE 0x07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define GREEN 0x07E0
#define CYAN 0x7FFF
#define YELLOW 0xFFE0
#define BROWN 0xBC40
#define BRRED 0xFC07
#define GRAY 0x8430

#define DARKBLUE 0x01CF
#define LIGHTBLUE 0x7D7C
#define GRAYBLUE 0x5458

#define LIGHTGREEN 0x841F
#define LIGHTGRAY 0xEF5B
#define LGRAY 0xC618

#define LGRAYBLUE 0xA651
#define LBBLUE 0x2B12

// lcd 模式定义
#define LCD_USE8BIT_MODEL 0

// lcd 尺寸定义
#define LCD_W 320
#define LCD_H 480

// lcd 命令/数据地址定义
#define XMC_LCD_COMMAND 0x6007FFFE
#define XMC_LCD_DATA    0x60080000

// lcd 显示方向定义
typedef enum {
    LCD_DISPLAY_VERTICAL        = 0x00,
    LCD_DISPLAY_HORIZONTAL      = 0x01,
    LCD_DISPLAY_VERTICAL_180    = 0x02,
    LCD_DISPLAY_HORIZONTAL_180  = 0x03
} lcd_display_type;

// lcd 总线访问类型定义
typedef struct {
#if LCD_USE8BIT_MODEL
    volatile uint8_t LCD_REG;
    volatile uint8_t LCD_RAM;
#else
    volatile uint16_t LCD_REG;
    volatile uint16_t LCD_RAM;
#endif
} lcd_type;

// lcd 设备定义
typedef struct {
    uint16_t width;
    uint16_t height;
    uint16_t id;
    uint8_t dir;
    uint16_t wramcmd;
    uint16_t rramcmd;
    uint16_t setxcmd;
    uint16_t setycmd;
} lcd_device_type;

// lcd 设备实例
extern lcd_device_type lcddev;
extern uint16_t POINT_COLOR;
extern uint16_t BACK_COLOR;

// lcd IO 定义
#define LCD_D0_GPIO_PORT            GPIOD
#define LCD_D0_GPIO_CLK             CRM_GPIOD_PERIPH_CLOCK
#define LCD_D0_GPIO_PIN             GPIO_PINS_14
#define LCD_D0_GPIO_PINS_SOURCE     GPIO_PINS_SOURCE14
#define LCD_D0_GPIO_MUX             GPIO_MUX_12

#define LCD_D1_GPIO_PORT            GPIOD
#define LCD_D1_GPIO_CLK             CRM_GPIOD_PERIPH_CLOCK
#define LCD_D1_GPIO_PIN             GPIO_PINS_15
#define LCD_D1_GPIO_PINS_SOURCE     GPIO_PINS_SOURCE15
#define LCD_D1_GPIO_MUX             GPIO_MUX_12

#define LCD_D2_GPIO_PORT            GPIOD
#define LCD_D2_GPIO_CLK             CRM_GPIOD_PERIPH_CLOCK
#define LCD_D2_GPIO_PIN             GPIO_PINS_0
#define LCD_D2_GPIO_PINS_SOURCE     GPIO_PINS_SOURCE0
#define LCD_D2_GPIO_MUX             GPIO_MUX_12

#define LCD_D3_GPIO_PORT            GPIOD
#define LCD_D3_GPIO_CLK             CRM_GPIOD_PERIPH_CLOCK
#define LCD_D3_GPIO_PIN             GPIO_PINS_1
#define LCD_D3_GPIO_PINS_SOURCE     GPIO_PINS_SOURCE1
#define LCD_D3_GPIO_MUX             GPIO_MUX_12

#define LCD_D4_GPIO_PORT            GPIOE
#define LCD_D4_GPIO_CLK             CRM_GPIOE_PERIPH_CLOCK
#define LCD_D4_GPIO_PIN             GPIO_PINS_7
#define LCD_D4_GPIO_PINS_SOURCE     GPIO_PINS_SOURCE7
#define LCD_D4_GPIO_MUX             GPIO_MUX_12

#define LCD_D5_GPIO_PORT            GPIOE
#define LCD_D5_GPIO_CLK             CRM_GPIOE_PERIPH_CLOCK
#define LCD_D5_GPIO_PIN             GPIO_PINS_8
#define LCD_D5_GPIO_PINS_SOURCE     GPIO_PINS_SOURCE8
#define LCD_D5_GPIO_MUX             GPIO_MUX_12

#define LCD_D6_GPIO_PORT            GPIOE
#define LCD_D6_GPIO_CLK             CRM_GPIOE_PERIPH_CLOCK
#define LCD_D6_GPIO_PIN             GPIO_PINS_9
#define LCD_D6_GPIO_PINS_SOURCE     GPIO_PINS_SOURCE9
#define LCD_D6_GPIO_MUX             GPIO_MUX_12

#define LCD_D7_GPIO_PORT            GPIOE
#define LCD_D7_GPIO_CLK             CRM_GPIOE_PERIPH_CLOCK
#define LCD_D7_GPIO_PIN             GPIO_PINS_10
#define LCD_D7_GPIO_PINS_SOURCE     GPIO_PINS_SOURCE10
#define LCD_D7_GPIO_MUX             GPIO_MUX_12

#define LCD_D8_GPIO_PORT            GPIOE
#define LCD_D8_GPIO_CLK             CRM_GPIOE_PERIPH_CLOCK
#define LCD_D8_GPIO_PIN             GPIO_PINS_11
#define LCD_D8_GPIO_PINS_SOURCE     GPIO_PINS_SOURCE11
#define LCD_D8_GPIO_MUX             GPIO_MUX_12

#define LCD_D9_GPIO_PORT            GPIOE
#define LCD_D9_GPIO_CLK             CRM_GPIOE_PERIPH_CLOCK
#define LCD_D9_GPIO_PIN             GPIO_PINS_12
#define LCD_D9_GPIO_PINS_SOURCE     GPIO_PINS_SOURCE12
#define LCD_D9_GPIO_MUX             GPIO_MUX_12

#define LCD_D10_GPIO_PORT           GPIOE
#define LCD_D10_GPIO_CLK            CRM_GPIOE_PERIPH_CLOCK
#define LCD_D10_GPIO_PIN            GPIO_PINS_13
#define LCD_D10_GPIO_PINS_SOURCE    GPIO_PINS_SOURCE13
#define LCD_D10_GPIO_MUX            GPIO_MUX_12

#define LCD_D11_GPIO_PORT           GPIOE
#define LCD_D11_GPIO_CLK            CRM_GPIOE_PERIPH_CLOCK
#define LCD_D11_GPIO_PIN            GPIO_PINS_14
#define LCD_D11_GPIO_PINS_SOURCE    GPIO_PINS_SOURCE14
#define LCD_D11_GPIO_MUX            GPIO_MUX_12

#define LCD_D12_GPIO_PORT           GPIOE
#define LCD_D12_GPIO_CLK            CRM_GPIOE_PERIPH_CLOCK
#define LCD_D12_GPIO_PIN            GPIO_PINS_15
#define LCD_D12_GPIO_PINS_SOURCE    GPIO_PINS_SOURCE15
#define LCD_D12_GPIO_MUX            GPIO_MUX_12

#define LCD_D13_GPIO_PORT           GPIOD
#define LCD_D13_GPIO_CLK            CRM_GPIOD_PERIPH_CLOCK
#define LCD_D13_GPIO_PIN            GPIO_PINS_8
#define LCD_D13_GPIO_PINS_SOURCE    GPIO_PINS_SOURCE8
#define LCD_D13_GPIO_MUX            GPIO_MUX_12

#define LCD_D14_GPIO_PORT           GPIOD
#define LCD_D14_GPIO_CLK            CRM_GPIOD_PERIPH_CLOCK
#define LCD_D14_GPIO_PIN            GPIO_PINS_9
#define LCD_D14_GPIO_PINS_SOURCE    GPIO_PINS_SOURCE9
#define LCD_D14_GPIO_MUX            GPIO_MUX_12

#define LCD_D15_GPIO_PORT           GPIOD
#define LCD_D15_GPIO_CLK            CRM_GPIOD_PERIPH_CLOCK
#define LCD_D15_GPIO_PIN            GPIO_PINS_10
#define LCD_D15_GPIO_PINS_SOURCE    GPIO_PINS_SOURCE10
#define LCD_D15_GPIO_MUX            GPIO_MUX_12

#define LCD_NE1_GPIO_PORT           GPIOD
#define LCD_NE1_GPIO_CLK            CRM_GPIOD_PERIPH_CLOCK
#define LCD_NE1_GPIO_PIN            GPIO_PINS_7
#define LCD_NE1_GPIO_PINS_SOURCE    GPIO_PINS_SOURCE7
#define LCD_NE1_GPIO_MUX            GPIO_MUX_12

#define LCD_NWE_GPIO_PORT           GPIOD
#define LCD_NWE_GPIO_CLK            CRM_GPIOD_PERIPH_CLOCK
#define LCD_NWE_GPIO_PIN            GPIO_PINS_5
#define LCD_NWE_GPIO_PINS_SOURCE    GPIO_PINS_SOURCE5
#define LCD_NWE_GPIO_MUX            GPIO_MUX_12

#define LCD_NOE_GPIO_PORT           GPIOD
#define LCD_NOE_GPIO_CLK            CRM_GPIOD_PERIPH_CLOCK
#define LCD_NOE_GPIO_PIN            GPIO_PINS_4
#define LCD_NOE_GPIO_PINS_SOURCE    GPIO_PINS_SOURCE4
#define LCD_NOE_GPIO_MUX            GPIO_MUX_12

#define LCD_A16_GPIO_PORT           GPIOD
#define LCD_A16_GPIO_CLK            CRM_GPIOD_PERIPH_CLOCK
#define LCD_A16_GPIO_PIN            GPIO_PINS_13
#define LCD_A16_GPIO_PINS_SOURCE    GPIO_PINS_SOURCE13
#define LCD_A16_GPIO_MUX            GPIO_MUX_12

#define LCD_BL_GPIO_CLK             CRM_GPIOA_PERIPH_CLOCK
#define LCD_BL_GPIO_PIN             GPIO_PINS_8
#define LCD_BL_GPIO_PORT            GPIOA
// 背光PWM：PA8 -> TMR1_CH1 (AF1)
#define LCD_BL_GPIO_PINS_SOURCE     GPIO_PINS_SOURCE8
#define LCD_BL_GPIO_MUX             GPIO_MUX_1

#define LCD_RESET_GPIO_CLK          CRM_GPIOE_PERIPH_CLOCK
#define LCD_RESET_GPIO_PIN          GPIO_PINS_5
#define LCD_RESET_GPIO_PORT         GPIOE

#define LCD_BL_HIGH()               gpio_bits_set(LCD_BL_GPIO_PORT, LCD_BL_GPIO_PIN)
#define LCD_BL_LOW()                gpio_bits_reset(LCD_BL_GPIO_PORT, LCD_BL_GPIO_PIN)

#define LCD_RESET_HIGH()            gpio_bits_set(LCD_RESET_GPIO_PORT, LCD_RESET_GPIO_PIN)
#define LCD_RESET_LOW()             gpio_bits_reset(LCD_RESET_GPIO_PORT, LCD_RESET_GPIO_PIN)

// C 接口函数，用于 LVGL 和 C 模块
void xmc_init(void);
uint16_t lcd_read(void);
void lcd_reg_write(uint16_t data);
void lcd_data_write(uint16_t data);
uint16_t lcd_data_read(void);
void lcd_command_write(uint16_t lcd_comm, uint16_t lcd_regvalue);
void lcd_command_read(uint16_t lcd_comm, uint8_t *rval, int32_t n);
void lcd_ram_prepare_write(void);
void lcd_ram_prepare_read(void);
void lcd_data_16bit_write(uint16_t data);
uint16_t color_to_565(uint8_t r, uint8_t g, uint8_t b);
uint16_t lcd_data_16bit_read(void);
void lcd_point_draw(uint16_t x, uint16_t y, uint16_t color);
uint16_t lcd_point_read(uint16_t x, uint16_t y);
void lcd_draw_line(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color);
void lcd_clear(uint16_t color);
void lcd_init(lcd_display_type direction);
void lcd_windows_set(uint16_t xstar, uint16_t ystar, uint16_t xend, uint16_t yend);
void lcd_cursor_set(uint16_t xpos, uint16_t ypos);
void lcd_direction(uint8_t direction);
uint16_t lcd_id_read(void);
void lcd_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color);
void lcd_color_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t *color);

#ifdef __cplusplus
}
#endif