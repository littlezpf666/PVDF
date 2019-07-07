
#include "usart.h"


////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//串口1初始化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/8/18
//版本：V1.5
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//********************************************************************************
//V1.3修改说明 
//支持适应不同频率下的串口波特率设置.
//加入了对printf的支持
//增加了串口接收命令功能.
//修正了printf第一个字符丢失的bug
//V1.4修改说明
//1,修改串口初始化IO的bug
//2,修改了USART_RX_STA,使得串口最大接收字节数为2的14次方
//3,增加了USART_REC_LEN,用于定义串口最大允许接收的字节数(不大于2的14次方)
//4,修改了EN_USART1_RX的使能方式
//V1.5修改说明
//1,增加了对UCOSII的支持
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 0
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*使用microLib的方法*/
 
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
	char *s[5];//用存储分割之后字符串的数组
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
	//sizeof(s)//获取的是数组s总的字节数
	//数组s总的字节数初除以每一个元素的尺寸就是数组的个数sizeof(s)/sizeof(s[0])
	//printf("指令个数:%d\r\n",num_command);
	/*while(i<num_command)
	{
		p1=strtok(s[i],":");
		printf("%s\r\n",p1);
		p1=strtok(NULL,":");
		printf("%s\r\n",p1);
		i++;
	}*/
	
	//ptr=strcmp(s[0],s[1]);
	//printf("是否一致：%d",ptr);	
	return 0;
} 


#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0xf000;       //接收状态标记	  
u8 DETECT_USART_COMM=0;  
void uart_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //组2：2位抢占优先级，2位响应优先级
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 

}


void USART1_IRQHandler(void)                	//串口1中断服务程序
	{
	u8 i,Res;
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
		Res =USART_ReceiveData(USART1);	//读取接收到的数据
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
					if(Res==0x0d)//等待空格
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
						}//接收数据错误,重新开始接收	  
					}		 
					break;
        case 2:
					if(Res==0x0a)//等待回车
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
				
		/*if((USART_RX_STA&0x8000)==0)//接收未完成
			{
			if(USART_RX_STA&0x4000)//接收到了0x0d即空格
				{
				if(Res!=0x0a)USART_RX_STA=0;//接收错误,重新开始
				else{                       //接收到空格后，接收到了回车
											 
				   USART_RX_STA|=0x8000;	//接收完成了
					 printf("%x",USART_RX_STA);
					} 
				 
				}
			else //还没收到0X0D
				{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
					{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收	  
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
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收	  
					}		 
			 }*/
     } 
#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntExit();  											 
#endif
} 
#endif	
/*********************接收数据缓存函数******************************/
void Usart2_Put_Buf(u8 a[],u8 _cnt) 
{
  u8 i;
  for(i=0;i<_cnt;i++) 
	{
	USART_SendData(USART1,a[i]);
	while (USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);	
  }
}

/*********************波形产生函数*************************/
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
