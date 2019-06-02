#ifndef __PID_H
#define __PID_H
#include "stm32f10x.h"

extern u16 SetPoint; //	�趨ֵ  R
extern u16 Kp;       //	����ϵ��  Kp
extern u16 Ki;      //	����ϵ��  Ki
extern u16 Kd;     // 	΢��ϵ��  Kd
extern u16 LastError; //	ǰһ�����  ekt-t
extern u16 PrevError;  //	ǰ�������  ekt-2t

u16 Regulation(u16 vSet, u16 v3);
u16 feed(u16 adcin);
#endif
