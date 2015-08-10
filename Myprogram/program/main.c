#include "stm32f4xx_conf.h"
#include "main.h"
#include "stm32f4xx_it.h"
#include "led.h"
#include "usart.h"
#include "pwm.h"
#include "receive.h"
#include "w25q16.h"
#include "at25512.h"


int main()
{
	LED_GPIO_Config();
	USART_DT_Config();
	PwmInit();
	Timer5Init();
	Receive_Config();
	SPI2_Init();
}
