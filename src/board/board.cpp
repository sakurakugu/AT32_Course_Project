#include "board.h"
#include "lm75.h"
#include "eeprom.h"
#include "delay.h"
#include "led/color_led.hpp"
#include "led/led.hpp"
#include "led/oled.h"
#include "sound/beep.hpp"
#include "sensor/adc_voltage.h"
#include "timer.h"
#include "uart.h"
// #include "wifi.hpp"

// #include "FreeRTOS.h"
// #include "task.h"

extern "C" {
#include "at32f435_437_clock.h"

/**
 * @brief  retargets the c library printf function to the usart.
 * @param  none
 * @retval none
 */
#if defined(__GNUC__) && !defined(__clang__)
int _write(int fd, char *pbuffer, int size) {
    for (int i = 0; i < size; i++) {
        __io_putchar(*pbuffer++);
    }

    return size;
}
#endif
}

Board::Board() {
    // 初始化板级资源
    color_led_ = &ColorLed::GetInstance();
}

Board::~Board() {
    // 释放板级资源
}

void Board::Init(void) {

    system_clock_config();
    /*
       Event Recorder：
       - 可用于代码执行时间测量，MDK5.25及其以上版本才支持，IAR不支持。
       - 默认不开启，如果要开启此选项，务必看V6开发板用户手册第8章
    */
#if Enable_EventRecorder == 1
    /* 初始化EventRecorder并开启 */
    EventRecorderInitialize(EventRecordAll, 1U);
    EventRecorderStart();
#endif
    delay_init();
    ADC_Config();
    iic_init(); /* 初始化I2C接口，用于LM75温度传感器 */
    // g_eep_lm75.init(); /* 初始化I2C接口，用于LM75温度传感器 */
    Key::GetInstance().Init(); /* 按键初始化，要放在滴答定时器之前，因为按钮检测是通过滴答定时器扫描 */
    bsp_InitTimer();           /* 初始化滴答定时器 */
                               // bsp_InitESP12();
    uart_print_init(UART1_BAUD); // 初始化COM1串口，用于打印调试信息
    OLED::GetInstance().Init(); /* 初始化OLED屏幕 */
    g_beep.Init();              /* 初始化蜂鸣器 */
                                // bsp_InitDWT();      /* 初始化DWT时钟周期计数器 */
    color_led_->Init();
    auto &led = LED::GetInstance();
    led.Init(LED_Green);
    led.Init(LED_Yellow);
    led.TurnOff(LED_Green);
    led.TurnOff(LED_Yellow);

    /* 初始化OLED显示 */
    OLED::GetInstance().Clear();                                      /* 清屏 */
    OLED::GetInstance().ShowString(0, 0, (uint8_t *)"2023030103024"); /* 在(0,0)位置显示字符串 */
}

extern "C" {

/* support printf function, usemicrolib is unnecessary */
#if (__ARMCC_VERSION > 6000000)
__asm(".global __use_no_semihosting\n\t");
void _sys_exit(int x) {
    (void)x;
}
/* __use_no_semihosting was requested, but _ttywrch was */
void _ttywrch(int ch) {
    (void)ch;
}
FILE __stdout;
#else
#ifdef __CC_ARM
#pragma import(__use_no_semihosting)
struct __FILE {
    int handle;
};
FILE __stdout;
void _sys_exit(int x) {
    (void)x;
}
/* __use_no_semihosting was requested, but _ttywrch was */
void _ttywrch(int ch) {
    (void)ch;
}
#endif
#endif

#if defined(__GNUC__) && !defined(__clang__)
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

/**
 * @brief  retargets the c library printf function to the usart.
 * @param  none
 * @retval none
 */
PUTCHAR_PROTOTYPE {
    while (usart_flag_get(PRINT_UART, USART_TDBE_FLAG) == RESET)
        ;
    usart_data_transmit(PRINT_UART, ch);
    return ch;
}

#if defined(__GNUC__) && !defined(__clang__)
int _write(int fd, char *pbuffer, int size) {
    for (int i = 0; i < size; i++) {
        __io_putchar(*pbuffer++);
    }

    return size;
}
#endif

/*
*********************************************************************************************************
*	函 数 名: bsp_RunPer10ms
*	功能说明: 该函数每隔10ms被Systick中断调用1次。详见 bsp_timer.c的定时中断服务程序。一些处理时间要求不严格的
*			任务可以放在此函数。比如：按键扫描、蜂鸣器鸣叫控制等。
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_RunPer10ms(void) {
    Key::GetInstance().Scan10ms();
    g_beep.Process();
}

/*
*********************************************************************************************************
*	函 数 名: bsp_RunPer1ms
*	功能说明: 该函数每隔1ms被Systick中断调用1次。详见 bsp_timer.c的定时中断服务程序。一些需要周期性处理的事务
*			 可以放在此函数。比如：触摸坐标扫描。
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_RunPer1ms(void) {}
}