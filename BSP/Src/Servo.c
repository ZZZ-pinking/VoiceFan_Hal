#include "Servo.h"
#include "PWM.h"
#include "Variable.h"

/**
  * @brief  舵机初始化
  */
void Servo_Init(void)
{
    Servo_Current = 90;
    Servo_Target = 90;
    Servo_Enable = 0;
    Servo_oscillation(90);
}

/**
  * @brief  设置目标角度
  * @param  angle 目标角度，范围 0~120
  */
void Servo_SetTarget(float angle)
{
    if (angle < 0) angle = 0;
    if (angle > 120) angle = 120;
    Servo_Target = angle;
    Servo_Enable = 1;
}

/**
  * @brief  舵机更新（在 TIM3 中断中每 20ms 调用一次）
  */
void Servo_Update(void)
{
    if (!Servo_Enable) return;

    if (Fan_Swing == 1)
    {
        /* 摇摆模式：左右往复 */
        if (Swing_Direction == 1)  /* 向右 */
        {
            Servo_Current += SERVO_STEP;
            if (Servo_Current >= SWING_RIGHT)
            {
                Servo_Current = SWING_RIGHT;
                Swing_Direction = -1;  /* 到达右边界，反向 */
            }
        }
        else  /* 向左 */
        {
            Servo_Current -= SERVO_STEP;
            if (Servo_Current <= SWING_LEFT)
            {
                Servo_Current = SWING_LEFT;
                Swing_Direction = 1;  /* 到达左边界，反向 */
            }
        }
    }
    else
    {
        /* 非摇摆模式：直接移动到目标 */
        if (Servo_Current < Servo_Target)
        {
            Servo_Current += SERVO_STEP;
            if (Servo_Current > Servo_Target)
                Servo_Current = Servo_Target;
        }
        else if (Servo_Current > Servo_Target)
        {
            Servo_Current -= SERVO_STEP;
            if (Servo_Current < Servo_Target)
                Servo_Current = Servo_Target;
        }
        if (Servo_Current == Servo_Target)
            Servo_Enable = 0;
    }

    Servo_oscillation(Servo_Current);
}

/**
  * @brief  舵机角度转 PWM 脉宽
  * @param  Angle 角度值，0~180
  */
void Servo_oscillation(float Angle)
{
    PWM_servo(Angle / 180 * 2000 + 500);
}
