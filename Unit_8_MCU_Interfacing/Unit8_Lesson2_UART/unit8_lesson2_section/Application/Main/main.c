/*******************************************************************************
 * main.c
 *
 *  Created on: Apr 2, 2023
 *      Author: Abanoub Salah
 *		 Brief: Read a character from UART /w echo then display it on LCD using
 *				blocking method
 ******************************************************************************/

#include "gpio_interface.h"
#include "lcd_interface.h"
#include "uart_interface.h"

int main(void)
{
	uint8_t readChar;

	/* MCAL initializations */
	MCAL_UART_Void_Init();

	/* HAL initializations */
	HAL_LCD_Void_Init();


	HAL_LCD_Void_WriteString((uint8_t *) "Learn in Depth");
	MCAL_UART_Void_SendString((uint8_t *) "Learn in Depth\n\r");

	/* Loop forever */
	while(TRUE)
	{
		readChar = MCAL_UART_U16_Receive();
		HAL_LCD_Void_WriteCharacter(readChar);
	}

	return 0;
}
