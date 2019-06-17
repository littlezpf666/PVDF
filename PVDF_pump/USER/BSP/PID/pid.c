#include "pid.h"               //����ʽPID

int Kp=4;       //	����ϵ��  Kp
int Ki;      //	����ϵ��  Ki
int Kd;     // 	΢��ϵ��  Kd

int Regulation( int vSet, int vref)  //    Vset ����ֵ R   Vref ����ֵ

{
	int SetPoint; //	�趨ֵ  R
	int LastError; //	ǰһ�����  ekt-t
	int PrevError;  //	ǰ�������  ekt-2t
	int vOut;						// PID Response (Output) PID���
	int iError;          //��ǰ���
 
	SetPoint = vSet;			// Set PID Setpoint ������PID�趨ֵ ����ֵR
	iError = SetPoint - vref;   //�趨ֵ-��ǰ����ֵ ��ǰ���

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

