#ifndef __PID_H
#define __PID_H
#include "stm32f10x.h"


extern int Kp;       //	����ϵ��  Kp
extern int Ki;      //	����ϵ��  Ki
extern int Kd;     // 	΢��ϵ��  Kd


int Regulation(int vSet, int v3);
u16 feed(u16 adcin);
#endif
