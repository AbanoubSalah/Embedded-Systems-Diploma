/**
 * @file lcd.c
 * @brief This file is the LCD driver
 *
 * @author Abanoub Salah
 * @date March 20, 2023
 *
 */
 
#include "lcd.h"
#include "bit_math.h"

static inline void SetPinValue(uint8 pin, uint8 value)
{
	if(value == 0)
	{
		CLR_BIT(LCD_PORT, pin);
	}
	else
	{
		SET_BIT(LCD_PORT, pin);
	}

	return ;
}

void lcd_Init(void)
{
	SET_BIT(LCD_DDR, LCD_D0_PIN);
	SET_BIT(LCD_DDR, LCD_D1_PIN);
	SET_BIT(LCD_DDR, LCD_D2_PIN);
	SET_BIT(LCD_DDR, LCD_D3_PIN);
	SET_BIT(LCD_DDR, LCD_RS_PIN);
	SET_BIT(LCD_DDR, LCD_EN_PIN);
	
	SET_BIT(LCD_PORT, LCD_D0_PIN);
	SET_BIT(LCD_PORT, LCD_D1_PIN);
	SET_BIT(LCD_PORT, LCD_D2_PIN);
	SET_BIT(LCD_PORT, LCD_D3_PIN);
	SET_BIT(LCD_PORT, LCD_RS_PIN);
	SET_BIT(LCD_PORT, LCD_EN_PIN);
	
	lcd_WriteCommand(LCD_4_BIT_MODE_COMMAND_1);
	lcd_WriteCommand(LCD_4_BIT_MODE_COMMAND_2);
	lcd_WriteCommand(LCD_4_BIT_MODE_COMMAND_3);
	lcd_WriteCommand(LCD_DISPLAY_ON_COMMAND);
	lcd_WriteCommand(LCD_RETURN_HOME_COMMAND);
	lcd_WriteCommand(LCD_CLEAR);
}

void lcd_WriteCharacter(uint8 character)
{
	SET_BIT(LCD_PORT, LCD_RS_PIN);

	SetPinValue(LCD_D0_PIN, GET_BIT(character, 4));
	SetPinValue(LCD_D1_PIN, GET_BIT(character, 5));
	SetPinValue(LCD_D2_PIN, GET_BIT(character, 6));
	SetPinValue(LCD_D3_PIN, GET_BIT(character, 7));
	
	SetPinValue(LCD_EN_PIN, HIGH);
	_delay_ms(1);
	SetPinValue(LCD_EN_PIN, LOW);
	_delay_ms(1);
	
	SetPinValue(LCD_D0_PIN,GET_BIT(character, 0));
	SetPinValue(LCD_D1_PIN,GET_BIT(character, 1));
	SetPinValue(LCD_D2_PIN,GET_BIT(character, 2));
	SetPinValue(LCD_D3_PIN,GET_BIT(character, 3));
	
	SetPinValue(LCD_EN_PIN,HIGH);
	_delay_ms(1);
	SetPinValue(LCD_EN_PIN, LOW);
	_delay_ms(5);
}

void lcd_WriteCommand(uint8 command)
{
	SetPinValue(LCD_RS_PIN, LOW);

	SetPinValue(LCD_D0_PIN, GET_BIT(command, 4));
	SetPinValue(LCD_D1_PIN, GET_BIT(command, 5));
	SetPinValue(LCD_D2_PIN, GET_BIT(command, 6));
	SetPinValue(LCD_D3_PIN, GET_BIT(command, 7));
	
	SetPinValue(LCD_EN_PIN, HIGH);
	_delay_ms(1);
	SetPinValue(LCD_EN_PIN, LOW);
	_delay_ms(1);
	
	SetPinValue(LCD_D0_PIN, GET_BIT(command, 0));
	SetPinValue(LCD_D1_PIN, GET_BIT(command, 1));
	SetPinValue(LCD_D2_PIN, GET_BIT(command, 2));
	SetPinValue(LCD_D3_PIN, GET_BIT(command, 3));
	
	SetPinValue(LCD_EN_PIN, HIGH);
	_delay_ms(1);
	SetPinValue(LCD_EN_PIN, LOW);
	_delay_ms(5);
}

void lcd_WriteString(uint8 *strPtr)
{
	uint8 counter = 0;
	
	while(strPtr[counter] != NULL)
	{
		lcd_WriteCharacter(strPtr[counter]);
		counter++;
	}
}

void lcd_Clear(void)
{
	lcd_WriteCommand(LCD_CLEAR);
}

void lcd_WriteNumber(sint32 num)
{
	sint8 strCounter = 0;
	uint8 strArr[10] = {0};
	
	if(num < 0)
	{
		num = num * -1;
		lcd_WriteCharacter('-');
	}

	do
	{
		strArr[strCounter] = num % 10;
		num = num / 10;
		strCounter++;
	}while(num != 0);

	while(strCounter > 0)
	{
		lcd_WriteCharacter(strArr[--strCounter] + 48);
	}
}

void lcd_GoTo(uint8 row, uint8 col)
{
	uint8 strArr [4] = {LCD_R0_COMMAND , LCD_R1_COMMAND , LCD_R2_COMMAND , LCD_R3_COMMAND};
	lcd_WriteCommand(strArr[row] + col);
}
