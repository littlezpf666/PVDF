#include "interaction.h"

extern char DETECT_TOUCH,DETECT_KEY,DETECT_USART_COMM;
char feedback_control=0;
char sel_state=0,scr_state=0,wave_pattern=0,amplitude_level=0,isBoot=0;;
extern uint16_t ADC_ConvertedValue[2];
extern uint8_t mode_status,stop_status;
extern uint16_t DDS_step,DDSM;
char time_interval=3;
extern u16 vol_per;
extern const unsigned char gImage_arrow_up[3200];
extern const unsigned char gImage_arrow_down[3200];
extern const unsigned char gImage_switch[3200];
extern const unsigned char gImage_mode[3200];
extern const unsigned char gImage_shool[3200]; 
char uart_comm[5],Init[5],tcp_Port[5],udp_Port[5];

void scr0_content()
{
	  LCD_ShowChar(300,0,GREEN,WHITE,'%',16,0);//电量百分比
		Gui_StrCenter(0,64,GREEN,WHITE,"上海师范大学",32,1);//居中显示
		Show_Str(150,100,LIGHTGREEN,WHITE,"精控实验室",24,1);
			 
		Gui_Drawbmp16(10,60,gImage_shool);
}
void scr1_content()
{
		Gui_Drawbmp16(20,170,gImage_arrow_up);
		Gui_Drawbmp16(100,170,gImage_arrow_down);
		Gui_Drawbmp16(180,170,gImage_switch);
		Gui_Drawbmp16(260,170,gImage_mode);
	  //Gui_Drawbmp16(180,0,gImage_wifi);
		Show_Str(40,40,RED,WHITE,"强度",16,1);
		Show_Str(100,40,GREEN,WHITE,"频率",16,1);
		LCD_DrawRectangle(170, 60, 300, 140);
		Show_Str(180,70,RED,WHITE,"吸乳",16,1);
		Show_Str(260,70,GREEN,WHITE,"开奶",16,1);
		Show_Str(180,110,GREEN,WHITE,"催乳",16,1);
		Show_Str(260,110,GREEN,WHITE,"按摩",16,1);
		LCD_ShowChar(300,0,GREEN,WHITE,'%',16,0);//电量百分比
}
char touch_process(void)
{
	char status_buffer[250]="";
		if(DETECT_TOUCH==1||DETECT_USART_COMM==1)
		{
			if(scr_state==0&&DETECT_TOUCH==1)
			{
	      printf("\r\n坐标x:%d,坐标y:%d",tp_dev.x,tp_dev.y);
				scr_state=1;
				LCD_Clear(WHITE);
				scr1_content();
				DETECT_KEY=0;
			}
			if(scr_state==1)
			{
				
				if(KEY_ADD||uart_comm[0]=='1')
				{

					if(sel_state==0)
					{
//							if(++amplitude_level>5)
//						{
//							amplitude_level=5;	
//						}
						if(amplitude_level<4) amplitude_level++; 
					}
					else
					{
						if(DDSM<3) DDSM++;
					}
				}

				if(KEY_SUB||uart_comm[1]=='1')
				{
					if(sel_state==0)
					{
						if(amplitude_level>0) --amplitude_level;
				  }
					else
					{
						if(DDSM>1)DDSM--;
					}
				}
				
				if(KEY_SWITCH||uart_comm[2]=='1')
				{
					if(sel_state==1){
						Show_Str(40,40,RED,WHITE,"强度",16,1);
					  Show_Str(100,40,GREEN,WHITE,"频率",16,1);
						sel_state=0;
					}
					else {
						Show_Str(100,40,RED,WHITE,"频率",16,1);
						Show_Str(40,40,GREEN,WHITE,"强度",16,1);
						sel_state=0;
					sel_state++;}
				}

        if(KEY_MODE||uart_comm[3]=='1')
				{	
						if(wave_pattern==3)wave_pattern=0;
					  else wave_pattern++;
					  switch (wave_pattern)
						{
							case 0:
								Show_Str(180,70,RED,WHITE,"吸乳",16,1);
								Show_Str(260,110,GREEN,WHITE,"按摩",16,1);
							break;
							case 1:
								Show_Str(260,70,RED,WHITE,"开奶",16,1);
								Show_Str(180,70,GREEN,WHITE,"吸乳",16,1);
							break;
							case 2:
								Show_Str(180,110,RED,WHITE,"催乳",16,1);
								Show_Str(260,70,GREEN,WHITE,"开奶",16,1);
							break;
							case 3:
								Show_Str(260,110,RED,WHITE,"按摩",16,1);
								Show_Str(180,110,GREEN,WHITE,"催乳",16,1);
							break;	
						}
				}
				/*if((DETECT_USART_COMM==1)&&(uart_comm[3]-48<5))
        {
					wave_pattern=uart_comm[3]-48;
				}	*/
				if(uart_comm[4]=='1')
				{
					if(isBoot)
					{
						amplitude_level=0;
						LCD_ShowNum(40,80,amplitude_level+1,1,48);
						TIM_SetCompare2(TIM3, 0);
						TIM_SetCompare3(TIM3, 0);
						GAS=0;
						TIM_ITConfig(TIM3,TIM_IT_Update,DISABLE);
					}
					else
					{
						TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);			
					}
					isBoot=~isBoot;
				}

				if(DETECT_USART_COMM==1)
				{
					/*sprintf(status_buffer,
					"{\n\"MsgId\":5,\n\"MSgObj\":{\n\"DeviceId\":\"001\",\n\"Name\":\"pvdf\",\n\"IsBoot\":%d,\n\"Strength\":%d,\n\"Frequency\":%d,\n\"Mode\":%d,\n\"PowerBattery\":%d,\n\"NetworkMode\":%s,\n\"TcpPort\":%s,\n\"UdpPort\":%s\n},\n\"MsgStatus\":\"True\"\n}"
					,isBoot,amplitude_level,DDSM,wave_pattern,vol_per,Init,tcp_Port,udp_Port);*/
					sprintf(status_buffer,
					"{\"MsgId\":5,\"MsgObj\":{\"DeviceId\":\"001\",\"Name\":\"pvdf\",\"IsBoot\":\"%s\",\"Strength\":%d,\"Frequency\":%d,\"Select\":\"%s\",\"Mode\":%d,\"PowerBattery\":%d,\"NetworkMode\":%s,\"TcpPort\":%s,\"UdpPort\":%s},\"MsgStatus\":\"True\"}"
					,isBoot==255?"True":"False",amplitude_level,DDSM,sel_state==0?"Strength":"Frequency",wave_pattern,vol_per,Init,tcp_Port,udp_Port);
					
				  printf("%s",status_buffer);
					memset(status_buffer,0,250);
					DETECT_USART_COMM=0;
				}
				
        
				LCD_ShowNum(40,80,amplitude_level+1,1,48);
				LCD_ShowNum(100,80,DDSM,1,48);
        if(DETECT_TOUCH==1)	
				{
					//LCD_ShowNum(160,70,wave_pattern,1,48);
					DETECT_TOUCH=0;
				}					
				
				
			}
		}
		return 0;
}
char key_process(void)
{
	
	if(DETECT_KEY==1)
	{
    if(scr_state==1)
		{
				if(isBoot)
			{
				amplitude_level=0;
				LCD_ShowNum(40,80,amplitude_level+1,1,48);
				TIM_SetCompare2(TIM3, 0);
				TIM_SetCompare3(TIM3, 0);
				GAS=0;
				
				feedback_control=0;
				TIM_ITConfig(TIM3,TIM_IT_Update,DISABLE);
			}
			else
			{
				feedback_control=1;
				TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);			
			}
			isBoot=~isBoot;
			}		
		DETECT_KEY=0;
	}
		
	return 0;
}