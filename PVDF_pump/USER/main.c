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
/*一个源文件调用另一个源文件的函数只需要声明一下另一文件中的函数名就可以了，
与原函数同名的.h文件的作用：
对调用的文件来说起作用的是.h中的函数声明，有了这个声明就可以调用对应源函数中的函数
对于被调用文件来说，其作用是如果在同一文件中函数要相互调用，将函数声明都写到.h中就可以
不用考虑函数定义顺序问题，并且将一些宏，和结构体，外部调用变量声明写在里面可以实现资源
共享。
*/
/*
.h中不要进行变量声明，因为调用函数与被调用都有.h文件也就是变量会被声明两次导致语法错误
*/
/************************************************
 PVDF_pump
************************************************/
u16 PWM=0;  //PWM变量
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
  u16 adcx; //adc变量
	float temp;
	double mod;
	delay_init();	    	 //延时函数初始化	
	
	 
	uart_init(115200);	 	//串口初始化为115200
 	LED_Init();			     //LED端口初始化
	//EXTIX_Init(); 	 //按键中断初始化
	//Adc_Init();		  	 	//ADC初始化Adc_Init();		  	 	//ADC初始化 
	LCD_Init();			 	   //LCD初始化
	//TIM_Init(2048,2048);
	Gui_StrCenter(0,64,GREEN,BLUE,"上海师范大学",32,1);//居中显示  
 	
	TP_Init();
	
  //TIM3_Mode_config(390,71);	 
  //TIM3_PWM_Init(47999,99);	 //不分频。PWM频率=72000000/4800000=15hz   定时器3 PWM初始化
	//TIM3_PWM_Init(47999,99);	 //不分频。PWM频率=72000000/4800000=15hz   定时器3 PWM初始化
	//TIM_SetCompare2(TIM3,PWM);
	//TIM4_Int_Init(99,7199);   //定时器4  控制电磁阀的开关时间 10ms
 
	
  printf("-----------------\n");
  printf("PVDF压电薄膜\n");
	printf("-----------------\n");
	

	//显示提示信息
	/*POINT_COLOR=BLUE;//设置字体为蓝色
	//LCD_ShowString(60,130,200,16,16,"ADC_CH0_VAL:");	      //显示ADC值  
	//LCD_ShowString(60,150,200,16,16,"ADC_CH0_VOL:0.000V");	//显示电压值
	LCD_ShowString(60,170,200,16,16,"PWM:");	//显PWM频率
	LCD_ShowString(155,170,200,16,16,"%");
	LCD_ShowString(60,190,200,16,16,"level:");	//显PWM频率
	LCD_ShowString(60,210,200,16,16,"mode");
	LCD_ShowString(110,210,200,16,16,"prolactin");
	LCD_ShowString(60,230,200,16,16,"stop");
	//LCD_ShowString(60,250,200,16,16,"mod");	
	LCD_ShowxNum(130,170,0,3,16,0);*/
	
  while(1)   
	{
	  //printf("DDS_step:%d\n",DDS_step);
		//adcx=Get_Adc_Average(ADC_Channel_1,10);  //采集ADC数据
		//printf("adc:%d",adcx);
//		//LCD_ShowxNum(156,130,adcx,4,16,0);//显示ADC的值
//		tempfeed = adcx;
//		temp=(float)adcx*(3.3/4096);  //归一化
//		adcx=temp;
//		mod = MOD_func((double)temp); //逆模型
//		//LCD_ShowxNum(156,250, mod*10000, 3,16,0);
//    if(PEN==0)
//   {
		TP_Read_XY2(&tp_dev.x,&tp_dev.y);
	  printf("坐标x:%d,坐标y:%d\n",tp_dev.x,tp_dev.y);
//		}			
//		
//		//LCD_ShowxNum(156,150,adcx,1,16,0);//显示电压值
//		temp-=adcx;  //取出小数部分
//		temp*=1000;
//		//LCD_ShowxNum(172,150,temp, 3,16,0X80); //显示电压值小数部分
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

 

 
//外部中断3服务程序  kup 控制开始和暂停
 /*void EXTI0_IRQHandler(void)
{
	delay_ms(10);//消抖
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

	EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位  
}

//外部中断2服务程序   key2 控制模式切换
void EXTI2_IRQHandler(void)
{
	delay_ms(10);//消抖
	
	if( KEY2 == 0 )
	{
  				if(flagmod==1)			
					{
						flagmod=0;
					LCD_ShowString(110,210,200,16,16,"prolactin");  // flagmod 0 按摩模式
					}
					else
					{
						flagmod= 1;
					LCD_ShowString(110,210,200,16,16,"sucking");  // 1 吸乳模式
					}
	}				
	EXTI_ClearITPendingBit(EXTI_Line2);  //清除LINE4上的中断标志位  
}


//外部中断3服务程序  key1
void EXTI3_IRQHandler(void)
{
	delay_ms(10);//消抖
	
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
	EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE3上的中断标志位  
}


//外部中断4服务程序  key0
 void EXTI4_IRQHandler(void)
{
	delay_ms(10);//消抖
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
					
					else if(flagmod == 0)  //按摩模式 控制频率
					{						   
  				if(flagE==0)
						flagE=2;
					else
						flagE= flagE-1;
					}
			}
	}
	EXTI_ClearITPendingBit(EXTI_Line4); //清除LINE0上的中断标志位  
}

//定时器4中断服务程序
void TIM4_IRQHandler(void)   //TIM4中断  10ms 一次
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update );  //清除TIMx的中断待处理位:TIM 中断源 
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
			
		if (num == t)       //flgaE控制时间
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
