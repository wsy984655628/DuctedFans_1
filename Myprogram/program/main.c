#include "stm32f4xx_conf.h"
#include "main.h"
#include "stm32f4xx_it.h"
#include "stdio.h"
#include "string.h"
#include "led.h"
#include "usart.h"
#include "pwm.h"
#include "receive.h"
#include "w25q16.h"
#include "at25512.h"
#include "ms5803.h"
#include "mpu9250.h"
#include "struct_all.h"
#include "control.h"
#include "MavlinkProtocol.h"

uint32_t MainTntCounter=0;

static void Delay(__IO u32 nCount); 
int main()
{
	System_Config();
	
	while(1);
}

void System_Config(void)
{
	LED_GPIO_Config();
	USART2_DT_Config();
	SPI2_Init();
	AT25512_SPI_GPIO_Config();	
	PwmInit();
	Timer5Init();
	Timer3Init();
	Receive_Config();
	SPI4_Config();
	MS5803_Config();
	MPU9250_Config();
	mavlink_int();	
}

void MainInterrupt(void) //100Hz
{
	MainInt_Time.EntranceT = SYS_TIME;
	MainTntCounter++;
	
	GetReceiverInfo();
	
	MPU9250_GetData();
	EstimateAttitude();
	
	//MS5803_GetData();
	//EstimateHeight();
	
	PositionControl();
	
	HeightControl();
	
	Pidcontrol();
	
	DealCommunication();
	
	MainInt_Time.ExitT = SYS_TIME;
	MainInt_Time.gap = MainInt_Time.ExitT - MainInt_Time.EntranceT;
	
	
	
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
}

void DealCommunication(void);
{
	//mavlink_message();
}

static void Delay(__IO uint32_t nCount)	 
{
	for(; nCount != 0; nCount--);
}
