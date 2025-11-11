#pragma once
#include "color_led.h"

class Color_Led {
  public:
    static Color_Led &GetInstance() {
        static Color_Led instance;
        return instance;
    }
    // 删除拷贝构造函数和赋值运算符
    Color_Led(const Color_Led &) = delete;
    Color_Led &operator=(const Color_Led &) = delete;

    void Init(); // 初始化颜色LED
    void SetColor(uint8_t r, uint8_t g, uint8_t b); // 设置RGB颜色
    void SetBrightness(uint8_t brightness); // 设置亮度 (0-100)
    void TurnOn(); // 打开彩灯
    void TurnOff(); // 关闭彩灯

  private:
    Color_Led() = default;
    ~Color_Led() = default;
    uint8_t current_r = 255;
    uint8_t current_g = 255;
    uint8_t current_b = 255;
    uint8_t current_brightness = 100;
};