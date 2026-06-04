#include "PWM.h"
#include "tim.h"    /* CubeMX 生成的 htim2, htim3 */

/**
  * @brief  启动所有 PWM 通道
  * @note   CubeMX 已完成 TIM2/TIM3 的时基和 OC 配置，
  *         此函数只需启动 PWM 输出即可
  */
void PWM_Init(void)
{
	/* 先确保所有 CCR=0，防止电机上电就转，再启动 PWM */
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);
	
    /* 启动 TIM2_CH1（电机 PWM，PA0） */
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);

    /* 启动 TIM3_CH3（LED PWM，PB0） */
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);

    /* 启动 TIM3_CH4（舵机 PWM，PB1） */
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
}

/**
  * @brief  设置电机 PWM 占空比
  * @param  Compare CCR 值，范围 0~99（对应 0%~99%）
  */
void PWM_motor(uint16_t Compare)
{
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, Compare);
}

/**
  * @brief  设置 LED PWM 占空比
  * @param  Compare CCR 值，范围 0~19999
  */
void PWM_LED(uint16_t Compare)
{
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, Compare);
}

/**
  * @brief  设置舵机 PWM 占空比
  * @param  Compare CCR 值，范围 500~2500（对应 0.5ms~2.5ms 脉宽）
  */
void PWM_servo(uint16_t Compare)
{
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, Compare);
}
