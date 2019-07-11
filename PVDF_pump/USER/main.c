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
  u16 adcx; //adc����
	
	double mod;
    char command[] = "add|sub:1;switch:1;wave_mode:2;on|off:1";
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
  generate_wave();
  while(1)   
	{
		//printf("\r\nch1:%d ,ch2:%d",ADC_ConvertedValue[0],ADC_ConvertedValue[1]);
		LCD_ShowNum(280,0,vol_per,2,16);//��ʾADC��ֵ	
		
	  touch_process();
	 	key_process();
		
	}	 
 }

