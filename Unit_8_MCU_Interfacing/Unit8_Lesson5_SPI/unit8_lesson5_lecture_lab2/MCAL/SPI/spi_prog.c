/*******************************************************************************
 * spi_prog.c
 *
 *  Created on: Apr 10, 2023
 *      Author: Abanoub Salah
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "spi_config.h"
#include "spi_interface.h"
#include "spi_private.h"

static void (*interruptCallBack[SPI_PERIPHERALS_COUNT])(void) = {NULL};

void MCAL_SPI_Void_Init(SPI_Config_t *configStruct)
{
	uint16_t cr1Tmp = 0x00;
	uint16_t cr2Tmp = 0x00;

	/* Initiating GPIO and enabling clock are done on main */

	/* Enable SPI */
	SET_BIT(cr1Tmp, SPI_CR1_SPE_BIT);

	/* Master/Slave mode */
	if((SPI_MasterSelection_Slave == configStruct->masterSelection) || (SPI_MasterSelection_Master == configStruct->masterSelection))
	{
		cr1Tmp |= configStruct->masterSelection;
	}
	else
	{
		configStruct->status = SPI_Status_Error;
	}

	/* Communication mode */
	switch(configStruct->communicationMode)
	{
		case SPI_CommunicationMode_2line_unidirectionalTxRx:
		case SPI_CommunicationMode_2line_unidirectionalRx:
		case SPI_CommunicationMode_1line_bidirectionalRx:
		case SPI_CommunicationMode_1line_bidirectionalTx:
			cr1Tmp |= configStruct->communicationMode;
			break;
		default:
			configStruct->status = SPI_Status_Error;
			break;
	}

	/* Frame format */
	if((SPI_FrameFormat_MSB_First == configStruct->frameFormat) || (SPI_FrameFormat_LSB_First == configStruct->frameFormat))
	{
		cr1Tmp |= configStruct->frameFormat;
	}
	else
	{
		configStruct->status = SPI_Status_Error;
	}

	/* Data frame format */
	if((SPI_DataFrameFormat_8Bit == configStruct->dataFrameFormat) || (SPI_DataFrameFormat_16Bit == configStruct->dataFrameFormat))
	{
		cr1Tmp |= configStruct->dataFrameFormat;
	}
	else
	{
		configStruct->status = SPI_Status_Error;
	}

	/* Clock polarity */
	if((SPI_ClockPolarity_Idle_High == configStruct->clockPolarity) || (SPI_ClockPolarity_Idle_Low == configStruct->clockPolarity))
	{
		cr1Tmp |= configStruct->clockPolarity;
	}
	else
	{
		configStruct->status = SPI_Status_Error;
	}

	/* Clock phase */
	if((SPI_ClockPhase_Sample_Leading_setup_trailing == configStruct->clockPhase) || (SPI_ClockPhase_setup_Leading_sample_trailing == configStruct->clockPhase))
	{
		cr1Tmp |= configStruct->clockPhase;
	}
	else
	{
		configStruct->status = SPI_Status_Error;
	}

	/* NSS management */
	if((SPI_NSS_SlaveHardware == configStruct->NSS) || (SPI_NSS_SoftwareSSIReset == configStruct->NSS) || (SPI_NSS_SoftwareSSISet == configStruct->NSS))
	{
		cr1Tmp |= configStruct->NSS;
	}
	else if((SPI_NSS_MasterHardwareOutputDisable == configStruct->NSS) || (SPI_NSS_MasterHardwareOutputEnable == configStruct->NSS))
	{
		cr2Tmp |= configStruct->NSS;
	}
	else
	{
		configStruct->status = SPI_Status_Error;
	}

	/* Baud rate */
	switch(configStruct->clockPreScaler)
	{
		case SPI_Prescaler_2:
		case SPI_Prescaler_4:
		case SPI_Prescaler_8:
		case SPI_Prescaler_16:
		case SPI_Prescaler_32:
		case SPI_Prescaler_64:
		case SPI_Prescaler_128:
		case SPI_Prescaler_256:
			cr1Tmp |= configStruct->clockPreScaler;
			break;
		default:
			configStruct->status = SPI_Status_Error;
			break;
	}

	/* Interrupts enable */
	if(SPI_IRQEnable_NONE != configStruct->IRQ_Enable)
	{
		cr2Tmp |= configStruct->IRQ_Enable;

		if(SPI1 == configStruct->SPIx)
		{
			interruptCallBack[0] = configStruct->pIRQCallBack;
		}
		else if(SPI2 == configStruct->SPIx)
		{
			interruptCallBack[1] = configStruct->pIRQCallBack;
		}
		else
		{
		}
	}
	else
	{
	}

	/* Write temporary registers for the configuration to take effect */
	configStruct->SPIx->CR2 = cr2Tmp;
	configStruct->SPIx->CR1 = cr1Tmp;

	return ;
}

void MCAL_SPI_Void_DeInit(SPI_Config_t *configStruct)
{
	configStruct->status = SPI_Status_Ok;

	if(SPI1 == configStruct->SPIx)
	{
		MCAL_RCC_Void_ResetPeripheral(RCC_BusName_APB2, RCC_APB2_Peripheral_RST_SPI1RST);
	}
	else if(SPI2 == configStruct->SPIx)
	{
		MCAL_RCC_Void_ResetPeripheral(RCC_BusName_APB1, RCC_APB1_Peripheral_RST_SPI2RST);
	}
	else
	{
		configStruct->status = SPI_Status_Error;
	}

	return ;
}

void MCAL_SPI_Void_Receive(SPI_Config_t *configStruct, uint16_t *pTxBuffer, SPI_Mechanism_et mechanism)
{
	if(SPI_Mechanism_Polling == mechanism)
	{
		/* Wait transmission complete */
		while(FALSE == (GET_BIT(configStruct->SPIx->SR, SPI_SR_RXNE_BIT)));
	}
	else
	{
	}

	*pTxBuffer = configStruct->SPIx->DR;
	configStruct->status = ((configStruct->SPIx->SR) & SPI_SR_ERROR_FLAGS_MASK);

	return ;
}

void MCAL_SPI_Void_Send(SPI_Config_t *configStruct, uint16_t *pTxBuffer, SPI_Mechanism_et mechanism)
{
	/* Write to SPI data register to start transmission */
	configStruct->SPIx->DR = *(pTxBuffer);

	if(SPI_Mechanism_Polling == mechanism)
	{
		/* Wait transmission complete */
		while(FALSE == (GET_BIT(configStruct->SPIx->SR, SPI_SR_TXE_BIT)));
	}
	else
	{
	}

	configStruct->status = ((configStruct->SPIx->SR) & SPI_SR_ERROR_FLAGS_MASK);

	return ;
}

void MCAL_SPI_Void_transceive(SPI_Config_t *configStruct, uint16_t *pTxBuffer, SPI_Mechanism_et mechanism)
{
	if(SPI_Mechanism_Polling == mechanism)
	{
		/* Wait transmission complete */
		while(FALSE == (GET_BIT(configStruct->SPIx->SR, SPI_SR_TXE_BIT)));
		configStruct->status = SPI_Status_Ok;
	}
	else
	{
	}

	/* Write to SPI data register to start transmission */
	configStruct->SPIx->DR = *pTxBuffer;

	if(SPI_Mechanism_Polling == mechanism)
	{
		/* Wait transmission complete */
		while(FALSE == (GET_BIT(configStruct->SPIx->SR, SPI_SR_RXNE_BIT)));
		configStruct->status = SPI_Status_Ok;
	}
	else
	{
	}

	*pTxBuffer = configStruct->SPIx->DR;
	configStruct->status = ((configStruct->SPIx->SR) & SPI_SR_ERROR_FLAGS_MASK);

	return ;
}

/*******************************************************************************
 * IRQ function
 ******************************************************************************/

void SPI1_IRQHandler(void)
{
	if(NULL != interruptCallBack[0])
	{
		interruptCallBack[0]();
	}
	else
	{
	}
}


void SPI2_IRQHandler(void)
{
		if(NULL != interruptCallBack[0])
		{
			interruptCallBack[0]();
		}
		else
		{
		}
}

/*******************************************************************************
 *  END OF FILE: spi_prog.c
 ******************************************************************************/
