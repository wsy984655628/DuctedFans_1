#include "mpu9250.h"

unsigned char MPU9250_OriData_Cache[14];
unsigned short MPU9250_Data_Cache[7];

void MPU9250_Config(void)
{
	MPU9250_DataRegion_Config();
	MPU9250_SPI_GPIO_Config();
	MPU9250_INT_GPIO_Config();
	MPU9250_WriteReg(MPU9250_PWR_MGMT_1 , 0x80);
	SPI4_Delay(2200000); // 300ms
	MPU9250_WriteReg(MPU9250_USER_CTRL , 0x10);
	MPU9250_WriteReg(MPU9250_PWR_MGMT_2 , 0x00);
	MPU9250_WriteReg(MPU9250_SMPLRT_DIV , 0x03);
	MPU9250_WriteReg(MPU9250_CONFIG , 0x00);
	MPU9250_WriteReg(MPU9250_GYRO_CONFIG , 0x08);
	MPU9250_WriteReg(MPU9250_ACCEL_CONFIG , 0x08);
	MPU9250_WriteReg(MPU9250_ACCEL2_CONFIG , 0x08);
	MPU9250_WriteReg(MPU9250_INT_PIN_CFG , 0x80); // FSYNC is active high and int is active low 
}

//PE4-SPI4_NSS1
void MPU9250_SPI_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
	
	MPU9250_Raise_CS();	
}

//PC13-INT
void MPU9250_INT_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	MPU9250_Raise_INT();		
}
void MPU9250_DataRegion_Config(void)
{
	int i;
	for(i=0;i<14;i++)
		MPU9250_OriData_Cache[i] = 0;
	for(i=0;i<7;i++)
		MPU9250_Data_Cache[i] = 0;
}
unsigned char MPU9250_WriteReg(unsigned char RegAddr , unsigned char Data)
{
	MPU9250_Lower_CS();
	SPI4_SendByte(RegAddr);
	SPI4_SendByte(Data);
	MPU9250_Raise_CS();
	
	return 0;
}
void MPU9250_GetData(void)
{
	int i;
	MPU9250_Lower_CS();
	SPI4_SendByte(0xBB);	//where can i find the 0xbb
	for(i=0;i<14;i++)
		MPU9250_OriData_Cache[i] = SPI4_SendByte(0x00);
	MPU9250_Raise_CS();
	
	MPU9250_Data_Cache[0] = MPU9250_OriData_Cache[0]<<8 | MPU9250_OriData_Cache[1];
	MPU9250_Data_Cache[1] = MPU9250_OriData_Cache[2]<<8 | MPU9250_OriData_Cache[3];
	MPU9250_Data_Cache[2] = MPU9250_OriData_Cache[4]<<8 | MPU9250_OriData_Cache[5];
	MPU9250_Data_Cache[3] = MPU9250_OriData_Cache[8]<<8 | MPU9250_OriData_Cache[9];
	MPU9250_Data_Cache[4] = MPU9250_OriData_Cache[10]<<8 | MPU9250_OriData_Cache[11];
	MPU9250_Data_Cache[5] = MPU9250_OriData_Cache[12]<<8 | MPU9250_OriData_Cache[13];
	MPU9250_Data_Cache[6] = MPU9250_OriData_Cache[6]<<8 | MPU9250_OriData_Cache[7];
	
	MPU9250_Filter();
}

void MPU9250_Filter(void)
{
	
}

void EstimateAttitude(void)
{
	
}

