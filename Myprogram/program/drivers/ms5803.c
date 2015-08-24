#include "ms5803.h"

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
	MS5803_SPI_GPIO_Config();
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

