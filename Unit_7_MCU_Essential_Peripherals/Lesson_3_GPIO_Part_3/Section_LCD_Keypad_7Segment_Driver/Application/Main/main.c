/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "lcd_interface.h"
#include "seven_segment_interface.h"
#include "gpio_interface.h"
#include "keypad_interface.h"

static void delay_ms(uint32 time);

int main(void)
{
	uint8 keyReading = KEYPAD_RELEASED;
	uint8 counter = 0;

	/* Clock Enable */
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();

	/* Initializations */
	HAL_LCD_Void_Init();
	HAL_Keypad_Void_Init();
	HAL_SevenSegment_Void_Init();

	HAL_LCD_Void_WriteString((uint8 *) "Hello LCD!");

	for(counter = 0; counter <= 0xf; counter++)
	{
		HAL_SevenSegment_Void_Display(counter);
		delay_ms(300);
	}

	HAL_SevenSegment_Void_Reset();
	HAL_LCD_Void_Clear();

	HAL_LCD_Void_WriteString((uint8 *) "System is now up");
	delay_ms(500);
	HAL_LCD_Void_Clear();

	/* Loop forever */
	while(TRUE)
	{
		keyReading = HAL_Keypad_Uint8_Read();

		if(KEYPAD_RELEASED != keyReading)
		{
			if('C' == keyReading)
			{
				HAL_SevenSegment_Void_Reset();
				HAL_LCD_Void_Clear();
			}
			else
			{
				HAL_LCD_Void_WriteCharacter(keyReading);
				HAL_SevenSegment_Void_Display(keyReading - '0');
			}
		}
		else
		{
		}
	}

	return 0;
}

static void delay_ms(uint32 time)
{
	vuint32 i;

	while(0 != time--)
	{
		for(i = 0; i < 0xff ; i++);
	}

	return;
}