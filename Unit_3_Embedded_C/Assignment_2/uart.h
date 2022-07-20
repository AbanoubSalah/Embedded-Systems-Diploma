#ifndef _UART_H_
#define _UART_H_

#include "platform_types.h"

//uart registers
#define UART0DR *((vuint32_t* const)((uint32 *)0x101f1000))

//UART APIS
void Uart_Send_String(uint8 *P_tx_string);

#endif