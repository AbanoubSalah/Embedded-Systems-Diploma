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

/*******************************************************************************
 * Fn                -MCAL_GPIO_Init
 *
 * Brief             -Initializes the GPIOx PINy according to the specified
 *                    parameters in the pinConfig
 *
 * Param [in]        -GPIOx: where x can be (A..E depending on device used) to
 *                    select the GPIO Peripheral
 *
 * Param [in]        -pinConfig: is a pointer to GPIO_pinConfig_t structure that
 *                    contains the configuration information for the specified
 *                    GPIO PIN.
 *
 * Retval            -None
 *
 * Note              -STM32F103C6 MCU has GPIO A,B,C,D and E Modules but LQFP4
 *                    package has only GPIO A,B and part of C AND D exported as
 *                    external PINs from the MCU
 ******************************************************************************/
void MCAL_GPIO_Init (GPIO_TypeDef *GPIOx, GPIO_PinConfig_t *pinConfig)
{
	vuint32 *cfgReg = NULL;
	vint32 pinBitPos = -1;
	vuint32 tmpNum = pinConfig->GPIO_PinNumber;

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
	else if((pinConfig->GPIO_Mode == GPIO_MODE_ANALOG) || (pinConfig->GPIO_Mode == GPIO_MODE_INPUT_FLO) || (pinConfig->GPIO_Mode == GPIO_MODE_INPUT_PU) || (pinConfig->GPIO_Mode == GPIO_MODE_INPUT_PD) || (pinConfig->GPIO_Mode == GPIO_MODE_AF_INPUT))
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

/*******************************************************************************
 * @Fn				- MCAL_GPIO_DeInit
 *
 * @brief			- Reset all the GPIO Registers
 *
 * @param [in] 		- GPIOx: where x can be (A..E depending on device used)
 *					  to select GPIO peripheral
 *
 * @retval 			- None
 *
 * Note				- None
 ******************************************************************************/
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx)
{
	/* Holds bit position of GPIO reset in APB2RSTR */
	uint8 resetBitNumberRefA = 2;

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

/*******************************************************************************
 * @Fn				- MCAL_GPIO_ReadPin
 *
 * @brief			- Read Specific PIN
 *
 * @param [in] 		- GPIOx: where x can be (A..E depending on device used)
 * 					  to select GPIO peripheral
 *
 * @param [in] 		- PinNumber: Set Pin Number according to
 * 					  @ref GPIO_PINS_define
 *
 * @retval 			- The input pin value
 * 					  (two values based on @ref GPIO_PIN_state)
 *
 * Note				- None
 ******************************************************************************/
uint8 MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16 PinNumber)
{
	uint8 pinState = GPIO_PIN_SET;

	if(((GPIOx->IDR) & PinNumber) == 0)
	{
		pinState = GPIO_PIN_RESET;
	}
	else
	{
		pinState = GPIO_PIN_SET;
	}

	return pinState;
}

/*******************************************************************************
* Fn                -MCAL_GPIO_ReadPort
*
* Brief             -Read specific PORT
*
* Param [in]        -GPIOx: where x can be (A..E depending on device used) to
*                    select the GPIO Peripheral
*
* Retval            -The input port value
*
* Note              -None
*******************************************************************************/
uint16 MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx)
{
	return ((uint16) GPIOx->IDR);
}

/*******************************************************************************
* Fn                -MCAL_GPIO_WritePort
*
* Brief             -Write on specific PIN
*
* Param [in]        -GPIOx: where x can be (A..E depending on device used) to
*                    select the GPIO Peripheral
*
* Param [in]        -PinNumber: specifies the port pin to write on it, set pin
*                    number according @ref GPIO_PINS_define
*
* Param [in]        -Value: Pin value
*
* Retval            -None
*
* Note              -None
*******************************************************************************/
void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16 PinNumber, uint8 Value)
{
	if (Value == GPIO_PIN_RESET)
	{
		GPIOx->BRR = (uint32) PinNumber;
	}
	else
	{
		GPIOx->BSRR = (uint32) PinNumber;
	}

	return ;
}

/*******************************************************************************
 * @Fn				- MCAL_GPIO_WritePort
 *
 * @brief			- Write on Specific PORT
 *
 * @param [in] 		- GPIOx: where x can be (A..E depending on device used)
 *					  to select GPIO peripheral
 *
 * @param [in] 		- Value: Port value
 *
 * @retval 			- None
 *
 * Note				- None
 ******************************************************************************/
void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx, uint16 Value)
{
	GPIOx->ODR = (uint32) Value;

	return ;
}

/*******************************************************************************
* Fn                -MCAL_GPIO_TogglePin
*
* Brief             -Toggle a specific pin in GPIOx
*
* Param [in]        -GPIOx: where x can be (A..E depending on device used) to
*                    select the GPIO Peripheral
*
* Param [in]        -PinNumber: specifies the port pin to toggle it, set pin
*                    number according @ref GPIO_PINS_define
*
* Retval            -None
*
* Note              -None
*******************************************************************************/
void MCAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
	GPIOx->ODR ^= PinNumber;

	return ;
}
/*******************************************************************************
 * Fn                -MCAL_GPIO_LockPin
 *
 * Brief             -The locking mechanism allows the IO configuration to be
 *                    frozen.
 *
 * Param [in]        -GPIOx: where x can be (A..E depending on device used) to
 *                    select the GPIO Peripheral.
 *
 * Param [in]        -PinNumber: specifies the port pin to lock it, set pin
 *                    number according @ref GPIO_PINS_define.
 *
 * Retval            -DONE if pinConfig is locked or ERROR if pin not locked
 *                    Return_t is defined at @ref GLOBAL_ENUM.
 *
 * Note              -During the LOCK Key Writing sequence, the value of
 *                    LCK[15:0] must not change. Any error in the lock
 *                    sequence will abort the lock.
*******************************************************************************/
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
	uint32 curLockReading = (GPIOx->LCKR | PinNumber);
	uint8 resultState = GPIO_RETURN_LOCK_ENABLED;

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
