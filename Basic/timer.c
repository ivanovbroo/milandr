#include "timer.h"
#include "lcdtext.h"

void TimerInit(unsigned int freq, unsigned int time) {
	
	unsigned int prescaler = freq/1000;
	unsigned int period    = time*1000; 
	// Указание типа структуры и имени структуры
	TIMER_CntInitTypeDef TIM1Init;
	
	// Сброс установок таймера 1
	TIMER_DeInit(MDR_TIMER1);
  
  //Разрешение тактовой частоты на TIM1:
	MDR_RST_CLK->TIM_CLOCK = RST_CLK_TIM_CLOCK_TIM1_CLK_EN;
	
  // Включение тактирования
  //RST_CLK_PCLKcmd(RST_CLK_PCLK_TIMER1, ENABLE);
	
  // Заполнение структуры значениями по умолчанию
  TIMER_CntStructInit(&TIM1Init);
	
  // Настройка делителя тактовой частоты
  TIMER_BRGInit (MDR_TIMER1, TIMER_HCLKdiv1);
	
  // Задание предделителя тактовой частоты
  TIM1Init.TIMER_Prescaler = (uint16_t)prescaler;
	
  // Задание периода срабатывания таймера
  TIM1Init.TIMER_Period = (uint16_t)period;
	
  // Инициализация порта таймера объявленной структурой
  TIMER_CntInit (MDR_TIMER1, &TIM1Init);
	
  // Включение прерываний
  NVIC_EnableIRQ (Timer1_IRQn);
	
  // Установка приоритета прерываний
  NVIC_SetPriority (Timer1_IRQn, 0);
	
  // Включение прерывания при равенстве нулю значения TIMER1
  TIMER_ITConfig(MDR_TIMER1, TIMER_STATUS_CNT_ZERO, ENABLE);
	
  // Запуск таймера
  TIMER_Cmd(MDR_TIMER1, ENABLE);
}

// Процедура обработки прерывания, вызванного таймером
void Timer1_IRQHandler(){
	// Если таймер сброшен в ноль, вызвать процедуру LED()
  // и сбросить флаг прерывания 
  if (TIMER_GetITStatus(MDR_TIMER1, TIMER_STATUS_CNT_ZERO)){
		IRQCounter++;
		// чтобы не было переполнения, так как unsigned int IRQCounter 4 байта, 2^32 - 1 = 4294967295
		if(IRQCounter == 4294967295)
			IRQCounter = 0;
		
		IQRFlag();
    TIMER_ClearITPendingBit(MDR_TIMER1, TIMER_STATUS_CNT_ZERO);
  }
}
