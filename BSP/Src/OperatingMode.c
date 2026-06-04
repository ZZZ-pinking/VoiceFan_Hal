#include "OperatingMode.h"
#include "Variable.h"
#include "Motor.h"
#include "Servo.h"

/*运行模式函数，在主循环中调用*/
void OperatingMode(void)
{
    switch(Fan_Speed)
    {
        case 0: Motor_SetSpeed(0);   break;  // 关闭
        case 1: Motor_SetSpeed(30);  break;  // 一档
        case 2: Motor_SetSpeed(60);  break;  // 二档
        case 3: Motor_SetSpeed(100); break;  // 最大
    }

    if (Fan_Swing == 1)
    {
        Servo_Enable = 1;
    }
    else if (Fan_Swing == 0)
    {
        Servo_SetTarget(90);
    }
}
