#ifndef __NVIC_H
#define __NVIC_H

#include "stm32f10x.h"

void EXTI_NVIC_Configuration(void);
void DMA_NVIC_Configuration(void);
void TIM_NVIC_Configuration(void);
void USART_NVIC_Configuration(void);
#endif