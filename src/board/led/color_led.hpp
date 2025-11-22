#pragma once
#include "color_led.h"

class ColorLed {
  public:
    static ColorLed &GetInstance() {
        static ColorLed instance;
        return instance;
    }
    // 删除拷贝构造函数和赋值运算符
    ColorLed(const ColorLed &) = delete;
    ColorLed &operator=(const ColorLed &) = delete;

    void Init(); // 初始化颜色LED
    void SetColor(uint8_t r, uint8_t g, uint8_t b); // 设置RGB颜色
    void SetBrightness(uint8_t brightness); // 设置亮度 (0-100)
    void TurnOn(); // 打开彩灯
    void TurnOff(); // 关闭彩灯

  private:
    ColorLed() = default;
    ~ColorLed() = default;
    uint8_t current_r = 255;
    uint8_t current_g = 255;
    uint8_t current_b = 255;
    uint8_t current_brightness = 100;
};