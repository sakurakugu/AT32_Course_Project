#include "led.h"
#include "at32f435_437_crm.h"
#include "at32f435_437_gpio.h"

/* at-start led resouce array */
gpio_type *led_gpio_port[LED_NUM] = {LED_Green_GPIO, LED_Yellow_GPIO};
uint16_t led_gpio_pin[LED_NUM] = {LED_Green_PIN, LED_Yellow_PIN};
crm_periph_clock_type led_gpio_crm_clk[LED_NUM] = {LED_Green_GPIO_CRM_CLK, LED_Yellow_GPIO_CRM_CLK};

/**
 * @brief  configure led gpio
 * @param  led: specifies the led to be configured.
 * @retval none
 */
void LED::Init(led_type led) {
    gpio_init_type gpio_init_struct;

    /* enable the led clock */
    crm_periph_clock_enable(led_gpio_crm_clk[led], TRUE);

    /* set default parameter */
    gpio_default_para_init(&gpio_init_struct);

    /* configure the led gpio */
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_pins = led_gpio_pin[led];
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(led_gpio_port[led], &gpio_init_struct);
}

/**
 * @brief  turns selected led on.
 * @param  led: specifies the led to be set on.
 *   this parameter can be one of following parameters:
 *     @arg LED_Green
 *     @arg LED_Yellow
 *     @arg LED4
 * @retval none
 */
void LED::On(led_type led) {
    if (led > (LED_NUM - 1))
        return;
    if (led_gpio_pin[led])
        led_gpio_port[led]->clr = led_gpio_pin[led];
}

/**
 * @brief  turns selected led off.
 * @param  led: specifies the led to be set off.
 *   this parameter can be one of following parameters:
 *     @arg LED_Green
 *     @arg LED_Yellow
 *     @arg LED4
 * @retval none
 */
void LED::Off(led_type led) {
    if (led > (LED_NUM - 1))
        return;
    if (led_gpio_pin[led])
        led_gpio_port[led]->scr = led_gpio_pin[led];
}

/**
 * @brief  turns selected led toggle.
 * @param  led: specifies the led to be set off.
 *   this parameter can be one of following parameters:
 *     @arg LED_Green
 *     @arg LED_Yellow
 *     @arg LED4
 * @retval none
 */
void LED::Toggle(led_type led) {
    if (led > (LED_NUM - 1))
        return;
    if (led_gpio_pin[led])
        led_gpio_port[led]->odt ^= led_gpio_pin[led];
}
