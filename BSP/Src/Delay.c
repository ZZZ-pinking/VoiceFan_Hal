#include "Delay.h"

/* HAL 库已占用 SysTick 做 HAL_Delay()，微秒延时改用 DWT 周期计数器 */

#define DWT_CR      (*(__IO uint32_t *)0xE0001000)  /* DWT Control Register */
#define DWT_CYCCNT  (*(__IO uint32_t *)0xE0001004)  /* DWT Cycle Count Register */

/**
  * @brief  初始化 DWT 周期计数器（在 main 中调用一次）
  */
void DWT_Init(void)
{
    DWT_CR |= (1 << 0);  /* 使能 CYCCNT 计数器 */
    DWT_CYCCNT = 0;
}

/**
  * @brief  微秒级延时
  * @param  us 延时时长
  * @note   基于 DWT 周期计数器，72MHz 下 1us = 72 个周期
  */
void Delay_us(uint32_t us)
{
    uint32_t start = DWT_CYCCNT;
    uint32_t ticks = us * (SystemCoreClock / 1000000);  /* 72 * us */
    while ((DWT_CYCCNT - start) < ticks);
}

/**
  * @brief  毫秒级延时
  * @param  ms 延时时长
  */
void Delay_ms(uint32_t ms)
{
    while (ms--)
    {
        Delay_us(1000);
    }
}

/**
  * @brief  秒级延时
  * @param  s 延时时长
  */
void Delay_s(uint32_t s)
{
    while (s--)
    {
        Delay_ms(1000);
    }
}
