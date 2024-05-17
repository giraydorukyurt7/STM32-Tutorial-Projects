#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

char Rx_Buff[100];
int i = 0;

void RCC_Config()
{
	RCC->CR |= 0x00010000; 			//HSEON enable
	while(!(RCC->CR & 0x00020000)); //HSEON Ready Flag Wait
	RCC->CR |= 0x00080000;			//CSS ENABLE
	RCC->CR |= 0x01000000;			//PLL ON
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
	RCC->AHB1ENR  	|= 0X00000002; //GPIOB clock enable

	GPIOB->MODER  	|= (2 << 20) | (2 << 22); //PB10 and PB11 AF
	GPIOB->AFR[1]	|= (7 << 8)  | (7 << 12); //PB10 and PB11 AF7 [USART3]
}

void USART_Config()
{
	RCC->APB1ENR	|= 1 << 18; //USART3 Clock Enable

	USART3->BRR	= 0x1112;		//BaudRate 9600
	USART3->CR1 |= 1 << 2;		//Rx enable
	USART3->CR1 |= 1 << 3;		//Tx enable
	USART3->CR1 |= 1 << 5;		//RXNE interrupt enable
	USART3->CR1 |= 0 << 10;		//No parity
	USART3->CR1 |= 0 << 12;		//Word length 8 bit
	USART3->CR2 |= 0 << 12;		//Stop bit 1
	USART3->CR1 |= 1 << 13;		//USART enable
}

void NVIC_Config()
{
	NVIC->ISER[1] |= 1 << 7; //0x0000080;
}

void USART3_IRQHandler()
{
	volatile int Str;

	Str = USART3->SR;
	Rx_Buff[i] = USART3->DR;
	i++;
}

void Send_Char(char message)
{
	while(!(USART3->SR & 0x00000080));	//TXE Buffer dolu ise bekle
	USART3->DR = message;
}

void Send_Message(char *Str)
{
	while(*Str)
	{
		Send_Char(*Str);
		Str++;
	}
}

int main(void)
{
	RCC_Config();
	GPIO_Config();
	USART_Config();
	NVIC_Config();
	while (1)
	{
		Send_Message("Hello World \n");
		for(int i = 0; i<1000000;i++);
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
