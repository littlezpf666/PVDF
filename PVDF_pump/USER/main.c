#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "adc.h"
#include "timer.h"
#include "pid.h"
#include "mod.h"
#include "touch.h"
/*һ��Դ�ļ�������һ��Դ�ļ��ĺ���ֻ��Ҫ����һ����һ�ļ��еĺ������Ϳ����ˣ�
��ԭ����ͬ����.h�ļ������ã�
�Ե��õ��ļ���˵�����õ���.h�еĺ���������������������Ϳ��Ե��ö�ӦԴ�����еĺ���
���ڱ������ļ���˵���������������ͬһ�ļ��к���Ҫ�໥���ã�������������д��.h�оͿ���
���ÿ��Ǻ�������˳�����⣬���ҽ�һЩ�꣬�ͽṹ�壬�ⲿ���ñ�������д���������ʵ����Դ
����
*/
/*
.h�в�Ҫ���б�����������Ϊ���ú����뱻���ö���.h�ļ�Ҳ���Ǳ����ᱻ�������ε����﷨����
*/
/************************************************
 PVDF_pump
************************************************/
u16 PWM=0;  //PWM����
u8 num = 0;
u8 flagE = 0;
u8 flagup = 0;
u8 flagmod =0;
u8 t = 1;
u16 tempfeed ;
u16 feedt ;
extern uint8_t mode_step,stop_stage;
extern uint16_t DDS_step;
extern uint16_t si[][256],sawtooth[][256],triangle[][256],rectangel[][256],ex[][256];
char time_interval=4;
char scr_state,wave_pattern,amplitude_level=1;
 int main(void)
 {	
  char tp_x;
  u16 adcx; //adc����
	float temp;
	double mod;
	delay_init();	    	 //��ʱ������ʼ��	
	
	 
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
	//EXTIX_Init(); 	 //�����жϳ�ʼ��
	//Adc_Init();		  	 	//ADC��ʼ��Adc_Init();		  	 	//ADC��ʼ�� 
	LCD_Init();			 	   //LCD��ʼ��
	//TIM_Init(2048,2048);
	Gui_StrCenter(0,64,GREEN,BLUE,"�Ϻ�ʦ����ѧ",32,1);//������ʾ  
 	
	TP_Init();
	
  //TIM3_Mode_config(390,71);	 
  //TIM3_PWM_Init(47999,99);	 //����Ƶ��PWMƵ��=72000000/4800000=15hz   ��ʱ��3 PWM��ʼ��
	//TIM3_PWM_Init(47999,99);	 //����Ƶ��PWMƵ��=72000000/4800000=15hz   ��ʱ��3 PWM��ʼ��
	//TIM_SetCompare2(TIM3,PWM);
	//TIM4_Int_Init(99,7199);   //��ʱ��4  ���Ƶ�ŷ��Ŀ���ʱ�� 10ms
 
	
  printf("-----------------\n");
  printf("PVDFѹ�籡Ĥ\n");
	printf("-----------------\n");
	

	//��ʾ��ʾ��Ϣ
	/*POINT_COLOR=BLUE;//��������Ϊ��ɫ
	//LCD_ShowString(60,130,200,16,16,"ADC_CH0_VAL:");	      //��ʾADCֵ  
	//LCD_ShowString(60,150,200,16,16,"ADC_CH0_VOL:0.000V");	//��ʾ��ѹֵ
	LCD_ShowString(60,170,200,16,16,"PWM:");	//��PWMƵ��
	LCD_ShowString(155,170,200,16,16,"%");
	LCD_ShowString(60,190,200,16,16,"level:");	//��PWMƵ��
	LCD_ShowString(60,210,200,16,16,"mode");
	LCD_ShowString(110,210,200,16,16,"prolactin");
	LCD_ShowString(60,230,200,16,16,"stop");
	//LCD_ShowString(60,250,200,16,16,"mod");	
	LCD_ShowxNum(130,170,0,3,16,0);*/
	
  while(1)   
	{
	  //printf("DDS_step:%d\n",DDS_step);
		//adcx=Get_Adc_Average(ADC_Channel_1,10);  //�ɼ�ADC����
		//printf("adc:%d",adcx);
//		//LCD_ShowxNum(156,130,adcx,4,16,0);//��ʾADC��ֵ
//		tempfeed = adcx;
//		temp=(float)adcx*(3.3/4096);  //��һ��
//		adcx=temp;
//		mod = MOD_func((double)temp); //��ģ��
//		//LCD_ShowxNum(156,250, mod*10000, 3,16,0);
//    if(PEN==0)
//   {
		TP_Read_XY2(&tp_dev.x,&tp_dev.y);
	  printf("����x:%d,����y:%d\n",tp_dev.x,tp_dev.y);
//		}			
//		
//		//LCD_ShowxNum(156,150,adcx,1,16,0);//��ʾ��ѹֵ
//		temp-=adcx;  //ȡ��С������
//		temp*=1000;
//		//LCD_ShowxNum(172,150,temp, 3,16,0X80); //��ʾ��ѹֵС������
//		

//		
//		
//		//LCD_ShowxNum(130,190,flagE, 3,16,0);
//		
//		if(flagup==0) 
//		{
//				TIM_SetCompare2(TIM3,0);
//				//LCD_ShowxNum(130,170,0,3,16,0);				
//			
//		}
//		else if(flagup == 1)
//		{
//			if(flagmod ==0 )
//			{
//			if(tempfeed <2500)
//				feedt  = 10000;
//			else if(tempfeed > 2500  && tempfeed <2600)
//				feedt  = 9900;
//			else if(tempfeed > 2600 && tempfeed <2700)
//				feedt  = 9850;
//			else if(tempfeed > 2700  && tempfeed <2800)
//				feedt  = 9800;
//			else if(tempfeed > 2800 && tempfeed <2900)
//				feedt  = 9600;
//			else if(tempfeed > 2900 && tempfeed <3000)
//				feedt  = 9000;
//			else if(tempfeed > 3000 && tempfeed <3100)
//				feedt  = 8000;
//			else if(tempfeed > 3100 && tempfeed <3200)
//				feedt  = 7000;
//			else if(tempfeed >3200)
//				feedt  = 6000;

//			TIM_SetCompare2(TIM3,feedt );
//			//LCD_ShowxNum(130,170,feedt /480,3,16,0);	
//		}
//		}
	}	 
 }

 

 
//�ⲿ�ж�3�������  kup ���ƿ�ʼ����ͣ
 /*void EXTI0_IRQHandler(void)
{
	delay_ms(10);//����
			if( KEYup == 1 )
	{
  				if(flagup==1)
					{
						flagup=0;
						TIM_Cmd(TIM4, DISABLE);
						LCD_ShowxNum(130,170,0,3,16,0);		
						LCD_ShowString(60,230,200,16,16,"stop");
					}
					else
					{
						flagup= 1;
						LCD_ShowString(60,230,200,16,16,"star");
						TIM_SetCompare2(TIM3,PWM);
						TIM_Cmd(TIM4, ENABLE);
						LCD_ShowxNum(130,170,PWM/480,3,16,0);	
					}
	}

	EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ  
}

//�ⲿ�ж�2�������   key2 ����ģʽ�л�
void EXTI2_IRQHandler(void)
{
	delay_ms(10);//����
	
	if( KEY2 == 0 )
	{
  				if(flagmod==1)			
					{
						flagmod=0;
					LCD_ShowString(110,210,200,16,16,"prolactin");  // flagmod 0 ��Ħģʽ
					}
					else
					{
						flagmod= 1;
					LCD_ShowString(110,210,200,16,16,"sucking");  // 1 ����ģʽ
					}
	}				
	EXTI_ClearITPendingBit(EXTI_Line2);  //���LINE4�ϵ��жϱ�־λ  
}


//�ⲿ�ж�3�������  key1
void EXTI3_IRQHandler(void)
{
	delay_ms(10);//����
	
	if( KEY1  == 0 )
	{
		if(flagup ==1)
		{
					if(flagmod== 1 )
					{
  				if(PWM >=48000)				
						PWM=0;
					else
						PWM=PWM+2000;
						TIM_SetCompare2(TIM3,PWM);
						LCD_ShowxNum(130,170,PWM/480,3,16,0);					
					}
					
					else if(flagmod ==0)
					{						   
  				if(flagE==2)
						flagE=0;
					else
						flagE= flagE+1;
					}
			}
	}	
	EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE3�ϵ��жϱ�־λ  
}


//�ⲿ�ж�4�������  key0
 void EXTI4_IRQHandler(void)
{
	delay_ms(10);//����
	if( KEY0 == 0 )
	{
		if(flagup == 1)
		{
					if(flagmod== 1 )
					{
					
  				if(PWM == 0)
						PWM=48000;
					else 
						PWM=PWM-2000;
					TIM_SetCompare2(TIM3,PWM);
					LCD_ShowxNum(130,170,PWM/480,3,16,0);					
					}
					
					else if(flagmod == 0)  //��Ħģʽ ����Ƶ��
					{						   
  				if(flagE==0)
						flagE=2;
					else
						flagE= flagE-1;
					}
			}
	}
	EXTI_ClearITPendingBit(EXTI_Line4); //���LINE0�ϵ��жϱ�־λ  
}

//��ʱ��4�жϷ������
void TIM4_IRQHandler(void)   //TIM4�ж�  10ms һ��
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
			switch(flagE)
			{				 
				case 0:	 
					t = 100;				   				
					break;	

				
				case 1:	  
					t = 80;		     			
					break;
				case 2:	  
					t = 50;			   
					break;
			}
			
		if (num == t)       //flgaE����ʱ��
		{
			LED1= 1;
			ELE = 0;
			num =0;
			TIM_SetCompare2(TIM3,0);
			delay_ms(500);
		 TIM_SetCompare2(TIM3,PWM);
		}
		else 
		{
			num = num+1;	
			LED1= 0;
			ELE = 1;
		}
		}
}*/
