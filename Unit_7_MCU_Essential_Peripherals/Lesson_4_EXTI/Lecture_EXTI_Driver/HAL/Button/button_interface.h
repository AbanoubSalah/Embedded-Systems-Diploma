/*******************************************************************************
 * button_interface.h
 *
 *  Created on: Mar 30, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

#ifndef HAL_BUTTON_BUTTON_INTERFACE_H_
#define HAL_BUTTON_BUTTON_INTERFACE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "gpio_interface.h"
#include "platform_types.h"

typedef enum
{
	Button_Off,
	Button_On,
}Button_Status;

Button_Status HAL_Button_IsPressed(GPIO_TypeDef, uint16);

#endif  /* HAL_BUTTON_BUTTON_INTERFACE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: button_interface.h
 *********************************************************************************************************************/
