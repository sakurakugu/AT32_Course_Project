/**
 **************************************************************************
 * @file     touch.h
 * @version  v2.0.0
 * @date     2020-11-02
 * @brief    触摸屏应用库头文件
 */

#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 触摸屏导出函数
 */
bool Touch_ReadXY(uint16_t *x, uint16_t *y);

#ifdef __cplusplus
}
#endif
