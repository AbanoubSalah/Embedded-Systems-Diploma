#include "platform_types.h"
#include "uart.h"

uint8 string_buffer[100] = "learn-in-depth: Abanoub Salah";

void main(void)
{
	//VersatilePB physical Board
	Uart_Send_String(string_buffer);
}