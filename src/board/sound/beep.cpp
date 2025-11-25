/**
 * @brief 蜂鸣器驱动模块
 */

#include "beep.hpp"
#include "at32f435_437_gpio.h"

#define PWWTIMER TMR5

void Beep::Init() {
    gpio_init_type gpio_init_struct;
    tmr_output_config_type tmr_oc_init_structure;
    crm_clocks_freq_type crm_clocks_freq_struct = {0};

    mute = 0;
    enableFlag = 0;
    state = 0;
    beepTime = 0;
    stopTime = 0;
    cycle = 0;
    count = 0;
    cycleCount = 0;

    crm_periph_clock_enable(CRM_TMR5_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
    gpio_init_struct.gpio_pins = GPIO_PINS_12;
    gpio_init(GPIOB, &gpio_init_struct);
    gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE12, GPIO_MUX_2);

    /* get system clock */
    crm_clocks_freq_get(&crm_clocks_freq_struct);
    /* compute the prescaler value  */ // the freq is 15MHz
    prescalerValue = (uint16_t)(crm_clocks_freq_struct.apb1_freq * 2 / 1000000) - 1;

    /* tmr5 time base configuration */ // the PWM freq is 15KHz
    tmr_base_init(PWWTIMER, 999, prescalerValue);
    tmr_cnt_dir_set(PWWTIMER, TMR_COUNT_UP);
    tmr_clock_source_div_set(PWWTIMER, TMR_CLOCK_DIV1);

    tmr_output_default_para_init(&tmr_oc_init_structure);

    tmr_oc_init_structure.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_A;
    tmr_oc_init_structure.oc_idle_state = FALSE;
    tmr_oc_init_structure.oc_polarity = TMR_OUTPUT_ACTIVE_HIGH;
    tmr_oc_init_structure.oc_output_state = TRUE;

    tmr_output_channel_config(PWWTIMER, TMR_SELECT_CHANNEL_1, &tmr_oc_init_structure);
    tmr_channel_value_set(PWWTIMER, TMR_SELECT_CHANNEL_1, 500);

    tmr_output_channel_buffer_enable(PWWTIMER, TMR_SELECT_CHANNEL_1, TRUE);
    tmr_period_buffer_enable(PWWTIMER, TRUE);
    /* tmr enable counter */
    tmr_counter_enable(PWWTIMER, FALSE);
}

void Beep::SetFreq(int freq) {
    if (freq <= 0)
        return;
    tmr_base_init(PWWTIMER, 1000000UL / (uint32_t)freq, prescalerValue);
}

/*
 *	函 数 名: BEEP_Start
 *	功能说明: 启动蜂鸣音。
 *	形    参: _usBeepTime : 蜂鸣时间，单位10ms; 0 表示不鸣叫
 *			  _usStopTime : 停止时间，单位10ms; 0 表示持续鸣叫
 *			  _usCycle : 鸣叫次数， 0 表示持续鸣叫
 *	返 回 值: 无
 */
void Beep::Start(uint16_t bt, uint16_t st, uint16_t cy) {
    if (bt == 0 || mute == 1) {
        return;
    }

    beepTime = bt;
    stopTime = st;
    cycle = cy;
    count = 0;
    cycleCount = 0;
    state = 0;
    enableFlag = 1;

    EnableOutput(); /* 开始发声 */
}

/*
 *	函 数 名: BEEP_Stop
 *	功能说明: 停止蜂鸣音。
 *	形    参: 无
 *	返 回 值: 无
 */
void Beep::Stop() {
    enableFlag = 0;
    DisableOutput();
}

/*
 *	函 数 名: BEEP_Pause
 *	功能说明: 由于TIM冲突等原因，临时屏蔽蜂鸣音。通过 BEEP_Resume 恢复
 *	形    参: 无
 *	返 回 值: 无
 */
void Beep::Pause() {
    Stop();
    mute = 1;
}

/*
 *	函 数 名: BEEP_Resume
 *	功能说明: 恢复蜂鸣器正常功能
 *	形    参: 无
 *	返 回 值: 无
 */
void Beep::Resume() {
    Stop();
    mute = 0; /* 静音 */
}

/*
 *	函 数 名: BEEP_KeyTone
 *	功能说明: 发送按键音
 *	形    参: 无
 *	返 回 值: 无
 */
void Beep::KeyTone() {
    Start(5, 1, 1); /* 鸣叫50ms，停10ms， 1次 */
}

/*
 *	函 数 名: BEEP_Pro
 *	功能说明: 每隔10ms调用1次该函数，用于控制蜂鸣器发声。该函数在 bsp_timer.c 中被调用。
 *	形    参: 无
 *	返 回 值: 无
 */
void Beep::Process() {
    if ((enableFlag == 0) || (stopTime == 0) || (mute == 1)) {
        return;
    }

    if (state == 0) {
        if (stopTime > 0) { /* 间断发声 */
            if (++count >= beepTime) {
                DisableOutput(); /* 停止发声 */
                count = 0;
                state = 1;
            }
        } else {
            // 连续发声，不处理
        }
    } else if (state == 1) {
        if (++count >= stopTime) {
            if (cycle > 0) {
                if (++cycleCount >= cycle) {
                    enableFlag = 0;
                }

                if (enableFlag == 0) {
                    stopTime = 0;
                    return;
                }
            }

            count = 0;
            state = 0;

            EnableOutput(); /* 开始发声 */
        }
    }
}

/* 无源蜂鸣器 */
// PB12   TMR5_CH1
/* 1500表示频率1.5KHz，5000表示50.00%的占空比 */
void Beep::EnableOutput() {
    tmr_counter_enable(PWWTIMER, TRUE);
}

/* 禁止蜂鸣器鸣叫 */
void Beep::DisableOutput() {
    tmr_counter_enable(PWWTIMER, FALSE);
}

/**
 * @brief 设置蜂鸣器静音
 * @param mute : true 表示静音，false 表示正常发声
 * @retval none
 */
void Beep::SetMute(bool mute) {
    if (mute) {
        Pause();
    } else {
        Resume();
    }
}

