#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int count=0;
GPIO_InitTypeDef GPIO_InitStruct;

void GPIO_Config()
{
	RCC->CR |= 0x00030000; //HSEON and HSEONRDY enable
	while(!(RCC->CR & 0x00020000)); //HSEON Ready Flag Wait
	RCC->CR |= 0x00080000;	//CSS ENABLE
	RCC->PLLCFGR |= 0x00400000; // PLL'e HSE seçtik
	RCC->PLLCFGR |= 0x00000004; // PLLM = 4 oldu (4'e böldük.)
	RCC->PLLCFGR |= 0x00005A00; // PLLN = 168Hz oldu.
	RCC->PLLCFGR |= 0x00000000; // PLLP = 2 oldu.
	RCC->CFGR    |= 0x00000000; // AHB Presclaer = 1 oldu.
	RCC->CFGR    |= 0x00080000; // AHB2 = 2 oldu. ///80.000?
	RCC->CFGR    |= 0x00001400; // AHB1 = 4 oldu.
	RCC->CIR     |= 0x00080000; //HSERDY Flag Clear.
	RCC->CIR     |= 0x00800000; //CSS Flag Clear.

	RCC->AHB1ENR  	= 0X00000009; //GPIOA ve GPIOD aktif

	GPIOD->MODER  	= 0X55000000; //12,13,14,15. pins digital output
	GPIOD->OTYPER 	= 0x00000000; //12,13,14,15. pins push pull
	GPIOD->OSPEEDR  = 0xFF000000; //12,13,14,15. pins very high speed 100Mh
	GPIOD->PUPDR    = 0x00000000; //12,13,14,15. pins no pull

}

void delay(uint32_t time){
	while(time--);
}

int main(void)
{
	GPIO_Config();
	while (1)
	{
		if(GPIOA->IDR & 0X00000001)
		{
			while(GPIOA->IDR & 0X00000001);
			delay(1680000);

			count++;
		}
		if(count%2==0)
			{
			GPIOA->ODR = 0x00000000;
			}
		else
		{
			GPIOA->ODR = 0x0000F000;
		}
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
