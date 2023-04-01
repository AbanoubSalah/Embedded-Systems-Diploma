/**
 * @file lcd.h
 * @brief This file is the LCD interface
 *
 * @author Abanoub Salah
 * @date March 20, 2023
 *
 */
 
#ifndef LCD_H_
#define LCD_H_

/*--------------------------------------------------------------------------------------------*/
/*   INCLUDES   */
/*--------------------------------------------------------------------------------------------*/
#include <avr/io.h>
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <util/delay.h>
#include "platform_types.h"

/* LCD Coniguration */
#define LCD_DDR					  	  DDRA
#define LCD_PORT				  	  PORTA
#define LCD_D0_PIN                	  0
#define LCD_D1_PIN                	  1
#define LCD_D2_PIN                	  2
#define LCD_D3_PIN                	  3
#define LCD_RS_PIN                	  4
#define LCD_EN_PIN                	  5

/* LCD commands */
#define LCD_DISPLAY_ON_COMMAND        0x0C
#define LCD_RETURN_HOME_COMMAND       0x02
#define LCD_4_BIT_MODE_COMMAND_1      0x33
#define LCD_4_BIT_MODE_COMMAND_2      0x32
#define LCD_4_BIT_MODE_COMMAND_3      0x28
#define LCD_CLEAR                     0x01
#define LCD_R0_COMMAND                0x80
#define LCD_R1_COMMAND                0xC0
#define LCD_R2_COMMAND                0x94
#define LCD_R3_COMMAND                0xD4

/* LCD definitions */
#define NULL                          '\0'

/*--------------------------------------------------------------------------------------------*/
/*   PROTOTYPES   */
/*--------------------------------------------------------------------------------------------*/
void lcd_Init(void);
void lcd_WriteCharacter(uint8);
void lcd_WriteCommand(uint8);
void lcd_WriteString(uint8 *);
void lcd_Clear(void);
void lcd_WriteNumber(sint32);
void lcd_GoTo(uint8, uint8);

#endif

/**********************************************************************************************************************
 *  END OF FILE: keypad.h
 *********************************************************************************************************************/