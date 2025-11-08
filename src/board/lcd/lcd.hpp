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

    // 高等级操作
    void init(lcd_display_type direction);                                                              // 初始化 LCD
    void clear(uint16_t color);                                                                         // 清除 LCD 屏幕
    void draw_line(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color); // 绘制一条线
    void point_draw(uint16_t x, uint16_t y, uint16_t color);                                            // 绘制一个点
    uint16_t point_read(uint16_t x, uint16_t y);                                    // 读取一个点的颜色
    void windows_set(uint16_t xstar, uint16_t ystar, uint16_t xend, uint16_t yend); // 设置窗口
    void cursor_set(uint16_t xpos, uint16_t ypos);                                  // 设置光标位置
    void direction(uint8_t direction);                                              // 设置显示方向
    uint16_t id_read();                                                             // 读取 LCD ID

    // 低等级操作
    void xmc_init();                                                // 初始化 XMC
    uint16_t read();                                                // 读取数据
    void reg_write(uint16_t data);                                  // 写入寄存器
    void data_write(uint16_t data);                                 // 写入数据
    uint16_t data_read();                                           // 读取数据
    void command_write(uint16_t lcd_comm, uint16_t lcd_regvalue);   // 写入命令
    void command_read(uint16_t lcd_comm, uint8_t *rval, int32_t n); // 读取命令
    void ram_prepare_write();                                       // 准备写入 RAM
    void ram_prepare_read();                                        // 准备读取 RAM
    void data_16bit_write(uint16_t data);                           // 写入 16 位数据
    uint16_t color_to_565(uint8_t r, uint8_t g, uint8_t b);         // 将 RGB 转换为 565 格式
    uint16_t data_16bit_read();                                     // 读取 16 位数据

  private:
    LCD() = default;
};