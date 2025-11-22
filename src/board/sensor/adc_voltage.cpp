#include "adc_voltage.h"
#include "at32f435_437_adc.h"

/**
 * @brief  配置ADC电压采集
 * @param  none
 * @retval none
 */
void ADC_Config(void) {
    gpio_init_type gpio_initstructure;
    adc_common_config_type adc_common_struct;
    adc_base_config_type adc_base_struct;

    crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

    gpio_default_para_init(&gpio_initstructure);

    /* 配置 ADC 引脚为模拟输入模式 */
    gpio_initstructure.gpio_mode = GPIO_MODE_ANALOG;
    gpio_initstructure.gpio_pins = GPIO_PINS_0;
    gpio_init(GPIOA, &gpio_initstructure);

    crm_periph_clock_enable(CRM_ADC1_PERIPH_CLOCK, TRUE);
    nvic_irq_enable(ADC1_2_3_IRQn, 0, 0);

    adc_common_default_para_init(&adc_common_struct);

    /* 配置 ADC 为独立模式 */
    adc_common_struct.combine_mode = ADC_INDEPENDENT_MODE;

    /* 配置 ADC 时钟分频为 HCLK 除以 4 */
    adc_common_struct.div = ADC_HCLK_DIV_4;

    /* 配置公共 DMA 模式，在独立模式下无用 */
    adc_common_struct.common_dma_mode = ADC_COMMON_DMAMODE_DISABLE;

    /* 配置公共 DMA 请求重复 */
    adc_common_struct.common_dma_request_repeat_state = FALSE;

    /* 配置相邻 ADC 采样间隔，对普通移位模式有用 */
    adc_common_struct.sampling_interval = ADC_SAMPLING_INTERVAL_5CYCLES;

    /* 配置内部温度传感器和 vintrv */
    adc_common_struct.tempervintrv_state = FALSE;

    /* 配置电压电池 */
    adc_common_struct.vbat_state = FALSE;
    adc_common_config(&adc_common_struct);

    adc_base_default_para_init(&adc_base_struct);

    adc_base_struct.sequence_mode = TRUE;
    adc_base_struct.repeat_mode = FALSE;
    adc_base_struct.data_align = ADC_RIGHT_ALIGNMENT;
    adc_base_struct.ordinary_channel_length = 1;
    adc_base_config(ADC1, &adc_base_struct);
    adc_resolution_set(ADC1, ADC_RESOLUTION_12B);

    /* 配置普通通道 */
    adc_ordinary_channel_set(ADC1, ADC_CHANNEL_0, 1, ADC_SAMPLETIME_640_5);

    /* 配置普通触发源和触发边缘 */
    adc_ordinary_conversion_trigger_set(ADC1, ADC_ORDINARY_TRIG_TMR1CH1, ADC_ORDINARY_TRIG_EDGE_NONE);

    /* 配置 DMA 模式，在公共 DMA 模式下无用 */
    adc_dma_mode_enable(ADC1, FALSE);

    /* 配置 DMA 请求重复，在公共 DMA 模式下无用 */
    adc_dma_request_repeat_enable(ADC1, FALSE);

    /* 每个普通通道转换设置 occe 标志 */
    adc_occe_each_conversion_enable(ADC1, TRUE);

    /* 使能 adc 溢出中断 */
    adc_interrupt_enable(ADC1, ADC_OCCO_INT, TRUE);

    /* 使能 adc */
    adc_enable(ADC1, TRUE);
    while (adc_flag_get(ADC1, ADC_RDY_FLAG) == RESET)
        ;

    /* adc 校准 */
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