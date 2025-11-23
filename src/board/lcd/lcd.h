/**
 * @file  lcd.h
 * @brief LCD类 的 C接口, 为LVGL和C模块提供.
 */

#pragma once
#include <stdint.h>

// lcd 命令/数据地址定义
#define XMC_LCD_COMMAND 0x6007FFFE
#define XMC_LCD_DATA    0x60080000

#ifdef __cplusplus
extern "C" {
#endif

// C 接口函数，用于 LVGL 和 C 模块
void LCD_WindowsSet(uint16_t xstar, uint16_t ystar, uint16_t xend, uint16_t yend);

#ifdef __cplusplus
}
#endif