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
//u16 PWM=0;  //PWM变量
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
		Gui_StrCenter(0,64,GREEN,WHITE,"上海师范大学",32,1);//居中显示
		Show_Str(150,100,LIGHTGREEN,WHITE,"精控实验室",24,1);
			 
		Gui_Drawbmp16(10,60,gImage_shool);
}
void scr1_content()
{
		Gui_Drawbmp16(20,170,gImage_arrow_up);
		Gui_Drawbmp16(100,170,gImage_arrow_down);
		Gui_Drawbmp16(180,170,gImage_switch);
		Gui_Drawbmp16(260,170,gImage_mode);
	  Gui_Drawbmp16(180,0,gImage_wifi);
		Show_Str(40,40,RED,WHITE,"强度",16,1);
		Show_Str(100,40,GREEN,WHITE,"频率",16,1);
		LCD_DrawRectangle(170, 60, 300, 140);
		Show_Str(180,70,RED,WHITE,"吸乳",16,1);
		Show_Str(260,70,GREEN,WHITE,"开奶",16,1);
		Show_Str(180,110,GREEN,WHITE,"催乳",16,1);
		Show_Str(260,110,GREEN,WHITE,"按摩",16,1);
		LCD_ShowChar(300,0,GREEN,WHITE,'%',16,0);//电量百分比
}

char touch_process(void)
{
		if(DETECT_TOUCH==1||DETECT_USART_COMM==1)
		{
			if(scr_state==0)
			{
	      printf("\r\n坐标x:%d,坐标y:%d",tp_dev.x,tp_dev.y);
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
						Show_Str(40,40,RED,WHITE,"强度",16,1);
					  Show_Str(100,40,GREEN,WHITE,"频率",16,1);
						sel_state=0;
					}
					else {
						Show_Str(100,40,RED,WHITE,"频率",16,1);
						Show_Str(40,40,GREEN,WHITE,"强度",16,1);
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
								Show_Str(180,70,RED,WHITE,"吸乳",16,1);
								Show_Str(260,110,GREEN,WHITE,"按摩",16,1);
							break;
							case 1:
								Show_Str(260,70,RED,WHITE,"开奶",16,1);
								Show_Str(180,70,GREEN,WHITE,"吸乳",16,1);
							break;
							case 2:
								Show_Str(180,110,RED,WHITE,"催乳",16,1);
								Show_Str(260,70,GREEN,WHITE,"开奶",16,1);
							break;
							case 3:
								Show_Str(260,110,RED,WHITE,"按摩",16,1);
								Show_Str(180,110,GREEN,WHITE,"催乳",16,1);
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
  u16 adcx; //adc变量
	
	double mod;
  
/********************usart_init**************************/	 
	uart_init(115200);	 	//串口初始化为115200
	printf("\r\n-----------------");
  printf("PVDF压电薄膜");
	printf("-----------------\r\n");
	 
/********************TIM3/4_init**************************/
	TIM_Init(0,0); 
	GAS_VALVE_Init(); 
/********************LCD/touch_init***********************/
	LCD_Init();
  scr0_content();	 

	TP_Init();
	EXTIX_Init(); 	 //按键中断初始化
	tp_dev.xfac=(float)(lcddev.width-40)/(400-3800);//得到xfac		 
	tp_dev.xoff=(lcddev.width-tp_dev.xfac*(3800+387))/2;//得到xoff
						  
	tp_dev.yfac=(float)(lcddev.height-40)/(294-3783);//得到yfac
	tp_dev.yoff=(lcddev.height-tp_dev.yfac*(3785+294))/2;//得到yoff 
/********************DMA/ADC_init***********************/
	DMA_Config(); 
	Adc_Init();	//ADC初始化Adc_Init();
  //generate_wave();
  while(1)   
	{
		//printf("\r\nch1:%d ,ch2:%d",ADC_ConvertedValue[0],ADC_ConvertedValue[1]);
		LCD_ShowNum(270,0,vol_per,2,16);//显示ADC的值	
		
	  touch_process();
	 	key_process();
		
//		tempfeed = adcx;
//		temp=(float)adcx*(3.3/4096);  //归一化
//		adcx=temp;
//		mod = MOD_func((double)temp); //逆模型
//		//LCD_ShowxNum(156,250, mod*10000, 3,16,0);
  		
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
