#include "usart.h"

uint8_t USART_SendBuffer[USART_SendBuffer_Size]={0x11,0x22,0x33,0x44};
uint8_t USART_ReceiveBuffer[USART_SendBuffer_Size+100];

void USART2_DT_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;
	DMA_InitTypeDef	DMA_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);
	
	//configure the GPIOD_Pin5 and GPIO_Pin6
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	//configure the usart2
	USART_InitStructure.USART_BaudRate=115200;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART2, &USART_InitStructure);
	
	USART_Cmd(USART2,ENABLE);
	
	//configure the tx dma
	DMA_InitStructure.DMA_BufferSize=USART_SendBuffer_Size;
	DMA_InitStructure.DMA_Channel=DMA_Channel_4;
	DMA_InitStructure.DMA_DIR=DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_FIFOMode=DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold=DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_Memory0BaseAddr=(uint32_t)USART_SendBuffer;
	DMA_InitStructure.DMA_MemoryBurst=DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode=DMA_Mode_Normal;
	DMA_InitStructure.DMA_PeripheralBaseAddr=(uint32_t)&(USART2->DR);
	DMA_InitStructure.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_Priority=DMA_Priority_High;
	
	DMA_Init(DMA1_Stream6,&DMA_InitStructure);
	
	//configure the rx dma
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralToMemory;	
	DMA_InitStructure.DMA_Memory0BaseAddr=(uint32_t)USART_ReceiveBuffer;
	
	DMA_Init(DMA1_Stream5,&DMA_InitStructure);
	
	//DMA command
	USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);
	USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);
	
	//enable the USART2 Interrupt
	USART_ITConfig(USART2,USART_IT_TC,ENABLE);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	
	//enable the tx DMA interrupt
	DMA_ITConfig(DMA1_Stream6,DMA_IT_TC,ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel=DMA1_Stream6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);	
	
	//enable the rx DMA interrupt
	DMA_ITConfig(DMA1_Stream5,DMA_IT_TC,ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel=DMA1_Stream5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);		
	
	//enable the rx dma
	DMA_Cmd(DMA1_Stream5,ENABLE);
}

void USART2_DMA_SendData(uint8_t *pAddr,uint32_t len)
{
	DMA_Cmd(DMA1_Stream6,DISABLE);
	
	DMA_DeInit(DMA1_Stream6);
	DMA_InitTypeDef	DMA_InitStructure;
	DMA_InitStructure.DMA_BufferSize=len;
	DMA_InitStructure.DMA_Memory0BaseAddr=(uint32_t)pAddr;
	DMA_Init(DMA1_Stream6, &DMA_InitStructure);
	DMA_ITConfig(DMA1_Stream6 , DMA_IT_TC,ENABLE);
	
	DMA_Cmd(DMA1_Stream6,ENABLE);
}

void USART2_DMA_ReceiveData(void)
{
	DMA_Cmd(DMA1_Stream5,ENABLE);
}

void USART2_Print( const char *str )
{
    int Len = strlen(str);
    int i=0;
    for(i=0;i<Len;i++)
    {
        while( RESET == USART_GetFlagStatus(USART2,USART_FLAG_TXE));
        USART_SendData(USART2,(uint16_t)str[i]);
    }
}

