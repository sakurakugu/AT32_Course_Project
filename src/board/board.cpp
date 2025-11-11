#include "board.h"
#include "bsp_eep_lm75.h"
#include "delay.h"
#include "key/key.h"
#include "led/color_led.h"
#include "led/led.h"
#include "led/oled.h"
#include "sound/beep.h"
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
    color_led_ = &Color_Led::GetInstance();
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
    adc_config();
    iic_init(); /* 初始化I2C接口，用于LM75温度传感器 */
    // g_eep_lm75.init(); /* 初始化I2C接口，用于LM75温度传感器 */
    Key::GetInstance().init(); /* 按键初始化，要放在滴答定时器之前，因为按钮检测是通过滴答定时器扫描 */
    bsp_InitTimer();           /* 初始化滴答定时器 */
                               // bsp_InitESP12();
    uart_print_init(UART1_BAUD); // 初始化COM1串口，用于打印调试信息
    OLED::GetInstance().init(); /* 初始化OLED屏幕 */
    g_beep.init();              /* 初始化蜂鸣器 */
                                // bsp_InitDWT();      /* 初始化DWT时钟周期计数器 */
    color_led_->Init();
    auto &led = LED::GetInstance();
    led.Init(LED_Green);
    led.Init(LED_Yellow);
    led.Off(LED_Green);
    led.Off(LED_Yellow);

    /* 初始化OLED显示 */
    OLED::GetInstance().clear();                                      /* 清屏 */
    OLED::GetInstance().showString(0, 0, (uint8_t *)"2023030103024"); /* 在(0,0)位置显示字符串 */
}

extern "C" {
/**
 * @brief  adc configuration.
 * @param  none
 * @retval none
 */
void adc_config(void) {
    gpio_init_type gpio_initstructure;
    adc_common_config_type adc_common_struct;
    adc_base_config_type adc_base_struct;

    crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

    gpio_default_para_init(&gpio_initstructure);

    /* config adc pin as analog input mode */
    gpio_initstructure.gpio_mode = GPIO_MODE_ANALOG;
    gpio_initstructure.gpio_pins = GPIO_PINS_0;
    gpio_init(GPIOA, &gpio_initstructure);

    crm_periph_clock_enable(CRM_ADC1_PERIPH_CLOCK, TRUE);
    nvic_irq_enable(ADC1_2_3_IRQn, 0, 0);

    adc_common_default_para_init(&adc_common_struct);

    /* config combine mode */
    adc_common_struct.combine_mode = ADC_INDEPENDENT_MODE;

    /* config division,adcclk is division by hclk */
    adc_common_struct.div = ADC_HCLK_DIV_4;

    /* config common dma mode,it's not useful in independent mode */
    adc_common_struct.common_dma_mode = ADC_COMMON_DMAMODE_DISABLE;

    /* config common dma request repeat */
    adc_common_struct.common_dma_request_repeat_state = FALSE;

    /* config adjacent adc sampling interval,it's useful for ordinary shifting mode */
    adc_common_struct.sampling_interval = ADC_SAMPLING_INTERVAL_5CYCLES;

    /* config inner temperature sensor and vintrv */
    adc_common_struct.tempervintrv_state = FALSE;

    /* config voltage battery */
    adc_common_struct.vbat_state = FALSE;
    adc_common_config(&adc_common_struct);

    adc_base_default_para_init(&adc_base_struct);

    adc_base_struct.sequence_mode = TRUE;
    adc_base_struct.repeat_mode = FALSE;
    adc_base_struct.data_align = ADC_RIGHT_ALIGNMENT;
    adc_base_struct.ordinary_channel_length = 1;
    adc_base_config(ADC1, &adc_base_struct);
    adc_resolution_set(ADC1, ADC_RESOLUTION_12B);

    /* config ordinary channel */
    adc_ordinary_channel_set(ADC1, ADC_CHANNEL_0, 1, ADC_SAMPLETIME_640_5);

    /* config ordinary trigger source and trigger edge */
    adc_ordinary_conversion_trigger_set(ADC1, ADC_ORDINARY_TRIG_TMR1CH1, ADC_ORDINARY_TRIG_EDGE_NONE);

    /* config dma mode,it's not useful when common dma mode is use */
    adc_dma_mode_enable(ADC1, FALSE);

    /* config dma request repeat,it's not useful when common dma mode is use */
    adc_dma_request_repeat_enable(ADC1, FALSE);

    /* each ordinary channel conversion set occe flag */
    adc_occe_each_conversion_enable(ADC1, TRUE);

    /* enable adc overflow interrupt */
    adc_interrupt_enable(ADC1, ADC_OCCO_INT, TRUE);

    /* adc enable */
    adc_enable(ADC1, TRUE);
    while (adc_flag_get(ADC1, ADC_RDY_FLAG) == RESET)
        ;

    /* adc calibration */
    adc_calibration_init(ADC1);
    while (adc_calibration_init_status_get(ADC1))
        ;
    adc_calibration_start(ADC1);
    while (adc_calibration_status_get(ADC1))
        ;
}

/**
 * @brief  读取 adc 值
 * @param  none
 * @retval adc 值
 */
uint16_t analogRead(void) {
    adc_ordinary_software_trigger_enable(ADC1, TRUE);
    while (adc_flag_get(ADC1, ADC_OCCE_FLAG) == RESET)
        ;
    return adc_ordinary_conversion_data_get(ADC1);
}

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
    Key::GetInstance().scan10ms();
    g_beep.process();
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