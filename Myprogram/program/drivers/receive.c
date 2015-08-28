#include "receive.h"

uint8_t LineFalling[5]={0};
uint32_t	LineFallingTime[5]={0};
uint32_t	LineRisingTime[5]={0};
uint16_t	LineHT[5]={0};
uint16_t	RC[5] = {1000,1000,1000,1000,1000};

void Receive_Config(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	EXTI_InitTypeDef	EXTI_InitStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource7);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource8);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource9);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource10);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line7 | EXTI_Line8 | EXTI_Line9 | EXTI_Line10;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
}

void GetReceiverInfo(void)
{
	int i;
	if (LineHT[0] > 1000)
	{
		for(i=0;i<5;i++)
		RC[i] = LineHT[i];
	}
}