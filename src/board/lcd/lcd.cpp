/**
 * @file     lcd.cpp
 * @version  v2.0.0
 * @date     2020-11-02
 * @brief    一组用于管理LED和按键的固件函数
 *           初始化延迟函数
 */

#include "lcd.hpp"
#include "delay.h"

lcd_device_type lcddev;

uint16_t POINT_COLOR = 0x0000, BACK_COLOR = 0xFFFF;

/**
 * @brief  初始化XMC和GPIO以与LCD接口
 *         必须在任何对LCD的写/读操作之前调用此函数
 * @param  none
 * @retval none
 */
void LCD::XMCInit() {
    gpio_init_type gpio_init_struct = {0};
    xmc_norsram_init_type xmc_norsram_init_struct;
    xmc_norsram_timing_init_type rw_timing_struct, w_timing_struct;

    /* 开启LCD相关GPIO的时钟 */
    crm_periph_clock_enable(LCD_D0_GPIO_CLK, TRUE);
    crm_periph_clock_enable(LCD_D1_GPIO_CLK, TRUE);
    crm_periph_clock_enable(LCD_D2_GPIO_CLK, TRUE);
    crm_periph_clock_enable(LCD_D3_GPIO_CLK, TRUE);
    crm_periph_clock_enable(LCD_D4_GPIO_CLK, TRUE);
    crm_periph_clock_enable(LCD_D5_GPIO_CLK, TRUE);
    crm_periph_clock_enable(LCD_D6_GPIO_CLK, TRUE);
    crm_periph_clock_enable(LCD_D7_GPIO_CLK, TRUE);
    crm_periph_clock_enable(LCD_D8_GPIO_CLK, TRUE);
    crm_periph_clock_enable(LCD_D9_GPIO_CLK, TRUE);
    crm_periph_clock_enable(LCD_D10_GPIO_CLK, TRUE);
    crm_periph_clock_enable(LCD_D11_GPIO_CLK, TRUE);
    crm_periph_clock_enable(LCD_D12_GPIO_CLK, TRUE);
    crm_periph_clock_enable(LCD_D13_GPIO_CLK, TRUE);
    crm_periph_clock_enable(LCD_D14_GPIO_CLK, TRUE);
    crm_periph_clock_enable(LCD_D15_GPIO_CLK, TRUE);
    crm_periph_clock_enable(LCD_NE1_GPIO_CLK, TRUE);
    crm_periph_clock_enable(LCD_NWE_GPIO_CLK, TRUE);
    crm_periph_clock_enable(LCD_NOE_GPIO_CLK, TRUE);
    crm_periph_clock_enable(LCD_A16_GPIO_CLK, TRUE);
    crm_periph_clock_enable(LCD_BL_GPIO_CLK, TRUE);
    crm_periph_clock_enable(LCD_RESET_GPIO_CLK, TRUE);

    /* 开启XMC时钟 */
    crm_periph_clock_enable(CRM_XMC_PERIPH_CLOCK, TRUE);

    /*-- gpio 配置 ------------------------------------------------------*/
    gpio_pin_mux_config(LCD_D0_GPIO_PORT, LCD_D0_GPIO_PINS_SOURCE, LCD_D0_GPIO_MUX);
    gpio_pin_mux_config(LCD_D1_GPIO_PORT, LCD_D1_GPIO_PINS_SOURCE, LCD_D1_GPIO_MUX);
    gpio_pin_mux_config(LCD_D2_GPIO_PORT, LCD_D2_GPIO_PINS_SOURCE, LCD_D2_GPIO_MUX);
    gpio_pin_mux_config(LCD_D3_GPIO_PORT, LCD_D3_GPIO_PINS_SOURCE, LCD_D3_GPIO_MUX);
    gpio_pin_mux_config(LCD_D4_GPIO_PORT, LCD_D4_GPIO_PINS_SOURCE, LCD_D4_GPIO_MUX);
    gpio_pin_mux_config(LCD_D5_GPIO_PORT, LCD_D5_GPIO_PINS_SOURCE, LCD_D5_GPIO_MUX);
    gpio_pin_mux_config(LCD_D6_GPIO_PORT, LCD_D6_GPIO_PINS_SOURCE, LCD_D6_GPIO_MUX);
    gpio_pin_mux_config(LCD_D7_GPIO_PORT, LCD_D7_GPIO_PINS_SOURCE, LCD_D7_GPIO_MUX);
    gpio_pin_mux_config(LCD_D8_GPIO_PORT, LCD_D8_GPIO_PINS_SOURCE, LCD_D8_GPIO_MUX);
    gpio_pin_mux_config(LCD_D9_GPIO_PORT, LCD_D9_GPIO_PINS_SOURCE, LCD_D9_GPIO_MUX);
    gpio_pin_mux_config(LCD_D10_GPIO_PORT, LCD_D10_GPIO_PINS_SOURCE, LCD_D10_GPIO_MUX);
    gpio_pin_mux_config(LCD_D11_GPIO_PORT, LCD_D11_GPIO_PINS_SOURCE, LCD_D11_GPIO_MUX);
    gpio_pin_mux_config(LCD_D12_GPIO_PORT, LCD_D12_GPIO_PINS_SOURCE, LCD_D12_GPIO_MUX);
    gpio_pin_mux_config(LCD_D13_GPIO_PORT, LCD_D13_GPIO_PINS_SOURCE, LCD_D13_GPIO_MUX);
    gpio_pin_mux_config(LCD_D14_GPIO_PORT, LCD_D14_GPIO_PINS_SOURCE, LCD_D14_GPIO_MUX);
    gpio_pin_mux_config(LCD_D15_GPIO_PORT, LCD_D15_GPIO_PINS_SOURCE, LCD_D15_GPIO_MUX);
    gpio_pin_mux_config(LCD_NE1_GPIO_PORT, LCD_NE1_GPIO_PINS_SOURCE, LCD_NE1_GPIO_MUX);
    gpio_pin_mux_config(LCD_NWE_GPIO_PORT, LCD_NWE_GPIO_PINS_SOURCE, LCD_NWE_GPIO_MUX);
    gpio_pin_mux_config(LCD_NOE_GPIO_PORT, LCD_NOE_GPIO_PINS_SOURCE, LCD_NOE_GPIO_MUX);
    gpio_pin_mux_config(LCD_A16_GPIO_PORT, LCD_A16_GPIO_PINS_SOURCE, LCD_A16_GPIO_MUX);

    /* lcd 数据线配置 */
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;

    gpio_init_struct.gpio_pins = LCD_D0_GPIO_PIN;
    gpio_init(LCD_D0_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = LCD_D1_GPIO_PIN;
    gpio_init(LCD_D1_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = LCD_D2_GPIO_PIN;
    gpio_init(LCD_D2_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = LCD_D3_GPIO_PIN;
    gpio_init(LCD_D3_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = LCD_D4_GPIO_PIN;
    gpio_init(LCD_D4_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = LCD_D5_GPIO_PIN;
    gpio_init(LCD_D5_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = LCD_D6_GPIO_PIN;
    gpio_init(LCD_D6_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = LCD_D7_GPIO_PIN;
    gpio_init(LCD_D7_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = LCD_D8_GPIO_PIN;
    gpio_init(LCD_D8_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = LCD_D9_GPIO_PIN;
    gpio_init(LCD_D9_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = LCD_D10_GPIO_PIN;
    gpio_init(LCD_D10_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = LCD_D11_GPIO_PIN;
    gpio_init(LCD_D11_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = LCD_D12_GPIO_PIN;
    gpio_init(LCD_D12_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = LCD_D13_GPIO_PIN;
    gpio_init(LCD_D13_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = LCD_D14_GPIO_PIN;
    gpio_init(LCD_D14_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = LCD_D15_GPIO_PIN;
    gpio_init(LCD_D15_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = LCD_NE1_GPIO_PIN;
    gpio_init(LCD_NE1_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = LCD_NWE_GPIO_PIN;
    gpio_init(LCD_NWE_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = LCD_NOE_GPIO_PIN;
    gpio_init(LCD_NOE_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = LCD_A16_GPIO_PIN;
    gpio_init(LCD_A16_GPIO_PORT, &gpio_init_struct);
    // /* lcd BL  背光引脚配置 */
    // gpio_init_struct.gpio_pins = LCD_BL_GPIO_PIN;
    // gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    // gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    // gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    // gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    // gpio_init(LCD_BL_GPIO_PORT, &gpio_init_struct);
    // 背光由独立的 PWM 驱动模块初始化

    /* lcd rst  复位引脚配置 */
    gpio_init_struct.gpio_pins = LCD_RESET_GPIO_PIN;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init(LCD_RESET_GPIO_PORT, &gpio_init_struct);

    /*-- xmc 配置 ------------------------------------------------------*/
    xmc_norsram_default_para_init(&xmc_norsram_init_struct);
    xmc_norsram_init_struct.subbank = XMC_BANK1_NOR_SRAM1;
    xmc_norsram_init_struct.data_addr_multiplex = XMC_DATA_ADDR_MUX_DISABLE;
    xmc_norsram_init_struct.device = XMC_DEVICE_SRAM;
    xmc_norsram_init_struct.bus_type = XMC_BUSTYPE_16_BITS;
    xmc_norsram_init_struct.burst_mode_enable = XMC_BURST_MODE_DISABLE;
    xmc_norsram_init_struct.asynwait_enable = XMC_ASYN_WAIT_DISABLE;
    xmc_norsram_init_struct.wait_signal_lv = XMC_WAIT_SIGNAL_LEVEL_LOW;
    xmc_norsram_init_struct.wrapped_mode_enable = XMC_WRAPPED_MODE_DISABLE;
    xmc_norsram_init_struct.wait_signal_config = XMC_WAIT_SIGNAL_SYN_BEFORE;
    xmc_norsram_init_struct.write_enable = XMC_WRITE_OPERATION_ENABLE;
    xmc_norsram_init_struct.wait_signal_enable = XMC_WAIT_SIGNAL_DISABLE;
    xmc_norsram_init_struct.write_timing_enable = XMC_WRITE_TIMING_ENABLE;
    xmc_norsram_init_struct.write_burst_syn = XMC_WRITE_BURST_SYN_DISABLE;
    xmc_nor_sram_init(&xmc_norsram_init_struct);

    /* timing 配置 */
    xmc_norsram_timing_default_para_init(&rw_timing_struct, &w_timing_struct);
    rw_timing_struct.subbank = XMC_BANK1_NOR_SRAM1;
    rw_timing_struct.write_timing_enable = XMC_WRITE_TIMING_ENABLE;
    rw_timing_struct.addr_setup_time = 0x2;
    rw_timing_struct.addr_hold_time = 0x0;
    rw_timing_struct.data_setup_time = 0x2;
    rw_timing_struct.bus_latency_time = 0x0;
    rw_timing_struct.clk_psc = 0x0;
    rw_timing_struct.data_latency_time = 0x0;
    rw_timing_struct.mode = XMC_ACCESS_MODE_A;
    w_timing_struct.subbank = XMC_BANK1_NOR_SRAM1;
    w_timing_struct.write_timing_enable = XMC_WRITE_TIMING_ENABLE;
    w_timing_struct.addr_setup_time = 0x2;
    w_timing_struct.addr_hold_time = 0x0;
    w_timing_struct.data_setup_time = 0x2;
    w_timing_struct.bus_latency_time = 0x0;
    w_timing_struct.clk_psc = 0x0;
    w_timing_struct.data_latency_time = 0x0;
    w_timing_struct.mode = XMC_ACCESS_MODE_A;
    xmc_nor_sram_timing_config(&rw_timing_struct, &w_timing_struct);

    xmc_ext_timing_config(XMC_BANK1_NOR_SRAM1, 0, 0);
    /* 开启 xmc bank1_nor_sram1 */
    xmc_nor_sram_enable(XMC_BANK1_NOR_SRAM1, TRUE);
}

/**
 * @brief  lcd 数据读取
 * @param  none
 * @retval data
 */
uint16_t LCD::Read() {
    uint16_t data;

    data = *(__IO uint16_t *)XMC_LCD_DATA;

    return data;
}

/**
 * @brief  lcd 寄存器写入
 * @param  data:要写入的寄存器值
 * @retval none
 */
void LCD::RegWrite(uint16_t data) {
    *(__IO uint16_t *)XMC_LCD_COMMAND = data;
}

/**
 * @brief  lcd 数据写入
 * @param  data:要写入的数据值
 * @retval none
 */
void LCD::DataWrite(uint16_t data) {
    *(__IO uint16_t *)XMC_LCD_DATA = data;
}

/**
 * @brief  lcd 数据读取
 * @param  none
 * @retval 读取到的数据值
 */
uint16_t LCD::DataRead() {
    return Read();
}

/**
 * @brief  lcd 寄存器写入
 * @param  lcd_reg:寄存器地址
 * @param  lcd_regvalue:要写入的数据值
 * @retval none
 */
void LCD::CommandWrite(uint16_t lcd_comm, uint16_t lcd_regvalue) {
    *(__IO uint16_t *)XMC_LCD_COMMAND = lcd_comm;
    *(__IO uint16_t *)XMC_LCD_DATA = lcd_regvalue;
}

/**
 * @brief  lcd 寄存器读取
 * @param  lcd_reg:寄存器地址
 * @retval 读取到的数据值
 */
void LCD::CommandRead(uint16_t lcd_comm, uint8_t *rval, int32_t n) {
    RegWrite(lcd_comm);

    while (n--) {
        *(rval++) = DataRead();
    }
}

/**
 * @brief  lcd GRAM 写入
 * @param  none
 * @retval none
 */
void LCD::RamPrepareWrite() {
    RegWrite(lcddev.wramcmd);
}

/**
 * @brief  lcd GRAM 读取
 * @param  none
 * @retval none
 */
void LCD::RamPrepareRead() {
    RegWrite(lcddev.rramcmd);
}

/**
 * @brief  lcd 数据写入
 * @param  data:要写入的数据值
 * @retval none
 */
void LCD::Data16BitWrite(uint16_t data) {
#if LCD_USE8BIT_MODEL
    LCD->LCD_RAM = data >> 8;
    LCD->LCD_RAM = data;
#else
    *(__IO uint16_t *)XMC_LCD_DATA = data;
#endif
}

/**
 * @brief  将RGB颜色值转换为565格式
 * @param  red: 颜色红色值
 * @param  green: 颜色绿色值
 * @param  blue: 颜色蓝色值
 * @retval 转换后的565格式颜色值
 */
uint16_t LCD::ColorTo565(uint8_t red, uint8_t green, uint8_t blue) {
    return ((red & 0xF8) << 8) | ((green & 0xFC) << 3) | ((blue & 0xF8) >> 3);
}

/**
 * @brief  lcd 数据读取
 * @param  none
 * @retval 读取到的数据值
 */
uint16_t LCD::Data16BitRead() {
    uint16_t r, g, b;

    r = DataRead();
    // delay_us(1);

    r = DataRead();
    // delay_us(1);

    g = DataRead();

#if LCD_USE8BIT_MODEL
    delay_us(1);
    b = data_read();
#else
    b = g >> 8;
    g = r & 0xFF;
    r = r >> 8;
#endif

    return ColorTo565(r, g, b);
}

/**
 * @brief  lcd 像素点写入
 * @param  x:像素点的x坐标
 * @param  y:像素点的y坐标
 * @param  color:像素点的颜色值
 * @retval none
 */
void LCD::PointDraw(uint16_t x, uint16_t y, uint16_t color) {
    CursorSet(x, y);
    Data16BitWrite(color);
}

/**
 * @brief  lcd 直线绘制
 * @param  x_start:直线的起始x坐标
 * @param  x_end  :直线的结束x坐标
 * @param  y_start:直线的起始y坐标
 * @param  y_end  :直线的结束y坐标
 * @param  color  :直线的颜色值
 * @retval none
 */
void LCD::DrawLine(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color) {
    uint16_t t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    delta_x = x_end - x_start;
    delta_y = y_end - y_start;
    uRow = x_start;
    uCol = y_start;
    if (delta_x > 0)
        incx = 1;
    else if (delta_x == 0)
        incx = 0;
    else {
        incx = -1;
        delta_x = -delta_x;
    }
    if (delta_y > 0)
        incy = 1;
    else if (delta_y == 0)
        incy = 0;
    else {
        incy = -1;
        delta_y = -delta_y;
    }
    if (delta_x > delta_y)
        distance = delta_x;
    else
        distance = delta_y;
    for (t = 0; t <= distance + 1; t++) {
        PointDraw(uRow, uCol, color);
        xerr += delta_x;
        yerr += delta_y;
        if (xerr > distance) {
            xerr -= distance;
            uRow += incx;
        }
        if (yerr > distance) {
            yerr -= distance;
            uCol += incy;
        }
    }
}

/**
 * @brief  lcd 像素点读取
 * @param  x:像素点的x坐标
 * @param  y:像素点的y坐标
 * @retval 读取到的像素点颜色值
 */
uint16_t LCD::PointRead(uint16_t x, uint16_t y) {   
    uint16_t color;
    if (x >= lcddev.width || y >= lcddev.height) {
        return 0;
    }

    CursorSet(x, y);

    RamPrepareRead();

    color = Data16BitRead();

    return color;
}

/**
 * @brief  lcd 全屏填充
 * @param  color:填充颜色值
 * @retval none
 */
void LCD::Clear(uint16_t color) {
    uint32_t i;

    uint32_t total_point = lcddev.width * lcddev.height;

    WindowsSet(0, 0, lcddev.width - 1, lcddev.height - 1);

    for (i = 0; i < total_point; i++) {
#if LCD_USE8BIT_MODEL
        LCD->LCD_RAM = color >> 8;
        LCD->LCD_RAM = color;
#else
        *(__IO uint16_t *)XMC_LCD_DATA = color;
#endif
    }
}

/**
 * @brief  lcd 初始化
 * @param  direction: 显示方向
 *         该参数可以是以下值之一:
 *         - LCD_DISPLAY_VERTICAL: 垂直显示.
 *         - LCD_DISPLAY_HORIZONTAL: 水平显示.
 * @retval none
 */
void LCD::Init(lcd_display_type direction_) {
    XMCInit();
    LCD_RESET_HIGH();
    delay_ms(10);
    LCD_RESET_LOW();
    delay_ms(10);
    LCD_RESET_HIGH();
    delay_ms(10);

    RegWrite(0xF7);
    DataWrite(0xA9);
    DataWrite(0x51);
    DataWrite(0x2C);
    DataWrite(0x82);

    RegWrite(0xC0);
    DataWrite(0x11);
    DataWrite(0x09);

    RegWrite(0xC1);
    DataWrite(0x41);

    RegWrite(0xC5);
    DataWrite(0x00);
    DataWrite(0x0A);
    DataWrite(0x80);

    RegWrite(0xB1);
    DataWrite(0xB0);
    DataWrite(0x11);

    RegWrite(0xB4);
    DataWrite(0x02);

    RegWrite(0xB6);
    DataWrite(0x02);
    DataWrite(0x22);

    RegWrite(0xB7);
    DataWrite(0xc6);

    RegWrite(0xBE);
    DataWrite(0x00);
    DataWrite(0x04);

    RegWrite(0xE9);
    DataWrite(0x00);

    RegWrite(0x36);
    DataWrite(0x08);

    RegWrite(0x3A);
    DataWrite(0x55);

    RegWrite(0xE0);
    DataWrite(0x00);
    DataWrite(0x07);
    DataWrite(0x10);
    DataWrite(0x09);
    DataWrite(0x17);
    DataWrite(0x0B);
    DataWrite(0x41);
    DataWrite(0x89);
    DataWrite(0x4B);
    DataWrite(0x0A);
    DataWrite(0x0C);
    DataWrite(0x0E);
    DataWrite(0x18);
    DataWrite(0x1B);
    DataWrite(0x0F);

    RegWrite(0xE1);
    DataWrite(0x00);
    DataWrite(0x17);
    DataWrite(0x1A);
    DataWrite(0x04);
    DataWrite(0x0E);
    DataWrite(0x06);
    DataWrite(0x2F);
    DataWrite(0x45);
    DataWrite(0x43);
    DataWrite(0x02);
    DataWrite(0x0A);
    DataWrite(0x09);
    DataWrite(0x32);
    DataWrite(0x36);
    DataWrite(0x0F);

    RegWrite(0x11);
    delay_ms(10);
    RegWrite(0x29);
    delay_ms(10);

    Direction(direction_);
    delay_ms(10);
    // 初始化背光PWM并设置默认亮度（80%）
    BacklightInitPWM();
    BacklightSetPercent(80);
    delay_ms(10);
}

/**
 * @brief  lcd 窗口设置
 * @param  xstar:窗口的起始x坐标
 * @param  ystar:窗口的起始y坐标
 * @param  xend:窗口的结束x坐标
 * @param  yend:窗口的结束y坐标
 * @retval none
 */
void LCD::WindowsSet(uint16_t xstar, uint16_t ystar, uint16_t xend, uint16_t yend) {
    RegWrite(lcddev.setxcmd);
    DataWrite(xstar >> 8);
    DataWrite(0x00FF & xstar);
    DataWrite(xend >> 8);
    DataWrite(0x00FF & xend);

    RegWrite(lcddev.setycmd);
    DataWrite(ystar >> 8);
    DataWrite(0x00FF & ystar);
    DataWrite(yend >> 8);
    DataWrite(0x00FF & yend);

    RamPrepareWrite();
}

/**
 * @brief  lcd 光标设置
 * @param  xpos:像素点的x坐标
 * @param  ypos:像素点的y坐标
 * @retval none
 */
void LCD::CursorSet(uint16_t xpos, uint16_t ypos) {
    WindowsSet(xpos, ypos, xpos, ypos);
}

/**
 * @brief  lcd 显示方向设置
 * @param  direction:显示方向
 *         该参数可以是以下值之一:
 *         - LCD_DISPLAY_VERTICAL: 垂直显示.
 *         - LCD_DISPLAY_HORIZONTAL: 水平显示.
 * @retval none
 */
void LCD::Direction(uint8_t direction) {
    lcddev.setxcmd = 0x2A;
    lcddev.setycmd = 0x2B;
    lcddev.wramcmd = 0x2C;
    lcddev.rramcmd = 0x2E;
    lcddev.dir = direction % 4;

    switch (lcddev.dir) {
    case LCD_DISPLAY_HORIZONTAL:
        lcddev.width = LCD_H;
        lcddev.height = LCD_W;
        CommandWrite(0x36, (1 << 3) | (1 << 6) | (1 << 5));
        break;
    case LCD_DISPLAY_HORIZONTAL_180:
        lcddev.width = LCD_H;
        lcddev.height = LCD_W;
        CommandWrite(0x36, (1 << 3) | (1 << 7) | (1 << 5));
        break;
    case LCD_DISPLAY_VERTICAL:
        lcddev.width = LCD_W;
        lcddev.height = LCD_H;
        CommandWrite(0x36, (1 << 3) | (1 << 6) | (1 << 7));
        break;
    case LCD_DISPLAY_VERTICAL_180:
        lcddev.width = LCD_W;
        lcddev.height = LCD_H;
        CommandWrite(0x36, (1 << 3));
        break;
    default:
        break;
    }
}

/**
 * @brief  lcd id读取
 * @param  none
 * @retval id 值
 */
uint16_t LCD::IDRead(void) {
    uint8_t val[4] = {0};

    CommandRead(0xD3, val, 4);

    return (val[2] << 8) | val[3];
}

// C 接口包装器，保持与 lcd.h 兼容
extern "C" {
void LCD_XMCInit(void) {
    LCD::GetInstance().XMCInit();
}
uint16_t LCD_Read(void) {
    return LCD::GetInstance().Read();
}
void LCD_RegWrite(uint16_t data) {
    LCD::GetInstance().RegWrite(data);
}
void LCD_DataWrite(uint16_t data) {
    LCD::GetInstance().DataWrite(data);
}
uint16_t LCD_DataRead(void) {
    return LCD::GetInstance().DataRead();
}
void LCD_CommandWrite(uint16_t lcd_comm, uint16_t lcd_regvalue) {
    LCD::GetInstance().CommandWrite(lcd_comm, lcd_regvalue);
}
void LCD_CommandRead(uint16_t lcd_comm, uint8_t *rval, int32_t n) {
    LCD::GetInstance().CommandRead(lcd_comm, rval, n);
}
void LCD_RamPrepareWrite(void) {
    LCD::GetInstance().RamPrepareWrite();
}
void LCD_RamPrepareRead(void) {
    LCD::GetInstance().RamPrepareRead();
}
void LCD_Data16BitWrite(uint16_t data) {
    LCD::GetInstance().Data16BitWrite(data);
}
uint16_t LCD_ColorTo565(uint8_t r, uint8_t g, uint8_t b) {
    return LCD::GetInstance().ColorTo565(r, g, b);
}
uint16_t LCD_Data16BitRead(void) {
    return LCD::GetInstance().Data16BitRead();
}
void LCD_PointDraw(uint16_t x, uint16_t y, uint16_t color) {
    LCD::GetInstance().PointDraw(x, y, color);
}
uint16_t LCD_PointRead(uint16_t x, uint16_t y) {
    return LCD::GetInstance().PointRead(x, y);
}
void LCD_DrawLine(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color) {
    LCD::GetInstance().DrawLine(x_start, y_start, x_end, y_end, color);
}
void LCD_Clear(uint16_t color) {
    LCD::GetInstance().Clear(color);
}
void LCD_Init(lcd_display_type direction) {
    LCD::GetInstance().Init(direction);
}
void LCD_WindowsSet(uint16_t xstar, uint16_t ystar, uint16_t xend, uint16_t yend) {
    LCD::GetInstance().WindowsSet(xstar, ystar, xend, yend);
}
void LCD_CursorSet(uint16_t xpos, uint16_t ypos) {
    LCD::GetInstance().CursorSet(xpos, ypos);
}
void LCD_Direction(uint8_t direction) {
    LCD::GetInstance().Direction(direction);
}
uint16_t LCD_IDRead(void) {
    return LCD::GetInstance().IDRead();
}
}

/**
 * @brief  lcd 区域填充
 * @param  sx : 行坐标起始值
 * @param  sy : 列坐标起始值
 * @param  ex : 行坐标结束值
 * @param  ey : 列坐标结束值
 * @param  color : 填充颜色
 * @retval none
 */
void LCD_Fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color) {
    uint16_t height, width;
    uint16_t i, j;

    width = ex - sx + 1;
    height = ey - sy + 1;

    LCD::GetInstance().WindowsSet(sx, sy, ex, ey);

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            LCD::GetInstance().Data16BitWrite(color);
        }
    }
}

/**
 * @brief  lcd 区域颜色填充
 * @param  sx : 行坐标起始值
 * @param  sy : 列坐标起始值
 * @param  ex : 行坐标结束值
 * @param  ey : 列坐标结束值
 * @param  color : 颜色指针，用于填充lcd区域
 * @retval none
 */
void LCD_ColorFill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t *color) {
    uint16_t height, width;
    uint16_t i, j;

    width = ex - sx + 1;
    height = ey - sy + 1;

    LCD::GetInstance().WindowsSet(sx, sy, ex, ey);

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            LCD::GetInstance().Data16BitWrite(color[i * width + j]);
        }
    }
}

void LCD::BacklightInitPWM(void) {
    if (m_backlight_initialized) return;

    // 开启定时器1和背光GPIO时钟
    crm_periph_clock_enable(CRM_TMR1_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(LCD_BL_GPIO_CLK, TRUE);

    // 将 PA8 配置为 TIM1_CH1 (备用功能) 
    gpio_init_type gpio_init_struct;
    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_pins = LCD_BL_GPIO_PIN;
    gpio_init(LCD_BL_GPIO_PORT, &gpio_init_struct);
    gpio_pin_mux_config(LCD_BL_GPIO_PORT, LCD_BL_GPIO_PINS_SOURCE, LCD_BL_GPIO_MUX);

    // 配置定时器1为PWM模式，周期为1000000/100000=1000（10kHz）
    crm_clocks_freq_type clocks = {0};
    crm_clocks_freq_get(&clocks);
    m_prescaler = (uint16_t)((clocks.apb2_freq * 2) / 1000000) - 1; // 1MHz

    tmr_base_init(TMR1, (uint16_t)(m_backlight_period - 1), m_prescaler);
    tmr_cnt_dir_set(TMR1, TMR_COUNT_UP);
    tmr_clock_source_div_set(TMR1, TMR_CLOCK_DIV1);

    // PWM 通道配置
    tmr_output_config_type oc;
    tmr_output_default_para_init(&oc);
    oc.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_A;
    oc.oc_idle_state = FALSE;
    oc.oc_polarity = TMR_OUTPUT_ACTIVE_HIGH;
    oc.oc_output_state = TRUE;

    tmr_output_channel_config(TMR1, TMR_SELECT_CHANNEL_1, &oc);
    tmr_channel_value_set(TMR1, TMR_SELECT_CHANNEL_1, 0);
    tmr_output_channel_buffer_enable(TMR1, TMR_SELECT_CHANNEL_1, TRUE);
    tmr_period_buffer_enable(TMR1, TRUE);

    // 开启定时器1输出通道1
    tmr_output_enable(TMR1, TRUE);

    // 启动定时器1
    tmr_counter_enable(TMR1, TRUE);

    m_backlight_initialized = true;
}

/**
 * @brief  设置lcd背光亮度
 * @param  percent : 背光亮度百分比，范围0-100
 * @retval none
 */
void LCD::BacklightSetPercent(uint8_t percent) {
    if (!m_backlight_initialized) {
        BacklightInitPWM();
    }
    if (percent > 100) percent = 100;

    uint16_t arr = (uint16_t)(m_backlight_period - 1);
    uint16_t duty = (uint16_t)((arr * percent) / 100);
    tmr_channel_value_set(TMR1, TMR_SELECT_CHANNEL_1, duty);
}
