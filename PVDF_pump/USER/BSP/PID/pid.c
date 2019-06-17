#include "pid.h"               //增量式PID

int Kp=4;       //	比例系数  Kp
int Ki;      //	积分系数  Ki
int Kd;     // 	微分系数  Kd

int Regulation( int vSet, int vref)  //    Vset 期望值 R   Vref 输入值

{
	int SetPoint; //	设定值  R
	int LastError; //	前一拍误差  ekt-t
	int PrevError;  //	前两拍误差  ekt-2t
	int vOut;						// PID Response (Output) PID输出
	int iError;          //当前误差
 
	SetPoint = vSet;			// Set PID Setpoint ；输入PID设定值 期望值R
	iError = SetPoint - vref;   //设定值-当前输入值 当前误差

	//vOut = Kp*(iError-LastError)+Ki*iError + Kd *(iError-2*LastError+PrevError);              
  vOut = Kp*iError;
	PrevError = LastError;
	LastError = iError;	

	return vOut;    
}


u16 feed(u16 adcin)
{
	u16 out ;
	if(adcin <2500)
		out = 28000;
	else if(adcin > 2500  && adcin <2600)
		out = 14000;
	else if(adcin > 2600 && adcin <2700)
		out = 10000;
	else if(adcin > 2700  && adcin <2800)
		out = 9800;
	else if(adcin > 2800 && adcin <2900)
		out = 9600;
	else if(adcin > 2900 && adcin <3000)
		out = 9000;
	else if(adcin > 3000 && adcin <3100)
		out = 8000;
	else if(adcin > 3100 && adcin <3200)
		out = 7000;
	else if(adcin >3200)
		out = 6000;
	return out;
}

