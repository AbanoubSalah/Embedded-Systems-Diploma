/*******************************************************************************
 * usart_prog.c
 *
 *  Created on: Apr 3, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "usart_config.h"
#include "usart_interface.h"
#include "usart_private.h"

static volatile void (*pCallBackArray[USART_PERIPHERALS_COUNT])(void) = {NULL};

void MCAL_USART_Void_Init(USART_Config_t *configStruct)
{
	uint16_t cr1Tmp = 0x0000;
	uint16_t usartDiv = 1;
	uint32_t curBusClock = 1;

	/* Enable clock/interrupt for peripheral initiation main */

	/* Enable USART */
	SET_BIT(cr1Tmp, USART_CR1_UE);

	/* Enable USART TX/RX mode */
	switch(configStruct->USARTMode)
	{
		case USART_Mode_RX:
			SET_BIT(cr1Tmp, USART_CR1_RE);
			CLR_BIT(cr1Tmp, USART_CR1_TE);
			break;
		case USART_Mode_TX:
			CLR_BIT(cr1Tmp, USART_CR1_RE);
			SET_BIT(cr1Tmp, USART_CR1_TE);
			break;
		case USART_Mode_TX_RX:
			SET_BIT(cr1Tmp, USART_CR1_RE);
			SET_BIT(cr1Tmp, USART_CR1_TE);
			break;
		default:
			configStruct->status = USART_Status_Error;
			return ;
			break;
		}

	/*  Set payload Length */
	if(USART_PayloadLength_9B == configStruct->payloadLength)
	{
		SET_BIT(cr1Tmp, USART_CR1_M);
	}
	else if(USART_PayloadLength_8B == configStruct->payloadLength)
	{
		CLR_BIT(cr1Tmp, USART_CR1_M);
	}
	else
	{
		configStruct->status = USART_Status_Error;
		return ;
	}

	/* Set parity-bit control */
	switch(configStruct->Parity)
	{
		/* For enable/odd/even the case should fall through */
		/* enabling the parity and select parity accordingly */
		case USART_Parity_ODD:
		case USART_Parity_EVEN:
			SET_BIT(cr1Tmp, USART_CR1_PCE);
			if(USART_Parity_ODD == configStruct->Parity)
			{
				SET_BIT(cr1Tmp, USART_CR1_PS);
			}
			else
			{
				CLR_BIT(cr1Tmp, USART_CR1_M);
			}
			break;
		case USART_Parity_Disable:
			CLR_BIT(cr1Tmp, USART_CR1_PCE);
			break;
		default:
			configStruct->status = USART_Status_Error;
			return ;
			break;
	}

	/* Set number of stop bit(s) */
	switch(configStruct->StopBits)
	{
		case USART_StopBits_1:
		case USART_StopBits_0_5:
		case USART_StopBits_2:
		case USART_StopBits_1_5:
			configStruct->USARTx->CR2 &= ~(0b11 << USART_CR2_STOP);
			configStruct->USARTx->CR2 |= (configStruct->StopBits << USART_CR2_STOP);
			break;
		default:
			configStruct->status = USART_Status_Error;
			return ;
			break;
	}

	/* Set hardware flow control */
	switch(configStruct->HWFlowControl)
	{
		case USART_HWFlowControl_NONE:
			CLR_BIT(configStruct->USARTx->CR3, USART_CR3_CTSE);
			CLR_BIT(configStruct->USARTx->CR3, USART_CR3_RTSE);
			break;
		case USART_HWFlowControl_CTS:
			SET_BIT(configStruct->USARTx->CR3, USART_CR3_CTSE);
			CLR_BIT(configStruct->USARTx->CR3, USART_CR3_RTSE);
			break;
		case USART_HWFlowControl_RTS:
			CLR_BIT(configStruct->USARTx->CR3, USART_CR3_CTSE);
			SET_BIT(configStruct->USARTx->CR3, USART_CR3_RTSE);
			break;
		case USART_HWFlowControl_RTS_CTS:
			SET_BIT(configStruct->USARTx->CR3, USART_CR3_CTSE);
			SET_BIT(configStruct->USARTx->CR3, USART_CR3_RTSE);
			break;
		default:
			configStruct->status = USART_Status_Error;
			return ;
			break;
		}

	/* Calculate and set baud rate */
	if(USART1 == configStruct->USARTx)
	{
		curBusClock = MCAL_RCC_U32_GetBusFrequency(RCC_BusName_APB2);
	}
	else
	{
		curBusClock = MCAL_RCC_U32_GetBusFrequency(RCC_BusName_APB1);
	}

	/* Divide bus clock by baud rate to get the pre-scaler then by 16
	 * to get the integer part to get the fraction use modulo 16 then or-ing
	 * them together with their corresponding place in the register */
	usartDiv = curBusClock / configStruct->BaudRate;
	configStruct->USARTx->BRR = (((usartDiv >> 4) << USART_BRR_DIV_Mantissa) |	((usartDiv % 16) << USART_BRR_DIV_Fraction));

	/* Enable/Disable Interrupt */
	if(configStruct->IRQEnable != USART_IRQEnable_NONE)
	{
		cr1Tmp |= configStruct->IRQEnable;

		/* Set the pointer to callback function */
		if(USART1 == configStruct->USARTx)
		{
			pCallBackArray[0] = configStruct->pIRQCallBack;
		}
		else if(USART2 == configStruct->USARTx)
		{
			pCallBackArray[1] = configStruct->pIRQCallBack;
		}
		else if(USART3 == configStruct->USARTx)
		{
			pCallBackArray[2] = configStruct->pIRQCallBack;
		}
		else
		{
			configStruct->status = USART_Status_Error;
			return ;
		}
	}
	else
	{
	}

	configStruct->USARTx->CR1 = cr1Tmp;
	configStruct->status = USART_Status_Ok;

	return ;
}


void MCAL_USART_Void_DeInit(USART_Config_t *configStruct)
{
	if(USART1 == configStruct->USARTx)
	{
		MCAL_RCC_Void_ResetPeripheral(RCC_BusName_APB2, RCC_APB2_Peripheral_RST_USART1RST);
	}
	else if(USART2 == configStruct->USARTx)
	{
		MCAL_RCC_Void_ResetPeripheral(RCC_BusName_APB1, RCC_APB1_Peripheral_RST_USART2RST);
	}
	else if(USART3 == configStruct->USARTx)
	{
		MCAL_RCC_Void_ResetPeripheral(RCC_BusName_APB1, RCC_APB1_Peripheral_RST_USART3RST);
	}
	else
	{
		configStruct->status = USART_Status_Error;
		return ;
	}

	configStruct->status = USART_Status_Ok;

	return ;
}


void MCAL_USART_Void_Send(USART_Config_t *configStruct, uint16_t *pTxBuffer, USART_Mechanism_et mechanism)
{
	if((USART1 != configStruct->USARTx) && (USART2 != configStruct->USARTx) && (USART3 != configStruct->USARTx))
	{
		configStruct->status = USART_Status_Error;
		return ;
	}
	else
	{
	}

	/*  Wait until  Transmit data register is empty */
	if(USART_Mechanism_Polling == mechanism)
	{
		while(FALSE == GET_BIT(configStruct->USARTx->SR, USART_SR_TXE));
	}
	else
	{
	}

	/* Check the USART_WordLength item for 9-bit or 8-bit in a frame */
	switch(GET_BIT(configStruct->USARTx->CR1, USART_CR1_M))
	{
		case USART_PayloadLength_8B:
			configStruct->USARTx->DR = ((uint8_t)((*pTxBuffer) & 0xFF));
			break;
		case USART_PayloadLength_9B:
			configStruct->USARTx->DR = ((uint16_t)((*pTxBuffer) & 0x1FF));
			break;
		default:
			break;
	}

	configStruct->status = USART_Status_Ok;

	return ;
}

void MCAL_USART_Void_SendString(USART_Config_t *configStruct, uint8_t *pStr, USART_Mechanism_et mechanism)
{
	uint16_t tmpHold16;

	/* Loop over the string sending one by one until reaching null */
	while(USART_NUL_CHARACTER != (*pStr))
	{
		tmpHold16 = *pStr;
		MCAL_USART_Void_Send(configStruct, &tmpHold16, mechanism);
		if(USART_Status_Ok != configStruct->status)
		{
			configStruct->status = USART_Status_Error;
			return ;
		}
		else
		{
		}
		pStr++;
	}

	configStruct->status = USART_Status_Ok;

	return ;
}

void MCAL_USART_Void_Receive(USART_Config_t *configStruct, uint16_t *pRxBuffer, USART_Mechanism_et mechanism)
{
	if((USART1 != configStruct->USARTx) && (USART2 != configStruct->USARTx) && (USART3 != configStruct->USARTx))
	{
		configStruct->status = USART_Status_Error;
		return ;
	}
	else
	{
	}

	/* 1. Wait until Read data register not empty */
	if(USART_Mechanism_Polling == mechanism)
	{
		while(GPIO_PIN_RESET == GET_BIT(configStruct->USARTx->SR, USART_SR_RXNE));
	}
	else
	{
	}

	/* Check the USART_WordLength item for 9-bit or 8-bit in a frame */
	switch(GET_BIT(configStruct->USARTx->CR1, USART_CR1_M))
	{
		case USART_PayloadLength_8B:
			if(GPIO_PIN_RESET == GET_BIT(configStruct->USARTx->CR1, USART_CR1_PCE))
				*pRxBuffer = (configStruct->USARTx->DR & 0xFF);
			else
				*pRxBuffer = (configStruct->USARTx->DR & 0x7F);
			break;
		case USART_PayloadLength_9B:
			if(GPIO_PIN_RESET == GET_BIT(configStruct->USARTx->CR1, USART_CR1_PCE))
				*pRxBuffer = configStruct->USARTx->DR;
			else
				*pRxBuffer = (configStruct->USARTx->DR & 0xFF);
			break;
		default:
			configStruct->status = USART_Status_Error;
			return ;
			break;
	}

	configStruct->status = USART_Status_Ok;

	return ;
}

/*******************************************************************************
 * IRQ handlers
 ******************************************************************************/

void USART1_IRQHandler(void)
{
	if(NULL != pCallBackArray[0])
	{
		pCallBackArray[0]();
	}
	else
	{
		while(TRUE);
	}
}

void USART2_IRQHandler(void)
{
	if(NULL != pCallBackArray[1])
	{
		pCallBackArray[1]();
	}
	else
	{
		while(TRUE);
	}
}

void USART3_IRQHandler(void)
{
	if(NULL != pCallBackArray[2])
	{
		pCallBackArray[2]();
	}
	else
	{
		while(TRUE);
	}
}

/******************************************************************************
 *  END OF FILE: usart_prog.c
 ******************************************************************************/
