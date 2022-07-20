#include "platform_types.h"
#include "uart.h"

void Uart_Send_String(uint8 *P_tx_string)
{
	/* Loop until end of string */
	while(*P_tx_string != '\0')
	{
		UART0DR = (uint32)(*P_tx_string); /* Transmit char */
		++P_tx_string; /* Next char */
	}
}