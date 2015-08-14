#include "stm32f4xx_conf.h"
#include "main.h"
#include "stm32f4xx_it.h"
#include "led.h"
#include "usart.h"
#include "pwm.h"
#include "receive.h"
#include "w25q16.h"
#include "at25512.h"


int main()
{
	LED_GPIO_Config();
	USART2_DT_Config();
//	PwmInit();
//	Timer5Init();
//	Receive_Config();
//	SPI2_Init();
	
	GPIO_ResetBits(GPIOC, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);
	//USART2_DMA_SendData();
	USART_SendData(USART2, 'A');
	printf(" test \r\n");
	{
		uint16_t i;
		for (i=0; i<USART_SendBuffer_Size; i++)
		{
			USART_SendBuffer[i]= 0x11 ;
		}
	}
	USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);
}
