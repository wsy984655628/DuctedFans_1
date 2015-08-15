#ifndef __USART_H__
#define	__USART_H__

#include"stm32f4xx.h"
#include <stdio.h>
#include <string.h>

#define USART_SendBuffer_Size 10

extern uint8_t USART_SendBuffer[USART_SendBuffer_Size];
extern uint8_t USART_ReceiveBuffer[USART_SendBuffer_Size+100];

void USART2_DT_Config(void);
void USART2_DMA_SendData(void);
void USART2_DMA_ReceiveData(void);

void USART2_Print( const char *str );
int fputc(int ch, FILE *f);
int fgetc(FILE *f);

#endif

