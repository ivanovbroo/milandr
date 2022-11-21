#include "lcd.h" 
#include "text.h"
#include "font_defs.h"

extern int flag;

void lcdTxt(int flag, const char* name, const char* group, 
						unsigned int CPUFreq, unsigned int IRQPeriod, 
						unsigned int UARTSpeed, unsigned int IRQCounter);

void lcdInit(void);

void IQRFlag(void);