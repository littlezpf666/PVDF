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
extern char feedback_control;
uint16_t DDS_step=0,DDSM=1;
uint16_t temp[1][256];//注意数组访问时不能超出范围，否则会出现卡死
u32 temp_val=0;
u16 vol_per;

uint16_t buffer[40]={0};
void DMA1_Channel1_IRQHandler(void)
{  
  static char t;	
  char i;
	if(DMA_GetFlagStatus(DMA1_FLAG_GL1)!=RESET)
	{ 
		/*********************求电源电压***************************/
		vol_per=(int)((float)ADC_ConvertedValue[1]/3500*100);  //归一化	
		if(feedback_control)
		{
				/*********************滑动滤波***************************/
				/*buffer[0]=ADC_ConvertedValue[0];	
				for(i=40;i>0;i--)
				{
					buffer[i]=buffer[i-1];
				}
				for(i=0;i<40;i++)
				{
					temp_val+=buffer[i]/40;
				}
				Data_Send_Senser(temp[0][DDS_step],0,0,0);
				temp_val=0;*/
				/*********************均值滤波***************************/
				if(++t<40)
					temp_val+=ADC_ConvertedValue[0]/40;
				else if(t==40)
				{			
					//printf("DDS_step:%d,temp:%d\r\n",DDS_step,temp[0][DDS_step]);
					 /*if(Regulation(temp[0][DDS_step], temp_val)>0)
					 {
						 TIM_SetCompare2(TIM3, Regulation(temp[0][DDS_step], temp_val));
						 GAS=0;
					 }
					 else
					 {
						 TIM_SetCompare2(TIM3, 0);
						 GAS=1;
					 }*/
					if(temp_val>3000)
					{
						TIM_SetCompare2(TIM3, 0);
						TIM_ITConfig(TIM3,TIM_IT_Update,DISABLE);
					}
					else
					{
						TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
					}
					Data_Send_Senser(temp_val,temp[0][DDS_step],0,0);
					temp_val=0;
					t=0;
				}
		}
		DMA_ClearFlag(DMA1_FLAG_GL1);
	}		    
}
/**
  * @brief  This function handles GENERAL_TIM3 interrupt request.
  * @param  None
  * @retval None
  */

extern uint16_t si[][256],triangle[][256],ex[][256],square[][256];
extern char amplitude_level,wave_pattern;
uint8_t mode_status=0,stop_status=0;
uint8_t max_step;
uint8_t tim3_counter=0;
void TIM3_IRQHandler(void)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
	{
		if(tim3_counter++==1)
		{
			if(DDS_step>252)//放气阶段停止占空比为0，气阀放气
			 {
				DDS_step=0;
			 }
			else{
			DDS_step=DDS_step+DDSM;	
			}
			tim3_counter=0;
		}
		 switch (wave_pattern)
			 {
				  case 0:					
					 temp[0][DDS_step]=si[0][DDS_step]+amplitude_level*100;
			     break;
			    case 1:
						temp[0][DDS_step]=triangle[0][DDS_step]+amplitude_level*100;
			     break;
				  case 2:
						temp[0][DDS_step]=square[0][DDS_step]+amplitude_level*80;
			     break;
					case 3:
						temp[0][DDS_step]=ex[0][DDS_step]+amplitude_level*100;
					 break;
			 }
		switch(DDSM)
		{
			case 1:
				max_step=90;
				break;
			case 2:
				max_step=130;
			  break;
			case 3:
				max_step=180;
				break;
		}
		if(DDS_step<max_step)//放气阶段停止占空比为0，气阀放气
		 {
			 GAS=0;
			 TIM_SetCompare2(TIM3, temp[0][DDS_step]);	
		 }
		 else//在吸气阶段电机不断改变占空比
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
extern char time_interval;//引用变量要与源变量声明的类型相同

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
char DETECT_TOUCH=0;
void EXTI3_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line3) != RESET){
		  delay_ms(10);
		  if(PEN==0)
			{
			 DETECT_TOUCH=1;
		   TP_Read_XY2(&tp_dev.y,&tp_dev.x);
			 tp_dev.x=tp_dev.xfac*tp_dev.x+tp_dev.xoff;//将结果转换为屏幕坐标
			 tp_dev.y=tp_dev.yfac*tp_dev.y+tp_dev.yoff;
			}
      EXTI_ClearITPendingBit(EXTI_Line3);     
	  }
}
char DETECT_KEY=0;
extern char scr_state;
void EXTI9_5_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line8) != RESET){
		  delay_ms(10);
		  if(PAin(8)==0)
			{
				
				DETECT_KEY=1;
				//printf("按键按下");
			}
      EXTI_ClearITPendingBit(EXTI_Line8);     
	  }
}