#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;

void CLK_Config()
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
}

void GPIO_Config(){
	RCC->AHB1ENR  	= 0X00000009; //GPIOA ve GPIOD aktif

	GPIOD->MODER  	= 0X55000000; //12,13,14,15. pins digital output
	GPIOD->OTYPER 	= 0x00000000; //12,13,14,15. pins push pull
	GPIOD->OSPEEDR  = 0xFF000000; //12,13,14,15. pins very high speed 100Mh
	GPIOD->PUPDR    = 0x00000000; //12,13,14,15. pins no pull
}

void EXTI_Config()
{
	RCC->APB2ENR	= 0x00004000; //SYSCFG active (EXTI)

	SYSCFG->EXTICR[0] = 0X00000000;

	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);

	NVIC_SetPriority(EXTI0_IRQn, 0);
	NVIC_SetPriority(EXTI1_IRQn, 1);
	NVIC_SetPriority(EXTI2_IRQn, 2);
	EXTI->IMR 	= 0x00000007;
	EXTI->RTSR	= 0x00000007;

}

void delay(uint32_t time)
{
	while(time--);
}

void EXTI0_IRQHANDLER()
{
	if(EXTI->PR & 0x00000001)
	{
		GPIOD->ODR = 0x00001000;
		delay(33600000);

		EXTI->PR = 0x00000001;
	}
}
void EXTI1_IRQHANDLER()
{
	if(EXTI->PR & 0x00000002)
	{
		GPIOD->ODR = 0x00002000;
		delay(33600000);

		EXTI->PR = 0x00000002;
	}
}
void EXTI2_IRQHANDLER()
{
	if(EXTI->PR & 0x00000004)
	{
		GPIOD->ODR = 0x00004000;
		delay(33600000);

		EXTI->PR = 0x00000004;
	}
}
int main(void)
{
	CLK_Config();
	GPIO_Config();
	EXTI_Config();
	while (1)
	{
		GPIOD->ODR = 0x0000F000;
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
