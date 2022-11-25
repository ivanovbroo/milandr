#include "timer.h"
#include "settingsports.h"
#include "lcdtext.h"
#include "systick.h"
#include "led.h"


// Структура параметров
struct Parameters {
	unsigned int CPUFreq;
	unsigned int IRQPeriod;
	unsigned int UARTSpeed;
};

int flag = 0;
unsigned int IRQCounter = 0;

 int main() { 	
	 const char name[]  = "Иванов Н. Н.";
	 const char group[] = "РЛ1-119";
 	 
	 struct Parameters param;	 
	 param.CPUFreq   = 16000000;
	 param.IRQPeriod = 4;
	 param.UARTSpeed = 19200;
	 
	 setCPUFreq(param.CPUFreq);
	 settingsPorts();
		 
	 TimerInit(param.CPUFreq, param.IRQPeriod);
	 
	 UART_ini(param.UARTSpeed);
	 
	 lcdInit();
	 
	 char stroka[6];
	 sprintf(stroka, "16 МГц");

	 lcdTxt(0, name, group, param.CPUFreq, param.IRQPeriod, param.UARTSpeed, 0);
				
   while (1) {
		 
		 if(flag == 0) {
			
			 for(int i = 0; i < 8; i++) {
					UART_SendData(MDR_UART2, stroka[i]);
			 }
			 
		   LCD_PUTS_UNINT(90, 40, IRQCounter);
			 flashingDiode();
			 
			  // ставим двойку, чтобы срабатывало один раз counter == 0 в цикле, так как counter меняется по прерыванию
			  flag = 2;
		 }
		 if(flag == 1) {
			 for(int i = 0; i < 8; i++) {
					UART_SendData(MDR_UART2, stroka[i]);
			 }
				
			  LCD_PUTS_UNINT(90, 40, IRQCounter);
			  flashingDiode();
			   
			  // ставим тройку, чтобы срабатывало один раз flag == 1 в цикле, так как flag меняется по прерыванию
			  flag = 3;
		 }		 
   } 
 }
