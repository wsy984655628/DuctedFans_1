#include "pwm.h"

uint16_t ch[6]={0,1500,1500,1500,1500,1000};
 

void PwmInit(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure;
	TIM_OCInitTypeDef		TIM_OCInitSTructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,	ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	//PA0-CH1 PA1-CH2 PA2-CH3 PA3-CH4
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,	&GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOA,	GPIO_PinSource0,	GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOA,	GPIO_PinSource1,	GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOA,	GPIO_PinSource2,	GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOA,	GPIO_PinSource3,	GPIO_AF_TIM2);
	
	//100Hz
	TIM_TimeBaseStructure.TIM_ClockDivision	= 0;
	TIM_TimeBaseStructure.TIM_CounterMode	=	TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = 5000;
	TIM_TimeBaseStructure.TIM_Prescaler	= 45;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	//TIM2:Channel 1
	TIM_OCInitSTructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitSTructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitSTructure.TIM_OutputState= TIM_OutputState_Enable;
	TIM_OCInitSTructure.TIM_Pulse = ch[1];
	TIM_OC1Init(TIM2, &TIM_OCInitSTructure);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	//TIM2:Channel 2
	TIM_OCInitSTructure.TIM_OutputState= TIM_OutputState_Enable;
	TIM_OCInitSTructure.TIM_Pulse = ch[2];	
	TIM_OC2Init(TIM2, &TIM_OCInitSTructure);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	//TIM2:Channel 3
	TIM_OCInitSTructure.TIM_OutputState= TIM_OutputState_Enable;
	TIM_OCInitSTructure.TIM_Pulse = ch[3];	
	TIM_OC3Init(TIM2, &TIM_OCInitSTructure);
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	//TIM2:Channel 4
	TIM_OCInitSTructure.TIM_OutputState= TIM_OutputState_Enable;
	TIM_OCInitSTructure.TIM_Pulse = ch[4];	
	TIM_OC4Init(TIM2, &TIM_OCInitSTructure);
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
	
	//PD12-CH5
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,	ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,	&GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOD,	GPIO_PinSource12,	GPIO_AF_TIM4);
	
	TIM_TimeBaseStructure.TIM_ClockDivision	= 0;
	TIM_TimeBaseStructure.TIM_CounterMode	=	TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = 5000;
	TIM_TimeBaseStructure.TIM_Prescaler	= 90;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	//TIM4:Channel 1
	TIM_OCInitSTructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitSTructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitSTructure.TIM_OutputState= TIM_OutputState_Enable;
	TIM_OCInitSTructure.TIM_Pulse = ch[5];
	TIM_OC1Init(TIM4, &TIM_OCInitSTructure);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM4, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
}
void Timer5Init(void)
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = 0xffffffff;
	TIM_TimeBaseStructure.TIM_Prescaler = 90;
	
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	TIM_ITConfig(TIM5,TIM_IT_Update,DISABLE);
	TIM_Cmd(TIM5, ENABLE);
}

// main interrupt timmer
void Timer3Init(void)
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = 10000;
	TIM_TimeBaseStructure.TIM_Prescaler = 90;
	
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM5, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStructure);		
}

