#include "led.h"
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 

////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void GAS_VALVE_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 //����-->PB.1 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.1
 GAS=0;
 /*GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PE.5 �˿�����, �������
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				//�����趨������ʼ��GPIOE.5
 GPIO_SetBits(GPIOE,GPIO_Pin_5); 						 //PE.5 ����� 
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	    		 //LED1-->PA.5 �˿�����, �������
 GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //�����趨������ʼ��GPIOA.6
 GPIO_SetBits(GPIOA,GPIO_Pin_6); 						 //PA.6 ����� */
	
}
 

