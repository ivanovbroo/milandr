#include <MDR32F9Qx_timer.h>

extern unsigned int IRQCounter;

void TimerInit(unsigned int freq, unsigned int period);

void Timer1_IRQHandler(void);
