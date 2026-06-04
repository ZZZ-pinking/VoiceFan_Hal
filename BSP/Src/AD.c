#include "AD.h"
#include "adc.h"    /* CubeMX 生成的 hadc1 */

/**
  * @brief  ADC 初始化
  * @note   CubeMX 已完成 ADC1 配置，此处只需校准并启动
  */
void AD_Init(void)
{
    /* HAL ADC 校准（对应标准库的 ResetCalibration + StartCalibration） */
    HAL_ADCEx_Calibration_Start(&hadc1);
}

/**
  * @brief  获取一次 ADC 转换结果
  * @retval ADC 值，范围 0~4095（12位）
  */
uint16_t Get_ADC(void)
{
    /* 启动转换 */
    HAL_ADC_Start(&hadc1);

    /* 等待转换完成 */
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);

    /* 获取转换结果 */
    return (uint16_t)HAL_ADC_GetValue(&hadc1);
}
