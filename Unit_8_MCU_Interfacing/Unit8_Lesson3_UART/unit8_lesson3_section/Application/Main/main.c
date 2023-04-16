/*******************************************************************************
 * main.c
 *
 *  Created on: Apr 2, 2023
 *      Author: Abanoub Salah
 *       Brief: Read a character from UART /w echo then display it on LCD
 *				using interrupt
 *
 ******************************************************************************/

#include "gpio_interface.h"
#include "lcd_interface.h"
#include "uart_interface.h"

uint8_t data;

static void USART_RxCallBack(void);

int main(void)
{
	/* MCAL initializations */
	MCAL_UART_Void_Init();
	MCAL_UART_Void_SetRxCCallBack(USART_RxCallBack);

	/* HAL initializations */
	HAL_LCD_Void_Init();


	HAL_LCD_Void_WriteString((uint8_t *) "Learn in Depth");
	MCAL_UART_Void_SendString((uint8_t *) "UART initiated\n\r");
	HAL_LCD_Void_Clear();

	/* Enable global interrupt */
	sei();

	/* Loop forever */
	while(TRUE)
	{
	}

	return 0;
}

static void USART_RxCallBack(void)
{
	data = MCAL_UART_U16_Receive();
	MCAL_UART_Void_Send(data);
	HAL_LCD_Void_WriteCharacter(data);
}
