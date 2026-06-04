#include "Control.h"
#include "BSP_Usart.h"
#include "Variable.h"
#include "Face_Config.h"
#include "OperatingMode.h"
#include "usart.h"   /* huart1 */

/* 串口接收数据缓存（Usart.c 中定义） */
extern uint8_t Usart_RxData;


void Control_Init(void)
{
    Usart_Init();
}

/**
  * @brief  USART1 接收中断回调函数
  * @note   HAL 库的中断流程：
  *         USART1_IRQHandler → HAL_UART_IRQHandler → HAL_UART_RxCpltCallback
  *         每次收到数据后需重新调用 HAL_UART_Receive_IT 开启下一次接收
  * @param  huart 触发中断的串口句柄
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        switch(Usart_RxData)
        {
        case 0x01: Fan_Speed=1, Face_Mode=6; break;  // 打开风扇(一档)
        case 0x02: Fan_Speed=2, Face_Mode=1; break;  // 二档
        case 0x03: Fan_Speed=3, Face_Mode=2; break;  // 最大档
        case 0x04: Fan_Speed=0, Face_Mode=0; break;  // 关闭风扇
        case 0x05: Fan_Swing=1, Face_Mode=3; break;  // 开始摇摆
        case 0x06: Fan_Swing=0, Face_Mode=4; break;  // 停止摇摆

        case 0x07: AllLed=1; break;     // 开启灯光
        case 0x08: AllLed=0; break;     // 关闭灯光
        case 0x09: BreatheLed=1; break;  // 开启呼吸灯
        case 0x10: BreatheLed=0; break;  // 关闭呼吸灯

        case 0x11: Battery_Bit^=1; break;  // 显示电量
        }

        /* 重新开启接收中断（HAL 库每次只接收一次，必须重新调用） */
        HAL_UART_Receive_IT(&huart1, &Usart_RxData, 1);
    }
}
