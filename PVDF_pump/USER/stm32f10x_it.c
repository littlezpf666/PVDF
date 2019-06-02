/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 
#include "time.h"

 
void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}
 
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
/**
  * @brief  This function handles BASIC_TIM6 interrupt request.
  * @param  None
  * @retval None
  */
uint16_t DDS_step=0,DDSM=1;
extern uint16_t si[][256];
uint8_t mode_step=0;
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
	{
		DDS_step=DDS_step+DDSM;
		if(DDS_step>255)
		 {
			DDS_step=0;
			if(mode_step==0)
			mode_step++;
			else if(mode_step==1)
			mode_step=0;	
		 }
		 //TIM_OCInitStructure.TIM_Pulse = si[0][DDS_step];
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
		
}

/**
  * @brief  This function handles BASIC_TIM7 interrupt request.
  * @param  None
  * @retval None
  */
unsigned int tim4_counter1=0,tim4_counter2=0;
extern char time_interval;//���ñ���Ҫ��Դ����������������ͬ
uint8_t stop_stage=0;
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=RESET)
	{
		
		if(++tim4_counter1>=1000)
		{
			tim4_counter2++;
			tim4_counter1=0;
			
		}
		if(tim4_counter2==time_interval)
			{
				stop_stage=0;
			}
			if(tim4_counter2==time_interval*2)
			{
				stop_stage=1;
			  tim4_counter2=0;
			}	
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	}
		
}