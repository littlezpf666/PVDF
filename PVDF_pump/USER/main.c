#include "sys.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "lcd.h"
#include "GUI.h"
#include "usart.h"
#include "dma.h"
#include "adc.h"
#include "timer.h"
#include "pid.h"
#include "mod.h"
#include "touch.h"
#include "pic.h"
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
extern char DETECT_KEY;
extern uint16_t ADC_ConvertedValue[2];
extern uint8_t mode_status,stop_status;
extern uint16_t DDS_step,DDSM;
char time_interval=4;
char sel_state=0,scr_state=0,wave_pattern=0,amplitude_level=0;
char count_press;
 int main(void)
 {	
  char tp_x;
  u16 adcx; //adc����
	float temp;
	double mod;	
/********************usart_init**************************/	 
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	printf("\r-----------------");
  printf("PVDFѹ�籡Ĥ");
	printf("-----------------\n");
	 
/********************TIM3/4_init**************************/
	TIM_Init(2048,2048);
	 
/********************LCD/touch_init***********************/
	LCD_Init();			 	   
	Gui_StrCenter(0,64,GREEN,WHITE,"�Ϻ�ʦ����ѧ",32,1);//������ʾ
  	 
	Gui_Drawbmp16(10,55,gImage_shool);
	TP_Init();
	EXTIX_Init(); 	 //�����жϳ�ʼ��
	tp_dev.xfac=(float)(lcddev.width-40)/(400-3800);//�õ�xfac		 
	tp_dev.xoff=(lcddev.width-tp_dev.xfac*(3800+387))/2;//�õ�xoff
						  
	tp_dev.yfac=(float)(lcddev.height-40)/(294-3783);//�õ�yfac
	tp_dev.yoff=(lcddev.height-tp_dev.yfac*(3785+294))/2;//�õ�yoff 
/********************DMA/ADC_init***********************/
	DMA_Config(); 
	Adc_Init();	//ADC��ʼ��Adc_Init();		  	 	
	 
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
		if(DETECT_KEY==1)
		{
			if(scr_state==0)
			{
				printf("\r\nch1:%d ,ch2:%d",ADC_ConvertedValue[0],ADC_ConvertedValue[1]);
				
	      printf("\r\n����x:%d,����y:%d",tp_dev.x,tp_dev.y);
				scr_state=1;
				LCD_Clear(WHITE);
				Gui_Drawbmp16(20,160,gImage_arrow_up);
				Gui_Drawbmp16(100,160,gImage_arrow_down);
				Gui_Drawbmp16(180,160,gImage_switch);
				Gui_Drawbmp16(260,160,gImage_mode);
				POINT_COLOR=RED;
				LCD_ShowString(40,30,16,"stre",1);
				POINT_COLOR=GREEN;
				LCD_ShowString(100,30,16,"freq",1);
				DETECT_KEY=0;
			}
			if(scr_state==1)
			{
				printf("\r\n����x:%d,����y:%d",tp_dev.x,tp_dev.y);
				
				if(tp_dev.x>20&&tp_dev.x<60&&tp_dev.y>160&&tp_dev.y<200)
				{
					if(sel_state==0)
					{
							if(++amplitude_level>5)
						{
							amplitude_level=5;	
						}
					}
					else
					{
						if(DDSM<4)
						 {
						   DDSM++;
						 }
					}
				}
				if(tp_dev.x>100&&tp_dev.x<140&&tp_dev.y>160&&tp_dev.y<200)
				{
					if(sel_state==0)
					{
						if(amplitude_level>0)
						{
							--amplitude_level;	
						}
				 }
					else
					{
						if(DDSM>1)
						 {
						  DDSM--;
						 }
					}
				}
				if(tp_dev.x>180&&tp_dev.x<220&&tp_dev.y>160&&tp_dev.y<200)
				{
					if(sel_state==1){
						POINT_COLOR=RED;
						LCD_ShowString(40,30,16,"stre",1);
						POINT_COLOR=GREEN;
					  LCD_ShowString(100,30,16,"freq",1);
						sel_state=0;
					}
					else {
						POINT_COLOR=RED;
					  LCD_ShowString(100,30,16,"freq",1);
						POINT_COLOR=GREEN;
						LCD_ShowString(40,30,16,"stre",1);
						sel_state=0;
					sel_state++;}
				}
        if(tp_dev.x>260&&tp_dev.x<300&&tp_dev.y>160&&tp_dev.y<180)
				{
					
					if(wave_pattern>0)
					{
						if(wave_pattern==4)wave_pattern=0;
					  else wave_pattern++;	
					}
				}				
				LCD_ShowNum(40,50,amplitude_level+1,1,16);
				LCD_ShowNum(100,50,DDSM,1,16);
				DETECT_KEY=0;
			}
		}
		
//		//LCD_ShowxNum(156,130,adcx,4,16,0);//��ʾADC��ֵ
//		tempfeed = adcx;
//		temp=(float)adcx*(3.3/4096);  //��һ��
//		adcx=temp;
//		mod = MOD_func((double)temp); //��ģ��
//		//LCD_ShowxNum(156,250, mod*10000, 3,16,0);
  		
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
