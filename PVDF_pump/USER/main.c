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
/******************************/

char *comm1="add|sub", *comm2="switch",*comm3="mode";
int ptr;
/******************************/  
extern char DETECT_KEY;
extern uint16_t ADC_ConvertedValue[2];
extern uint8_t mode_status,stop_status;
extern uint16_t DDS_step,DDSM;
char time_interval=2;
char sel_state=0,scr_state=0,wave_pattern=0,amplitude_level=0;
char count_press;
extern u16 vol_per;

int Test(void)
{
	char command[] = "add|sub#11*switch#22*mode#33*mo12345de#33ascas";
	//char *s[4]={0};
	char *s[5];
	char *p,*p1;
	int num_command=0;
	int elenmentSize=0;
	int i=0; 
	
	//double *temp =(double*)malloc(30*sizeof(double)); //分配空间
	p = strtok(command, "*");
	while(p)
	{
		s[num_command++]=p;
		printf("%s\r\n",s[num_command-1]);
		p= strtok(NULL,"*");
	}
	//sizeof(s)//获取的是数组s总的字节数
	//数组s总的字节数初除以每一个元素的尺寸就是数组的个数
	printf("S长度:%d\r\n",sizeof(s));
	printf("S[0]长度:%d\r\n",strlen(s[0]));
	while(i<num_command)
	{
		p1=strtok(s[i],"#");
		printf("%s\r\n",p1);
		p1=strtok(NULL,"#");
		printf("%s\r\n",p1);
		i++;
	}
	
	ptr=strcmp(s[0],s[1]);
	printf("是否一致：%d",ptr);	
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
	TIM_Init(2048,0); 
	GAS_VALVE_Init(); 
/********************LCD/touch_init***********************/
	LCD_Init();			 	   
	Gui_StrCenter(0,64,GREEN,WHITE,"上海师范大学",32,1);//居中显示
  	 
	Gui_Drawbmp16(10,55,gImage_shool);
	
	TP_Init();
	EXTIX_Init(); 	 //按键中断初始化
	tp_dev.xfac=(float)(lcddev.width-40)/(400-3800);//得到xfac		 
	tp_dev.xoff=(lcddev.width-tp_dev.xfac*(3800+387))/2;//得到xoff
						  
	tp_dev.yfac=(float)(lcddev.height-40)/(294-3783);//得到yfac
	tp_dev.yoff=(lcddev.height-tp_dev.yfac*(3785+294))/2;//得到yoff 
/********************DMA/ADC_init***********************/
	DMA_Config(); 
	Adc_Init();	//ADC初始化Adc_Init();
		
	Test();
	
  while(1)   
	{
		
		if(DETECT_KEY==1)
		{
			if(scr_state==0)
			{
				
				//printf("\r\nch1:%d ,ch2:%d",ADC_ConvertedValue[0],vol_per);
	      printf("\r\n坐标x:%d,坐标y:%d",tp_dev.x,tp_dev.y);
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
				LCD_ShowChar(300,0,GREEN,WHITE,'%',16,0);//电量百分比
				DETECT_KEY=0;
			}
			if(scr_state==1)
			{
				LCD_ShowNum(270,0,vol_per,3,16);//显示ADC的值
				printf("\r\n坐标x:%d,坐标y:%d",tp_dev.x,tp_dev.y);
				
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
						if(wave_pattern==4)wave_pattern=0;
					  else wave_pattern++;		
				}				
				LCD_ShowNum(40,50,amplitude_level+1,1,16);
				LCD_ShowNum(100,50,DDSM,1,16);
				LCD_ShowNum(160,50,wave_pattern,1,16);
				DETECT_KEY=0;
			}
		}
	 
	 	
   
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
