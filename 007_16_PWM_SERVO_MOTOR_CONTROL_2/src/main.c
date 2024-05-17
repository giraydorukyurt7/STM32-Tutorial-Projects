#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;
TIM_TimeBaseInitTypeDef TIM_InitStruct;
TIM_OCInitTypeDef TIMOC_InitStruct;

uint32_t delay_count;

void SysTick_Handler(void)
{
	delay_count--;
}

void Delay_ms(uint32_t time)
{
	delay_count = time;
	while(time);
}

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);

	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType	= GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_13;
	GPIO_InitStruct.GPIO_PuPd	= GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed	= GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void TIM_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	TIM_InitStruct.TIM_ClockDivision		= TIM_CKD_DIV1;
	TIM_InitStruct.TIM_CounterMode			= TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Period				= 19999;
	TIM_InitStruct.TIM_Prescaler			= 83;
	TIM_InitStruct.TIM_RepetitionCounter	= 0;

	TIM_TimeBaseInit(TIM4, &TIM_InitStruct);

	TIM_Cmd(TIM4, ENABLE);

	TIMOC_InitStruct.TIM_OCMode			= TIM_OCMode_PWM1;
	TIMOC_InitStruct.TIM_OutputState	= ENABLE;
	TIMOC_InitStruct.TIM_OCPolarity		= TIM_OCPolarity_High;

	SysTick_Config(SystemCoreClock/1000 ); //1ms de 1 kesmeye git
}

int main(void)
{
	GPIO_Config();
	TIM_Config();
	while (1)
	{
		for(int i = 500; i<= 2000; i++)
		{
			TIMOC_InitStruct.TIM_Pulse = 500;
			TIM_OC2Init(TIM4, &TIMOC_InitStruct);
			TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
			Delay_ms(2);
		}
		for(int i = 2000; i>= 500; i--)
		{
			TIMOC_InitStruct.TIM_Pulse = 500;
			TIM_OC2Init(TIM4, &TIMOC_InitStruct);
			TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
			Delay_ms(2);
		}
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
