#ifndef __PID_H
#define __PID_H
#include "stm32f10x.h"


extern int Kp;       //	比例系数  Kp
extern int Ki;      //	积分系数  Ki
extern int Kd;     // 	微分系数  Kd


int Regulation(int vSet, int v3);
u16 feed(u16 adcin);
#endif
