#ifndef __USART_H__
#define	__USART_H__

#include"stm32f4xx.h"
#include <stdio.h>

#define USART_SendBuffer_Size 500

extern uint8_t USART_SendBuffer[USART_SendBuffer_Size];
extern uint8_t USART_ReceiveBuffer[USART_SendBuffer_Size+100];

void USART_DT_Config(void);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);

#endif

