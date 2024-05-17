#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int i = 0;

void delay(uint32_t time)
{
	while(time--);
}

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

void DAC1_Config()
{
	RCC->AHB1ENR	|= 0x00000001;
	RCC->APB1ENR 	|= 0x20000000;

	DAC->CR			|= 0x00000001; // DAC channel 1 enable.
	DAC->SWTRIGR	|= 0x00000000; // DAC channel 1 software trigger disable.
	DAC->DHR12R1	|= 0x00000000; // DAC channel 1 12-bit right-aligned data.

}

int main(void)
{
	RCC_Config();
	DAC1_Config();

	while (1)
	{
		for(i=0;i <4096;i++)
		{
			DAC->DHR12R1 |= i;
			delay(16800); //10ms
		}
		i = 0;
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
