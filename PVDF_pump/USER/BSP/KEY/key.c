
#include "key.h"
								    
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY3���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY_UP!!
void EXTIX_Init(void)
{
	//������ʼ������
		GPIO_InitTypeDef GPIO_InitStructure;
	  EXTI_InitTypeDef EXTI_InitStructure;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);//ʹ��PORTA 
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;//PA.3 �Ӵ����ж�
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
		GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
	  
	  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;//PA.8 home��
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
		GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
	
	  //GPIOA.3	  �ж����Լ��жϳ�ʼ������ �½��ش��� 
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	  
	  //GPIOA.8	  �ж����Լ��жϳ�ʼ������  �½��ش���	
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line8;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ��� 
	  
		EXTI_NVIC_Configuration();
}






