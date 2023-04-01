/*******************************************************************************
 * lcd_private.h
 *
 *  Created on: Apr 30, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

#ifndef HAL_LCD_LCD_PRIVATE_H_
#define HAL_LCD_LCD_PRIVATE_H_

/*******************************************************************************
 * Defines
 ******************************************************************************/
#define LCD_CLEAR                     0x01
#define LCD_RETURN_HOME               0x02
#define LCD_ENTRY_MODE      		  0x06
#define LCD_DISPLAY_ON_COMMAND        0x0C
#define LCD_4_BIT_MODE_COMMAND        0x28
#define LCD_8_BIT_MODE_COMMAND        0x38
#define LCD_ROW0_COMMAND              0x80
#define LCD_ROW1_COMMAND              0xC0

#define MODE_8_BIT	                   8
#define MODE_4_BIT	                   4
#define LCD_ROWS_NUMBER				   2
#define LCD_COLUMNS_NUMBER			   16
#define LCD_EN_DELAY       			   20

#define STRING_NUL                    '\0'

#endif /* HAL_LCD_LCD_PRIVATE_H_ */

/*******************************************************************************
 *  END OF FILE: lcd_private.h
 ******************************************************************************/
