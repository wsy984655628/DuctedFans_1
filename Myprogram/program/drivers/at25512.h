#ifndef __AT25512_H__
#define __AT25512_H__

#include "stm32f4xx.h"

#define AT25512_WREN	0x06
#define AT25512_WRDI	0x04
#define AT25512_RDSR	0x05
#define AT25512_WRSR	0x01
#define AT25512_READ	0x03
#define AT25512_WRITE	0x02

void SPI2_Init(void);
void AT25512_SPI_GPIO_Config(void);

unsigned char SPI2_SendByte(unsigned char data);

int AT25512_IsBusy(void);
void AT25512_ReadData(unsigned short Addr , unsigned char *data , unsigned char Len);
void AT25512_PageWrite(unsigned short Addr , const unsigned char *data , unsigned char Len);

#define AT25512_Lower_CS()			GPIO_ResetBits(GPIOD,GPIO_Pin_10)
#define AT25512_Raise_CS()			GPIO_SetBits(GPIOD,GPIO_Pin_10)

#define AT25512_Read()				  SPI2_SendByte(0x00)

#endif
