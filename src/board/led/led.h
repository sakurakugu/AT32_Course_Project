#pragma once
#include <stdint.h>

typedef enum {
    LED_Green = 0,
    LED_Yellow = 1,
} led_type;

#define LED_NUM 2

#define LED_Green_PIN GPIO_PINS_12
#define LED_Green_GPIO GPIOC
#define LED_Green_GPIO_CRM_CLK CRM_GPIOC_PERIPH_CLOCK

#define LED_Yellow_PIN GPIO_PINS_9
#define LED_Yellow_GPIO GPIOC
#define LED_Yellow_GPIO_CRM_CLK CRM_GPIOC_PERIPH_CLOCK

class LED {
  public:
    static LED &GetInstance() {
        static LED instance;
        return instance;
    }
    // 删除拷贝构造函数和赋值运算符
    LED(const LED &) = delete;
    LED &operator=(const LED &) = delete;

    void Init(led_type led);
    void On(led_type led);
    void Off(led_type led);
    void Toggle(led_type led);

  private:
    LED() = default;
    ~LED() = default;
    uint8_t led_pin;
};