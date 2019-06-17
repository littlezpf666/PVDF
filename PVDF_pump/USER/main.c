#include "sys.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "lcd.h"
#include "GUI.h"
#include "usart.h"
#include "dma.h"
#include "adc.h"
#include "string.h"
#include "timer.h"
#include "pid.h"
#include "mod.h"
#include "touch.h"
#include "pic.h"
#include "math.h"
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
//u16 PWM=0;  //PWM����
//u8 num = 0;
//u8 flagE = 0;
//u8 flagup = 0;
//u8 flagmod =0;
//u8 t = 1;
//u16 tempfeed ;
//u16 feedt ;
/******************************/


/******************************/  
extern char DETECT_TOUCH,DETECT_KEY,DETECT_USART_COMM;
//extern char DETECT_USART_COMM;
extern uint16_t ADC_ConvertedValue[2];
extern uint8_t mode_status,stop_status;
extern uint16_t DDS_step,DDSM;
extern u16 vol_per;
extern u32 temp_val;
char time_interval=3;
char sel_state=0,scr_state=0,wave_pattern=0,amplitude_level=0;
char count_press;
char uart_comm[4];
void scr0_content()
{
		Gui_StrCenter(0,64,GREEN,WHITE,"�Ϻ�ʦ����ѧ",32,1);//������ʾ
		Show_Str(150,100,LIGHTGREEN,WHITE,"����ʵ����",24,1);
			 
		Gui_Drawbmp16(10,60,gImage_shool);
}
void scr1_content()
{
		Gui_Drawbmp16(20,170,gImage_arrow_up);
		Gui_Drawbmp16(100,170,gImage_arrow_down);
		Gui_Drawbmp16(180,170,gImage_switch);
		Gui_Drawbmp16(260,170,gImage_mode);
	  Gui_Drawbmp16(180,0,gImage_wifi);
		Show_Str(40,40,RED,WHITE,"ǿ��",16,1);
		Show_Str(100,40,GREEN,WHITE,"Ƶ��",16,1);
		LCD_DrawRectangle(170, 60, 300, 140);
		Show_Str(180,70,RED,WHITE,"����",16,1);
		Show_Str(260,70,GREEN,WHITE,"����",16,1);
		Show_Str(180,110,GREEN,WHITE,"����",16,1);
		Show_Str(260,110,GREEN,WHITE,"��Ħ",16,1);
		LCD_ShowChar(300,0,GREEN,WHITE,'%',16,0);//�����ٷֱ�
}

char touch_process(void)
{
		if(DETECT_TOUCH==1||DETECT_USART_COMM==1)
		{
			if(scr_state==0)
			{
	      printf("\r\n����x:%d,����y:%d",tp_dev.x,tp_dev.y);
				scr_state=1;
				LCD_Clear(WHITE);
				scr1_content();
				DETECT_KEY=0;
			}
			if(scr_state==1)
			{
				if(KEY_ADD||uart_comm[0]=='1')
				{
					if(sel_state==0)
					{
//							if(++amplitude_level>5)
//						{
//							amplitude_level=5;	
//						}
						if(amplitude_level<5) amplitude_level++; 
					}
					else
					{
						if(DDSM<4) DDSM++;
					}
				}
				if(KEY_SUB||uart_comm[1]=='1')
				{
					if(sel_state==0)
					{
						if(amplitude_level>0) --amplitude_level;
				  }
					else
					{
						if(DDSM>1)DDSM--;
					}
				}
				
				if(KEY_SWITCH||uart_comm[2]=='1')
				{
					if(sel_state==1){
						Show_Str(40,40,RED,WHITE,"ǿ��",16,1);
					  Show_Str(100,40,GREEN,WHITE,"Ƶ��",16,1);
						sel_state=0;
					}
					else {
						Show_Str(100,40,RED,WHITE,"Ƶ��",16,1);
						Show_Str(40,40,GREEN,WHITE,"ǿ��",16,1);
						sel_state=0;
					sel_state++;}
				}
        if(KEY_MODE)
				{	
						if(wave_pattern==3)wave_pattern=0;
					  else wave_pattern++;
					  switch (wave_pattern)
						{
							case 0:
								Show_Str(180,70,RED,WHITE,"����",16,1);
								Show_Str(260,110,GREEN,WHITE,"��Ħ",16,1);
							break;
							case 1:
								Show_Str(260,70,RED,WHITE,"����",16,1);
								Show_Str(180,70,GREEN,WHITE,"����",16,1);
							break;
							case 2:
								Show_Str(180,110,RED,WHITE,"����",16,1);
								Show_Str(260,70,GREEN,WHITE,"����",16,1);
							break;
							case 3:
								Show_Str(260,110,RED,WHITE,"��Ħ",16,1);
								Show_Str(180,110,GREEN,WHITE,"����",16,1);
							break;	
						}
							
				}
        if((DETECT_USART_COMM==1)&&(uart_comm[3]-48<5))
        {
					wave_pattern=uart_comm[3]-48;
				}									
				LCD_ShowNum(40,80,amplitude_level+1,1,48);
				LCD_ShowNum(100,80,DDSM,1,48);
				//LCD_ShowNum(160,70,wave_pattern,1,48);
				DETECT_TOUCH=0;
				DETECT_USART_COMM=0;
			}
		}
		return 0;
}
char key_process(void)
{
	static char mode=0;
	if(DETECT_KEY==1)
	{
//		scr_state=0;
//		sel_state=0;
//		amplitude_level=0;
//		wave_pattern=0;
		if(mode)
		{
			amplitude_level=0;
			LCD_ShowNum(40,80,amplitude_level+1,1,48);
			TIM_SetCompare2(TIM3, 0);
			TIM_SetCompare3(TIM3, 0);
			GAS=0;
			TIM_ITConfig(TIM3,TIM_IT_Update,DISABLE);
		}
		else
		{
			TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);			
		}
		mode=~mode;
		DETECT_KEY=0;
	}
		
	return 0;
}
char generate_wave()
{
	u8 time=0;
	u16 y;
		for(time=0;time<128;time++)
	{
		y=400*sin(6.28/255*(time+192))+1200;
		printf("%d,",y);
	}
  printf("\n\r");
	return 0;
}

 int main(void)
 {	
  char tp_x;
  u16 adcx; //adc����
	
	double mod;
  
/********************usart_init**************************/	 
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	printf("\r\n-----------------");
  printf("PVDFѹ�籡Ĥ");
	printf("-----------------\r\n");
	 
/********************TIM3/4_init**************************/
	TIM_Init(0,0); 
	GAS_VALVE_Init(); 
/********************LCD/touch_init***********************/
	LCD_Init();
  scr0_content();	 

	TP_Init();
	EXTIX_Init(); 	 //�����жϳ�ʼ��
	tp_dev.xfac=(float)(lcddev.width-40)/(400-3800);//�õ�xfac		 
	tp_dev.xoff=(lcddev.width-tp_dev.xfac*(3800+387))/2;//�õ�xoff
						  
	tp_dev.yfac=(float)(lcddev.height-40)/(294-3783);//�õ�yfac
	tp_dev.yoff=(lcddev.height-tp_dev.yfac*(3785+294))/2;//�õ�yoff 
/********************DMA/ADC_init***********************/
	DMA_Config(); 
	Adc_Init();	//ADC��ʼ��Adc_Init();
  //generate_wave();
  while(1)   
	{
		//printf("\r\nch1:%d ,ch2:%d",ADC_ConvertedValue[0],ADC_ConvertedValue[1]);
		LCD_ShowNum(270,0,vol_per,2,16);//��ʾADC��ֵ	
		
	  touch_process();
	 	key_process();
		
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
