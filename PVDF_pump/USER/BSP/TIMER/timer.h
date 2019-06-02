#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#include "nvic.h"
//////////////////////////////////////////////////////////////////////////////////	 
					  
//********************************************************************************


#define            GENERAL_TIM_Period            4096
#define            GENERAL_TIM_Prescaler         71

void  TIM_Init(u16 crr2_val,u16 crr3_val);
void TIM3_GPIO_config(void);
void TIM3_Mode_config(u16 crr2_val,u16 crr3_val);
void TIM4_Mode_config(u16 arr,u16 psc);

/*void TIM3_PWM_Init(u16 arr,u16 psc); //驱动电机的PWM PA7  PB6
void TIM4_Int_Init(u16 arr,u16 psc); //定时器 定时电磁阀开关时间*/


#endif

