#pragma once
#include <stdint.h>

typedef enum {
    LED_Green = 0,
    LED_Yellow = 1,
} led_type;

#define LED_NUM 2

#define LED_Green_PIN GPIO_PINS_12
#define LED_Green_GPIO GPIOC
#define LED_Green_GPIO_CRM_CLK CRM_GPIOC_PERIPH_CLOCK

#define LED_Yellow_PIN GPIO_PINS_9
#define LED_Yellow_GPIO GPIOC
#define LED_Yellow_GPIO_CRM_CLK CRM_GPIOC_PERIPH_CLOCK

#ifdef __cplusplus
extern "C" {
#endif

// extern void LED_Init(led_type led);
extern void LED_On(led_type led);
extern void LED_Off(led_type led);
// extern void LED_Toggle(led_type led);

#ifdef __cplusplus
}
#endif
