#ifndef __MS5803_H__
#define __MS5803_H__

#include "stm32f4xx.h"

void SPI4_Config(void);
void SPI4_GPIO_Config(void);
void SPI4_Mode_Config(void);
unsigned char SPI4_SendByte(unsigned char data);
void SPI4_Delay(__IO long DelayTime);
void MS5803_Config(void);
void MS5803_SPI_GPIO_Config(void);

#define MS5803_Raise_CS() GPIO_SetBits(GPIOE,GPIO_Pin_3)
#define MS5803_Lower_CS() GPIO_ResetBits(GPIOE,GPIO_Pin_3)

#endif
