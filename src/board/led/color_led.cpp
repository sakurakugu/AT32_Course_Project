#include "color_led.h"

#include <stdint.h>
#include "at32f435_437_gpio.h"
#include "timer.h"


tmr_output_config_type tmr_oc_init_structure;

/**
 * @brief 初始化颜色LED
 * PWM输出模式，用于控制RGB颜色LED
 */
void Color_Led::Init() {
    uint16_t ccr1_val = 333;
    uint16_t ccr2_val = 249;
    uint16_t ccr3_val = 166;
    uint16_t prescalervalue = 0;

    gpio_init_type gpio_init_struct;
    crm_periph_clock_enable(CRM_TMR3_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_pins = GPIO_PINS_6 | GPIO_PINS_7 | GPIO_PINS_8;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init(GPIOC, &gpio_init_struct);

    gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE6, GPIO_MUX_2);
    gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE7, GPIO_MUX_2);
    gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE8, GPIO_MUX_2);

    /* compute the prescaler value */

    prescalervalue = (uint16_t)((crm_clocks_freq_struct.apb1_freq * 2) / 24000000) - 1;

    /* tmr3 time base configuration */
    tmr_base_init(TMR3, 665, prescalervalue);
    tmr_cnt_dir_set(TMR3, TMR_COUNT_UP);
    tmr_clock_source_div_set(TMR3, TMR_CLOCK_DIV1);

    tmr_output_default_para_init(&tmr_oc_init_structure);
    tmr_oc_init_structure.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_A;
    tmr_oc_init_structure.oc_idle_state = FALSE;
    tmr_oc_init_structure.oc_polarity = TMR_OUTPUT_ACTIVE_HIGH;
    tmr_oc_init_structure.oc_output_state = TRUE;
    tmr_output_channel_config(TMR3, TMR_SELECT_CHANNEL_1, &tmr_oc_init_structure);
    tmr_channel_value_set(TMR3, TMR_SELECT_CHANNEL_1, 665);
    tmr_output_channel_buffer_enable(TMR3, TMR_SELECT_CHANNEL_1, TRUE);

    tmr_output_channel_config(TMR3, TMR_SELECT_CHANNEL_2, &tmr_oc_init_structure);
    tmr_channel_value_set(TMR3, TMR_SELECT_CHANNEL_2, 0);
    tmr_output_channel_buffer_enable(TMR3, TMR_SELECT_CHANNEL_2, TRUE);

    tmr_output_channel_config(TMR3, TMR_SELECT_CHANNEL_3, &tmr_oc_init_structure);
    tmr_channel_value_set(TMR3, TMR_SELECT_CHANNEL_3, 665);
    tmr_output_channel_buffer_enable(TMR3, TMR_SELECT_CHANNEL_3, TRUE);

    tmr_period_buffer_enable(TMR3, TRUE);

    /* tmr enable counter */
    tmr_counter_enable(TMR3, TRUE);
}
