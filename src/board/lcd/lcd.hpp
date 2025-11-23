/**
 * @file     lcd.hpp
 * @brief    C++ LCD 类接口。实现驻留在 lcd.cpp 中。
 */

#pragma once

#include "lcd.h" // 重用类型、宏和 C 


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

class LCD {
  public:
    static LCD &GetInstance() {
        static LCD instance;
        return instance;
    }
    LCD(const LCD &) = delete;
    LCD &operator=(const LCD &) = delete;

    // 高等级操作
    void Init(lcd_display_type direction);                                                              // 初始化 LCD
    void Clear(uint16_t color);                                                                         // 清除 LCD 屏幕
    void DrawLine(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color); // 绘制一条线
    void PointDraw(uint16_t x, uint16_t y, uint16_t color);                                            // 绘制一个点
    uint16_t PointRead(uint16_t x, uint16_t y);                                    // 读取一个点的颜色
    void WindowsSet(uint16_t xstar, uint16_t ystar, uint16_t xend, uint16_t yend); // 设置窗口
    void CursorSet(uint16_t xpos, uint16_t ypos);                                  // 设置光标位置
    void Direction(uint8_t direction);                                              // 设置显示方向
    uint16_t IDRead();                                                             // 读取 LCD ID
    void Fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color); // lcd 区域颜色填充
    void ColorFill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t *color); // lcd 区域颜色填充

    // 低等级操作
    void XMCInit();                                                // 初始化 XMC
    uint16_t Read();                                                // 读取数据
    void RegWrite(uint16_t data);                                  // 写入寄存器
    void DataWrite(uint16_t data);                                 // 写入数据
    uint16_t DataRead();                                           // 读取数据
    void CommandWrite(uint16_t lcd_comm, uint16_t lcd_regvalue);   // 写入命令
    void CommandRead(uint16_t lcd_comm, uint8_t *rval, int32_t n); // 读取命令
    void RamPrepareWrite();                                       // 准备写入 RAM
    void RamPrepareRead();                                        // 准备读取 RAM
    void Data16BitWrite(uint16_t data);                           // 写入 16 位数据
    uint16_t ColorTo565(uint8_t r, uint8_t g, uint8_t b);         // 将 RGB 转换为 565 格式
    uint16_t Data16BitRead();                                     // 读取 16 位数据

    // 背光控制
    void BacklightInitPWM();                   // 初始化背光 PWM
    void BacklightSetPercent(uint8_t percent); // 设置背光亮度百分比（0..100），0=关闭，100=最亮

  private:
    LCD() = default;

    uint16_t m_backlight_period = 100; // 10kHz @ 1MHz timer clock // 背光周期
    uint16_t m_prescaler = 0; // 预分频器
    bool m_backlight_initialized = false; // 背光是否初始化
};