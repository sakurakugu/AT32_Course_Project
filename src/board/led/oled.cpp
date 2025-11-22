
// C++ OLED 类实现 + C 兼容接口包装

#include "oled.h"
#include "at32f435_437_clock.h"
#include "at32f435_437_gpio.h"
#include "delay.h"
#include "oled_font.h"

void OLED::Init() {
    GPIOConfig();
    SPIConfig();
    CSClr();
    RSTSet();
    delay_ms(10);
    RSTClr();
    delay_ms(10);
    RSTSet();

    WriteByte(0xAE, OLED_CMD); //--关闭OLED面板
    WriteByte(0x00, OLED_CMD); //---设置低列地址
    WriteByte(0x10, OLED_CMD); //---设置高列地址
    WriteByte(0x40, OLED_CMD); //--设置起始行地址
    WriteByte(0x81, OLED_CMD); //--设置对比度控制寄存器
    WriteByte(0xCF, OLED_CMD); // 亮度
    WriteByte(0xA1, OLED_CMD); //--SEG/列映射
    WriteByte(0xC8, OLED_CMD); //--COM/行扫描方向
    WriteByte(0xA6, OLED_CMD); //--正常显示
    WriteByte(0xA8, OLED_CMD); //--设置复用率(1到64)
    WriteByte(0x3f, OLED_CMD); //--设置复用率为64
    WriteByte(0xD3, OLED_CMD); //--设置显示偏移
    WriteByte(0x00, OLED_CMD); //--不偏移
    WriteByte(0xd5, OLED_CMD); //--设置显示时钟分频比/振荡器频率
    WriteByte(0x80, OLED_CMD); //--设置时钟为100帧/秒
    WriteByte(0xD9, OLED_CMD); //--预充电周期
    WriteByte(0xF1, OLED_CMD); //--预充电周期为15个时钟周期，放电周期为1个时钟周期
    WriteByte(0xDA, OLED_CMD); //--COM引脚硬件配置
    WriteByte(0x12, OLED_CMD); //--设置COM引脚硬件配置为 Alternative COM 配置
    WriteByte(0xDB, OLED_CMD); //--设置VCOMH电压倍率
    WriteByte(0x40, OLED_CMD); //--设置VCOM Deselect Level为0.77xVCC
    WriteByte(0x20, OLED_CMD); //--设置页地址模式
    WriteByte(0x02, OLED_CMD);
    WriteByte(0x8D, OLED_CMD); //--设置充电泵使能
    WriteByte(0x14, OLED_CMD);
    WriteByte(0xA4, OLED_CMD); //--设置整个显示关闭
    WriteByte(0xA6, OLED_CMD); //--设置正常显示
    WriteByte(0xAF, OLED_CMD); //--打开OLED面板

    WriteByte(0xAF, OLED_CMD); /*显示打开*/
    Clear();
    SetPos(0, 0);
}

void OLED::DisplayOn() {
    WriteByte(0X8D, OLED_CMD);
    WriteByte(0X14, OLED_CMD);
    WriteByte(0XAF, OLED_CMD);
}

void OLED::DisplayOff() {
    WriteByte(0X8D, OLED_CMD);
    WriteByte(0X10, OLED_CMD);
    WriteByte(0XAE, OLED_CMD);
}

void OLED::Clear() {
    uint8_t i, n;
    for (i = 0; i < 8; i++) {
        WriteByte(0xb0 + i, OLED_CMD); // 设置页地址（0~7）
        WriteByte(0x00, OLED_CMD);     // 设置显示位置—列低地址
        WriteByte(0x10, OLED_CMD);     // 设置显示位置—列高地址
        for (n = 0; n < 128; n++) {
            WriteByte(0x00, OLED_DATA);
        }
    } // 更新显示
}

void OLED::SetPos(uint8_t x, uint8_t y) {
    WriteByte(0xb0 + y, OLED_CMD);
    WriteByte(((x & 0xf0) >> 4) | 0x10, OLED_CMD);
    WriteByte((x & 0x0f), OLED_CMD);
}

// 在指定位置显示一个字符,包括部分字符
// x:0~127
// y:0~8
// mode:0,反白显示;1,正常显示
// size:选择字体 16/8
void OLED::ShowChar(uint8_t x, uint8_t y, uint8_t chr) {
    unsigned char c = 0, i = 0;
    c = chr - ' ';
    if (x > Max_Column - 1) {
        x = 0;
        y = y + 2;
    }
    if (SIZE == 16) {
        SetPos(x, y);
        for (i = 0; i < 8; i++)
            WriteByte(oled_font_8X16[c * 16 + i], OLED_DATA);
        SetPos(x, y + 1);
        for (i = 0; i < 8; i++)
            WriteByte(oled_font_8X16[c * 16 + i + 8], OLED_DATA);
    } else {
        SetPos(x, y + 1);
        for (i = 0; i < 6; i++) {
            WriteByte(oled_font_6x8[c][i], OLED_DATA);
        }
    }
}

void OLED::ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size2) {
    uint8_t t, temp;
    uint8_t enshow = 0;
    for (t = 0; t < len; t++) {
        temp = (num / PowUint32_t(10, len - t - 1)) % 10;
        if (enshow == 0 && t < (len - 1)) {
            if (temp == 0) {
                ShowChar(x + (size2 / 2) * t, y, ' ');
                continue;
            } else {
                enshow = 1;
            }
        }
        ShowChar(x + (size2 / 2) * t, y, temp + '0');
    }
}

void OLED::ShowString(uint8_t x, uint8_t y, uint8_t *str) {
    unsigned char j = 0;
    while (str[j] != '\0') {
        ShowChar(x, y, str[j]);
        x += 8;
        if (x > 120) {
            x = 0;
            y += 2;
        }
        j++;
    }
}

void OLED::ShowChinese(uint8_t x, uint8_t y, uint8_t no) {
    uint8_t t;
    SetPos(x, y);
    for (t = 0; t < 16; t++) {
        WriteByte(Hzk[2 * no][t], OLED_DATA);       
    }
    SetPos(x, y + 1);
    for (t = 0; t < 16; t++) {
        WriteByte(Hzk[2 * no + 1][t], OLED_DATA);
    }
}

void OLED::ShowCHStr(uint8_t X, uint8_t Y, uint8_t *pstr) {
    unsigned char i;
    unsigned char Addr = 0;
    unsigned char count = 0;

    while (*pstr) {
        for (i = 0; i < oled_font_chinese_12x12_len; i++) {
            if ((*pstr == oled_font_chinese_12x12[i].value[0]) && (*(pstr + 1) == oled_font_chinese_12x12[i].value[1])) {
                Addr = i;
                break;
            }
        }
        SetPos(X + count * 12, Y);
        for (i = 0; i < 12; i++) {
            WriteByte(oled_font_chinese_12x12[Addr].data[i], OLED_DATA);
        }
        SetPos(X + count * 12, Y + 1);
        for (i = 0; i < 12; i++) {
            WriteByte(oled_font_chinese_12x12[Addr].data[12 + i], OLED_DATA);
        }
        count++;
        pstr++;
        pstr++;
    }
}

void OLED::DrawBMP(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, unsigned char BMP[]) {
    unsigned int j = 0;
    unsigned char x, y;

    if (y1 % 8 == 0)
        y = y1 / 8;
    else
        y = y1 / 8 + 1;
    for (y = y0; y < y1; y++) {
        SetPos(x0, y);
        for (x = x0; x < x1; x++) {
            WriteByte(BMP[j++], OLED_DATA);
        }
    }
}

void OLED::WriteByte(uint8_t dat, uint8_t cmd) {
    if (cmd == OLED_DATA) {
        DCSet();
    } else {
        DCClr();
    }
    CSClr();
    SPITransferByte(dat);
    CSSet();
    DCSet();
}

uint32_t OLED::PowUint32_t(uint8_t m, uint8_t n) {
    uint32_t result = 1;
    while (n--)
        result *= m;
    return result;
}

void OLED::DCSet() {
    gpio_bits_write(GPIOD, GPIO_PINS_6, TRUE);
}
void OLED::DCClr() {
    gpio_bits_write(GPIOD, GPIO_PINS_6, FALSE);
}
void OLED::CSSet() {
    gpio_bits_write(GPIOD, GPIO_PINS_3, TRUE);
}
void OLED::CSClr() {
    gpio_bits_write(GPIOD, GPIO_PINS_3, FALSE);
}
void OLED::RSTSet() {
    gpio_bits_write(GPIOE, GPIO_PINS_6, TRUE);
}
void OLED::RSTClr() {
    gpio_bits_write(GPIOE, GPIO_PINS_6, FALSE);
}

void OLED::SPITransferByte(uint8_t data) {
    spi_i2s_data_transmit(SPI3, data);
    while (spi_i2s_flag_get(SPI3, SPI_I2S_BF_FLAG) == SET) {}
}

void OLED::SPIConfig() {
    spi_init_type spi_init_struct;
    crm_periph_clock_enable(CRM_SPI3_PERIPH_CLOCK, TRUE);

    spi_default_para_init(&spi_init_struct);
    spi_init_struct.transmission_mode = SPI_TRANSMIT_HALF_DUPLEX_TX;
    spi_init_struct.master_slave_mode = SPI_MODE_MASTER;
    spi_init_struct.mclk_freq_division = SPI_MCLK_DIV_32;
    spi_init_struct.first_bit_transmission = SPI_FIRST_BIT_MSB;
    spi_init_struct.frame_bit_num = SPI_FRAME_8BIT;
    spi_init_struct.clock_polarity = SPI_CLOCK_POLARITY_LOW;
    spi_init_struct.clock_phase = SPI_CLOCK_PHASE_1EDGE;
    spi_init_struct.cs_mode_selection = SPI_CS_SOFTWARE_MODE;
    spi_init(SPI3, &spi_init_struct);

    spi_enable(SPI3, TRUE);
}

void OLED::GPIOConfig() {
    gpio_init_type gpio_initstructure;
    crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOE_PERIPH_CLOCK, TRUE);

    gpio_default_para_init(&gpio_initstructure);
    // spi3 sck pin PB3
    gpio_initstructure.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_initstructure.gpio_pull = GPIO_PULL_DOWN;
    gpio_initstructure.gpio_mode = GPIO_MODE_MUX;
    gpio_initstructure.gpio_pins = GPIO_PINS_3;
    gpio_init(GPIOB, &gpio_initstructure);
    gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE3, GPIO_MUX_6);

    // spi3 mosi pin PB5
    gpio_initstructure.gpio_pull = GPIO_PULL_DOWN;
    gpio_initstructure.gpio_pins = GPIO_PINS_5;
    gpio_init(GPIOB, &gpio_initstructure);
    gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE5, GPIO_MUX_6);

    // 默认参数
    gpio_default_para_init(&gpio_initstructure);

    // CS, DC pins on GPIOD
    gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_initstructure.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_initstructure.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_initstructure.gpio_pins = GPIO_PINS_3;
    gpio_initstructure.gpio_pull = GPIO_PULL_NONE;
    gpio_init(GPIOD, &gpio_initstructure);

    gpio_initstructure.gpio_pins = GPIO_PINS_6;
    gpio_init(GPIOD, &gpio_initstructure);
}
