/*******************************************************************************
 * uart_prog.c
 *
 *  Created on: Apr 2, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "uart_config.h"
#include "uart_interface.h"
#include "uart_private.h"

void (*pTxCompleteCallBack)(void) = NULL;
void (*pRxCompleteCallBack)(void) = NULL;

void MCAL_UART_Void_Init(void)
{
	uint8_t tmpUCSRCValue = 0;
	GPIO_PinConfig_t PinConfig;

	/* Read UCSRC value to be modified and written-back later */
	tmpUCSRCValue = UART->UBRRH_UCSRC;
	tmpUCSRCValue = UART->UBRRH_UCSRC;

    /* Tx pin */
    PinConfig.GPIO_PinNumber = UART_TX_PIN;
    PinConfig.GPIO_Mode = GPIO_MODE_OUTPUT;
    MCAL_GPIO_Init(UART_TX_PORT, &PinConfig);

    /* Rx pin */
	PinConfig.GPIO_PinNumber = UART_RX_PIN;
	PinConfig.GPIO_Mode = GPIO_MODE_INPUT_PU;
	MCAL_GPIO_Init(UART_RX_PORT, &PinConfig);

	/* Baud rate */
	/* Calculate BaudRate */
	uint32_t baudRate = (((F_OSC * 1000000UL) / (16UL * UART_BAUD_RATE)) - 1);

	/* Set URSEL bit to 0 to write to UBRRH */
	baudRate &= ~(1 << (URSEL_BIT + 8));

	/* Lower byte */
	UART->UBRRL = ((uint8_t) (baudRate & 0x00FF));
	/* Higher byte */
	UART->UBRRH_UCSRC = ((uint8_t) (baudRate >> 8));

	/* Parity bit */
#if   UART_PARITY_MODE   ==   DISABLE_PARITY
	CLR_BIT(tmpUCSRCValue, UPM0_BIT);
	CLR_BIT(tmpUCSRCValue, UPM1_BIT);
#elif UART_PARITY_MODE   ==   EVEN_PARITY
	CLR_BIT(tmpUCSRCValue, UPM0_BIT);
	SET_BIT(tmpUCSRCValue, UPM1_BIT);
#elif UART_PARITY_MODE   ==   PARITY_ODD
	SET_BIT(tmpUCSRCValue, UPM0_BIT);
	SET_BIT(tmpUCSRCValue, UPM1_BIT);
#else
	#error Configuration Error: Wrong parity mode
#endif

	/* Stop bit */
#if   UART_STOP_BIT   ==   1
	CLR_BIT(tmpUCSRCValue, USBS_BIT);
#elif UART_STOP_BIT   ==   2
	SET_BIT(tmpUCSRCValue, USBS_BIT);
#else
	#error Configuration Error: Wrong stop bit(s) value
#endif

	SET_BIT(tmpUCSRCValue, URSEL_BIT);

	/* Data size */
#if UART_DATA_BITS == 5
	CLR_BIT(UART->UCSRB, UCSZ2_BIT);
	CLR_BIT(tmpUCSRCValue, UCSZ1_BIT);
	CLR_BIT(tmpUCSRCValue, UCSZ0_BIT);
#elif UART_DATA_BITS == 6
	CLR_BIT(UART->UCSRB, UCSZ2_BIT);
	CLR_BIT(tmpUCSRCValue, UCSZ1_BIT);
	SET_BIT(tmpUCSRCValue, UCSZ0_BIT);
#elif UART_DATA_BITS == 7
	CLR_BIT(UART->UCSRB, UCSZ2_BIT);
	SET_BIT(tmpUCSRCValue, UCSZ1_BIT);
	CLR_BIT(tmpUCSRCValue, UCSZ0_BIT);
#elif UART_DATA_BITS == 8
	CLR_BIT(UART->UCSRB, UCSZ2_BIT);
	SET_BIT(tmpUCSRCValue, UCSZ1_BIT);
	SET_BIT(tmpUCSRCValue, UCSZ0_BIT);
#elif UART_DATA_BITS == 9
	SET_BIT(UART->UCSRB, UCSZ2_BIT);
	SET_BIT(tmpUCSRCValue, UCSZ1_BIT);
	SET_BIT(tmpUCSRCValue, UCSZ0_BIT);
#else
	#error Configuration Error: Wrong data bits size
#endif

	/* Write-back USCRC register  */
	UART->UBRRH_UCSRC = tmpUCSRCValue;

	/* Enable rx/tx */
#if UART_TX_RX_ENABLE == RX_ENABLE
	/* Enable RX */
	SET_BIT(UART->UCSRB, RXEN_BIT);

	/* Disable TX */
	CLR_BIT(UART->UCSRB, TXEN_BIT);
#elif UART_TX_RX_ENABLE == TX_ENABLE
	/* Disable RX */
	CLR_BIT(UART->UCSRB, RXEN_BIT);

	/* Enable TX */
	SET_BIT(UART->UCSRB, TXEN_BIT);
#elif UART_TX_RX_ENABLE == TX_RX_ENABLE
	/* Enable RX */
	SET_BIT(UART->UCSRB, RXEN_BIT);

	/* Enable TX */
	SET_BIT(UART->UCSRB, TXEN_BIT);
#elif UART_TX_RX_ENABLE == TX_RX_DISABLE
	/* Disable RX */
	CLR_BIT(UART->UCSRB, RXEN_BIT);

	/* Disable TX */
	CLR_BIT(UART->UCSRB, TXEN_BIT);
#else
	#error Configuration Error: Wrong data bits size
#endif

	/* Configure interrupt flags */
#if UART_IRQ_ENABLE == IRQ_DIASABLE
	CLR_BIT(UART->UCSRB, RXCIE_BIT);
	CLR_BIT(UART->UCSRB, TXCIE_BIT);
#elif UART_IRQ_ENABLE == RXCIE_IRQ
	SET_BIT(UART->UCSRB, RXCIE_BIT);
	CLR_BIT(UART->UCSRB, TXCIE_BIT);
#elif UART_IRQ_ENABLE == TXCIE_IRQ
	CLR_BIT(UART->UCSRB, RXCIE_BIT);
	SET_BIT(UART->UCSRB, TXCIE_BIT);
#elif UART_IRQ_ENABLE == RXCIE_TXCIE_IRQ
	SET_BIT(UART->UCSRB, RXCIE_BIT);
	SET_BIT(UART->UCSRB, TXCIE_BIT);
#else
	#error Configuration Error: Wrong interrupt enable option
#endif

	return ;
}

void MCAL_UART_Void_Send(uint16_t data)
{
#if (UART_IRQ_ENABLE != TXCIE_IRQ) && (UART_IRQ_ENABLE != RXCIE_TXCIE_IRQ)
	/* Wait for data register empty flag */
	while(GPIO_PIN_RESET == GET_BIT(UART->UCSRA, UDRE_BIT));
#endif

	UART->UDR = ((uint8_t) (data & 0x00FF));

#if UART_DATA_BITS == 9
	/* Reset/Set the 9th bit to TXB8 */
	UART->UCSRB &= ~(1 << TXB8_BIT);

	if(GPIO_PIN_SET == ((data >> 8) & 1))
	{
		UART->UCSRB |= (1 << TXB8_BIT);
	}
	else
	{
	}

#endif
#if (UART_IRQ_ENABLE != TXCIE_IRQ) && (UART_IRQ_ENABLE != RXCIE_TXCIE_IRQ)
	/* Wait for tx complete flag */
	while(GPIO_PIN_RESET == GET_BIT(UART->UCSRA, TXC_BIT));

	/* Clear transmit complete flag by writing 1 */
	SET_BIT(UART->UCSRA, TXC_BIT);
#endif

	return ;
}

void MCAL_UART_Void_SendString(uint8_t *pStr)
{
	/* Loop over the string sending one by one until reaching null */
	while(NUL != (*pStr))
	{
		MCAL_UART_Void_Send(*pStr);
		++pStr;
	}

	return ;
}

uint16_t MCAL_UART_U16_Receive(void)
{
	uint16_t result = 0x0000;
#if (UART_IRQ_ENABLE != RXCIE_IRQ) && (UART_IRQ_ENABLE != RXCIE_TXCIE_IRQ)
	/* wait for rx complete flag */
	while(GPIO_PIN_RESET == GET_BIT(UART->UCSRA, RXC_BIT));
#endif
#if UART_DATA_BITS == 9
	/* Read the 8th bit first */
	result = (((uint16) GET_BIT(UART->UCSRB, RXB8_BIT)) << 8);
#endif

	result |= UART->UDR;

	return result;
}

/*******************************************************************************
 * Fn                -MCAL_UART_Void_SetTxCCallBack
 *
 * Brief             -Set TXC callback function
 *
 * Param [in]        -pFun: Pointer to a function
 *
 * Retval            -None
 *
 * Note              -None
 ******************************************************************************/
#if (UART_IRQ_ENABLE == TXCIE_IRQ) || (UART_IRQ_ENABLE == RXCIE_TXCIE_IRQ)
void MCAL_UART_Void_SetTxCCallBack(void (*pFun)(void))
{
	pTxCompleteCallBack = pFun;

	return ;
}

ISR(USART_TXC_vect)
{
	if(NULL != pTxCompleteCallBack)
	{
		pTxCompleteCallBack();
	}
	else
	{
	}
}

#endif

/*******************************************************************************
 * Fn                -MCAL_UART_Void_SetRxCCallBack
 *
 * Brief             -Set RXC callback function
 *
 * Param [in]        -pFun: Pointer to a function
 *
 * Retval            -None
 *
 * Note              -None
 ******************************************************************************/
#if (UART_IRQ_ENABLE == RXCIE_IRQ) || (UART_IRQ_ENABLE == RXCIE_TXCIE_IRQ)
void MCAL_UART_Void_SetRxCCallBack(void (*pFun)(void))
{
	pRxCompleteCallBack = pFun;

	return ;
}

ISR(USART_RXC_vect)

{
	if(NULL != pRxCompleteCallBack)
	{
		pRxCompleteCallBack();
	}
	else
	{
	}
}

#endif

/******************************************************************************
 *  END OF FILE: uart_prog.c
 ******************************************************************************/
