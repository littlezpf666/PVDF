#ifndef __PID_H
#define __PID_H
#include "stm32f10x.h"

extern u16 SetPoint; //	设定值  R
extern u16 Kp;       //	比例系数  Kp
extern u16 Ki;      //	积分系数  Ki
extern u16 Kd;     // 	微分系数  Kd
extern u16 LastError; //	前一拍误差  ekt-t
extern u16 PrevError;  //	前两拍误差  ekt-2t

u16 Regulation(u16 vSet, u16 v3);
u16 feed(u16 adcin);
#endif
