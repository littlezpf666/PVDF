#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
#include "key.h"
//////////////////////////////////////////////////////////////////////////////////	 
//����ģ��			  
//////////////////////////////////////////////////////////////////////////////////   	 

//#define KEY0 PEin(4)   	//PE4
//#define KEY1 PEin(3)	//PE3 
//#define WK_UP PAin(0)	//PA0  WK_UP

#define KEYup  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ����0 wk-up
#define KEY2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//��ȡ����1 key2
#define KEY1   GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//��ȡ����3(WK_UP)  key1
#define KEY0   GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//��ȡ����3(WK_UP)  key0


void EXTIX_Init(void);//�ⲿ�жϳ�ʼ��	 �жϰ���

#endif
