/**********************************************************************************************************************
 * @file driver.c
 * @brief This file is the implementation of the GPIO driver for STM32F103C6 μ-controller
 *
 * @author Engr. Keroles Shenouda
 * @date January 16, 2021
 * *********************************************************************************************************************/

#include "driver.h"

void Delay(vuint32 nCount)
{
	for(; nCount != 0U; nCount--);
}

uint32 getPressureVal(void)
{
	return (GPIOA_IDR & 0xFFU);
}

void Set_Alarm_actuator(boolean state)
{
	if(state == (boolean) TRUE)
	{
		SET_BIT(GPIOA_ODR, 13U);
	}
	else if(state == (boolean) FALSE)
	{
		RESET_BIT(GPIOA_ODR, 13U);
	}
}

void GPIO_Init()
{
	SET_BIT(APB2ENR, 2U);
	/* Input mode with pull-down Port A, Pin 0-7 */
	GPIOA_CRL = 0x88888888U;
	
	/* General purpose output push-pull with max speed 2 MHz */
	GPIOA_CRH &= 0x00000000U;
	GPIOA_CRH |= 0x22222222U;
}

/**********************************************************************************************************************
 *  END OF FILE: driver.c
 *********************************************************************************************************************/
