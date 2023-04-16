/*******************************************************************************
 * lcd.h
 *
 *  Created on: Apr 1, 2023
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
 * APIs Supported by "HAL LCD DRIVER"
 ******************************************************************************/

/*******************************************************************************
 * Fn                - HAL_LCD_Void_Init
 *
 * Brief             - Initializes the LCD pins according to the specified
 *                    parameters in the LCD configuration
 *
 * Param [in]        - None
 *
 * Retval            - None
 *
 * Note              - None
 ******************************************************************************/
void HAL_LCD_Void_Init(void);

/*******************************************************************************
 * Fn                - HAL_LCD_Void_WriteCharacter
 *
 * Brief             - Display given character on the LCD
 *
 * Param [in]        - ASCII character to be displayed
 *
 * Retval            - None
 *
 * Note              - None
 ******************************************************************************/
void HAL_LCD_Void_WriteCharacter(uint8_t);

/*******************************************************************************
 * Fn                - HAL_LCD_Void_WriteString
 *
 * Brief             - Write a string to be displayed
 *
 * Param [in]        - strPtr: pointer to an array of characters
 *
 * Retval            - None
 *
 * Note              - None
 ******************************************************************************/
void HAL_LCD_Void_WriteString(uint8_t *);

/*******************************************************************************
 * Fn                - HAL_LCD_Void_Clear
 *
 * Brief             - Clears entire LCD screen
 *
 * Param [in]        - None
 *
 * Retval            - None
 *
 * Note              - None
 ******************************************************************************/
void HAL_LCD_Void_Clear(void);

/*******************************************************************************
 * Fn                - HAL_LCD_Void_WriteNumber
 *
 * Brief             - Display an integer number on LCD screen
 *
 * Param [in]        - a 32-Bit integer number to be displayed
 *
 * Retval            - None
 *
 * Note              - None
 ******************************************************************************/
void HAL_LCD_Void_WriteNumber(sint32_t);

/*******************************************************************************
 * Fn                - HAL_LCD_Void_GoTo
 *
 * Brief             - Moves LCD cursor to the provided position
 *
 * Param [in]        - LCD row number
 * Param [in]        - LCD column number
 *
 * Retval            - None
 *
 * Note              - None
 ******************************************************************************/
void HAL_LCD_Void_GoTo(uint8_t, uint8_t);

#endif /* HAL_LCD_LCD_INTERFACE_H_ */

/*******************************************************************************
 *  END OF FILE: lcd_interface.h
 ******************************************************************************/
