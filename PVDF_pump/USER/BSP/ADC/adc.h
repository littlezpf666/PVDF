#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
////////////////////////////////////////////////////////////////////////////////// 
							  
////////////////////////////////////////////////////////////////////////////////// 

extern double x_1; 
extern double x_2;       
extern double u_1; 
extern double u_2;       
extern double y_1;  
extern double y_2; 
 

void Adc_Init(void);
u16  Get_Adc(u8 ch); 
u16 Get_Adc_Average(u8 ch,u8 times); 
 


#endif 
