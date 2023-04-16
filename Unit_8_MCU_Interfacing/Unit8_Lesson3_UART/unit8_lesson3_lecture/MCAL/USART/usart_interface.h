/*******************************************************************************
 * usart_interface.h
 *
 *  Created on: Apr 3, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

#ifndef MCAL_USART_USART_INTERFACE_H_
#define MCAL_USART_USART_INTERFACE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "stm32F103c6.h"
#include "platform_types.h"
#include "bit_math.h"
#include "gpio_interface.h"
#include "rcc_interface.h"

/*******************************************************************************
 * User define references macros
 ******************************************************************************/

/* @Ref USART_Mode */
typedef enum
{
	USART_Mode_RX = 0U,
	USART_Mode_TX = 1U,
	USART_Mode_TX_RX = 2U,
} USART_Mode_et;

/* @Ref USART_BaudRate */
typedef enum
{
	USART_BaudRate_2400 = 2400UL,
	USART_BaudRate_9600 = 9600UL,
	USART_BaudRate_19200 = 19200UL,
	USART_BaudRate_57600 =57600UL,
	USART_BaudRate_115200 = 115200UL,
	USART_BaudRate_230400 = 230400UL,
	USART_BaudRate_460800 = 460800UL,
	USART_BaudRate_921600 = 921600UL,
	USART_BaudRate_225000 = 2250000UL,
	USART_BaudRate_4500000 = 4500000UL,
} USART_BaudRate_et;

/* @Ref USART_PayloadLength */
typedef enum
{
	USART_PayloadLength_8B = 0U,
	USART_PayloadLength_9B = 1U,
} USART_PayloadLength_et;

/* @Ref USART_Parity */
typedef enum
{
	USART_Parity_Enable = 0U,
	USART_Parity_EVEN = 0U,
	USART_Parity_ODD = 1U,
	USART_Parity_Disable = 2U,
} USART_Parity_et;

/* @Ref USART_StopBits */
typedef enum
{
	USART_StopBits_1	= 0U,
	USART_StopBits_0_5 = 1U,
	USART_StopBits_2	= 2U,
	USART_StopBits_1_5 = 3U,
} USART_StopBits_et;

/* @Ref USART_HWFlowControl */
typedef enum
{
	USART_HWFlowControl_NONE = 0U,
	USART_HWFlowControl_RTS	= 1U,
	USART_HWFlowControl_CTS	= 2U,
	USART_HWFlowControl_RTS_CTS	= 3U,
} USART_HWFlowControl_et;

/* @Ref USART_IRQEnable */
typedef enum
{
	USART_IRQEnable_NONE = 0x0000UL,
	USART_IRQEnable_IDLE = 0x0010UL,
	USART_IRQEnable_RXNE = 0x0020UL,
	USART_IRQEnable_TC = 0x0040UL,
	USART_IRQEnable_TXE = 0x0080UL,
	USART_IRQEnable_PE = 0x0100UL,
} USART_IRQEnable_et;

/* @Ref USART_Mechanism */
typedef enum
{
	USART_Mechanism_Polling = 1U,
	USART_Mechanism_Interrupt = 0U,
} USART_Mechanism_et;

/* @ref USART_Status */
typedef enum
{
	USART_Status_Ok = 0U,
	USART_Status_Error,
} USART_Status_et;

/*******************************************************************************
 *   User type definitions (structures)
 ******************************************************************************/
typedef struct
{
	USART_TypeDef_t *USARTx;				/* Specifies USARTx peripheral where x = 1, 2 or 3 */
	USART_Mode_et USARTMode;				/* Enable/Disable TX or RX @Ref USART_Mode */
	USART_BaudRate_et BaudRate;				/* configure BaudRate @Ref USART_BaudRate */
	USART_PayloadLength_et payloadLength;	/* Specifies number of data bits in a frame @Ref USART_PayloadLength */
	USART_Parity_et Parity;					/* Specifies parity mode @Ref USART_Parity */
	USART_StopBits_et StopBits;				/* Specifies No. of stop bits @Ref USART_StopBits */
	USART_HWFlowControl_et HWFlowControl;	/* Specifies hardware flow control @Ref USART_HWFlowControl */
	uint32_t IRQEnable;						/* Enable/Disable interrupt @Ref USART_IRQEnable *flags can be combined  */
	void (*pIRQCallBack)(void);				/* Set callback function which will be called once the IRQ Happen */
	USART_Status_et status;					/* USART last operation status @ref USART_Status */
} USART_Config_t;

/*******************************************************************************
 * APIs Supported by "MCAL USART DRIVER"
 ******************************************************************************/

/*******************************************************************************
 * Fn				- MCAL_USART_Void_Init
 *
 * brief			- Initialize USART Asynchronous only
 *
 * param [in] 		- USART configuration structure
 *
 * retval 			- none
 *
 * Note				- Only support Asynchronous mode
 ******************************************************************************/
void MCAL_USART_Void_Init(USART_Config_t *);

/*******************************************************************************
* Fn                - MCAL_USART_Void_DeInit
*
* Brief             - DeInit USART
*
 * param [in] 		- USART configuration structure
*
* Retval            - None
*
* Note              - None
*******************************************************************************/
void MCAL_USART_Void_DeInit(USART_Config_t *);

/*******************************************************************************
 * Fn                - MCAL_USART_Void_Send
 *
 * Brief             - Send data through USART
 *
 * param [in] 		 - USART configuration structure
 *
 * param [in] 		 - Pointer to send data buffer
 *
 * Param [in]        - Mechanism for sending  @Ref USART_Mechanism
 *
 * Retval            - None
 *
 * Note              - None
 ******************************************************************************/
void MCAL_USART_Void_Send(USART_Config_t *, uint16_t *, USART_Mechanism_et);

/*******************************************************************************
 * Fn                - MCAL_USART_Void_Send
 *
 * Brief             - Send a string through USART
 *
 * param [in] 		 - USART configuration structure
 *
 * Param [in]        - Pointer to a string to be sent through
 *
 * Param [in]        - Mechanism for sending @Ref USART_Mechanism
 *
 * Retval            - None
 *
 * Note              - None
 ******************************************************************************/
void MCAL_USART_Void_SendString(USART_Config_t *, uint8_t *, USART_Mechanism_et);

/*******************************************************************************
 * Fn                - MCAL_USART_Void_Receive
 *
 * Brief             - Receive data through USART
 *
 * param [in] 		 - USART configuration structure
 *
 * param [in] 		 - Pointer to receive data buffer
 *
 * Param [in]        - Mechanism for receiving  @Ref USART_Mechanism
 *
 * Retval            - None
 *
 * Note              - None
 ******************************************************************************/
void MCAL_USART_Void_Receive(USART_Config_t *, uint16_t *, USART_Mechanism_et);

#endif /* MCAL_USART_USART_INTERFACE_H_ */

/******************************************************************************
 *  END OF FILE: usart_interface.h
 ******************************************************************************/
