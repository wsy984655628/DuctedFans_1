#include "at25512.h"


//PB13-SPI2_SCK  PB14-SPI_MISO	PB15-SPI2_MOSI
void SPI2_Init(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	SPI_InitTypeDef   SPI_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource13, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15, GPIO_AF_SPI2);
	
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	
	SPI_Init(SPI2, &SPI_InitStructure);
	SPI_Cmd(SPI2, ENABLE);
	
}

unsigned char SPI2_SendByte(unsigned char data)
{
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
	SPI_SendData(SPI2, data);
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
	return SPI_ReceiveData(SPI2);
}

//PD10-SPI2_NSS2
void AT25512_SPI_GPIO_Config(void)
{
	
	GPIO_InitTypeDef	GPIO_InitStructure;	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOD, &GPIO_InitStructure);	
	AT25512_Raise_CS();
}

int AT25512_IsBusy(void)
{
	unsigned status=0;
	AT25512_Lower_CS();
	SPI2_SendByte(AT25512_RDSR);
	status = AT25512_Read();
	AT25512_Raise_CS();
	if(status & 0x01)
		return 1;
	else
		return 0;
}

void AT25512_ReadData(unsigned short Addr , unsigned char *data , unsigned char Len)
{
	int i=0;
	AT25512_Lower_CS();
	SPI2_SendByte(AT25512_READ);
	SPI2_SendByte(Addr>>8);
	SPI2_SendByte(Addr&0x0F);
	for(i=0;i<Len;i++)
		data[i]=AT25512_Read();
	AT25512_Raise_CS();
}
void AT25512_PageWrite(unsigned short Addr , const unsigned char *data , unsigned char Len)
{
	
}
