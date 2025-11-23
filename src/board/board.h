#pragma once

#include "beep.hpp"
#include "key/key.h"
#include "led/color_led.h"
#include "led/oled.h"
#include "led/led.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class Board {
  public:
    static Board &GetInstance() {
        static Board instance;
        return instance;
    }
    Board(const Board &) = delete;            // 禁用拷贝构造函数
    Board &operator=(const Board &) = delete; // 禁用赋值操作

    void Init();
    Key &GetKey() { return key_; }
    ColorLed &GetColorLed() { return color_led_; }
    Beep &GetBeep() { return beep_; }
    OLED &GetOLED() { return oled_; }
    LED &GetLED() { return led_; }

  private:
    Board() = default;
    ~Board() = default;

    Key key_;
    Beep beep_;
    ColorLed color_led_;
    LED led_;
    OLED oled_;
};
