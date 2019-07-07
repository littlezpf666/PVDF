
#include "usart.h"


////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/8/18
//�汾��V1.5
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
//V1.5�޸�˵��
//1,�����˶�UCOSII��֧��
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 0
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*ʹ��microLib�ķ���*/
 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
u16 string_num;
u8 rx_status=0;
extern char uart_comm[5],Init[5],tcp_Port[5],udp_Port[5];
extern u16 vol_per;
u16 string_num;
u8 header_num=0;
char string_process(char command[])
{
	//char command[] = "add|sub:1;switch:1;wave_mode:2;on|off:1";
	char *comm1="\"add|sub\"", *comm2="\"switch\"",*comm3="\"wave_mode\"",*comm4="\"on|off\"";
	char *s[5];//�ô洢�ָ�֮���ַ���������
	char *p,*p1;
	char num_command=0;
	int i=0,ptr; 

	p = strtok(command, ",");
	while(p)
	{
		s[num_command++]=p;
		//printf("%s\r\n",s[num_command-1]);
		p= strtok(NULL,",");
	}
	strncpy(uart_comm,s[0],5);
	strncpy(Init,s[1],5);
	strncpy(tcp_Port,s[2],5);
	strncpy(udp_Port,s[3],5);
	//sizeof(s)//��ȡ��������s�ܵ��ֽ���
	//����s�ܵ��ֽ���������ÿһ��Ԫ�صĳߴ��������ĸ���sizeof(s)/sizeof(s[0])
	//printf("ָ�����:%d\r\n",num_command);
	/*while(i<num_command)
	{
		p1=strtok(s[i],":");
		printf("%s\r\n",p1);
		p1=strtok(NULL,":");
		printf("%s\r\n",p1);
		i++;
	}*/
	
	//ptr=strcmp(s[0],s[1]);
	//printf("�Ƿ�һ�£�%d",ptr);	
	return 0;
} 


#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0xf000;       //����״̬���	  
u8 DETECT_USART_COMM=0;  
void uart_init(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

}


void USART1_IRQHandler(void)                	//����1�жϷ������
	{
	u8 i,Res;
#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		Res =USART_ReceiveData(USART1);	//��ȡ���յ�������
			switch (rx_status)
			{
				case 0:
//					if(Res=='*')
//						printf("{\"power\":%d}",vol_per);
//          else					
					switch (header_num)
					{
						case 0:
								if(Res=='z') header_num=1; else {header_num=0;rx_status=0;}			
						break;
						case 1:
                if(Res=='p') header_num=2; else {header_num=0;rx_status=0;}
						break;
						case 2:	
							  if(Res=='f') {rx_status=1;header_num=0;} else {header_num=0;rx_status=0;}
            break;
					}							
				break;	
				case 1:
					if(Res==0x0d)//�ȴ��ո�
						rx_status=2;
					else
					{
						USART_RX_BUF[string_num]=Res ;
						string_num++;
						if(string_num>(USART_REC_LEN-1))
						{ 
							memset(USART_RX_BUF,0,string_num);
							string_num=0;
							rx_status=0;
						}//�������ݴ���,���¿�ʼ����	  
					}		 
					break;
        case 2:
					if(Res==0x0a)//�ȴ��س�
					{
						 string_process(USART_RX_BUF);
						 
						 /*printf("%s\r\n",uart_comm);
						 printf("%s\r\n",Init);
						 printf("%s\r\n",tcp_Port);
						 printf("%s\r\n",udp_Port);*/
						
						 DETECT_USART_COMM=1;
					 }
					 memset(USART_RX_BUF,0,string_num);
					 string_num=0;
					 rx_status=0;
					break;					
			}
				
		/*if((USART_RX_STA&0x8000)==0)//����δ���
			{
			if(USART_RX_STA&0x4000)//���յ���0x0d���ո�
				{
				if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
				else{                       //���յ��ո�󣬽��յ��˻س�
											 
				   USART_RX_STA|=0x8000;	//���������
					 printf("%x",USART_RX_STA);
					} 
				 
				}
			else //��û�յ�0X0D
				{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
					{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
					}		 
				}
			} 
			else if((USART_RX_STA&0x8000)==0x8000)
				{				
					USART_RX_STA=0;
				  if(Res==0x0d)USART_RX_STA|=0x4000;
				else
					{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
					}		 
			 }*/
     } 
#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntExit();  											 
#endif
} 
#endif	
/*********************�������ݻ��溯��******************************/
void Usart2_Put_Buf(u8 a[],u8 _cnt) 
{
  u8 i;
  for(i=0;i<_cnt;i++) 
	{
	USART_SendData(USART1,a[i]);
	while (USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);	
  }
}

/*********************���β�������*************************/
void Data_Send_Senser(u16 a,u16 b,u16 c,u16 d)
{
	u8  _cnt=0,i,sum=0;
  u8 		data_to_send[30];
	data_to_send[_cnt++]=0xAA;//???
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x02;
	data_to_send[_cnt++]=0;
	
	data_to_send[_cnt++]=a/256;  //16?? ??Y?3????? ???????
	data_to_send[_cnt++]=a%256;  //??????
	
	data_to_send[_cnt++]=b/256;  //??2
	data_to_send[_cnt++]=b%256;
	
	data_to_send[_cnt++]=c/256;  // ??3
	data_to_send[_cnt++]=c%256;
	
	data_to_send[_cnt++]=d/256;
	data_to_send[_cnt++]=d%256;
		
	data_to_send[3] = _cnt-4;
	
	for( i=0;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++] = sum;

	Usart2_Put_Buf(data_to_send,_cnt);
}
