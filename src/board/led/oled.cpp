
// C++ OLED 类实现 + C 兼容接口包装

#include "oled.h"
#include "at32f435_437_clock.h"
#include "at32f435_437_gpio.h"
#include "delay.h"
#include "oled_font.h"

void OLED::init() {
    gpioConfig();
    spiConfig();
    csClr();
    rstSet();
    delay_ms(10);
    rstClr();
    delay_ms(10);
    rstSet();

    writeByte(0xAE, OLED_CMD); //--turn off oled panel
    writeByte(0x00, OLED_CMD); //---set low column address
    writeByte(0x10, OLED_CMD); //---set high column address
    writeByte(0x40, OLED_CMD); //--set start line address
    writeByte(0x81, OLED_CMD); //--set contrast control register
    writeByte(0xCF, OLED_CMD); // brightness
    writeByte(0xA1, OLED_CMD); //--SEG/Column Mapping
    writeByte(0xC8, OLED_CMD); //--COM/Row Scan Direction
    writeByte(0xA6, OLED_CMD); //--normal display
    writeByte(0xA8, OLED_CMD); //--multiplex ratio(1 to 64)
    writeByte(0x3f, OLED_CMD); //--1/64 duty
    writeByte(0xD3, OLED_CMD); //--display offset
    writeByte(0x00, OLED_CMD); //--not offset
    writeByte(0xd5, OLED_CMD); //--display clock divide ratio
    writeByte(0x80, OLED_CMD); //--Set Clock as 100 Frames/Sec
    writeByte(0xD9, OLED_CMD); //--pre-charge period
    writeByte(0xF1, OLED_CMD); //--Pre-Charge as 15 Clocks & Discharge as 1 Clock
    writeByte(0xDA, OLED_CMD); //--com pins hardware configuration
    writeByte(0x12, OLED_CMD);
    writeByte(0xDB, OLED_CMD); //--vcomh
    writeByte(0x40, OLED_CMD); //--VCOM Deselect Level
    writeByte(0x20, OLED_CMD); //--Page Addressing Mode
    writeByte(0x02, OLED_CMD);
    writeByte(0x8D, OLED_CMD); //--Charge Pump enable
    writeByte(0x14, OLED_CMD);
    writeByte(0xA4, OLED_CMD); //--Disable Entire Display On
    writeByte(0xA6, OLED_CMD); //--Disable Inverse Display On
    writeByte(0xAF, OLED_CMD); //--turn on oled panel

    writeByte(0xAF, OLED_CMD); /*display ON*/
    clear();
    setPos(0, 0);
}

void OLED::displayOn() {
    writeByte(0X8D, OLED_CMD);
    writeByte(0X14, OLED_CMD);
    writeByte(0XAF, OLED_CMD);
}

void OLED::displayOff() {
    writeByte(0X8D, OLED_CMD);
    writeByte(0X10, OLED_CMD);
    writeByte(0XAE, OLED_CMD);
}

void OLED::clear() {
    uint8_t i, n;
    for (i = 0; i < 8; i++) {
        writeByte(0xb0 + i, OLED_CMD); // 设置页地址（0~7）
        writeByte(0x00, OLED_CMD);     // 设置显示位置—列低地址
        writeByte(0x10, OLED_CMD);     // 设置显示位置—列高地址
        for (n = 0; n < 128; n++) {
            writeByte(0x00, OLED_DATA);
        }
    } // 更新显示
}

void OLED::setPos(uint8_t x, uint8_t y) {
    writeByte(0xb0 + y, OLED_CMD);
    writeByte(((x & 0xf0) >> 4) | 0x10, OLED_CMD);
    writeByte((x & 0x0f), OLED_CMD);
}

// 在指定位置显示一个字符,包括部分字符
// x:0~127
// y:0~8
// mode:0,反白显示;1,正常显示
// size:选择字体 16/8
void OLED::showChar(uint8_t x, uint8_t y, uint8_t chr) {
    unsigned char c = 0, i = 0;
    c = chr - ' ';
    if (x > Max_Column - 1) {
        x = 0;
        y = y + 2;
    }
    if (SIZE == 16) {
        setPos(x, y);
        for (i = 0; i < 8; i++)
            writeByte(F8X16[c * 16 + i], OLED_DATA);
        setPos(x, y + 1);
        for (i = 0; i < 8; i++)
            writeByte(F8X16[c * 16 + i + 8], OLED_DATA);
    } else {
        setPos(x, y + 1);
        for (i = 0; i < 6; i++) {
            writeByte(F6x8[c][i], OLED_DATA);
        }
    }
}

void OLED::showNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size2) {
    uint8_t t, temp;
    uint8_t enshow = 0;
    for (t = 0; t < len; t++) {
        temp = (num / pow_uint32_t(10, len - t - 1)) % 10;
        if (enshow == 0 && t < (len - 1)) {
            if (temp == 0) {
                showChar(x + (size2 / 2) * t, y, ' ');
                continue;
            } else {
                enshow = 1;
            }
        }
        showChar(x + (size2 / 2) * t, y, temp + '0');
    }
}

void OLED::showString(uint8_t x, uint8_t y, uint8_t *str) {
    unsigned char j = 0;
    while (str[j] != '\0') {
        showChar(x, y, str[j]);
        x += 8;
        if (x > 120) {
            x = 0;
            y += 2;
        }
        j++;
    }
}

void OLED::showChinese(uint8_t x, uint8_t y, uint8_t no) {
    uint8_t t;
    setPos(x, y);
    for (t = 0; t < 16; t++) {
        writeByte(Hzk[2 * no][t], OLED_DATA);
    }
    setPos(x, y + 1);
    for (t = 0; t < 16; t++) {
        writeByte(Hzk[2 * no + 1][t], OLED_DATA);
    }
}

void OLED::showCHStr(uint8_t X, uint8_t Y, uint8_t *pstr) {
    unsigned char i;
    unsigned char Addr = 0;
    unsigned char count = 0;

    while (*pstr) {
        for (i = 0; i < chinese_12_len; i++) {
            if ((*pstr == chinese_12[i].value[0]) && (*(pstr + 1) == chinese_12[i].value[1])) {
                Addr = i;
                break;
            }
        }
        setPos(X + count * 12, Y);
        for (i = 0; i < 12; i++) {
            writeByte(chinese_12[Addr].data[i], 1);
        }
        setPos(X + count * 12, Y + 1);
        for (i = 0; i < 12; i++) {
            writeByte(chinese_12[Addr].data[12 + i], 1);
        }
        count++;
        pstr++;
        pstr++;
    }
}

void OLED::drawBMP(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, unsigned char BMP[]) {
    unsigned int j = 0;
    unsigned char x, y;

    if (y1 % 8 == 0)
        y = y1 / 8;
    else
        y = y1 / 8 + 1;
    for (y = y0; y < y1; y++) {
        setPos(x0, y);
        for (x = x0; x < x1; x++) {
            writeByte(BMP[j++], OLED_DATA);
        }
    }
}

void OLED::writeByte(uint8_t dat, uint8_t cmd) {
    if (cmd == OLED_DATA) {
        dcSet();
    } else {
        dcClr();
    }
    csClr();
    spiTransferByte(dat);
    csSet();
    dcSet();
}

uint32_t OLED::pow_uint32_t(uint8_t m, uint8_t n) {
    uint32_t result = 1;
    while (n--)
        result *= m;
    return result;
}

void OLED::dcSet() {
    gpio_bits_write(GPIOD, GPIO_PINS_6, TRUE);
}
void OLED::dcClr() {
    gpio_bits_write(GPIOD, GPIO_PINS_6, FALSE);
}
void OLED::csSet() {
    gpio_bits_write(GPIOD, GPIO_PINS_3, TRUE);
}
void OLED::csClr() {
    gpio_bits_write(GPIOD, GPIO_PINS_3, FALSE);
}
void OLED::rstSet() {
    gpio_bits_write(GPIOE, GPIO_PINS_6, TRUE);
}
void OLED::rstClr() {
    gpio_bits_write(GPIOE, GPIO_PINS_6, FALSE);
}

void OLED::spiTransferByte(uint8_t data) {
    spi_i2s_data_transmit(SPI3, data);
    while (spi_i2s_flag_get(SPI3, SPI_I2S_BF_FLAG) == SET) {}
}

void OLED::spiConfig() {
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

void OLED::gpioConfig() {
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

    // default parameter
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
