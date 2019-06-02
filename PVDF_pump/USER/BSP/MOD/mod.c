#include "mod.h"


double x_1=0; 
double x_2=0;       
double u_1=0; 
double u_2=0;       
double y_1=0;  
double y_2=0; 

double MOD_func(double Xin)   //PVDFÄæÄ£ÐÍº¯Êý
{
	double u;
	double y;
	
	u = 1.94*u_1 - 0.9409*u_2 - Xin + 1.8878*x_1 - 0.8934*x_2;
	
	if((u - u_1) > 0)
		y = y_1 - 0.0003*(0.0 - 0.00027*u_1*u_1*u_1 - y_1 - 0.667*u_1)*(u_1 - u) - 0.005*(u - u_1);	
	else
		y = y_1 - 0.0003*(0.0 - 0.00027*u_1*u_1*u_1 - y_1 - 0.667*u_1)*(u - u_1) - 0.005*(u - u_1);	
	
	x_2 = x_1;
	x_1 = Xin;
	u_2 = u_1;
	u_1 = u;
	y_2 = y_1;
	y_1 = y;
	return y;	
}
//float MOD_functiong(MOD *sptr, float Yin)
//{
//	float y1,y2;
//	float w1,w2;
//	
//}
