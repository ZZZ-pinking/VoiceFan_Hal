#include "BSP.h"
#include "tim.h"    /* htim3 */

/**
  * @brief  BSP 统一初始化
  * @note   在 main() 的 while(1) 之前调用
  *         CubeMX 生成的 MX_xxx_Init() 已在 main.c 中自动调用，
  *         此处只初始化用户级别的模块
  */
void BSP_Init(void)
{
    /* DWT 周期计数器初始化（Delay_us 依赖） */
    DWT_Init();

    /* OLED 显示屏初始化 */
    OLED_Init();

    /* 电机初始化（内部调用 PWM_Init 启动 PWM 输出） */
    Motor_Init();

    /* 舵机初始化 */
    Servo_Init();

    /* ADC 初始化（校准） */
    AD_Init();

    /* 串口初始化（开启接收中断） */
    Control_Init();

    /* 启动 TIM3 定时中断（20ms 周期） */
    HAL_TIM_Base_Start_IT(&htim3);
}
