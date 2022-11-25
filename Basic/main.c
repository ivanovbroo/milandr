#include "timer.h"
#include "settingsports.h"
#include "lcdtext.h"
#include "systick.h"
#include "led.h"


// ��������� ����������
struct Parameters {
	unsigned int CPUFreq;
	unsigned int IRQPeriod;
	unsigned int UARTSpeed;
};

int flag = 0;
unsigned int IRQCounter = 0;

 int main() { 	
	 const char name[]  = "������ �. �.";
	 const char group[] = "��1-119";
 	 
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
	 sprintf(stroka, "16 ���");

	 lcdTxt(0, name, group, param.CPUFreq, param.IRQPeriod, param.UARTSpeed, 0);
				
   while (1) {
		 
		 if(flag == 0) {
			
			 for(int i = 0; i < 8; i++) {
					UART_SendData(MDR_UART2, stroka[i]);
			 }
			 
		   LCD_PUTS_UNINT(90, 40, IRQCounter);
			 flashingDiode();
			 
			  // ������ ������, ����� ����������� ���� ��� counter == 0 � �����, ��� ��� counter �������� �� ����������
			  flag = 2;
		 }
		 if(flag == 1) {
			 for(int i = 0; i < 8; i++) {
					UART_SendData(MDR_UART2, stroka[i]);
			 }
				
			  LCD_PUTS_UNINT(90, 40, IRQCounter);
			  flashingDiode();
			   
			  // ������ ������, ����� ����������� ���� ��� flag == 1 � �����, ��� ��� flag �������� �� ����������
			  flag = 3;
		 }		 
   } 
 }
