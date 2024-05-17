#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void CLK_Config()
{
	RCC->CR |= 0x00010000; //HSEON enable
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

int main(void)
{
	CLK_Config();
  while (1)
  {

  }
}


void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
