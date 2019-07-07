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
  //generate_wave();
  while(1)   
	{
		//printf("\r\nch1:%d ,ch2:%d",ADC_ConvertedValue[0],ADC_ConvertedValue[1]);
		LCD_ShowNum(280,0,vol_per,2,16);//��ʾADC��ֵ	
		
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

