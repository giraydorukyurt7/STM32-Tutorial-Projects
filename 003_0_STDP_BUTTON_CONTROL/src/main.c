#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;

void GPIO_Config(){
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	 //Bu structure GPIOA  (A) portuna atandi
	 GPIO_InitStruct.GPIO_Mode	 = GPIO_Mode_IN; //or just 0x00;
	 GPIO_InitStruct.GPIO_OType		 = GPIO_Pin_0;
	 GPIO_InitStruct.GPIO_Pin	 = GPIO_OType_PP;
	 GPIO_InitStruct.GPIO_PuPd		 = GPIO_PuPd_DOWN;
	 GPIO_InitStruct.GPIO_Speed		 = GPIO_Speed_100MHz;

	 GPIO_Init(GPIOA, &GPIO_InitStruct); //Usttekileri A portuna atar

	 //Bu structure GPIOD  (D) portuna atandi
	 GPIO_InitStruct.GPIO_Mode	 = GPIO_Mode_OUT;
	 GPIO_InitStruct.GPIO_Pin	 = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	 GPIO_InitStruct.GPIO_OType		 = GPIO_OType_PP;
	 GPIO_InitStruct.GPIO_Speed		 = GPIO_Speed_100MHz;

	 GPIO_Init(GPIOD, &GPIO_InitStruct); //Usttekileri D portuna atar
}

void delay(uint32_t time){
	while(time--);
}

int main(void)
{
	GPIO_Config();
  while (1)
  {
	  if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)){
		  while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0));
		  delay(16800000); //1sn delay
		  GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
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
