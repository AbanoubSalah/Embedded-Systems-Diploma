/*******************************************************************************
 * button_prog.c
 *
 *  Created on: Mar 30, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "button_config.h"
#include "button_interface.h"
#include "button_private.h"

/*******************************************************************************
 * Fn                -HAL_Keypad_Void_Init
 *
 * Brief             -Checks if the Button is pressed
 *
 * Param [in]        -GPIOx: where x can be (A..E depending on device used) to
 *                    select the GPIO Peripheral
 *
 * @param [in] 		- PinNumber: GPIO pin number
 *
 * Retval            -None
 *
 * Note              -None
 ******************************************************************************/
Button_Status HAL_Button_IsPressed(GPIO_TypeDef GPIOx, uint16 PinNumber)
{
	Button_Status buttonState = Button_Off;
	
	if(GPIO_PIN_SET == MCAL_GPIO_ReadPin(GPIOx, PinNumber))
	{
		buttonState = Button_On;
	}
	else
	{
		buttonState = Button_Off;
	}
	
	return buttonState;
}

/**********************************************************************************************************************
 *  END OF FILE: button_prog.c
 *********************************************************************************************************************/
