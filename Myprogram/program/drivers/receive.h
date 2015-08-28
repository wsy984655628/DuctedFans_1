#ifndef __RECEIVE_H__
#define __RECEIVE_H__

#include "stm32f4xx.h"

extern	uint8_t LineFalling[5];
extern	uint32_t	LineFallingTime[5];
extern	uint32_t	LineRisingTime[5];
extern	uint16_t	LineHT[5];
extern  uint16_t	RC[5];

void Receive_Config(void);
void GetReceiverInfo(void);

#endif
