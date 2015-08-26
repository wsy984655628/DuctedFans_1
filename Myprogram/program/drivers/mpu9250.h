#ifndef __MPU9250_H__
#define __MPU9250_H__

#include "stm32f4xx.h"
#include "ms5803.h"

void MPU9250_Config(void);
void MPU9250_SPI_GPIO_Config(void);
void MPU9250_DataRegion_Config(void);
unsigned char MPU9250_WriteReg(unsigned char RegAddr , unsigned char Data);
void MPU9250_GetData(void);
void MPU9250_INT_GPIO_Config(void);


extern unsigned char MPU9250_OriData_Cache[14];
extern unsigned short MPU9250_Data_Cache[7];
#define MPU9250_SMPLRT_DIV		0x19
#define MPU9250_CONFIG			0x1A
#define MPU9250_GYRO_CONFIG		0x1B
#define MPU9250_ACCEL_CONFIG	0x1C
#define MPU9250_ACCEL2_CONFIG	0x1D
#define MPU9250_INT_PIN_CFG		0x37

#define MPU9250_USER_CTRL		0x6A
#define MPU9250_PWR_MGMT_1		0x6B
#define MPU9250_PWR_MGMT_2		0x6C



#define MPU9250_Raise_CS()		GPIO_SetBits(GPIOE , GPIO_Pin_4)
#define MPU9250_Lower_CS()		GPIO_ResetBits(GPIOE , GPIO_Pin_4)
#define MPU9250_Raise_INT()		GPIO_SetBits(GPIOC , GPIO_Pin_13)

#endif