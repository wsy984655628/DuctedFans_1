#ifndef __PWM_H__
#define __PWM_H__

#include "stm32f4xx.h"

#define SYS_TIME (TIM5->CNT)

extern uint16_t ch;
void PwmInit(void);
void Timer5Init(void);

#endif
