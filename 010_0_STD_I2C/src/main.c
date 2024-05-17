#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;
I2C_InitTypeDef I2C_InitStruct;

uint8_t m_address = 0x4E; //cihazin katalogunda bulunur bu bilgi.

int i = 0;

void delay(uint32_t time)
{
	while(time--);
}

void GPIO_Config()
{
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	 //Bu structure GPIOA  (A) portuna atandi
	 GPIO_InitStruct.GPIO_Mode		 = GPIO_Mode_IN;
	 GPIO_InitStruct.GPIO_Pin		 = GPIO_Pin_0;
	 GPIO_InitStruct.GPIO_OType		 = GPIO_OType_PP;
	 GPIO_InitStruct.GPIO_PuPd		 = GPIO_PuPd_DOWN; ////
	 GPIO_InitStruct.GPIO_Speed		 = GPIO_Speed_100MHz;

	 GPIO_Init(GPIOA, &GPIO_InitStruct);

	 GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);	//SCL Pin
	 GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);	//SDA Pin

	 //Bu structure GPIOA  (B) portuna atandi
	 GPIO_InitStruct.GPIO_Mode		 = GPIO_Mode_AF;
	 GPIO_InitStruct.GPIO_Pin		 = GPIO_Pin_6 | GPIO_Pin_7;
	 GPIO_InitStruct.GPIO_OType		 = GPIO_OType_PP;
	 GPIO_InitStruct.GPIO_PuPd		 = GPIO_PuPd_NOPULL;
	 GPIO_InitStruct.GPIO_Speed		 = GPIO_Speed_100MHz;

	 GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void I2C_Write(uint8_t address, uint8_t data)
{
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)); //I2C bayragi uygun olana kadar bekle

	I2C_GenerateSTART(I2C1, ENABLE);

	//master yap
	while(!(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)));

	I2C_Send7bitAddress(I2C1, address, I2C_Direction_Transmitter);

	while(!(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)));

	I2C_SendData(I2C1, data);

	I2C_GenerateSTOP(I2C1, ENABLE);
}

void I2C_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

	I2C_InitStruct.I2C_Ack					= ENABLE;
	I2C_InitStruct.I2C_AcknowledgedAddress	= I2C_AcknowledgedAddress_7bit;
	I2C_InitStruct.I2C_ClockSpeed			= 400000;
	I2C_InitStruct.I2C_DutyCycle			= I2C_DutyCycle_2;
	I2C_InitStruct.I2C_Mode					= I2C_Mode_I2C;
	I2C_InitStruct.I2C_OwnAddress1			= 0x00;

	I2C_Init(I2C1, &I2C_InitStruct);

	I2C_Cmd(I2C1, ENABLE);
}

int main(void)
{
	GPIO_Config();
	I2C_Config();
	while (1)
	{
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
		{
			while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0));
			i++;
			delay(160000);
		}

		switch(i)
		{
		case 0:
			I2C_Write(m_address, 0x00);
			break;
		case 1:
			I2C_Write(m_address, 0x01); //alette ogreniliyor bunlar
			break;
		case 2:
			I2C_Write(m_address, 0x03);
			break;
		case 3:
			I2C_Write(m_address, 0x04);
			break;
		case 4:
			I2C_Write(m_address, 0x08);
			break;
		case 5:
			I2C_Write(m_address, 0x10);
			break;
		case 6:
			I2C_Write(m_address, 0x20);
			break;
		case 7:
			I2C_Write(m_address, 0x40);
			break;
		case 8:
			I2C_Write(m_address, 0x80);
			break;
		default:
			i = 0;
			break;
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
