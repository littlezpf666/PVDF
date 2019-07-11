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


/******************************/  

//extern char DETECT_USART_COMM;
extern u16 vol_per;


extern uint16_t si[][256],triangle[][256],ex[][256],square[][256];
char generate_wave()
{
	u16 time=0;
	u16 y;
		for(time=0;time<256;time++)
	{
		//si[0][time]=400*sin(6.28/255*(time+192))+2800;
		si[0][time]=400*sin(6.28/255*(time+192))+1400;
		printf("%d,",si[0][time]);
	}
	printf("\n\r");
	for(time=0;time<256;time++)
	{
	 if(time<128)
	 triangle[0][time]=(uint16_t)((float)800/128*time+1000);	 
	 else
	 triangle[0][time]=(uint16_t)(-(float)800/127*time+2600);
	 //printf("time:%d,triangle:%d,",time,triangle[0][time]);
	 printf("%d,",triangle[0][time]);
	}  
	  printf("\n\r");
	for(time=0;time<256;time++)
	{
		 if(time<100)
		 square[0][time]=1400;
		 else
		 square[0][time]=1000;
		 printf("%d,",square[0][time]);
	}
	 printf("\n\r");
	  for(time=0;time<256;time++)
	{
		 if(time<128)
		 ex[0][time]=exp((double)5.99/128*time)+1400;
		 else
		 ex[0][time]=-exp((double)5.99/128*(time-128))+1400;
		 printf("%d,",ex[0][time]);
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
  generate_wave();
  while(1)   
	{
		//printf("\r\nch1:%d ,ch2:%d",ADC_ConvertedValue[0],ADC_ConvertedValue[1]);
		LCD_ShowNum(280,0,vol_per,2,16);//显示ADC的值	
		
	  touch_process();
	 	key_process();
		
	}	 
 }

