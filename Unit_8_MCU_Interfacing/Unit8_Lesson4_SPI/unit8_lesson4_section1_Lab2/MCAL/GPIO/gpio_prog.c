/*******************************************************************************
 * gpio_prog.c
 *
 *  Created on: Apr 1, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "gpio_config.h"
#include "gpio_interface.h"
#include "gpio_private.h"

void MCAL_GPIO_Init (GPIO_TypeDef_t *GPIOx, GPIO_PinConfig_t *pinConfig)
{
	if(GPIO_MODE_INPUT_HIGHZ == pinConfig->GPIO_Mode)
	{
		GPIOx->PORT.reg &= ~(pinConfig->GPIO_PinNumber);
		GPIOx->DDR.reg &= ~(pinConfig->GPIO_PinNumber);
	}
	else if(GPIO_MODE_INPUT_PU == pinConfig->GPIO_Mode)
	{
		GPIOx->PORT.reg |= (pinConfig->GPIO_PinNumber);
		GPIOx->DDR.reg &= ~(pinConfig->GPIO_PinNumber);
	}
	else if(GPIO_MODE_OUTPUT == pinConfig->GPIO_Mode)
	{
		GPIOx->DDR.reg |= (pinConfig->GPIO_PinNumber);
	}
	else
	{
		while(TRUE);
	}

	return ;
}

void MCAL_GPIO_DeInit(GPIO_TypeDef_t *GPIOx)
{
	/* Default states */
	GPIOx->DDR.reg = 0x00;
	GPIOx->PORT.reg = 0x00;

	return ;
}

uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef_t *GPIOx, uint8_t pinNumber)
{
	uint8_t pinState = GPIO_PIN_SET;

	if(((GPIOx->PIN.reg) & pinNumber) == 0)
	{
		pinState = GPIO_PIN_RESET;
	}
	else
	{
		pinState = GPIO_PIN_SET;
	}

	return pinState;
}

uint8_t MCAL_GPIO_ReadPort(GPIO_TypeDef_t *GPIOx)
{
	return ((uint8_t) GPIOx->PIN.reg);
}

void MCAL_GPIO_WritePin(GPIO_TypeDef_t *GPIOx, uint8_t pinNumber, uint8_t value)
{
	if (value == GPIO_PIN_RESET)
	{
		GPIOx->PORT.reg &= ~((uint32_t) pinNumber);
	}
	else
	{
		GPIOx->PORT.reg |= ((uint32_t) pinNumber);
	}

	return ;
}

void MCAL_GPIO_WritePort(GPIO_TypeDef_t *GPIOx, uint8_t value)
{
	GPIOx->PORT.reg = ((uint32_t) value);

	return ;
}

void MCAL_GPIO_TogglePin(GPIO_TypeDef_t *GPIOx, uint8_t pinNumber)
{
	GPIOx->PORT.reg ^= pinNumber;

	return ;
}

/******************************************************************************
 *  END OF FILE: gpio_prog.c
 ******************************************************************************/
