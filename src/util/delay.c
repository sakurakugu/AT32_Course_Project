#include "delay.h"
#include "at32f435_437_misc.h"

// FreeRTOS 仅在调度器运行、且不在中断中时使用
#include "FreeRTOS.h"
#include "task.h"

#define STEP_DELAY_MS 50

/* delay 变量 */
static __IO uint32_t fac_us;
static __IO uint32_t fac_ms;

// 检测是否处于中断上下文（Cortex-M）
static inline int delay_is_in_isr(void) {
    return (SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0U;
}

/**
 * @brief  初始化 delay 函数
 * @param  none
 * @retval none
 */
void delay_init() {
    /* 配置 系统滴答计时器 */
    systick_clock_source_config(SYSTICK_CLOCK_SOURCE_AHBCLK_NODIV);
    fac_us = system_core_clock / (1000000U);
    fac_ms = fac_us * (1000U);
}

/**
 * @brief  微秒级延时
 * @param  nus: 延时时间，单位：微秒
 * @retval none
 */
void delay_us(uint32_t nus) {
    uint32_t temp = 0;
    SysTick->LOAD = (uint32_t)(nus * fac_us);
    SysTick->VAL = 0x00;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    do {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16)));

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL = 0x00;
}

/**
 * @brief  毫秒级延时
 * @param  nms: 延时时间，单位：毫秒
 * @retval none
 */
void delay_ms(uint16_t nms) {
    // 仅当调度器已运行且不在中断中，使用 FreeRTOS 休眠以让出 CPU
    if (xTaskGetSchedulerState() == taskSCHEDULER_RUNNING && !delay_is_in_isr()) {
        vTaskDelay(pdMS_TO_TICKS(nms));
        return;
    }

    // 调度器未启动或处于中断中：沿用原 SysTick 忙等实现
    uint32_t temp = 0;
    while (nms) {
        if (nms > STEP_DELAY_MS) {
            SysTick->LOAD = (uint32_t)(STEP_DELAY_MS * fac_ms);
            nms -= STEP_DELAY_MS;
        } else {
            SysTick->LOAD = (uint32_t)(nms * fac_ms);
            nms = 0;
        }
        SysTick->VAL = 0x00;
        SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
        do {
            temp = SysTick->CTRL;
        } while ((temp & 0x01) && !(temp & (1 << 16)));

        SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
        SysTick->VAL = 0x00;
    }
}

/**
 * @brief  秒级延时
 * @param  sec: 延时时间，单位：秒
 * @retval none
 */
void delay_sec(uint16_t sec) {
    for (uint16_t index = 0; index < sec; index++) {
        delay_ms(500);
        delay_ms(500);
    }
}
