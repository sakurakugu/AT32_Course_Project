/**
 * @file custom.c
 * @brief 自定义函数实现文件
 * @details 包含自定义函数的实现，如更新音量图标等（该文件不会被覆盖）
 */

#include "custom.h"
#include "lvgl.h"
#include <stdio.h>

/*********************
 *      宏定义
 *********************/

/**********************
 *      类型定义
 **********************/

/**********************
 *  STATIC 函数原型
 **********************/

/**********************
 *  STATIC 变量
 **********************/

/**
 * Create a demo application
 */

void custom_init(lv_ui *ui) {
    /* Add your codes here */
}

/**
 * @brief 更新音量图标
 * @param ui 指向lv_ui结构体的指针，用于访问GUI元素
 * @param volume 音量值，0表示静音，1-100表示不同音量等级
 */
void update_volume_icon(lv_ui *ui, uint8_t volume) {
    if (volume > 0) {
        // 显示“有音量”
        // lv_obj_clear_flag(ui->screen_voice_on, LV_OBJ_FLAG_HIDDEN);
        // lv_obj_add_flag(ui->screen_voice_off, LV_OBJ_FLAG_HIDDEN);
    } else {
        // 显示“静音”
        // lv_obj_add_flag(ui->screen_voice_on, LV_OBJ_FLAG_HIDDEN);
        // lv_obj_clear_flag(ui->screen_voice_off, LV_OBJ_FLAG_HIDDEN);
    }
}

