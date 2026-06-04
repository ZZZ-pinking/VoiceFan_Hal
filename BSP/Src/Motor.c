#include "Motor.h"
#include "PWM.h"

/**
  * @brief  直流电机初始化
  * @note   GPIO（PA1/PA2）已由 CubeMX 配置，此处只需启动 PWM
  */
void Motor_Init(void)
{
    PWM_Init();
}

/**
  * @brief  直流电机设置速度
  * @param  Speed 速度值，范围：-100~100
  *         正值正转，负值反转，0停止
  */
void Motor_SetSpeed(int16_t Speed)
{
    if (Speed >= 0)
    {
        HAL_GPIO_WritePin(MOTOR_IN2_GPIO_Port, MOTOR_IN2_Pin, GPIO_PIN_SET);    /* PA2 高 */
        HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port, MOTOR_IN1_Pin, GPIO_PIN_RESET);  /* PA1 低，正转 */
        PWM_motor(Speed);
    }
    else
    {
        HAL_GPIO_WritePin(MOTOR_IN2_GPIO_Port, MOTOR_IN2_Pin, GPIO_PIN_RESET);  /* PA2 低 */
        HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port, MOTOR_IN1_Pin, GPIO_PIN_SET);    /* PA1 高，反转 */
        PWM_motor(-Speed);
    }
}
