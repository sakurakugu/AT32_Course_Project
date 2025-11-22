#include "led.hpp"
#include "at32f435_437_crm.h"
#include "at32f435_437_gpio.h"

/* 开始时的LED资源数组 */
gpio_type *led_gpio_port[LED_NUM] = {LED_Green_GPIO, LED_Yellow_GPIO};
uint16_t led_gpio_pin[LED_NUM] = {LED_Green_PIN, LED_Yellow_PIN};
crm_periph_clock_type led_gpio_crm_clk[LED_NUM] = {LED_Green_GPIO_CRM_CLK, LED_Yellow_GPIO_CRM_CLK};

/**
 * @brief  配置LED GPIO
 * @param  led: 指定要配置的LED
 * @retval none
 */
void LED::Init(led_type led) {
    gpio_init_type gpio_init_struct;

    /* 使能LED时钟 */
    crm_periph_clock_enable(led_gpio_crm_clk[led], TRUE);

    /* 设置默认参数 */
    gpio_default_para_init(&gpio_init_struct);

    /* 配置LED GPIO */
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_pins = led_gpio_pin[led];
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(led_gpio_port[led], &gpio_init_struct);
}

/**
 * @brief  打开指定LED
 * @param  led: 指定要打开的LED
 * @retval none
 */
void LED::TurnOn(led_type led) {
    if (led > (LED_NUM - 1))
        return;
    if (led_gpio_pin[led])
        led_gpio_port[led]->clr = led_gpio_pin[led];
}

/**
 * @brief  关闭指定LED
 * @param  led: 指定要关闭的LED
 * @retval none
 */
void LED::TurnOff(led_type led) {
    if (led > (LED_NUM - 1))
        return;
    if (led_gpio_pin[led])
        led_gpio_port[led]->scr = led_gpio_pin[led];
}

/**
 * @brief  切换指定LED状态
 * @param  led: 指定要切换状态的LED
 * @retval none
 */
void LED::Toggle(led_type led) {
    if (led > (LED_NUM - 1))
        return;
    if (led_gpio_pin[led])
        led_gpio_port[led]->odt ^= led_gpio_pin[led];
}

// void LED_Init(led_type led) {
//     LED::GetInstance().Init(led);
// }

void LED_TurnOn(led_type led) {
    LED::GetInstance().TurnOn(led);
}

void LED_TurnOff(led_type led) {
    LED::GetInstance().TurnOff(led);
}

// void LED_Toggle(led_type led) {
//     LED::GetInstance().Toggle(led);
// }