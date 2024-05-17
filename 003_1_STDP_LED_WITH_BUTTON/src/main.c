#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int counter = 0;

GPIO_InitTypeDef GPIO_InitStruct;

void GPIO_Config()
{
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	 //Bu structure GPIOA  (B) portuna atandi
	 GPIO_InitStruct.GPIO_Mode		 = GPIO_Mode_IN; //or just 0x00;
	 GPIO_InitStruct.GPIO_Pin		 = GPIO_Pin_1;
	 GPIO_InitStruct.GPIO_OType		 = GPIO_OType_PP;
	 GPIO_InitStruct.GPIO_PuPd		 = GPIO_PuPd_DOWN;
	 GPIO_InitStruct.GPIO_Speed		 = GPIO_Speed_100MHz;

	 GPIO_Init(GPIOB, &GPIO_InitStruct);

	 //Bu structure GPIOD  (D) portuna atandi
	 GPIO_InitStruct.GPIO_Mode		 = GPIO_Mode_OUT;
	 GPIO_InitStruct.GPIO_Pin		 = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	 GPIO_InitStruct.GPIO_OType		 = GPIO_OType_PP;
	 GPIO_InitStruct.GPIO_Speed		 = GPIO_Speed_100MHz;
	 GPIO_InitStruct.GPIO_PuPd		 = GPIO_PuPd_NOPULL;

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
	  if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)){
		  while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1));
		  delay(3360000); //200ms delay
		  counter++;
	  }
	  if(counter==1){
		  GPIO_SetBits(GPIOD, GPIO_Pin_12);
	  }
	  else if(counter==2){
		  GPIO_SetBits(GPIOD, GPIO_Pin_13);
	  }
	  else if(counter==3){
		  GPIO_SetBits(GPIOD, GPIO_Pin_14);
	  }
	  else if(counter==4){
		  GPIO_SetBits(GPIOD, GPIO_Pin_15);
	  }
	  else{
		  counter=0;
		  GPIO_SetBits(GPIOD, GPIO_Pin_12);
		  delay(16800000); //1sn delay
		  GPIO_SetBits(GPIOD, GPIO_Pin_13);
		  delay(16800000); //1sn delay
		  GPIO_SetBits(GPIOD, GPIO_Pin_14);
		  delay(16800000); //1sn delay
		  GPIO_SetBits(GPIOD, GPIO_Pin_15);
	  }
  }
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size)
{
  /* TODO, implement your code here */
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
