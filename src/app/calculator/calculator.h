#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

// 初始化计算器，提供用于显示的 LVGL 标签对象
void Calculator_Init(lv_obj_t *display_label);

// 处理一个按键输入，按键值示例："0".."9", "+", "-", "*", "/", "%", "(", ")", "=", "C", "⬅", "x", "÷"
void Calculator_InputKey(const char *key);

void calc_key_event_handler(lv_event_t *e);         // 计算器按键事件处理器

#ifdef __cplusplus
}
#endif

#endif // CALCULATOR_H


