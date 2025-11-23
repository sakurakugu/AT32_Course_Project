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
#include <stdbool.h>
#include <stdio.h>

#include "../../src/app/calculator/calculator.h"       // 计算器接口：供界面自定义代码调用
#include "../../src/app/clock/clock_app.h"             // 时钟接口：供界面自定义代码调用
#include "../../src/app/drawing_board/drawing_board.h" // 绘图画布接口：供界面自定义代码调用
#include "../../src/app/system_bars/system_bars.h"

#include "../../src/app/IoT/smart_home.h"
#include "../../src/app/electronic_organ/electronic_organ.h"
#include "../../src/app/link_game/link_game.h"
#include "../../src/app/minecraft/minecraft.h"
#include "../../src/app/music/music.h" // 音乐模块控制标志与曲目定义
#include "../../src/app/setting/setting.h"

#ifdef KEIL_COMPILE
#endif

// 全局变量：状态栏日期标签（用于更新日期）
extern lv_obj_t *g_status_bar_date;
// 全局变量：时间小时、分钟、秒（用于更新时间）
extern int clock_app_g_time_hour_value;
extern int clock_app_g_time_min_value;
extern int clock_app_g_time_sec_value;

void custom_init(lv_ui *ui);


#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
