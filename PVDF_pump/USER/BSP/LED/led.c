#include "led.h"
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 

////////////////////////////////////////////////////////////////////////////////// 	   

//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化
void GAS_VALVE_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 //气阀-->PB.1 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.1
 GAS=0;
 /*GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PE.5 端口配置, 推挽输出
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				//根据设定参数初始化GPIOE.5
 GPIO_SetBits(GPIOE,GPIO_Pin_5); 						 //PE.5 输出高 
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	    		 //LED1-->PA.5 端口配置, 推挽输出
 GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //根据设定参数初始化GPIOA.6
 GPIO_SetBits(GPIOA,GPIO_Pin_6); 						 //PA.6 输出高 */
	
}
 

