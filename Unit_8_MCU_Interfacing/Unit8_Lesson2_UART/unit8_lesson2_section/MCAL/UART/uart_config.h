/*******************************************************************************
 * uart_config.h
 *
 *  Created on: Apr 2, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

#ifndef MCAL_UART_UART_CONFIG_H_
#define MCAL_UART_UART_CONFIG_H_

/*******************************************************************************
 * Pins definitions
 ******************************************************************************/
#define UART_RX_PORT					GPIOD
#define UART_TX_PORT					GPIOD

#define UART_RX_PIN						GPIO_PIN_0
#define UART_TX_PIN						GPIO_PIN_1

/*******************************************************************************
 * Select F_OSC in MHz
 ******************************************************************************/
#define F_OSC							1UL

/*******************************************************************************
 * Select UART_BAUD_RATE
 ******************************************************************************/
#define UART_BAUD_RATE					9600UL

/*******************************************************************************
 * UART_PARITY_MODE Options : DISABLE_PARITY | EVEN_PARITY | ODD_PARITY
 ******************************************************************************/
#define UART_PARITY_MODE				PARITY_DISABLE

/*******************************************************************************
 * UART_STOP_BIT OPTIONS : 1 | 2
 ******************************************************************************/
#define UART_STOP_BIT					1U

/*******************************************************************************
 * UART_DATA_BITS Options : 5 | 6 | 7 | 8 | 9
 ******************************************************************************/
#define UART_DATA_BITS					8U

/*******************************************************************************
 * UART_TX_RX_ENABLE Options : RX_ENABLE    | TX_ENABLE     |
 *			       TX_RX_ENABLE | TX_RX_DISABLE |
 ******************************************************************************/
#define UART_TX_RX_ENABLE				TX_RX_ENABLE

/*******************************************************************************
 * UART_IRQ_ENABLE Options : IRQ_DIASABLE | RXCIE_IRQ | TXCIE_IRQ |
 *							 RXCIE_TXCIE_IRQ |
 ******************************************************************************/
#define UART_IRQ_ENABLE					IRQ_DIASABLE

#endif /* MCAL_UART_UART_CONFIG_H_ */

/******************************************************************************
 *  END OF FILE: uart_config.h
 ******************************************************************************/