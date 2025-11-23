#pragma once

#include <stdint.h>

enum led_type {
    LED_Green = 0,
    LED_Yellow = 1,
};

#define LED_NUM 2

#define LED_Green_PIN GPIO_PINS_12
#define LED_Green_GPIO GPIOC
#define LED_Green_GPIO_CRM_CLK CRM_GPIOC_PERIPH_CLOCK

#define LED_Yellow_PIN GPIO_PINS_9
#define LED_Yellow_GPIO GPIOC
#define LED_Yellow_GPIO_CRM_CLK CRM_GPIOC_PERIPH_CLOCK

class LED {
  public:
    // 删除拷贝构造函数和赋值运算符
    LED(const LED &) = delete;
    LED &operator=(const LED &) = delete;

    void Init(led_type led);
    void TurnOn(led_type led);
    void TurnOff(led_type led);
    void Toggle(led_type led);

  private:
    friend class Board;
    LED() = default;
    ~LED() = default;
    uint8_t led_pin;
};