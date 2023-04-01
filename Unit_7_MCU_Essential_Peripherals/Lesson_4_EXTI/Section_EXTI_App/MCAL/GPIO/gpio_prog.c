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
 *                    parameters in the PinConfig
 *
 * Param [in]        -GPIOx: where x can be (A..D depending on device used) to
 *                    select the GPIO Peripheral
 *
 * Param [in]        -PinConfig: is a pointer to GPIO_PinConfig_t structure that
 *                    contains the configuration information for the specified
 *                    GPIO PIN.
 *
 * Retval            -None
 *
 * Note              -None
 ******************************************************************************/
void MCAL_GPIO_Init (GPIO_TypeDef *GPIOx, GPIO_PinConfig *PinConfig)
{
	if(GPIO_MODE_INPUT_HIGHZ == PinConfig->GPIO_Mode)
	{
		GPIOx->PORT.reg &= ~(PinConfig->GPIO_PinNumber);
		GPIOx->DDR.reg &= ~(PinConfig->GPIO_PinNumber);
	}
	else if(GPIO_MODE_INPUT_PU == PinConfig->GPIO_Mode)
	{
		GPIOx->PORT.reg |= (PinConfig->GPIO_PinNumber);
		GPIOx->DDR.reg &= ~(PinConfig->GPIO_PinNumber);
	}
	else if(GPIO_MODE_OUTPUT == PinConfig->GPIO_Mode)
	{
		GPIOx->DDR.reg |= (PinConfig->GPIO_PinNumber);
	}
	else
	{
		while(TRUE);
	}

	return ;
}

/*******************************************************************************
 * @Fn				- MCAL_GPIO_DeInit
 *
 * @brief			- Reset all the GPIO Registers
 *
 * @param [in] 		- GPIOx: where x can be (A..D depending on device used)
 *					  to select GPIO peripheral
 *
 * @retval 			- None
 *
 * Note				- None
 ******************************************************************************/
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx)
{
	/* Default states */
	GPIOx->DDR.reg = 0x00;
	GPIOx->PORT.reg = 0x00;

	return ;
}

/*******************************************************************************
 * @Fn				- MCAL_GPIO_ReadPin
 *
 * @brief			- Read Specific PIN
 *
 * @param [in] 		- GPIOx: where x can be (A..D depending on device used)
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
uint8 MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint8 PinNumber)
{
	uint8 pinState = GPIO_PIN_SET;

	if(((GPIOx->PIN.reg) & PinNumber) == 0)
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
* Param [in]        -GPIOx: where x can be (A..D depending on device used) to
*                    select the GPIO Peripheral
*
* Retval            -The input port value
*
* Note              -None
*******************************************************************************/
uint8 MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx)
{
	return ((uint8) GPIOx->PIN.reg);
}

/*******************************************************************************
* Fn                -MCAL_GPIO_WritePort
*
* Brief             -Write on specific PIN
*
* Param [in]        -GPIOx: where x can be (A..D depending on device used) to
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
void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint8 PinNumber, uint8 Value)
{
	if (Value == GPIO_PIN_RESET)
	{
		GPIOx->PORT.reg &= ~((uint32) PinNumber);
	}
	else
	{
		GPIOx->PORT.reg |= ((uint32) PinNumber);
	}

	return ;
}

/*******************************************************************************
 * @Fn				- MCAL_GPIO_WritePort
 *
 * @brief			- Write on Specific PORT
 *
 * @param [in] 		- GPIOx: where x can be (A..D depending on device used)
 *					  to select GPIO peripheral
 *
 * @param [in] 		- Value: Port value
 *
 * @retval 			- None
 *
 * Note				- None
 ******************************************************************************/
void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx, uint8 Value)
{
	GPIOx->PORT.reg = ((uint32) Value);

	return ;
}

/*******************************************************************************
* Fn                -MCAL_GPIO_TogglePin
*
* Brief             -Toggle a specific pin in GPIOx
*
* Param [in]        -GPIOx: where x can be (A..D depending on device used) to
*                    select the GPIO Peripheral
*
* Param [in]        -PinNumber: specifies the port pin to toggle it, set pin
*                    number according @ref GPIO_PINS_define
*
* Retval            -None
*
* Note              -None
*******************************************************************************/
void MCAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint8 PinNumber)
{
	GPIOx->PORT.reg ^= PinNumber;

	return ;
}

/******************************************************************************
 *  END OF FILE: gpio_prog.c
 ******************************************************************************/
