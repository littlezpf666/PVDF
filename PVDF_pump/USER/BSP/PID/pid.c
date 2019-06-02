#include "pid.h"               //����ʽPID

u16 SetPoint=0; //	�趨ֵ  R
u16 Kp=0.84;       //	����ϵ��  Kp
u16 Ki=0;      //	����ϵ��  Ki
u16 Kd=0;     // 	΢��ϵ��  Kd
u16 LastError=0; //	ǰһ�����  ekt-t
u16 PrevError=0;  //	ǰ�������  ekt-2t

u16 Regulation( u16 vSet, u16 vref)  //    Vset ����ֵ R   Vref ����ֵ

{
	u16 vOut;						// PID Response (Output) PID���
	u16 iError;          //��ǰ���
 
	SetPoint = vSet;			// Set PID Setpoint ������PID�趨ֵ ����ֵR
	iError = SetPoint - vref;   //�趨ֵ-��ǰ����ֵ ��ǰ���

	vOut = Kp*(iError-LastError)+Ki*iError + Kd *(iError-2*LastError+PrevError);              

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

