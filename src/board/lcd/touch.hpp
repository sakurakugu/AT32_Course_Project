#pragma once

#include <at32f435_437.h>
#include <stdint.h>

extern "C" {
#include "touch.h"
}

class Touch {
  public:
    static Touch &GetInstance() {
        static Touch instance;
        return instance;
    }
    Touch(const Touch &) = delete;
    Touch &operator=(const Touch &) = delete;

    bool Init(touch_scan_type direction);
    bool Read(uint16_t &x, uint16_t &y);
    bool Adjust();

  private:
    Touch() {}
    ~Touch() {}

    touch_scan_type m_direction = TOUCH_SCAN_VERTICAL; /* 触摸扫描方向 */
    // uint16_t x_p[6];                                 // 保存x坐标
    // uint16_t y_p[6];                                 // 保存y坐标
};