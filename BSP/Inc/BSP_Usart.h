#ifndef __BSP_USART_H
#define __BSP_USART_H

#include "main.h"

void Usart_Init(void);

/* 串口接收数据缓存（Usart.c 中定义） */
extern uint8_t Usart_RxData;

#endif
