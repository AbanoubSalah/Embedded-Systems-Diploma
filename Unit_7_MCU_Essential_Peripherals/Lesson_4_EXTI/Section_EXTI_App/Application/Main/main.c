/*******************************************************************************
 * main.c
 *
 *  Created on: Apr 30, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

#include "gpio_interface.h"
#include "lcd_interface.h"

int main(void)
{
	/* HAL initializations */
	HAL_LCD_Void_Init();

	HAL_LCD_Void_WriteString((uint8 *) "Learn in Depth");

	/* Loop forever */
	while(TRUE)
	{
	}

	return 0;
}
