#include "lcdtext.h"

void lcdTxt(int counter, const char* name, const char* group, 
						unsigned int CPUFreq, unsigned int IRQPeriod, 
						unsigned int UARTSpeed, unsigned int IRQCounter) {	
	
			LCD_PUTS(0, 0, "ФИО: ");
	    LCD_PUTS(30, 0, name);
	 
	    LCD_PUTS(0, 8, "Группа: ");
	    LCD_PUTS(48, 8, group);
	 
	    LCD_PUTS(0, 16, "Частота МК: ");
	    LCD_PUTS_UNINT(72, 16, CPUFreq/1000000);
	    LCD_PUTS(90, 32, "МГц");
	 
	    LCD_PUTS(0, 24, "Частота прерыв: ");
	    LCD_PUTS_UNINT(96, 24, IRQPeriod);
	    LCD_PUTS(108, 24, "сек");
			
			LCD_PUTS(0, 32, "Скор UART: ");
		  LCD_PUTS_UNINT(66, 32, UARTSpeed);
		  LCD_PUTS(100, 32, " б/с");
		
			LCD_PUTS(0, 40, "Кол-во прерыв: ");
		  LCD_PUTS_UNINT(90, 40, IRQCounter);
}
						
void lcdInit() {
	LCD_INIT();
	CurrentFont = &Font_6x8; 
	CurrentMethod = MET_AND;	 
	LCD_CLS();
}

void IQRFlag() {
	if(flag == 2)
		flag = 1;
	if(flag == 3)
		flag = 0;
}
						