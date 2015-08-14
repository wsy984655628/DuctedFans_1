#ifndef __USART_H__
#define	__USART_H__

#include"stm32f4xx.h"
#include <stdio.h>

#define USART_SendBuffer_Size 500

extern uint8_t USART_SendBuffer[USART_SendBuffer_Size];
extern uint8_t USART_ReceiveBuffer[USART_SendBuffer_Size+100];

void USART2_DT_Config(void);
void USART2_DMA_SendData(void);
void USART2_DMA_ReceiveData(void);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);

#endif

