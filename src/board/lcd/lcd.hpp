/**
 * @file     lcd.hpp
 * @brief    C++ LCD 类接口。实现驻留在 lcd.cpp 中。
 */

#pragma once

#include "lcd.h" // 重用类型、宏和 C 接口定义

class LCD {
  public:
    static LCD &GetInstance() {
        static LCD instance;
        return instance;
    }
    LCD(const LCD &) = delete;
    LCD &operator=(const LCD &) = delete;

    // High-level operations
    void init(lcd_display_type direction);
    void clear(uint16_t color);
    void draw_line(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color);
    void point_draw(uint16_t x, uint16_t y, uint16_t color);
    uint16_t point_read(uint16_t x, uint16_t y);
    void windows_set(uint16_t xstar, uint16_t ystar, uint16_t xend, uint16_t yend);
    void cursor_set(uint16_t xpos, uint16_t ypos);
    void direction(uint8_t direction);
    uint16_t id_read();

    // Low-level operations
    void xmc_init();
    uint16_t read();
    void reg_write(uint16_t data);
    void data_write(uint16_t data);
    uint16_t data_read();
    void command_write(uint16_t lcd_comm, uint16_t lcd_regvalue);
    void command_read(uint16_t lcd_comm, uint8_t *rval, int32_t n);
    void ram_prepare_write();
    void ram_prepare_read();
    void data_16bit_write(uint16_t data);
    uint16_t color_to_565(uint8_t r, uint8_t g, uint8_t b);
    uint16_t data_16bit_read();

  private:
    LCD() = default;
};