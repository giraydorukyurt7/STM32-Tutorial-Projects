#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint8_t adc_value;

void RCC_Config()
{
	RCC->CR |= 0x00010000; 			//HSEON enable
	while(!(RCC->CR & 0x00020000)); //HSEON Ready Flag Wait
	RCC->CR |= 0x00080000;			//CSS ENABLE
	RCC->PLLCFGR |= 0x00400000; // PLL'e HSE seçtik
	RCC->PLLCFGR |= 0x00000004; // PLLM = 4 oldu (4'e böldük.)
	RCC->PLLCFGR |= 0x00005A00; // PLLN = 168Hz oldu.
	RCC->PLLCFGR |= 0x00000000; // PLLP = 2 oldu.
	RCC->CFGR    |= 0x00000000; // AHB Presclaer = 1 oldu.
	RCC->CFGR    |= 0x00080000; // AHB2 = 2 oldu. ///80.000?
	RCC->CFGR    |= 0x00001400; // AHB1 = 4 oldu.
	RCC->CIR     |= 0x00080000; //HSERDY Flag Clear.
	RCC->CIR     |= 0x00800000; //CSS Flag Clear.
}

void GPIO_Config()
{
	RCC->AHB1ENR  	|= 0X00000001; //GPIOA clock enable

	GPIOD->MODER  	|= 0X55000000; //12,13,14,15. pins digital output
	GPIOD->OTYPER 	|= 0x00000000; //12,13,14,15. pins push pull
	GPIOD->OSPEEDR  |= 0xFF000000; //12,13,14,15. pins very high speed 100Mh
	GPIOD->PUPDR    |= 0x00000000; //12,13,14,15. pins no pull
}

void ADC_Config()
{
	RCC->APB1ENR	|= 0x00000100; //adc1 clock enable

	ADC1->CR1		|= 0x02000000; //Resolotion 8 bits
	ADC1->CR2		|= 0x00000001; //ADC Enable
	ADC1->SMPR2		|= 0x00000003; //56 Cycles
	ADC->CCR		|= 0x00010000; //Div 4
}

uint8_t Read_ADC()
{
	uint8_t value;

	ADC1->CR2	|= 0x40000000;

	while(!(ADC1->SR & 0x00000002));

	value = ADC1->DR;

	return value;
}

int main(void)
{
	RCC_Config();
	GPIO_Config();
	ADC_Config();
	while (1)
	{
		adc_value = Read_ADC();
	}
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
