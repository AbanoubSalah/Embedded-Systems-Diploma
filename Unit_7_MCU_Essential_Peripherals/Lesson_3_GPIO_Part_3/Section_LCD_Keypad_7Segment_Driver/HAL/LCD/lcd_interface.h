/*******************************************************************************
 * lcd.h
 *
 *  Created on: Mar 28, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

#ifndef HAL_LCD_LCD_INTERFACE_H_
#define HAL_LCD_LCD_INTERFACE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "gpio_interface.h"
#include "bit_math.h"
#include "platform_types.h"

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void HAL_LCD_Void_Init(void);
void HAL_LCD_Void_WriteCharacter(uint8);
void HAL_LCD_Void_WriteCommand(uint8);
void HAL_LCD_Void_WriteString(uint8 *);
void HAL_LCD_Void_Clear(void);
void HAL_LCD_Void_WriteNumber(sint32);
void HAL_LCD_Void_GoTo(uint8, uint8);

#endif /* HAL_LCD_LCD_INTERFACE_H_ */

/*******************************************************************************
 *  END OF FILE: lcd_interface.h
 ******************************************************************************/
