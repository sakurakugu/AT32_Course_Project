#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

// 初始化计算器，提供用于显示的 LVGL 标签对象
void calculator_init(lv_obj_t *display_label);

// 处理一个按键输入，按键值示例："0".."9", "+", "-", "*", "/", "%", "(", ")", "=", "C", "⬅", "x", "÷"
void calculator_input_key(const char *key);

#ifdef __cplusplus
}
#endif

#endif // CALCULATOR_H


