/**
 * @file timer.cpp
 * @brief 基于 TMR6 的 1ms 系统节拍与软件定时器实现。
 */

#include "timer.h"
#include "logger.h"

extern "C" {

/* 开关全局中断的宏 */
#define ENABLE_INT() __set_PRIMASK(0)  /* 开启全局中断 */
#define DISABLE_INT() __set_PRIMASK(1) /* 禁止全局中断 */

volatile unsigned int systick_ms = 0; // 系统毫秒节拍计数（由 TMR6 中断累加）
volatile uint32_t debug_timerTick;    // 任务运行时间统计使用

/* 保存 TIM定时中断到后执行的回调函数指针 */
static void (*s_TIM_CallBack1)(void);
static void (*s_TIM_CallBack2)(void);
static void (*s_TIM_CallBack3)(void);
static void (*s_TIM_CallBack4)(void);

/* 这2个全局变量转用于 bsp_DelayMS() 函数 */
static volatile uint32_t s_uiDelayCount = 0;
static volatile uint8_t s_ucTimeOutFlag = 0;

/* 定于软件定时器结构体变量 */
static SOFT_TMR s_tTmr[TMR_COUNT] = {0};

// static void bsp_SoftTimerDec(SOFT_TMR *_tmr);

#include "board.h"

/**
 * @brief  每10ms被Systick中断调用1次。详见 bsp_timer.c的定时中断服务程序。一些处理时间要求不严格的
 *			任务可以放在此函数。比如：按键扫描、蜂鸣器鸣叫控制等。
 * @param  none
 * @retval none
 */
void bsp_RunPer10ms(void) {
    Board::GetInstance().GetKey().Scan10ms();
    Board::GetInstance().GetBeep().Process();
}

/**
 * @brief  每1ms被Systick中断调用1次。详见 bsp_timer.c的定时中断服务程序。一些需要周期性处理的事务
 *			 可以放在此函数。比如：触摸坐标扫描。
 * @param  none
 * @retval none
 */
void bsp_RunPer1ms(void) {}

/**
 * @brief TMR6 溢出中断服务程序，每 1ms 进入一次。
 * @note 负责递减软件定时器并驱动应用层心跳（每 10ms）。
 */
void TMR6_DAC_GLOBAL_IRQHandler(void) {
    static uint8_t count_10ms = 0;
    uint8_t i;
    if (tmr_flag_get(TMR6, TMR_OVF_FLAG) != RESET) {
        debug_timerTick++;
        /* 每隔1ms进来1次 （仅用于 bsp_DelayMS） */
        if (s_uiDelayCount > 0) {
            if (--s_uiDelayCount == 0) {
                s_ucTimeOutFlag = 1;
            }
        }

        /* 每隔1ms，对软件定时器的计数器进行减一操作 */
        for (i = 0; i < TMR_COUNT; i++) {
            Timer::GetInstance().SoftTimerDec(&s_tTmr[i]);
        }

        systick_ms++;

        bsp_RunPer1ms(); /* 每隔1ms调用一次此函数，此函数在 bsp.cpp */

        if (++count_10ms >= 10) {
            count_10ms = 0;
            bsp_RunPer10ms(); /* 每隔10ms调用一次此函数，此函数在 bsp.cpp */
        }
        tmr_flag_clear(TMR6, TMR_OVF_FLAG);
    }
}

crm_clocks_freq_type crm_clocks_freq_struct = {0};
/**
 * @brief 初始化 TMR6 产生 1ms 溢出中断。
 * @details 预分频 9，自动重载设为 (AHB/10000)-1，得到 1000Hz（1ms）。
 */
void timer6_init(void) {
    crm_clocks_freq_type crm_clocks_freq_struct = {0};
    /* 获取系统时钟频率 */
    crm_clocks_freq_get(&crm_clocks_freq_struct);

    /* 开启 TMR6 时钟 */
    crm_periph_clock_enable(CRM_TMR6_PERIPH_CLOCK, TRUE);
    /* TMR6 配置 */
    /* 系统时钟分频 9，自动重载设为 (AHB/10000)-1，得到 1000Hz（1ms） */
    /* 预分频 9，自动重载值 (AHB/10000)-1，得到 1000Hz（1ms）*/
    tmr_base_init(TMR6, 9, (crm_clocks_freq_struct.ahb_freq / 10000) - 1); // 1ms 中断
    tmr_cnt_dir_set(TMR6, TMR_COUNT_UP);
    /* 溢出中断开启 */
    tmr_interrupt_enable(TMR6, TMR_OVF_INT, TRUE);
    /* NVIC 配置 TMR6 溢出中断 */
    nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
    /* 设置 Timer6 ISR 为低于 FreeRTOS 系统调用的优先级（>=5） */
    nvic_irq_enable(TMR6_DAC_GLOBAL_IRQn, 5, 0);
    /* 开启 TMR6 计数器 */
    tmr_counter_enable(TMR6, TRUE);
}
}

/**
 * @brief 初始化软件定时器并启动 TMR6 1ms 中断。
 */
void Timer::InitTimer() {
    uint8_t i;

    /* clear all the softtimer */
    for (i = 0; i < TMR_COUNT; i++) {
        s_tTmr[i].Count = 0;
        s_tTmr[i].PreLoad = 0;
        s_tTmr[i].Flag = 0;
        s_tTmr[i].Mode = TMR_ONCE_MODE; /* 缺省是1次性工作模式 */
    }

    timer6_init(); // 1ms 中断
}

/**
 * @brief 每隔 1ms 对所有定时器变量减1，处理到期标志与自动重载。
 * @param _tmr 定时器变量指针。
 */
void Timer::SoftTimerDec(SOFT_TMR *_tmr) {
    if (_tmr->Count > 0) {
        /* 如果定时器变量减到 1 则设置到期标志 */
        if (--_tmr->Count == 0) {
            _tmr->Flag = 1;

            /* 如果是自动模式，到期后自动重装计数器 */
            if (_tmr->Mode == TMR_AUTO_MODE) {
                _tmr->Count = _tmr->PreLoad;
            }
        }
    }
}

/**
 * @brief 启动一次性定时器并设置周期。
 * @param _id 定时器 ID，范围 [0, TMR_COUNT-1]。
 * @param _period 定时周期，单位 1ms。
 */
void Timer::StartTimer(uint8_t _id, uint32_t _period) {
    if (_id >= TMR_COUNT) {
        /* 打印出错的源代码文件名、函数名称 */
        LOGI("Error: file %s, function %s()\r\n", __FILE__, __FUNCTION__);
        while (1)
            ; /* 参数异常，死机等待看门狗复位 */
    }

    DISABLE_INT(); /* 关中断 */

    s_tTmr[_id].Count = _period;      /* 实时计数器初值 */
    s_tTmr[_id].PreLoad = _period;    /* 计数器自动重装值，仅自动模式起作用 */
    s_tTmr[_id].Flag = 0;             /* 定时时间到标志 */
    s_tTmr[_id].Mode = TMR_ONCE_MODE; /* 1次性工作模式 */

    ENABLE_INT(); /* 开中断 */
}

/**
 * @brief 启动自动重载定时器并设置周期。
 * @param _id 定时器 ID，范围 [0, TMR_COUNT-1]。
 * @param _period 定时周期，单位 1ms。
 */
void Timer::StartAutoTimer(uint8_t _id, uint32_t _period) {
#if uCOS_EN == 1
    CPU_SR_ALLOC();
#endif

    if (_id >= TMR_COUNT) {
        /* 打印出错的源代码文件名、函数名称 */
        LOGI("Error: file %s, function %s()\r\n", __FILE__, __FUNCTION__);
        while (1)
            ; /* 参数异常，死机等待看门狗复位 */
    }

    DISABLE_INT(); /* 关中断 */

    s_tTmr[_id].Count = _period;      /* 实时计数器初值 */
    s_tTmr[_id].PreLoad = _period;    /* 计数器自动重装值，仅自动模式起作用 */
    s_tTmr[_id].Flag = 0;             /* 定时时间到标志 */
    s_tTmr[_id].Mode = TMR_AUTO_MODE; /* 自动工作模式 */

    ENABLE_INT(); /* 开中断 */
}

/**
 * @brief 停止一个定时器。
 * @param _id 定时器 ID，范围 [0, TMR_COUNT-1]。
 */
void Timer::StopTimer(uint8_t _id) {
#if uCOS_EN == 1
    CPU_SR_ALLOC();
#endif

    if (_id >= TMR_COUNT) {
        /* 打印出错的源代码文件名、函数名称 */
        LOGI("错误: 文件 %s, 函数 %s()\r\n", __FILE__, __FUNCTION__);
        while (1)
            ; /* 参数异常，死机等待看门狗复位 */
    }

    DISABLE_INT(); /* 关中断 */

    s_tTmr[_id].Count = 0;            /* 实时计数器初值 */
    s_tTmr[_id].Flag = 0;             /* 定时时间到标志 */
    s_tTmr[_id].Mode = TMR_ONCE_MODE; /* 自动工作模式 */

    ENABLE_INT(); /* 开中断 */
}

/**
 * @brief 检测定时器是否到期。
 * @param _id 定时器 ID，范围 [0, TMR_COUNT-1]。
 * @return true 表示到期；false 表示尚未到期或 ID 异常。
 */
bool Timer::CheckTimer(uint8_t _id) {
    if (_id >= TMR_COUNT) {
        return 0;
    }

    if (s_tTmr[_id].Flag == 1) {
        s_tTmr[_id].Flag = 0;
        return 1;
    } else {
        return 0;
    }
}
