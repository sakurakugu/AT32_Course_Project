/**
 * @file custom.c
 * @brief 自定义函数实现文件
 * @details 包含自定义函数的实现，如更新音量图标等（该文件不会被覆盖）
 */

#include "custom.h"
#include "lvgl.h"
#include <stdio.h>
#include <string.h>

#include "../../src/app/calculator/calculator.h"
#include "../../src/board/sound/beep.h" // 蜂鸣器接口：设定频率并发声
#include "../lvgl/src/extra/widgets/dclock/lv_dclock.h"

#ifdef KEIL_COMPILE
// 背光、音量、网络时间同步接口
#include "../../src/app/setting/setting.h"
#endif

void custom_init(lv_ui *ui) {
    // 初始化统一状态栏与导航栈
    status_bar_init(ui);
    status_bar_update_sound(true);
#ifdef KEIL_COMPILE
    Beep_SetMute(0);
#endif
    // 清空导航栈
    // （栈定义在本文件的静态区域）
    // 无需额外操作：status_bar_init 不依赖当前屏幕
}


