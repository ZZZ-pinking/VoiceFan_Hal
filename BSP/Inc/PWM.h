#ifndef __PWM_H
#define __PWM_H

#include "main.h"

void PWM_Init(void);           /* 启动 PWM 输出（CubeMX 已完成配置，此处仅启动） */
void PWM_motor(uint16_t Compare);
void PWM_LED(uint16_t Compare);
void PWM_servo(uint16_t Compare);

#endif
