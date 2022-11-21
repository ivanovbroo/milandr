#include "settingsports.h"

void setCPUFreq(unsigned int freq) {
	 unsigned int multiplication_factor = (freq/8000000)-1;
	 //Регистр управления тактовой частотой периферийных блоков
   MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;
	
	 // Включение HSE
	 MDR_RST_CLK->HS_CONTROL |= RST_CLK_HS_CONTROL_HSE_ON;
	
	 // Ожидание, когда запуститься генератор
	 while(!(MDR_RST_CLK->CLOCK_STATUS & RST_CLK_CLOCK_STATUS_HSE_RDY));
	
	 // Настройка мультиплексора, 0010 - без деления на два
	 MDR_RST_CLK->CPU_CLOCK |= 0x2;
	
	 // Переключение с HSI на CPU_C3
	 MDR_RST_CLK->CPU_CLOCK |= 0x1<<RST_CLK_CPU_CLOCK_HCLK_SEL_Pos;
	
	 // Коэф умножения
	 MDR_RST_CLK->PLL_CONTROL |= multiplication_factor<<RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Pos;
	
	 // Включение PLL 
	 MDR_RST_CLK->PLL_CONTROL |= RST_CLK_PLL_CONTROL_PLL_CPU_ON;
	 
	 // Ожидание, когда запуститься CPU PLL
	 while(!(MDR_RST_CLK->CLOCK_STATUS & RST_CLK_CLOCK_STATUS_PLL_CPU_RDY));
	 
	 //Задержка памяти программ при чтении в циклах
	 //MDR_EEPROM->CMD |= 0<<EEPROM_CMD_DELAY_Pos;
	
	 // Переключение с HSI на CPU_C2
	 MDR_RST_CLK->CPU_CLOCK |= 0x1<<RST_CLK_CPU_CLOCK_CPU_C2_SEL_Pos;
}

void settingsPorts(void) {
	
	PORT_InitTypeDef GPIOInitStruct;
	
	PORT_StructInit(&GPIOInitStruct);

  GPIOInitStruct.PORT_Pin = (PORT_Pin_0|PORT_Pin_1);
  GPIOInitStruct.PORT_OE = PORT_OE_OUT;
  GPIOInitStruct.PORT_SPEED = PORT_SPEED_SLOW;
  GPIOInitStruct.PORT_MODE = PORT_MODE_DIGITAL;

  PORT_Init(MDR_PORTC, &GPIOInitStruct);
}

void UART_ini(unsigned int UARTSpeed) {
	
	//RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTF, ENABLE);
	
	PORT_InitTypeDef GPIO_ini_1;
	PORT_InitTypeDef GPIO_ini_2;
	UART_InitTypeDef uart_user_ini;
	
	PORT_StructInit(&GPIO_ini_1);
	
	GPIO_ini_1.PORT_Pin       = PORT_Pin_1;
	GPIO_ini_1.PORT_OE        = PORT_OE_OUT;
	//GPIO_ini.PORT_PULL_UP   = PORT_PULL_UP_OFF;
	//GPIO_ini.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
	//GPIO_ini.PORT_PD_SHM    = PORT_PD_SHM_OFF;
	//GPIO_ini.PORT_PD        = PORT_PD_DRIVER;
	//GPIO_ini.PORT_GFEN      = PORT_GFEN_OFF;
	GPIO_ini_1.PORT_FUNC      = PORT_FUNC_OVERRID;
	GPIO_ini_1.PORT_SPEED     = PORT_SPEED_MAXFAST;
	GPIO_ini_1.PORT_MODE      = PORT_MODE_DIGITAL;
	
	PORT_Init(MDR_PORTF, &GPIO_ini_1);
	
	PORT_StructInit(&GPIO_ini_2);
	
	GPIO_ini_2.PORT_Pin       = PORT_Pin_0;
	GPIO_ini_2.PORT_OE        = PORT_OE_IN;
	//GPIO_ini.PORT_PULL_UP   = PORT_PULL_UP_OFF;
	//GPIO_ini.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
	//GPIO_ini.PORT_PD_SHM    = PORT_PD_SHM_OFF;
	//GPIO_ini.PORT_PD        = PORT_PD_DRIVER;
	//GPIO_ini.PORT_GFEN      = PORT_GFEN_OFF;
	GPIO_ini_2.PORT_FUNC      = PORT_FUNC_OVERRID;
	GPIO_ini_2.PORT_SPEED     = PORT_SPEED_MAXFAST;
	GPIO_ini_2.PORT_MODE      = PORT_MODE_DIGITAL;
	
	PORT_Init(MDR_PORTF, &GPIO_ini_2);
	 
	RST_CLK_PCLKcmd(RST_CLK_PCLK_UART2, ENABLE);
	
	UART_BRGInit(MDR_UART2, UART_HCLKdiv1);
	
	uart_user_ini.UART_BaudRate            = UARTSpeed;
	uart_user_ini.UART_FIFOMode            = UART_FIFO_OFF;
	uart_user_ini.UART_HardwareFlowControl = UART_HardwareFlowControl_TXE|UART_HardwareFlowControl_RXE;
	uart_user_ini.UART_Parity              = UART_Parity_No; 
	uart_user_ini.UART_StopBits            = UART_StopBits1;
	uart_user_ini.UART_WordLength          = UART_WordLength8b;
	
	UART_Init(MDR_UART2, &uart_user_ini);

	UART_Cmd(MDR_UART2, ENABLE);
}
 
