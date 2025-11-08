/**
 * @brief 背光控制实现（当前为开关控制；如需PWM可后续扩展）
 */
#include <stdint.h>
#include "../board/lcd/lcd.h"

void backlight_set_percent(uint8_t percent) {
    if (percent == 0) {
        LCD_BL_LOW();
    } else {
        LCD_BL_HIGH();
    }
}