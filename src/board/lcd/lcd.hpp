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
    void Init(lcd_display_type direction);                                                              // 初始化 LCD
    void Clear(uint16_t color);                                                                         // 清除 LCD 屏幕
    void DrawLine(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color); // 绘制一条线
    void PointDraw(uint16_t x, uint16_t y, uint16_t color);                                            // 绘制一个点
    uint16_t PointRead(uint16_t x, uint16_t y);                                    // 读取一个点的颜色
    void WindowsSet(uint16_t xstar, uint16_t ystar, uint16_t xend, uint16_t yend); // 设置窗口
    void CursorSet(uint16_t xpos, uint16_t ypos);                                  // 设置光标位置
    void Direction(uint8_t direction);                                              // 设置显示方向
    uint16_t IDRead();                                                             // 读取 LCD ID

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