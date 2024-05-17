#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void RCC_Config()
{
	RCC->CR |= 0x00010000; //HSEON enable
	while(!(RCC->CR & 0x00020000)); //HSEON Ready Flag Wait
	RCC->CR |= 0x00080000;	//CSS ENABLE
	RCC->CR |= 0x01000000; 	//PLL ON
	RCC->PLLCFGR |= 0x00400000; // PLL'e HSE seçtik
	RCC->PLLCFGR |= 0x00000004; // PLLM = 4 oldu (4'e böldük.)
	RCC->PLLCFGR |= 0x00005A00; // PLLN = 168Hz oldu.
	RCC->PLLCFGR |= 0x00000000; // PLLP = 2 oldu.
	RCC->CFGR    |= 0x00000000; // AHB Presclaer = 1 oldu.
	RCC->CFGR    |= 0x00080000; // AHB2 = 2 oldu.
	RCC->CFGR    |= 0x00001400; // AHB1 = 4 oldu.
	RCC->CIR     |= 0x00080000; //HSERDY Flag Clear.
	RCC->CIR     |= 0x00800000; //CSS Flag Clear.
}

void GPIO_Config()
{
	RCC->AHB1ENR  	|= 1 <<3; //GPIOD ENABLE

	GPIOD->MODER  	|= 2 << 24 | 2 << 26 | 2 << 28 | 2 << 30; //PortD -> Pin 12 | 13 | 14 | 15 AF
	GPIOD->AFR[1]	|= 2 << 16 | 2 << 20 | 2 << 24 | 2 << 28; //PortD -> Pin 12 | 13 | 14 | 15 TIM4
}

void TIM_Config()
{
	RCC->APB1ENR	|= 1 << 2; //Tim4 clock enable

	TIM4->CR1	|= 0 << 4; //Timer counter mode upcounter
	TIM4->CR1	|= 0 << 5; // Timer center-aligned mode edge-aligned mode
	TIM4->CR1	|= 0 << 8; //Timer clock div1
	TIM4->CCMR1 |= 0 << 0 | 6 << 4 | 0 << 8 | 6 << 12;
	/*
	 * Capture/Compare 1 & 2 output selected
	 * Capture/Compare 1 & 2 PWM1 selected
	 */
	TIM4->CCMR2 |= 0 << 0 | 6 << 4 | 0 << 8 | 6 << 12;
	/*
	 * Capture/Compare 3 & 4 output selected
	 * Capture/Compare 3 & 4 PWM1 selected
	 */
	TIM4->CCER  |= 1 << 0 | 1 << 4 | 1 << 8 | 1 << 12;
	/*
	 * Capture/Compare 1 & 2 & 3 & 4 output enable
	 */
	TIM4->PSC = 8399;
	TIM4->ARR = 9999;
	TIM4->CCR1 = 2499;
	TIM4->CCR2 = 4999;
	TIM4->CCR3 = 7499;
	TIM4->CCR4 = 9999;
	TIM4->CR1 |= 1 << 0;
}
int main(void)
{
	RCC_Config();
	GPIO_Config();
	TIM_Config();
	while (1)
	{

	}
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size)
{
  /* TODO, implement your code here */
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void)
{
  /* TODO, implement your code here */
  return -1;
}
