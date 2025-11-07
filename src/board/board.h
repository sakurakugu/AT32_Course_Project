#pragma once



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "at32f435_437_board.h"
#include "at32f435_437_clock.h"
#include "bsp_ext_flash.h"
#include "key.h"
#include "oled.h"
#define ESP12_DEBUG 0

#define ERROR_HANDLER() Error_Handler(__FILE__, __LINE__);
void adc_config(void);
uint16_t analogRead(void);

/* 默认是关闭状态 */
#define Enable_EventRecorder 0

#if Enable_EventRecorder == 1
#include "EventRecorder.h"
#endif



/* 定义优先级分组 */
#define NVIC_PREEMPT_PRIORITY 4

#include "timer.h"
#include "wifi.h"
#include "bsp_eep_lm75.h"
#include "bsp_uart.h"
#include "bsp_ext_flash.h"


/* 提供给其他C文件调用的函数 */
void bsp_Init(void);
void delay_us(uint32_t nus);
// void System_Init(void);

// void bsp_GetCpuID(uint32_t *_id);
void Error_Handler(char *file, uint32_t line);

void adc_config(void);
uint16_t analogRead(void);
void at32_led_init(led_type led);
void at32_led_on(led_type led);
void at32_led_off(led_type led);
void at32_led_toggle(led_type led);
void delay_ms(uint16_t nms);
/* delay function */
}




class Board {
  public:
    static Board &GetInstance() {
        static Board instance;
        return instance;
    }
    Board(const Board &) = delete;            // 禁用拷贝构造函数
    Board &operator=(const Board &) = delete; // 禁用赋值操作

    void Init(); // 初始化板级资源

  private:
    Board();
    ~Board();

    // Button *button_;      // 声明按键
    // LcdDisplay *display_; // 声明液晶屏
};
