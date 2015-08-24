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
void MS5803_DataRegion_Config(void);

void MS5803_WriteCmd(unsigned char Cmd);
unsigned short	MS5803_ReadProm(unsigned char Cmd);

unsigned char MS5803_CRC_Calc(void);
void MS5803_PreReadPressure(void);
void MS5803_PreReadTemperature(void);
unsigned long MS5803_ReadPressure(void);
unsigned long MS5803_ReadTemperature(void);
unsigned long MS5803_Pressure_Filter(void);
unsigned long MS5803_Temperature_Filter(void);
void MS5803_GetData(void);

#define MS5803_Cmd_RESET		0x1E
#define	MS5803_Cmd_CONV_P256	0x40
#define MS5803_Cmd_CONV_P512	0x42
#define MS5803_Cmd_CONV_P1024	0x44
#define MS5803_Cmd_CONV_P2048	0x46
#define MS5803_Cmd_CONV_P4096	0x48
#define MS5803_Cmd_CONV_T256	0x50
#define MS5803_Cmd_CONV_T512	0x52
#define MS5803_Cmd_CONV_T1024	0x54
#define MS5803_Cmd_CONV_T2048	0x56
#define	MS5803_Cmd_CONV_T4096	0x58
#define MS5803_Cmd_READ_ADC		0x00
#define	MS5803_Cmd_READ_PROM0	0xA0
#define	MS5803_Cmd_READ_PROM1	0xA2
#define	MS5803_Cmd_READ_PROM2	0xA4
#define	MS5803_Cmd_READ_PROM3	0xA6
#define	MS5803_Cmd_READ_PROM4	0xA8
#define	MS5803_Cmd_READ_PROM5	0xAA
#define	MS5803_Cmd_READ_PROM6	0xAC
#define	MS5803_Cmd_READ_PROM7	0xAE

extern unsigned short	MS5803_Coefficient[8];
extern unsigned char 	MS5803_OriData_Cache[6];
extern unsigned long	MS5803_DataCache[2];

#define MS5803_Raise_CS() GPIO_SetBits(GPIOE,GPIO_Pin_3)
#define MS5803_Lower_CS() GPIO_ResetBits(GPIOE,GPIO_Pin_3)

#endif
