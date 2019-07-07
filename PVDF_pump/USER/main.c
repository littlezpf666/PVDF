#include "sys.h"
#include "delay.h"
#include "key.h"
#include "lcd.h"
#include "pic.h"
#include "usart.h"
#include "dma.h"
#include "adc.h"
#include "string.h"
#include "timer.h"
#include "pid.h"
#include "mod.h"
#include "math.h"
#include "interaction.h"
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

//extern char DETECT_USART_COMM;
extern u16 vol_per;



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
    char command[] = "add|sub:1;switch:1;wave_mode:2;on|off:1";
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
		LCD_ShowNum(280,0,vol_per,2,16);//显示ADC的值	
		
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

