#include "led.h"
#include "settingsports.h"

void flashingDiode(void) {
	
	static uint8_t i = 0;
	
	switch(i++) {
	 case 0:
		 PORT_SetBits(MDR_PORTC, PORT_Pin_0);
	   PORT_SetBits(MDR_PORTC, PORT_Pin_1);
	   break;
	 case 1:
		 PORT_ResetBits(MDR_PORTC, PORT_Pin_0);
	   PORT_ResetBits(MDR_PORTC, PORT_Pin_1);
	   i = 0;
	   break;
	}
}

