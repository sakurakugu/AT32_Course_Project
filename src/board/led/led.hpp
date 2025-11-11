#pragma once
#include "led.h"

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