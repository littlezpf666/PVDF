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
  * @brief  This function handles ADC DMA interrupt request.
  * @param  None
  * @retval None
  */
extern uint16_t ADC_ConvertedValue[2];
u32 temp_val=0;
u8 t=0;
u16 vol_per;
uint16_t flag1=0,flag2=0,flag3=0;

void DMA1_Channel1_IRQHandler(void)
{                                  

	if(DMA_GetFlagStatus(DMA1_FLAG_GL1)!=RESET)
	{ 
		//vol_per=(int)((float)ADC_ConvertedValue[1]/4096*100);  //��һ��		
		if(++t<40)
			temp_val+=ADC_ConvertedValue[0]/40;
		else if(t==40)
		{
			//printf("ƽ����ѹ%d\r\n",temp_val);
			Data_Send_Senser(temp_val,flag1,flag2,flag3);//??????
      temp_val=0;
		  t=0;
		}
		DMA_ClearFlag(DMA1_FLAG_GL1);
	}		    
}
/**
  * @brief  This function handles GENERAL_TIM3 interrupt request.
  * @param  None
  * @retval None
  */
uint16_t DDS_step=0,DDSM=1;
uint16_t temp[1][256];//ע���������ʱ���ܳ�����Χ���������ֿ���
extern uint16_t si[][256],sawtooth[][256],triangle[][256],ex[][256];
extern char amplitude_level,wave_pattern;
uint8_t mode_status=0;
uint8_t stop_status=0;
void TIM3_IRQHandler(void)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
	{
		DDS_step=DDS_step+DDSM;
		if(DDS_step>255)
		 {
			DDS_step=0;
			if(mode_status==0)
			mode_status++;
			else if(mode_status==1)
			mode_status=0;	
		 }
		 if(stop_status==0)//�������׶ε�����ϸı�ռ�ձ�
		 {
			 switch (wave_pattern)
			 {
				  case 0:
						temp[0][DDS_step]=si[amplitude_level][DDS_step];
			     break;
			    case 1:
						temp[0][DDS_step]=sawtooth[amplitude_level][DDS_step];
			     break;
				  case 3:
						temp[0][DDS_step]=triangle[amplitude_level][DDS_step];
			     break;
					case 4:
						temp[0][DDS_step]=ex[amplitude_level][DDS_step];
					 break;
			 }
				
			 TIM_SetCompare2(TIM3, temp[0][DDS_step]);
			 GAS=0;
		 }
     else//�����׶�ֹͣռ�ձ�Ϊ0����������
		 {
			 TIM_SetCompare2(TIM3, 0);
			 GAS=1;
		 }
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
		
}

/**
  * @brief  This function handles GENERAL_TIM4 interrupt request.
  * @param  None
  * @retval None
  */
unsigned int tim4_counter1=0,tim4_counter2=0;
extern char time_interval;//���ñ���Ҫ��Դ����������������ͬ

void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=RESET)
	{
		
		if(++tim4_counter1>=500)
		{
			tim4_counter2++;
			tim4_counter1=0;
			
		}
		if(tim4_counter2==time_interval)
			{
				stop_status=0;
			}
			if(tim4_counter2==time_interval*2)
			{
				stop_status=1;
			  tim4_counter2=0;
				
	      
			}	
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	}
		
}
char DETECT_KEY=0;
void EXTI3_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line3) != RESET){
		  delay_ms(10);
		  if(PEN==0)
			{
			 DETECT_KEY=1;
		   TP_Read_XY2(&tp_dev.y,&tp_dev.x);
			 tp_dev.x=tp_dev.xfac*tp_dev.x+tp_dev.xoff;//�����ת��Ϊ��Ļ����
			 tp_dev.y=tp_dev.yfac*tp_dev.y+tp_dev.yoff;
			}
      EXTI_ClearITPendingBit(EXTI_Line3);     
	  }
}