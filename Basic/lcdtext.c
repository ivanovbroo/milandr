#include "lcdtext.h"

void lcdTxt(int counter, const char* name, const char* group, 
						unsigned int CPUFreq, unsigned int IRQPeriod, 
						unsigned int UARTSpeed, unsigned int IRQCounter) {	
							
	switch(counter) {		
		case 0:	
		  LCD_PUTS(0, 0, "ФИО: ");
	    LCD_PUTS(30, 0, name);
	 
	    LCD_PUTS(0, 16, "Группа: ");
	    LCD_PUTS(48, 16, group);
	 
	    LCD_PUTS(0, 32, "Частота МК: ");
	    LCD_PUTS_UNINT(72, 32, CPUFreq/1000000);
	    LCD_PUTS(90, 32, "МГц");
	 
	    LCD_PUTS(0, 48, "Частота прерыв: ");
	    LCD_PUTS_UNINT(96, 48, IRQPeriod);
	    LCD_PUTS(108, 48, "сек");
	    break;
		
	  case 1:
		  LCD_PUTS(0, 0, "Скор UART: ");
		  LCD_PUTS_UNINT(66, 0, UARTSpeed);
		  LCD_PUTS(100, 0, "б/с");
		
			LCD_PUTS(0, 16, "Кол-во прерыв: ");
		  LCD_PUTS_UNINT(90, 16, IRQCounter);
		
	    break;	
	}	
						
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
						