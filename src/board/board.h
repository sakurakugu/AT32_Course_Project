#pragma once

#include "bsp_ext_flash.h"
#include "key/key.h"
#include "led/color_led.hpp"
#include "led/oled.h"
#include "timer.h"
#include "uart.h"
#include "beep.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#define ESP12_DEBUG 0

void ADC_Config(void);
uint16_t AnalogRead(void);

/* 定义优先级分组 */
#define NVIC_PREEMPT_PRIORITY 4
}

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

  private:
    Board() = default;
    ~Board() = default;

    Key key_;
    Beep beep_;
    ColorLed color_led_;
};
