/**
 * @brief 初始化颜色LED
 * PWM输出模式，用于控制RGB颜色LED
 */
#include "color_led.hpp"

#include "at32f435_437_gpio.h"
#include "at32f435_437_clock.h"
#include "timer.h"

tmr_output_config_type tmr_oc_init_structure;

/**
 * @brief 初始化颜色LED
 * PWM输出模式，用于控制RGB颜色LED
 */
void ColorLed::Init() {
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

    crm_clocks_freq_type clocks;
    crm_clocks_freq_get(&clocks);
    uint32_t presc = ((clocks.apb1_freq * 2U) / 24000000U);
    if (presc == 0) presc = 1;
    prescalervalue = (uint16_t)(presc - 1U);

    /* tmr3 time base configuration */
    tmr_base_init(TMR3, 665, prescalervalue);
    tmr_cnt_dir_set(TMR3, TMR_COUNT_UP);
    tmr_clock_source_div_set(TMR3, TMR_CLOCK_DIV1);

    tmr_output_default_para_init(&tmr_oc_init_structure);
    tmr_oc_init_structure.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_A;
    tmr_oc_init_structure.oc_idle_state = FALSE;
    tmr_oc_init_structure.oc_polarity = TMR_OUTPUT_ACTIVE_LOW;
    tmr_oc_init_structure.oc_output_state = TRUE;
    tmr_output_channel_config(TMR3, TMR_SELECT_CHANNEL_1, &tmr_oc_init_structure);
    tmr_channel_value_set(TMR3, TMR_SELECT_CHANNEL_1, 0);
    tmr_output_channel_buffer_enable(TMR3, TMR_SELECT_CHANNEL_1, TRUE);

    tmr_output_channel_config(TMR3, TMR_SELECT_CHANNEL_2, &tmr_oc_init_structure);
    tmr_channel_value_set(TMR3, TMR_SELECT_CHANNEL_2, 0);
    tmr_output_channel_buffer_enable(TMR3, TMR_SELECT_CHANNEL_2, TRUE);

    tmr_output_channel_config(TMR3, TMR_SELECT_CHANNEL_3, &tmr_oc_init_structure);
    tmr_channel_value_set(TMR3, TMR_SELECT_CHANNEL_3, 0);
    tmr_output_channel_buffer_enable(TMR3, TMR_SELECT_CHANNEL_3, TRUE);

    tmr_period_buffer_enable(TMR3, TRUE);

    /* tmr enable counter */
    tmr_counter_enable(TMR3, TRUE);
}

/**
 * @brief 设置RGB颜色
 * @param r 红色分量 (0-255)
 * @param g 绿色分量 (0-255)
 * @param b 蓝色分量 (0-255)
 */
void ColorLed::SetColor(uint8_t r, uint8_t g, uint8_t b) {
    current_r = r;
    current_g = g;
    current_b = b;

    // 应用当前亮度
    uint8_t adj_r = (uint8_t)((r * current_brightness) / 100);
    uint8_t adj_g = (uint8_t)((g * current_brightness) / 100);
    uint8_t adj_b = (uint8_t)((b * current_brightness) / 100);

    // 将RGB映射到PWM的CCR值 (0-665)
    uint16_t ccr_r = (uint16_t)((adj_r * 665) / 255);
    uint16_t ccr_g = (uint16_t)((adj_g * 665) / 255);
    uint16_t ccr_b = (uint16_t)((adj_b * 665) / 255);

    // 设置PWM通道值
    tmr_channel_value_set(TMR3, TMR_SELECT_CHANNEL_1, ccr_r);
    tmr_channel_value_set(TMR3, TMR_SELECT_CHANNEL_2, ccr_g);
    tmr_channel_value_set(TMR3, TMR_SELECT_CHANNEL_3, ccr_b);
}

/**
 * @brief 设置亮度
 * @param brightness 亮度值 (0-100)
 */
void ColorLed::SetBrightness(uint8_t brightness) {
    if (brightness > 100)
        brightness = 100;
    current_brightness = brightness;

    // 重新应用当前颜色和新亮度
    SetColor(current_r, current_g, current_b);
}

/**
 * @brief 打开彩灯
 */
void ColorLed::TurnOn() {
    tmr_counter_enable(TMR3, TRUE);
    SetColor(current_r, current_g, current_b);
}

/**
 * @brief 关闭彩灯
 */
void ColorLed::TurnOff() {
    tmr_channel_value_set(TMR3, TMR_SELECT_CHANNEL_1, 0);
    tmr_channel_value_set(TMR3, TMR_SELECT_CHANNEL_2, 0);
    tmr_channel_value_set(TMR3, TMR_SELECT_CHANNEL_3, 0);
}

/**
 * C接口实现
 */
void ColorLed_SetColor(uint8_t r, uint8_t g, uint8_t b) {
    ColorLed::GetInstance().SetColor(r, g, b);
}

void ColorLed_TurnOn() {
    ColorLed::GetInstance().TurnOn();
}

/**
 * @brief 关闭彩灯
 */
void ColorLed_TurnOff() {
    ColorLed::GetInstance().TurnOff();
}
