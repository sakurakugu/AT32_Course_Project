/**
 * @brief 定时器模块
 * @file timer.h
 */

#pragma once

#include "at32f435_437_crm.h"
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif

#define time_after(a, b) ((s32)((s32)(b) - (s32)(a)) < 0) // 比较当前节拍是否已超过目标时间（按有符号差）。
#define Timer_PassedDelay(startTime, msDelay)                                                                          \
    (time_after(Timer_GetTickCount(), (startTime + msDelay))) // 判断从 `startTime` 起是否已过去 `msDelay` 毫秒。
#define interval(a, b) ((s32)((s32)(b) - (s32)(a)))           // 计算两个节拍值的差（可能为负，用于间隔判断）。

#define Timer_GetTickCount() (systick_ms) // 获取系统毫秒节拍计数。

extern volatile unsigned int systick_ms; // 系统毫秒节拍计数（由 TMR6 中断累加）。
/*
    在此定义若干个软件定时器全局变量
    注意，必须增加__IO 即 volatile，因为这个变量在中断和主程序中同时被访问，有可能造成编译器错误优化。
*/
#define TMR_COUNT 4 /* 软件定时器的个数 （定时器ID范围 0 - 3) */

/* 定时器结构体，成员变量必须是 volatile, 否则C编译器优化时可能有问题 */
typedef enum {
    TMR_ONCE_MODE = 0, /* 一次工作模式 */
    TMR_AUTO_MODE = 1  /* 自动重载定时模式 */
} TMR_MODE_E;

/* 定时器结构体，成员变量必须是 volatile, 否则C编译器优化时可能有问题 */
typedef struct {
    volatile uint8_t Mode;     /**< 计数器模式（一次性/自动） */
    volatile uint8_t Flag;     /**< 到期标志位 */
    volatile uint32_t Count;   /**< 当前计数值 */
    volatile uint32_t PreLoad; /**< 自动模式下的重载值 */
} SOFT_TMR;

/* 提供给其他C文件调用的函数 */
void bsp_InitTimer(void); // 初始化软件定时器并启动 TMR6 1ms 中断。
void bsp_DelayMS(uint32_t n);
void bsp_DelayUS(uint32_t n);
void bsp_StartTimer(uint8_t _id, uint32_t _period);     // 启动一次性定时器。
void bsp_StartAutoTimer(uint8_t _id, uint32_t _period); // 启动自动重载定时器。
void bsp_StopTimer(uint8_t _id);                        // 停止一个定时器。
uint8_t bsp_CheckTimer(uint8_t _id);                    // 检测定时器是否到期。

void tone(int freq);
void toneOff(void);
void timer5_init(void);
void delay_ms1(uint16_t nms); // 毫秒级忙等待延时。
void bsp_InitHardTimer(void);
void bsp_StartHardTimer(uint8_t _CC, uint32_t _uiTimeOut, void *_pCallBack);

extern crm_clocks_freq_type crm_clocks_freq_struct; // 系统时钟频率信息缓存（由驱动更新）。

#ifdef __cplusplus
}
#endif
