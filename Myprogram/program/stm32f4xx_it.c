/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.3.0
  * @date    13-November-2013
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "receive.h"
#include "pwm.h"


/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line7) == SET)
	{
		EXTI_ClearITPendingBit(EXTI_Line7);
		if(LineFalling[1])
		{
			LineFalling[1]=0;
			LineFallingTime[1] = SYS_TIME;
			LineHT[1] = LineFallingTime[1]-LineRisingTime[1];
			EXTI->RTSR |= (uint32_t)EXTI_Line7;
			EXTI->FTSR &=~ (uint32_t)EXTI_Line7;
		}
		else
		{
			LineFalling[1]=1;
			LineRisingTime[1] = SYS_TIME;
			EXTI->RTSR &=~ (uint32_t)EXTI_Line7;
			EXTI->FTSR |= (uint32_t)EXTI_Line7;
		}
	}
	if(EXTI_GetITStatus(EXTI_Line8) == SET)
	{
		EXTI_ClearITPendingBit(EXTI_Line8);
		if(LineFalling[2])
		{
			LineFalling[2]=0;
			LineFallingTime[2] = SYS_TIME;
			LineHT[2] = LineFallingTime[2]-LineRisingTime[2];
			EXTI->RTSR |= (uint32_t)EXTI_Line8;
			EXTI->FTSR &=~ (uint32_t)EXTI_Line8;
		}
		else
		{
			LineFalling[2]=1;
			LineRisingTime[2] = SYS_TIME;
			EXTI->RTSR &=~ (uint32_t)EXTI_Line8;
			EXTI->FTSR |= (uint32_t)EXTI_Line8;
		}
	}
	if(EXTI_GetITStatus(EXTI_Line9) == SET)
	{
		EXTI_ClearITPendingBit(EXTI_Line9);
		if(LineFalling[3])
		{
			LineFalling[3]=0;
			LineFallingTime[3] = SYS_TIME;
			LineHT[3] = LineFallingTime[3]-LineRisingTime[3];
			EXTI->RTSR |= (uint32_t)EXTI_Line9;
			EXTI->FTSR &=~ (uint32_t)EXTI_Line9;
		}
		else
		{
			LineFalling[3]=1;
			LineRisingTime[3] = SYS_TIME;
			EXTI->RTSR &=~ (uint32_t)EXTI_Line9;
			EXTI->FTSR |= (uint32_t)EXTI_Line9;
		}
	}
}
void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line10) == SET)
	{
		EXTI_ClearITPendingBit(EXTI_Line10);
		if(LineFalling[4])
		{
			LineFalling[4]=0;
			LineFallingTime[4] = SYS_TIME;
			LineHT[4] = LineFallingTime[4]-LineRisingTime[4];
			EXTI->RTSR |= (uint32_t)EXTI_Line10;
			EXTI->FTSR &=~ (uint32_t)EXTI_Line10;
		}
		else
		{
			LineFalling[4]=1;
			LineRisingTime[4] = SYS_TIME;
			EXTI->RTSR &=~ (uint32_t)EXTI_Line10;
			EXTI->FTSR |= (uint32_t)EXTI_Line10;
		}
	}
}

