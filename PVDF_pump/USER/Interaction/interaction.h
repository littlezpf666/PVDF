#ifndef __INTER_H
#define __INTER_H

#include "sys.h"
#include "lcd.h"
#include "led.h"
#include "usart.h"
#include "touch.h"
#include "GUI.h"

char touch_process(void);
char key_process(void);
void scr0_content();
void scr1_content();

#endif