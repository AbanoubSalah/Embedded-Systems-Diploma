/*******************************************************************************
 * keypad_interface.h
 *
 *  Created on: Mar 29, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

#ifndef HAL_KEYPAD_KEYPAD_INTERFACE_H_
#define HAL_KEYPAD_KEYPAD_INTERFACE_H_

/*******************************************************************************
 * INCLUDES
 ******************************************************************************/
#include "gpio_interface.h"

#include "../../Libraries/bit_math.h"
#include "../../Libraries/platform_types.h"

/*******************************************************************************
 * Defines
 ******************************************************************************/
#define KEYPAD_PRESSED               1
#define KEYPAD_RELEASED              0

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void HAL_Keypad_Void_Init(void);
uint8 HAL_Keypad_Uint8_Read(void);

#endif /* HAL_KEYPAD_KEYPAD_INTERFACE_H_ */

/*******************************************************************************
 *  END OF FILE: keypad_interface.h
 ******************************************************************************/