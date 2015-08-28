#include "ms5803.h"

unsigned short	MS5803_Coefficient[8];
unsigned char 	MS5803_OriData_Cache[6];
unsigned long	MS5803_DataCache[2];

void SPI4_Config(void)
{
	SPI4_GPIO_Config();
	SPI4_Mode_Config();
}

//PE2-SPI4_SCK PE5-SPI4_MISO  PE6-SPI4_MOSI
void SPI4_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource2, GPIO_AF_SPI4);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_SPI4);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_SPI4);
}

void SPI4_Mode_Config(void)
{
	SPI_InitTypeDef	SPI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI4,ENABLE);
	
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	
	SPI_Init( SPI4, &SPI_InitStructure);
	SPI_Cmd( SPI4 , ENABLE);
}

unsigned char SPI4_SendByte(unsigned char data)
{
	while(SPI_I2S_GetFlagStatus( SPI4 , SPI_I2S_FLAG_TXE) == RESET);
	SPI_SendData(SPI4 , data);
	while(SPI_I2S_GetFlagStatus( SPI4 , SPI_I2S_FLAG_RXNE) == RESET);
	return SPI_ReceiveData( SPI4 );
}
void SPI4_Delay(__IO long DelayTime)
{
	while(DelayTime--);
}

void MS5803_Config(void)
{
	MS5803_DataRegion_Config();
	MS5803_SPI_GPIO_Config();
	MS5803_WriteCmd(MS5803_Cmd_RESET);
	SPI4_Delay(22000);					//3ms
	
	MS5803_Coefficient[0] = MS5803_ReadProm(MS5803_Cmd_READ_PROM0);
	MS5803_Coefficient[1] = MS5803_ReadProm(MS5803_Cmd_READ_PROM1);
	MS5803_Coefficient[2] = MS5803_ReadProm(MS5803_Cmd_READ_PROM2);
	MS5803_Coefficient[3] = MS5803_ReadProm(MS5803_Cmd_READ_PROM3);
	MS5803_Coefficient[4] = MS5803_ReadProm(MS5803_Cmd_READ_PROM4);
	MS5803_Coefficient[5] = MS5803_ReadProm(MS5803_Cmd_READ_PROM5);
	MS5803_Coefficient[6] = MS5803_ReadProm(MS5803_Cmd_READ_PROM6);
	MS5803_Coefficient[7] = MS5803_ReadProm(MS5803_Cmd_READ_PROM7);
	
	//MS5803_CRC_Calc();
}

//PE3-SPI4_NSS2
void MS5803_SPI_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
	
	MS5803_Raise_CS();
}

void MS5803_DataRegion_Config(void)
{
	int i=0;
	for(i=0;i<6;i++)
		MS5803_OriData_Cache[i] = 0;
	for(i=0;i<2;i++)
		MS5803_DataCache[i] = 0;
	for(i=0;i<8;i++)
		MS5803_Coefficient[i] = 0;
}

void MS5803_WriteCmd(unsigned char Cmd)
{
	MS5803_Lower_CS();
	SPI4_SendByte(Cmd);
	SPI4_Delay(100);
	MS5803_Raise_CS();
}

unsigned short	MS5803_ReadProm(unsigned char Cmd)
{
	unsigned char H8,L8;
	MS5803_Lower_CS();
	MS5803_WriteCmd(Cmd);
	H8 = SPI4_SendByte(0x00);
	L8 = SPI4_SendByte(0x00);
	return(H8<<8 | L8);
	//MS5803_Raise_CS();
}

void MS5803_PreReadPressure(void)
{
	MS5803_Lower_CS();
	MS5803_WriteCmd(MS5803_Cmd_CONV_P256);
	SPI4_Delay(100);
	MS5803_Raise_CS();
}

unsigned long MS5803_ReadPressure(void)
{
	unsigned long PressureData = 0;
	MS5803_Lower_CS();
	MS5803_WriteCmd(MS5803_Cmd_READ_ADC);
	MS5803_OriData_Cache[0] = SPI4_SendByte(0x00);
	MS5803_OriData_Cache[1] = SPI4_SendByte(0x00);
	MS5803_OriData_Cache[2] = SPI4_SendByte(0x00);
	SPI4_Delay(100);
	MS5803_Raise_CS();
	
	MS5803_DataCache[0] = MS5803_OriData_Cache[0]<<16 | MS5803_OriData_Cache[1]<<8 | MS5803_OriData_Cache[2];
	PressureData = MS5803_Pressure_Filter();
	return PressureData;
}

void MS5803_PreReadTemperature(void)
{
	MS5803_Lower_CS();
	MS5803_WriteCmd(MS5803_Cmd_CONV_T256);
	SPI4_Delay(100);
	MS5803_Raise_CS();
}

unsigned long MS5803_ReadTemperature(void)
{
	unsigned long TemperatureData = 0;
	MS5803_Lower_CS();
	MS5803_WriteCmd(MS5803_Cmd_READ_ADC);
	MS5803_OriData_Cache[3] = SPI4_SendByte(0x00);
	MS5803_OriData_Cache[4] = SPI4_SendByte(0x00);
	MS5803_OriData_Cache[5] = SPI4_SendByte(0x00);
	SPI4_Delay(100);
	MS5803_Raise_CS();
	
	MS5803_DataCache[1] = MS5803_OriData_Cache[3]<<16 | MS5803_OriData_Cache[4]<<8 | MS5803_OriData_Cache[5];
	TemperatureData = MS5803_Temperature_Filter();
	return TemperatureData;
}

unsigned long MS5803_Pressure_Filter(void)
{
	return MS5803_DataCache[0];
}

unsigned long MS5803_Temperature_Filter(void)
{
	return MS5803_DataCache[1];
}

unsigned char MS5803_CRC_Calc(void)
{
	
}

void MS5803_GetData(void)
{
	int64_t dT,TEMP,OFF,SENS,P;
	int64_t T2,TEMP2,OFF2,SENS2,P2;
	
	dT = MS5803_DataCache[1] - ((MS5803_Coefficient[5])<<8);
	TEMP = 2000 + ((dT*MS5803_Coefficient[6])>>23);
	
	OFF = (MS5803_Coefficient[2]<<16) + ((MS5803_Coefficient[4]*dT)>>7);
	SENS = (MS5803_Coefficient[1]<<15) + ((MS5803_Coefficient[3]*dT)>>8);
	
	if(TEMP<2000)
	{
		T2 = dT*dT>>31;
		OFF2 = 3*(TEMP-2000)*(TEMP-2000);
		SENS2 = 7*(TEMP-2000)*(TEMP-2000)>>3;
		if(TEMP<-1500)
			SENS2 = SENS2 + ((TEMP+1500)*(TEMP+1500)<<1);
	}
	else
	{
		T2 = 0;
		OFF2 = 0;
		SENS2 = 0;
		
		if(TEMP>=4500)
			SENS2 = SENS2 - ((TEMP-4500)*(TEMP-4500)>>3);
	}
	TEMP = TEMP - T2;
	OFF = OFF - OFF2;
	SENS = SENS - SENS2;
	
	P = ((MS5803_DataCache[0]*SENS>>21) - OFF)>>15;
	
}

void EstimateHeight(void)
{
	
}