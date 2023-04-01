/*******************************************************************************
 * @file main.c
 *
 * @author Abanoub Salah
 *
 * @date March 20, 2023
 ******************************************************************************/

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <util/delay.h>
#include "keypad.h"
#include "lcd.h"

int main(void)
{
	uint8 curPress = KEYPAD_RELEASED;
	
	lcd_Init();
	Keypad_Init();
	lcd_WriteString((uint8 *)"Hello!!!");
	_delay_ms(50);
	
    while (1) 
    {
		curPress = Keypad_GetKey();
		
		if('C' == curPress)
		{
			lcd_Clear();
		}
		else if(KEYPAD_RELEASED != curPress)
		{
			lcd_WriteCharacter(curPress);
		}
		else
		{
			continue;
		}
    }
	
	return 0;
}
