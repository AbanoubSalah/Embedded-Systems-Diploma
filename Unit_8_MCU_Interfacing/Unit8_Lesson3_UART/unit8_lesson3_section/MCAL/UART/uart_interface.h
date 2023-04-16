/*******************************************************************************
 * uart_interface.h
 *
 *  Created on: Apr 2, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

#ifndef MCAL_UART_UART_INTERFACE_H_
#define MCAL_UART_UART_INTERFACE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "atmega32.h"
#include "platform_types.h"
#include "bit_math.h"
#include "gpio_interface.h"

/*******************************************************************************
 * APIs Supported by "MCAL UART DRIVER"
 ******************************************************************************/

/*******************************************************************************
 * Fn                - MCAL_UART_Void_Init
 *
 * Brief             - Initializes the UART according to the specified
 *                     parameters in the Configuration
 *
 * Param [in]        - None
 *
 * Retval            - None
 *
 * Note              - None
 ******************************************************************************/
void MCAL_UART_Void_Init(void);

/*******************************************************************************
 * Fn                - MCAL_UART_Void_Send
 *
 * Brief             - Send the given data through the UART
 *
 * Param [in]        - Data to be sent through
 *
 * Retval            - None
 *
 * Note              - None
 ******************************************************************************/
void MCAL_UART_Void_Send(uint16_t);

/*******************************************************************************
 * Fn                - MCAL_UART_Void_SendString
 *
 * Brief             - Send a string through the UART
 *
 * Param [in]        - Pointer to a string to be sent through UART
 *
 * Retval            - None
 *
 * Note              - None
 ******************************************************************************/
void MCAL_UART_Void_SendString(uint8_t *);

/*******************************************************************************
 * Fn                - MCAL_UART_U16_Receive
 *
 * Brief             - Receive data from the UART
 *
 * Param [in]        - None
 *
 * Retval            - Data received
 *
 * Note              - None
 ******************************************************************************/
uint16_t MCAL_UART_U16_Receive(void);

#if (UART_IRQ_ENABLE == TXCIE_IRQ) || (UART_IRQ_ENABLE == RXCIE_TXCIE_IRQ)
void MCAL_UART_Void_SetTxCCallBack(void (*pFun)(void));
#endif

#if (UART_IRQ_ENABLE == RXCIE_IRQ) || (UART_IRQ_ENABLE == RXCIE_TXCIE_IRQ)
void MCAL_UART_Void_SetRxCCallBack(void (*pFun)(void));
#endif

#endif /* MCAL_UART_UART_INTERFACE_H_ */

/*******************************************************************************
 *  END OF FILE: uart_interface.h
 ******************************************************************************/
