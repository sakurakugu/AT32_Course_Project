#include "adc_voltage.h"
#include "at32f435_437_adc.h"

/**
 * @brief  adc configuration.
 * @param  none
 * @retval none
 */
void ADC_Config(void) {
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
uint16_t AnalogRead(void) {
    adc_ordinary_software_trigger_enable(ADC1, TRUE);
    while (adc_flag_get(ADC1, ADC_OCCE_FLAG) == RESET)
        ;
    return adc_ordinary_conversion_data_get(ADC1);
}