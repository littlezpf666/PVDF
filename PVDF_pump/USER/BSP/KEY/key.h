#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
#include "key.h"
//////////////////////////////////////////////////////////////////////////////////	 
//按键模块			  
//////////////////////////////////////////////////////////////////////////////////   	 

//#define KEY0 PEin(4)   	//PE4
//#define KEY1 PEin(3)	//PE3 
//#define WK_UP PAin(0)	//PA0  WK_UP

#define KEYup  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键0 wk-up
#define KEY2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//读取按键1 key2
#define KEY1   GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//读取按键3(WK_UP)  key1
#define KEY0   GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//读取按键3(WK_UP)  key0


void EXTIX_Init(void);//外部中断初始化	 中断按键

#endif
