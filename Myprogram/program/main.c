#include "stm32f4xx_conf.h"
#include "main.h"
#include "stm32f4xx_it.h"
#include "led.h"
#include "usart.h"
#include "pwm.h"
#include "receive.h"
#include "w25q16.h"
#include "at25512.h"
#include "mavlink.h"


static void Delay(__IO u32 nCount); 
int main()
{
	LED_GPIO_Config();
	USART2_DT_Config();
	SPI2_Init();
	AT25512_SPI_GPIO_Config();	
	PwmInit();
	Timer5Init();
	Receive_Config();
	Timer3Init();
	
	while(1);
}

void MainInterrupt(void)
{
//	uint8_t test[2]={0x05,0x09};
//	uint8_t test2[2]={0x01,0x08};
		
//	for(;;)
//		{
//			AT25512_PageWrite(0x00000,test,4);
//			LED1(OFF);
//			Delay(0xFFFFF);
//			AT25512_ReadData(0x00000,test2,4);
//			USART_SendBuffer[0]=test2[1];
//			USART2_DMA_SendData();
//			LED1(OFF);
//			Delay(0xFFFFF);
//		}
	Get_Mavlink_Info();
	Send_Mavlink_Info();
}

static void Delay(__IO uint32_t nCount)	 
{
	for(; nCount != 0; nCount--);
}
