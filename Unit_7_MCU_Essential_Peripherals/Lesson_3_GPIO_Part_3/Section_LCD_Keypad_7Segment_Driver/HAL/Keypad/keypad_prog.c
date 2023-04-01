/*******************************************************************************
 * keypad.c
 *
 *  Created on: Mar 29, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

/*============================================================================================*/
/*   INCLUDES   */
/*============================================================================================*/
#include "keypad_config.h"
#include "keypad_interface.h"
#include "keypad_interface.h"
#include "keypad_private.h"

#if   KEYPAD_MODEL   ==   KEYPAD_MODEL_A
uint8 keypadMatrix[KEYPAD_ROW_NUMBER][KEYPAD_COL_NUMBER] = {{'7' , '8' , '9', '/'}, {'4' , '5' , '6', 'x'}, {'1' , '2' , '3', '-'}, {'C' , '0' , '=', '+'}};
#elif KEYPAD_MODEL   ==   KEYPAD_MODEL_B
uint8 keypadMatrix[KEYPAD_ROW_NUMBER][KEYPAD_COL_NUMBER] = {{'7' , '8' , '9', '/'}, {'4' , '5' , '6', 'x'}, {'1' , '2' , '3', '-'}, {'C' , '0' , '=', '+'}};
#endif

uint16 keypadRowsPinConfig[KEYPAD_ROW_NUMBER] = {KEYPAD_R0_PIN, KEYPAD_R1_PIN, KEYPAD_R2_PIN, KEYPAD_R3_PIN};
uint16 keypadColumnsPinConfig[KEYPAD_COL_NUMBER] = {KEYPAD_C0_PIN, KEYPAD_C1_PIN, KEYPAD_C2_PIN, KEYPAD_C3_PIN};
GPIO_TypeDef *keypadRowsPortConfig[KEYPAD_ROW_NUMBER] = {KEYPAD_R0_PORT, KEYPAD_R1_PORT, KEYPAD_R2_PORT, KEYPAD_R3_PORT};
GPIO_TypeDef *keypadColumnsPortConfig[KEYPAD_COL_NUMBER] = {KEYPAD_C0_PORT, KEYPAD_C1_PORT, KEYPAD_C2_PORT, KEYPAD_C3_PORT};

static void delay_ms(uint32 time);

/*******************************************************************************
 * Fn                -HAL_Keypad_Void_Init
 *
 * Brief             -Initializes the keypad pins according to the specified
 *                    parameters in the Keypad configuration.
 *
 * Param [in]        -None.
 *
 * Retval            -None.
 *
 * Note              -None.
 *
 ******************************************************************************/
void HAL_Keypad_Void_Init(void)
{
	GPIO_PinConfig_t pinConfig;
	uint8 rowCounter = 0;
	uint8 colCounter = 0;

	/* Mode and speed are set one time here since all o/p pins	*/
	/* share the same configuration 							*/
	pinConfig.GPIO_Mode = GPIO_MODE_INPUT_PD;
	for(colCounter = 0 ; colCounter < KEYPAD_COL_NUMBER; colCounter++)
	{
		pinConfig.GPIO_PinNumber = keypadColumnsPinConfig[colCounter];
		MCAL_GPIO_Init(keypadColumnsPortConfig[colCounter], &pinConfig);
	}

	/* Mode and speed are set one time here since all i/p pins	*/
	/* share the same configuration 							*/
	pinConfig.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinConfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
	for(rowCounter = 0 ; rowCounter < KEYPAD_ROW_NUMBER ; rowCounter++)
	{
		pinConfig.GPIO_PinNumber = keypadRowsPinConfig[rowCounter];
		MCAL_GPIO_Init(keypadRowsPortConfig[rowCounter], &pinConfig);
		/* Set pin low */
		MCAL_GPIO_WritePin(keypadRowsPortConfig[rowCounter], keypadRowsPinConfig[rowCounter], GPIO_PIN_RESET);
	}

	return ;
}

/*******************************************************************************
 * Fn                -HAL_Keypad_Uint8_Read
 *
 * Brief             -Initializes the LCD pins according to the specified
 *                    parameters in the LCD configuration.
 *
 * Param [in]        -None.
 *
 * Retval            -uint8: Return ASCII character of the pressed key
 * 							 KEYPAD_RELEASED otherwise.
 *
 * Note              -None.
 *
 ******************************************************************************/
uint8 HAL_Keypad_Uint8_Read(void)
{
	uint8 reading = KEYPAD_RELEASED;
	uint8 rowCounter = 0;
	uint8 colCounter = 0;

	/* Looping over each row setting it to high and testing			*/
	/* for a pressed key by checking a high input in the columns	*/
	for(rowCounter = 0 ; rowCounter < KEYPAD_ROW_NUMBER ; rowCounter++)
	{
		MCAL_GPIO_WritePin(keypadRowsPortConfig[rowCounter], keypadRowsPinConfig[rowCounter], GPIO_PIN_SET);
		for(colCounter = 0 ; colCounter < KEYPAD_COL_NUMBER; colCounter++)
		{
			if(MCAL_GPIO_ReadPin(keypadColumnsPortConfig[colCounter], keypadColumnsPinConfig[colCounter]) == KEYPAD_PRESSED)
			{
				/* Switch software de-bouncing */
				DELAY(KEYPAD_DEBOUNCING_TIME);
				if(MCAL_GPIO_ReadPin(keypadColumnsPortConfig[colCounter], keypadColumnsPinConfig[colCounter]) == KEYPAD_PRESSED)
				{
					/* Wait for switch release */
					while(MCAL_GPIO_ReadPin(keypadColumnsPortConfig[colCounter], keypadColumnsPinConfig[colCounter]) == KEYPAD_PRESSED)
					reading = keypadMatrix[rowCounter][colCounter];
					break;
				}

			}
		}
		MCAL_GPIO_WritePin(keypadRowsPortConfig[rowCounter], keypadRowsPinConfig[rowCounter], GPIO_PIN_RESET);
	}

	return reading;
}

/*******************************************************************************
 * Fn                -delay_ms
 *
 * Brief             -Crude busy wait timer
 *
 * Param [in]        -time: Number of milliseconds.
 *
 * Retval            -None.
 *
 * Note              -None.
 *
 *******************************************************************************/
static void delay_ms(uint32 time)
{
	vuint32 i;

	while(0 != time--)
	{
		for(i = 0; i < 0xff ; i++);
	}

	return;
}

/*******************************************************************************
 *  END OF FILE: keypad.c
 ******************************************************************************/
