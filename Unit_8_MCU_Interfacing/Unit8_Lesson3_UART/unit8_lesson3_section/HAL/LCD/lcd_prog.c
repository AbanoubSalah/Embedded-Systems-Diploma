/*******************************************************************************
 * lcd_prog.c
 *
 *  Created on: Apr 1, 2023
 *      Author: Abanoub Salah
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lcd_config.h"
#include "lcd_interface.h"
#include "lcd_private.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
static uint8_t curXValue = 0, curYValue = 0;

void HAL_LCD_Void_Init(void)
{
	GPIO_PinConfig_t pinConfig;

	/* Mode and speed are set one time here since all pins */
	/* share the same configuration 					  */
	pinConfig.GPIO_Mode = GPIO_MODE_OUTPUT;

    /* RS, RW and En pins */
    pinConfig.GPIO_PinNumber = LCD_RS_PIN;
    MCAL_GPIO_Init(LCD_RS_PORT, &pinConfig);

    pinConfig.GPIO_PinNumber = LCD_RW_PIN;
	MCAL_GPIO_Init(LCD_RW_PORT, &pinConfig);

	pinConfig.GPIO_PinNumber = LCD_EN_PIN;
	MCAL_GPIO_Init(LCD_EN_PORT, &pinConfig);

	/* Default the RS, RW and En pins to o/p reset */
	MCAL_GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_RW_PORT, LCD_RW_PIN, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_EN_PORT, LCD_EN_PIN, GPIO_PIN_RESET);

#if LCD_MODE   ==   MODE_8_BIT

	/* Assumes same configuration as above only changing */
	/* the pins number 									 */
	pinConfig.GPIO_PinNumber = LCD_D0_PIN;
	MCAL_GPIO_Init(LCD_D0_PORT, &pinConfig);

	pinConfig.GPIO_PinNumber = LCD_D1_PIN;
	MCAL_GPIO_Init(LCD_D1_PORT, &pinConfig);

	pinConfig.GPIO_PinNumber = LCD_D2_PIN;
	MCAL_GPIO_Init(LCD_D2_PORT, &pinConfig);

	pinConfig.GPIO_PinNumber = LCD_D3_PIN;
	MCAL_GPIO_Init(LCD_D3_PORT, &pinConfig);

	pinConfig.GPIO_PinNumber = LCD_D4_PIN;
	MCAL_GPIO_Init(LCD_D4_PORT, &pinConfig);

	pinConfig.GPIO_PinNumber = LCD_D5_PIN;
	MCAL_GPIO_Init(LCD_D5_PORT, &pinConfig);

	pinConfig.GPIO_PinNumber = LCD_D6_PIN;
	MCAL_GPIO_Init(LCD_D6_PORT, &pinConfig);

	pinConfig.GPIO_PinNumber = LCD_D7_PIN;
	MCAL_GPIO_Init(LCD_D7_PORT, &pinConfig);

	/* 8-Bit mode specific command */
	HAL_LCD_Void_WriteCommand(LCD_8_BIT_MODE_COMMAND);

#elif LCD_MODE   ==   MODE_4_BIT

	/* Assumes same configuration as above only changing */
	/* the pins number 									 */
	pinConfig.GPIO_PinNumber = LCD_D4_PIN;
	MCAL_GPIO_Init(LCD_D4_PORT, &pinConfig);

	pinConfig.GPIO_PinNumber = LCD_D5_PIN;
	MCAL_GPIO_Init(LCD_D5_PORT, &pinConfig);

	pinConfig.GPIO_PinNumber = LCD_D6_PIN;
	MCAL_GPIO_Init(LCD_D6_PORT, &pinConfig);

	pinConfig.GPIO_PinNumber = LCD_D7_PIN;
	MCAL_GPIO_Init(LCD_D7_PORT, &pinConfig);

	/* 4-Bit mode specific commands */
	HAL_LCD_Void_WriteCommand(LCD_RETURN_HOME);
	HAL_LCD_Void_WriteCommand(LCD_4_BIT_MODE_COMMAND);

#endif

	/* Common commands between modes */
	HAL_LCD_Void_WriteCommand(LCD_ENTRY_MODE);
	HAL_LCD_Void_WriteCommand(LCD_ROW0_COMMAND);
	HAL_LCD_Void_WriteCommand(LCD_DISPLAY_ON_COMMAND);

	return ;
}

void HAL_LCD_Void_WriteCharacter(uint8_t character)
{
	/* Cursor position logic */
	if(LCD_COLUMNS_NUMBER <= curXValue)
	{
		curXValue = 0;
		++curYValue;
		if(LCD_ROWS_NUMBER <= curYValue)
		{
			curYValue = 0;
		}
		else
		{
		}

		HAL_LCD_Void_GoTo(curYValue, curXValue);

	}
	else
	{
	}

	MCAL_GPIO_WritePin(LCD_RW_PORT, LCD_RW_PIN, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, GPIO_PIN_SET);
	setPinsAndTriggerPulse(character);
	
	++curXValue;

	return ;
}

static void HAL_LCD_Void_WriteCommand(uint8_t command)
{
	MCAL_GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_RW_PORT, LCD_RW_PIN, GPIO_PIN_RESET);

	setPinsAndTriggerPulse(command);

	return ;
}

void HAL_LCD_Void_WriteString(uint8_t *strPtr)
{
	while(STRING_NUL != (*strPtr))
	{
		HAL_LCD_Void_WriteCharacter(*strPtr);
		strPtr++;
	}
	
	return ;
}

void HAL_LCD_Void_Clear(void)
{
	/* Clearing screen contents */
	HAL_LCD_Void_WriteCommand(LCD_CLEAR);

	/* Putting cursor at origin */
	HAL_LCD_Void_GoTo(0, 0);
	
	return ;
}

void HAL_LCD_Void_WriteNumber(sint32_t number)
{
	sint8_t counter = 0;
	sint8_t array[11] = {0};

	/* Taking care of minus sign */
	if(number < 0)
	{
		number = number * -1;
		HAL_LCD_Void_WriteCharacter('-');
	}

	do
	{
		array[counter] = (number % 10);
		number /= 10;
		++counter;
	}while(0 != number);

	/* array Contains the number in reverse order */
	/* so we use counter as a reverse index and   */
	/* decrement it inside the while loop         */
	while(counter > 0)
	{
		/* Adding ASCII 0 to convert the number to ASCII */
		HAL_LCD_Void_WriteCharacter(array[--counter] + '0');
	}
	
	return ;
}

void HAL_LCD_Void_GoTo(uint8_t row, uint8_t col)
{
	uint8_t array [2] = {LCD_ROW0_COMMAND , LCD_ROW1_COMMAND};
	
	/* Adding column to the command to shift the address since */
	/* the command lower 7-bits are the address                */
	HAL_LCD_Void_WriteCommand(array[row] + col);

	/* Updating local coordinates */
	curXValue = col;
	curYValue = row;

	return ;
}

/*******************************************************************************
 * Fn                -setPinsAndTriggerPulse
 *
 * Brief             -Set LCD pins according to the provided variable
 *
 * Param [in]        -data: Data/Command to be put on LCD data pins
 *
 * Retval            -None
 *
 * Note              -None
 ******************************************************************************/
static void setPinsAndTriggerPulse(uint8_t data)
{

#if LCD_MODE == MODE_8_BIT
	MCAL_GPIO_WritePin(LCD_D0_PORT, LCD_D0_PIN, GET_BIT(data, 0));
	MCAL_GPIO_WritePin(LCD_D1_PORT, LCD_D1_PIN, GET_BIT(data, 1));
	MCAL_GPIO_WritePin(LCD_D2_PORT, LCD_D2_PIN, GET_BIT(data, 2));
	MCAL_GPIO_WritePin(LCD_D3_PORT, LCD_D3_PIN, GET_BIT(data, 3));
	MCAL_GPIO_WritePin(LCD_D4_PORT, LCD_D4_PIN, GET_BIT(data, 4));
	MCAL_GPIO_WritePin(LCD_D5_PORT, LCD_D5_PIN, GET_BIT(data, 5));
	MCAL_GPIO_WritePin(LCD_D6_PORT, LCD_D6_PIN, GET_BIT(data, 6));
	MCAL_GPIO_WritePin(LCD_D7_PORT, LCD_D7_PIN, GET_BIT(data, 7));

	enablePulse();

#elif LCD_MODE   ==   MODE_4_BIT
	MCAL_GPIO_WritePin(LCD_D4_PORT, LCD_D4_PIN, GET_BIT(data, 4));
	MCAL_GPIO_WritePin(LCD_D5_PORT, LCD_D5_PIN, GET_BIT(data, 5));
	MCAL_GPIO_WritePin(LCD_D6_PORT, LCD_D6_PIN, GET_BIT(data, 6));
	MCAL_GPIO_WritePin(LCD_D7_PORT, LCD_D7_PIN, GET_BIT(data, 7));

	enablePulse();

	MCAL_GPIO_WritePin(LCD_D4_PORT, LCD_D4_PIN, GET_BIT(data, 0));
	MCAL_GPIO_WritePin(LCD_D5_PORT, LCD_D5_PIN, GET_BIT(data, 1));
	MCAL_GPIO_WritePin(LCD_D6_PORT, LCD_D6_PIN, GET_BIT(data, 2));
	MCAL_GPIO_WritePin(LCD_D7_PORT, LCD_D7_PIN, GET_BIT(data, 3));

	enablePulse();

#endif

	return ;
}

/*******************************************************************************
 * Fn                -delay_ms
 *
 * Brief             -a Crude busy wait timer
 *
 * Param [in]        -time: Number of milliseconds
 *
 * Retval            -None
 *
 * Note              -None
 ******************************************************************************/
static void delay_ms(uint32_t time)
{
	vuint32_t i;

	while(0 != time--)
	{
		for(i = 0; i < 0xff ; i++);
	}

	return;
}

/*******************************************************************************
 * Fn                -enablePulse
 *
 * Brief             -Sends enable pulse on the enable pin
 *					  of the LCD
 *
 * Param [in]        -None
 *
 * Retval            -None
 *
 * Note              -None
 ******************************************************************************/
static void enablePulse(void)
{
	/* High to Low pulse */
	MCAL_GPIO_WritePin(LCD_EN_PORT, LCD_EN_PIN, GPIO_PIN_SET);
	DELAY(LCD_EN_DELAY);
	MCAL_GPIO_WritePin(LCD_EN_PORT, LCD_EN_PIN, GPIO_PIN_RESET);

	return ;
}

/*******************************************************************************
 *  END OF FILE: lcd.c
 ******************************************************************************/
