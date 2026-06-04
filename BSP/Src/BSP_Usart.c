#include "BSP_Usart.h"
#include "usart.h"   /* CubeMX 生成的 huart1 */

/* 串口接收数据缓存 */
uint8_t Usart_RxData = 0;

/**
  * @brief  串口初始化
  * @note   CubeMX 已完成 USART1 的 GPIO/波特率/中断配置，
  *         此处只需开启接收中断
  */
void Usart_Init(void)
{
    /* 开启 USART1 接收中断：每收到1个字节触发 HAL_UART_RxCpltCallback */
    HAL_UART_Receive_IT(&huart1, &Usart_RxData, 1);
}
