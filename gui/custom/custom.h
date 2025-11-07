/**
 * @file custom.h
 * @brief 自定义函数头文件
 * @details 包含自定义函数的声明，如更新音量图标等（该文件不会被覆盖）
 */

#ifndef __CUSTOM_H_
#define __CUSTOM_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"
#include <stdio.h>

void custom_init(lv_ui *ui);

// 更新音量图标
void update_volume_icon(lv_ui *ui, uint8_t volume);

#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
