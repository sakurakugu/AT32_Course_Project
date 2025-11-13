/**
 **************************************************************************
 * @file     at32f435_437_int.c
 * @version  v2.0.0
 * @date     2020-11-02
 * @brief    main interrupt service routines.
 **************************************************************************
 *                       Copyright notice & Disclaimer
 *
 * The software Board Support Package (BSP) that is made available to
 * download from Artery official website is the copyrighted work of Artery.
 * Artery authorizes customers to use, copy, and distribute the BSP
 * software and its related documentation for the purpose of design and
 * development in conjunction with Artery microcontrollers. Use of the
 * software is governed by this copyright notice and the following disclaimer.
 *
 * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
 * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
 * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
 * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
 * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
 *
 **************************************************************************
 */

/* includes ------------------------------------------------------------------*/
#include "at32f435_437_int.h"
#include <stdio.h>

/** @addtogroup AT32F437_periph_template
 * @{
 */

/** @addtogroup 437_LED_toggle
 * @{
 */

/**
 * @brief  this function handles nmi exception.
 * @param  none
 * @retval none
 */
void NMI_Handler(void) {}

/**
 * @brief  this function handles hard fault exception.
 * @param  none
 * @retval none
 */

void HardFault_Handler(void) {
    /* 当出现硬故障异常时，会进入无限循环状态。 */
    printf("非法操作，硬故障\n");
    while (1) {}
}

/**
 * @brief  this function handles memory manage exception.
 * @param  none
 * @retval none
 */
void MemManage_Handler(void) {
    /* 当出现内存管理故障异常时，会进入无限循环状态。 */
    printf("内存管理故障\n");
    while (1) {}
}

/**
 * @brief  this function handles bus fault exception.
 * @param  none
 * @retval none
 */
void BusFault_Handler(void) {
    /* 当出现总线故障异常时，会进入无限循环状态。 */
    printf("总线故障\n");
    while (1) {}
}

/**
 * @brief  this function handles usage fault exception.
 * @param  none
 * @retval none
 */
void UsageFault_Handler(void) {
    /* 当出现使用故障异常时，会进入无限循环状态。 */
    printf("使用故障\n");
    while (1) {}
}

/**
 * @brief  this function handles debug monitor exception.
 * @param  none
 * @retval none
 */
void DebugMon_Handler(void) {}

// /* The following interrupt handlers are defined by FreeRTOS when using FreeRTOS */
// /**
//  * @brief  this function handles svcall exception.
//  * @param  none
//  * @retval none
//  */
// void SVC_Handler(void) {}

// /**
//  * @brief  this function handles pendsv_handler exception.
//  * @param  none
//  * @retval none
//  */
// void PendSV_Handler(void) {}

// /**
//  * @brief  this function handles systick handler.
//  * @param  none
//  * @retval none
//  */
// void SysTick_Handler(void) {}

/**
 * @}
 */

/**
 * @}
 */
