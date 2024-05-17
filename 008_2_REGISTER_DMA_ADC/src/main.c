#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint32_t adc;
uint32_t adc1[2];

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

	ADC1->CR1		|= 1 << 8;//ADC scan mode enable
	ADC1->CR1		|= 0 << 24; //Resolotion 12 bit
	ADC1->CR2		|= 1 << 0;  //ADC Enable
	ADC1->CR2		|= 1 << 1;	//Continuous conversion mode
	ADC1->CR2		|= 1 << 8;	//DMA mode Enable
	ADC1->CR2		|= 1 << 9;	//DDS Enable
	ADC1->CR2		|= 1 << 10; //EOC Enable
	ADC1->CR2		|= 1 << 30; //Start conversion
	ADC1->SQR1		|= 0 << 20;
	ADC1->SQR3		|= 0 << 0;
}

void DMA_Config()
{
	RCC->AHB1ENR |= 1 << 22; //DMA2 Clock Enable  //1 yaz sola dogru 22 birim otele.

	while((DMA2_Stream4->CR & 0x00000001) == 1); //wait for stream4 to be 0

	DMA2_Stream4->PAR 	|= (uint32_t) &ADC1->DR;
	DMA2_Stream4->M0AR 	|= (uint32_t) &adc1;
	DMA2_Stream4->NDTR 	|= 1;		//single channel
	DMA2_Stream4->CR 	|= 0 << 6; 	//peripheral to memory
	DMA2_Stream4->CR 	|= 1 << 8; 	//circular mode enable
	//DMA2_Stream4->CR 	|= 0 << 9; 	//peripheral address fixed
	DMA2_Stream4->CR 	|= 1 << 10;	//memory address incremented
	DMA2_Stream4->CR 	|= 2 << 11; //peripheral data size 32 bit(word) // 11.bite 10 yaz(00 01 10 11)
	DMA2_Stream4->CR 	|= 2 << 13; //memory data size 32 bit(word)
	DMA2_Stream4->CR 	|= 3 << 16; //priority level is very high
	DMA2_Stream4->CR 	|= 0 << 25; //channel 0 selected
	DMA2_Stream4->FCR 	|= 0 << 2;
	DMA2_Stream4->CR	|= 1 << 0; //stream 4 enable
}

int main(void)
{
	RCC_Config();
	GPIO_Config();
	ADC_Config();
	DMA_Config();
	ADC1->CR2	|= ADC_CR2_SWSTART;
	while (1)
	{
		adc = adc1[0];
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
