/**
 * @file keypad.h
 * @brief This file is the keypad interface
 *
 * @author Abanoub Salah
 * @date March 20, 2023
 *
 */
 
#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <avr/io.h>
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <util/delay.h>
#include "platform_types.h"
#include "bit_math.h"

/* Keypad Coniguration */
#define KEYPAD_ROWS_COUNT 			(4)
#define KEYPAD_COLUMNS_COUNT 		(4)

#define KEYPAD_DIR					DDRD
#define KEYPAD_PORT 				PORTD
#define KEYPAD_PIN					PIND

#define KEYPAD_ROW0_PIN 			0
#define KEYPAD_ROW1_PIN 			1
#define KEYPAD_ROW2_PIN 			2
#define KEYPAD_ROW3_PIN 			3
#define KEYPAD_COLUMN0_PIN 			4
#define KEYPAD_COLUMN1_PIN 			5
#define KEYPAD_COLUMN2_PIN 			6
#define KEYPAD_COLUMN3_PIN 			7

/* Keypad status */
#define KEYPAD_PRESSED              0
#define KEYPAD_RELEASED             1

/*   Select keypad_debouncing_time in milli second */
#define KEYPAD_DEBOUNCING_TIME   	40


/* Keypad Prototypes */
void Keypad_Init(void);
char Keypad_GetKey(void); 

#endif

/**********************************************************************************************************************
 *  END OF FILE: keypad.h
 *********************************************************************************************************************/