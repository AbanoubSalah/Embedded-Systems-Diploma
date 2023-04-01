/**
 * @file keypad.c
 * @brief This file is the keypad driver
 *
 * @author Abanoub Salah
 * @date March 20, 2023
 *
 */

#include "keypad.h"

uint8 keypadRows[KEYPAD_ROWS_COUNT] = 		  {KEYPAD_ROW0_PIN,
											   KEYPAD_ROW1_PIN,
											   KEYPAD_ROW2_PIN,
											   KEYPAD_ROW3_PIN,
											  };
uint8 keypadColumns[KEYPAD_COLUMNS_COUNT] = {KEYPAD_COLUMN0_PIN,
											 KEYPAD_COLUMN1_PIN,
											 KEYPAD_COLUMN2_PIN,
											 KEYPAD_COLUMN3_PIN,
											};

void Keypad_Init(void)
{
	uint8 tmpIdx;
	
	/* Set rows as i/p */
	for(tmpIdx = 0; tmpIdx < KEYPAD_ROWS_COUNT; tmpIdx++)
	{
		CLR_BIT(KEYPAD_DIR, keypadRows[tmpIdx]);
		SET_BIT(KEYPAD_PORT, keypadRows[tmpIdx]);
	}
	
	/* Set coloumns as o/p */
	for(tmpIdx = 0; tmpIdx < KEYPAD_COLUMNS_COUNT; tmpIdx++)
	{
		SET_BIT(KEYPAD_DIR, keypadColumns[tmpIdx]);
		SET_BIT(KEYPAD_PORT, keypadColumns[tmpIdx]);
	}
}

char Keypad_GetKey(void)
{
	uint8 keyReading = KEYPAD_RELEASED;
	uint8 currentColumnIdx, currentRowIdx;
	uint8 keypadValues[KEYPAD_ROWS_COUNT][KEYPAD_COLUMNS_COUNT] = {{'7' , '8' , '9' , '/'},
																   {'4' , '5' , '6' , 'x'},
																   {'1' , '2' , '3' , '-'},
																   {'C' , '0' , '=' , '+'}
																  };
	
	for (currentColumnIdx = 0; currentColumnIdx < KEYPAD_COLUMNS_COUNT; currentColumnIdx++)
	{
		CLR_BIT(KEYPAD_PORT, keypadColumns[currentColumnIdx]);
		
		for (currentRowIdx = 0; currentRowIdx < 4; currentRowIdx++)
		{
			if(GET_BIT(KEYPAD_PIN, keypadRows[currentRowIdx]) == KEYPAD_PRESSED)
			{
				_delay_ms(KEYPAD_DEBOUNCING_TIME);
				
				if(GET_BIT(KEYPAD_PIN, keypadRows[currentRowIdx]) == KEYPAD_PRESSED)
				{
					while(GET_BIT(KEYPAD_PIN, keypadRows[currentRowIdx]) == KEYPAD_PRESSED);
					keyReading = keypadValues[currentRowIdx][currentColumnIdx];
					
					break;
				}
			}
		}
		
		SET_BIT(KEYPAD_PORT, keypadColumns[currentColumnIdx]);
	}
	
	return keyReading;
}
