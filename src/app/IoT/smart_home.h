// 这是智能家居前端
#pragma once

#include "gui_guider.h"

// 智能家居事件
void smart_home_iot_color_led_event_handler(lv_event_t *e);          // IoT页面彩灯图标点击事件
void smart_home_iot_led_green_event_handler(lv_event_t *e);          // IoT页面绿灯图标点击事件
void smart_home_iot_adc_event_handler(lv_event_t *e);                // IoT页面ADC图标点击事件
void smart_home_iot_mpu6050_event_handler(lv_event_t *e);            // IoT页面MPU6050图标点击事件
void smart_home_iot_lm75_event_handler(lv_event_t *e);               // IoT页面LM75图标点击事件
void smart_home_iot_8key_event_handler(lv_event_t *e);               // IoT页面8Key图标点击事件
void smart_home_iot_return_event_handler(lv_event_t *e);             // IoT页面返回按键点击事件（关闭所有子页面）
void smart_home_color_led_sw_event_handler(lv_event_t *e);           // 彩灯开关事件
void smart_home_color_led_cpicker_event_handler(lv_event_t *e);      // 彩灯颜色选择事件
void smart_home_color_led_light_slider_event_handler(lv_event_t *e); // 彩灯亮度滑块事件
void smart_home_led_green_sw_event_handler(lv_event_t *e);           // 绿灯开关事件

// 通用页面滑动控制（供事件内部调用）
void smart_home_close_all_pages_with_slide(lv_ui *ui);           // 关闭所有IoT子页面（滑出并隐藏）
void smart_home_open_page_with_slide(lv_ui *ui, lv_obj_t *page); // 打开指定页面（滑入），并关闭其他页面


