#include "board.h"
#include "at32f435_437_clock.h"
#include "delay.h"
#include "eeprom.h"
#include "ext_flash.h"
#include "led/color_led.h"
#include "led/led.h"
#include "led/oled.h"
#include "lm75.h"
#include "sensor/adc_voltage.h"
#include "sound/beep.hpp"
#include "timer.h"
#include "uart.h"

extern "C" {
#if defined(__GNUC__) && !defined(__clang__)
int _write(int fd, char *pbuffer, int size) {
    for (int i = 0; i < size; i++) {
        __io_putchar(*pbuffer++);
    }

    return size;
}
#endif
}

void Board::Init(void) {
    system_clock_config();
    /**
     * Event Recorder：
     * - 可用于代码执行时间测量，MDK5.25及其以上版本才支持，IAR不支持。
     * - 默认不开启，如果要开启此选项，务必看V6开发板用户手册第8章
     */
#if Enable_EventRecorder == 1
    /* 初始化EventRecorder并开启 */
    EventRecorderInitialize(EventRecordAll, 1U);
    EventRecorderStart();
#endif
    delay_init();
    adc_voltage_.Init();    /* 初始化ADC电压采集 */
    I2C_Init(); /* 初始化I2C接口，用于LM75温度传感器 */
    // g_eep_lm75.init(); /* 初始化I2C接口，用于LM75温度传感器 */
    key_.Init();                 /* 按键初始化，要放在滴答定时器之前，因为按钮检测是通过滴答定时器扫描 */
    Timer::GetInstance().InitTimer();             /* 初始化滴答定时器 */
                                 // bsp_InitESP12();
    uart_print_init(UART1_BAUD); // 初始化COM1串口，用于打印调试信息
    oled_.Init();                /* 初始化OLED屏幕 */
    beep_.Init();                /* 初始化蜂鸣器 */
                                 // bsp_InitDWT();      /* 初始化DWT时钟周期计数器 */
    color_led_.Init();
    led_.Init(LED_Green);
    led_.Init(LED_Yellow);
    led_.TurnOff(LED_Green);
    led_.TurnOff(LED_Yellow);

    /* 初始化OLED显示 */
    oled_.Clear();                                      /* 清屏 */
    oled_.ShowString(0, 0, (uint8_t *)"2023030103024"); /* 在(0,0)位置显示字符串 */
    // oled_.ShowString(0, 16, (uint8_t *)"2023030103019");
}

extern "C" {

/* 支持 printf 函数, 无需使用半主机模式 */
#if (__ARMCC_VERSION > 6000000)
__asm(".global __use_no_semihosting\n\t");
void _sys_exit(int x) {
    (void)x;
}
/* __use_no_semihosting 模式下, 无需实现 _ttywrch 函数 */
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
/* __use_no_semihosting 模式下, 无需实现 _ttywrch 函数 */
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
 * @brief  打印字符到串口。
 * @param  ch 要打印的字符
 * @retval ch 打印的字符
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

}