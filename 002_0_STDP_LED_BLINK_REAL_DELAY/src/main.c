#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void Delay(uint32_t time)
{
	// 1/168.000.000  1 saniye elde etmek için 168.000.000/8 = 21.000.000
	while(time--); //while dongusu 8 cycle yapar
	/*
	 * while(time>0) //4 cycle while + 4cycle time>0
	 * {
	 * 		time--; //+ 4 cycle time--;
	 * } //toplamda 12 cycle
	 *  // yani bu durumda 168.000.000/12 = 14.000.000 1 saniye eder.
	 *
	 */

}

int main(void)
{
	GPIO_Config();
	while(1)
  {
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
		Delay(21000000); // 168.000.000 yerine 21.000.000 yazarsak tam olarak 1 sn geçmis olur
		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		Delay(21000000); // periyot 2 saniye oldu
  }
}


/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
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
