#include "timer.h"
#include "lcdtext.h"

void TimerInit(unsigned int freq, unsigned int time) {
	
	unsigned int prescaler = freq/1000;
	unsigned int period    = time*1000; 
	// �������� ���� ��������� � ����� ���������
	TIMER_CntInitTypeDef TIM1Init;
	
	// ����� ��������� ������� 1
	TIMER_DeInit(MDR_TIMER1);
  
  //���������� �������� ������� �� TIM1:
	MDR_RST_CLK->TIM_CLOCK = RST_CLK_TIM_CLOCK_TIM1_CLK_EN;
	
  // ��������� ������������
  //RST_CLK_PCLKcmd(RST_CLK_PCLK_TIMER1, ENABLE);
	
  // ���������� ��������� ���������� �� ���������
  TIMER_CntStructInit(&TIM1Init);
	
  // ��������� �������� �������� �������
  TIMER_BRGInit (MDR_TIMER1, TIMER_HCLKdiv1);
	
  // ������� ������������ �������� �������
  TIM1Init.TIMER_Prescaler = (uint16_t)prescaler;
	
  // ������� ������� ������������ �������
  TIM1Init.TIMER_Period = (uint16_t)period;
	
  // ������������� ����� ������� ����������� ����������
  TIMER_CntInit (MDR_TIMER1, &TIM1Init);
	
  // ��������� ����������
  NVIC_EnableIRQ (Timer1_IRQn);
	
  // ��������� ���������� ����������
  NVIC_SetPriority (Timer1_IRQn, 0);
	
  // ��������� ���������� ��� ��������� ���� �������� TIMER1
  TIMER_ITConfig(MDR_TIMER1, TIMER_STATUS_CNT_ZERO, ENABLE);
	
  // ������ �������
  TIMER_Cmd(MDR_TIMER1, ENABLE);
}

// ��������� ��������� ����������, ���������� ��������
void Timer1_IRQHandler(){
	// ���� ������ ������� � ����, ������� ��������� LED()
  // � �������� ���� ���������� 
  if (TIMER_GetITStatus(MDR_TIMER1, TIMER_STATUS_CNT_ZERO)){
		IRQCounter++;
		// ����� �� ���� ������������, ��� ��� unsigned int IRQCounter 4 �����, 2^32 - 1 = 4294967295
		if(IRQCounter == 4294967295)
			IRQCounter = 0;
		
		IQRFlag();
    TIMER_ClearITPendingBit(MDR_TIMER1, TIMER_STATUS_CNT_ZERO);
  }
}
