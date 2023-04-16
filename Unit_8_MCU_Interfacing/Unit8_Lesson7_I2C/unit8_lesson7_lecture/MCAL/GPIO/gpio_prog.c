/*******************************************************************************
 * gpio_prog.c
 *
 *  Created on: Mar 27, 2023
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
	vuint32_t *cfgReg = NULL;
	vint32_t pinBitPos = -1;
	vuint32_t tmpNum = pinConfig->GPIO_PinNumber;

	/* Get pin position */
	for(; tmpNum != 0; tmpNum >>= 1)
	{
		++pinBitPos;
	}

	/* Assign configuration register depending on pin position */
	/* 0..7 CRL, 8..15 CRH									   */
	if((pinBitPos >= 0) && (pinBitPos <= 7))
	{
		cfgReg = &(GPIOx->CRL);
	}
	else if((pinBitPos >= 8) && (pinBitPos <= 15))
	{
		cfgReg = &(GPIOx->CRH);
	}
	else
	{
		/* Out of range (0..15) pin number will get stuck here */
		while(TRUE);
	}

	/* Zero out the corresponding configuration bits */
	*cfgReg &= ~(0b1111 << ((pinBitPos % 8) << 2));

	if((pinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_PP) || (pinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_OD) || (pinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_AF_PP) || (pinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_AF_OD))
	{
		/* Output mode configuration */
		*cfgReg |= ((((pinConfig->GPIO_Mode - 4) << 2) | pinConfig->GPIO_OutputSpeed) << ((pinBitPos % 8) << 2));
	}
	else if((pinConfig->GPIO_Mode == GPIO_MODE_ANALOG) || (pinConfig->GPIO_Mode == GPIO_MODE_INPUT_FLO) || (pinConfig->GPIO_Mode == GPIO_MODE_INPUT_PU) || (pinConfig->GPIO_Mode == GPIO_MODE_INPUT_PD) || (pinConfig->GPIO_Mode == GPIO_MODE_INPUT_AF))
	{
		/* Input mode configuration */
		if(pinConfig->GPIO_Mode == GPIO_MODE_INPUT_PD)
		{
			/* Taking care of pull-down special case since 0b11 is reserved */
			*cfgReg |= (0b10 << (((pinBitPos % 8) << 2) + 2));
		}
		else
		{
			/* GPIO_MODE corresponds to configuration mode */
			/* with the exception above */
			*cfgReg |= (pinConfig->GPIO_Mode << (((pinBitPos % 8) << 2) + 2));
		}

		if(pinConfig->GPIO_Mode == GPIO_MODE_INPUT_PU)
		{
			/* Pull-up resistance activation */
			GPIOx->ODR |= pinConfig->GPIO_PinNumber;
		}
		else
		{
			/* Default value for pull-down if i/p mode is set */
			GPIOx->ODR &= ~(pinConfig->GPIO_PinNumber);
		}
	}
	else
	{
		/* Gets stuck here for wrong mode values */
		while(TRUE);
	}

	return ;
}

void MCAL_GPIO_DeInit(GPIO_TypeDef_t *GPIOx)
{
	/* Holds bit position of GPIO reset in APB2RSTR */
	uint8_t resetBitNumberRefA = 2;

	/* Shift bit position according to the given port */
	if(GPIOx == GPIOB)
	{
		resetBitNumberRefA++;
	}
	else if(GPIOx == GPIOC)
	{
		resetBitNumberRefA += 2;
	}
	else if(GPIOx == GPIOD)
	{
		resetBitNumberRefA += 3;
	}
	else if(GPIOx == GPIOE)
	{
		resetBitNumberRefA += 4;
	}
	else
	{
		while(TRUE);
	}

	SET_BIT(RCC->APB2RSTR, resetBitNumberRefA);
	CLR_BIT(RCC->APB2RSTR, resetBitNumberRefA);

	return ;
}

uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef_t *GPIOx, uint16_t pinNumber)
{
	uint8_t pinState = GPIO_PIN_SET;

	if(((GPIOx->IDR) & pinNumber) == 0)
	{
		pinState = GPIO_PIN_RESET;
	}
	else
	{
		pinState = GPIO_PIN_SET;
	}

	return pinState;
}

uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef_t *GPIOx)
{
	return ((uint16_t) GPIOx->IDR);
}

void MCAL_GPIO_WritePin(GPIO_TypeDef_t *GPIOx, uint16_t pinNumber, uint8_t value)
{
	if (value == GPIO_PIN_RESET)
	{
		GPIOx->BRR = (uint32_t) pinNumber;
	}
	else
	{
		GPIOx->BSRR = (uint32_t) pinNumber;
	}

	return ;
}

void MCAL_GPIO_WritePort(GPIO_TypeDef_t *GPIOx, uint16_t value)
{
	GPIOx->ODR = ((uint32_t) value);

	return ;
}

void MCAL_GPIO_TogglePin(GPIO_TypeDef_t *GPIOx, uint16_t pinNumber)
{
	GPIOx->ODR ^= pinNumber;

	return ;
}
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef_t *GPIOx, uint16_t pinNumber)
{
	uint32_t curLockReading = (GPIOx->LCKR | pinNumber);
	uint8_t resultState = GPIO_RETURN_LOCK_ENABLED;

	GPIOx->LCKR = curLockReading;

	/* LOCK key writing sequence: */
	/* Write 1					  */
	/* Write 0					  */
	/* Write 1  				  */
	/* Read  0 					  */
	/* Read  1 (Optional) 		  */
	GPIOx->LCKR |= (1 << 16);
	GPIOx->LCKR &= ~(1 << 16);
	GPIOx->LCKR |= (1 << 16);

	curLockReading = GPIOx->LCKR;
	curLockReading = GPIOx->LCKR;

	if((curLockReading & (1 << 16)) != 0)
	{
		resultState = GPIO_RETURN_LOCK_ENABLED;
	}
	else
	{
		resultState = GPIO_RETURN_LOCK_ERROR;
	}

	return resultState;
}

/******************************************************************************
 *  END OF FILE: gpio_prog.c
 ******************************************************************************/
