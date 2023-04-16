/*******************************************************************************
 * spi_prog.c
 *
 *  Created on: Apr 11, 2023
 *      Author: Abanoub Salah
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "spi_config.h"
#include "spi_interface.h"
#include "spi_private.h"

static void (*txCompleteCallBack)(void) = NULL;

void MCAL_SPI_Void_Init(SPI_Config_t *configStruct)
{
	SPI_Status_et result = SPI_Status_Ok;
	GPIO_PinConfig_t pinConfig;
	uint8_t spcrTmp = 0x00;

	/* GPIO pins configuration */
	if(SPI_Master_Slave_Select_Master == configStruct->modeSelect)
	{
		/* SS pin as o/p */
		pinConfig.GPIO_PinNumber = SPI_SS_PIN;
		pinConfig.GPIO_Mode = GPIO_MODE_OUTPUT;
		MCAL_GPIO_Init(SPI_SS_PORT, &pinConfig);

		/* MOSI pin as o/p */
		pinConfig.GPIO_PinNumber = SPI_MOSI_PIN;
		MCAL_GPIO_Init(SPI_MOSI_PORT, &pinConfig);

		/* SCK pin as o/p */
		pinConfig.GPIO_PinNumber = SPI_SCK_PIN;
		MCAL_GPIO_Init(SPI_SCK_PORT, &pinConfig);

		/* MISO pin as high-z i/p */
		pinConfig.GPIO_PinNumber = SPI_MISO_PIN;
		pinConfig.GPIO_Mode = GPIO_MODE_INPUT_HIGHZ;
		MCAL_GPIO_Init(SPI_MISO_PORT, &pinConfig);
	}
	else if(SPI_Master_Slave_Select_Slave == configStruct->modeSelect)
	{
		/* SS pin as high-z i/p */
		pinConfig.GPIO_PinNumber = SPI_SS_PIN;
		pinConfig.GPIO_Mode = GPIO_MODE_INPUT_HIGHZ;
		MCAL_GPIO_Init(SPI_SS_PORT, &pinConfig);

		/* MOSI pin as high-z i/p */
		pinConfig.GPIO_PinNumber = SPI_MOSI_PIN;
		MCAL_GPIO_Init(SPI_MOSI_PORT, &pinConfig);

		/* SCK pin as high-z i/p */
		pinConfig.GPIO_PinNumber = SPI_SCK_PIN;
		MCAL_GPIO_Init(SPI_SCK_PORT, &pinConfig);

		/* MISO pin as o/p */
		pinConfig.GPIO_PinNumber = SPI_MISO_PIN;
		pinConfig.GPIO_Mode = GPIO_MODE_OUTPUT;
		MCAL_GPIO_Init(SPI_MISO_PORT, &pinConfig);
	}
	else
	{
		result |= SPI_Status_Error;
	}

	/* SPI interrupt enabling */
	if(SPI_Interrupt_Disable == configStruct->interruptEnable)
	{
		CLR_BIT(spcrTmp, SPI_SPCR_SPIE);
	}
	else if(SPI_Interrupt_Enable == configStruct->interruptEnable)
	{
		SET_BIT(spcrTmp, SPI_SPCR_SPIE);
		txCompleteCallBack = configStruct->interruptCallBack;
	}
	else
	{
		result |= SPI_Status_Error;
	}

	/* SPI data order */
	if(SPI_DataOrder_MSB_First == configStruct->dataOrder)
	{
		CLR_BIT(spcrTmp, SPI_SPCR_DORD);
	}
	else if(SPI_DataOrder_LSB_First == configStruct->dataOrder)
	{
		SET_BIT(spcrTmp, SPI_SPCR_DORD);
	}
	else
	{
		result |= SPI_Status_Error;
	}

	/* SPI master/slave select */
	if(SPI_Master_Slave_Select_Slave == configStruct->modeSelect)
	{
		CLR_BIT(spcrTmp, SPI_SPCR_MSTR);
	}
	else if(SPI_Master_Slave_Select_Master == configStruct->modeSelect)
	{
		SET_BIT(spcrTmp, SPI_SPCR_MSTR);
	}
	else
	{
			result |= SPI_Status_Error;
	}

	/* SPI clock polarity select */
	if(SPI_ClockPolarity_Idle_Low == configStruct->clockPolarity)
	{
		CLR_BIT(spcrTmp, SPI_SPCR_CPOL);
	}
	else if(SPI_ClockPolarity_Idle_High == configStruct->clockPolarity)
	{
		SET_BIT(spcrTmp, SPI_SPCR_CPOL);
	}
	else
	{
		result |= SPI_Status_Error;
	}

	/* SPI clock phase select */
	if(SPI_ClockPhase_Sample_Leading_setup_trailing == configStruct->clockPhase)
	{
		CLR_BIT(spcrTmp, SPI_SPCR_CPHA);
	}
	else if(SPI_ClockPhase_setup_Leading_sample_trailing == configStruct->clockPhase)
	{
		SET_BIT(spcrTmp, SPI_SPCR_CPHA);
	}
	else
	{
		result |= SPI_Status_Error;
	}

	/* SPI clock rate select */
	switch(configStruct->clockRate)
	{
		/* Falling through */
		case SPI_ClockRate_4:
		case SPI_ClockRate_16:
		case SPI_ClockRate_64:
		case SPI_ClockRate_128:
			spcrTmp |= ((configStruct->clockRate) << SPI_SPCR_SPR0);
		default:
			result |= SPI_Status_Error;
			break;
	}

	/* SPI double speed select */
	if(SPI_DoubleSpeed_Disable == configStruct->doubleSpeed)
	{
		CLR_BIT(spcrTmp, SPI_SPSR_SPI2X);
	}
	else if(SPI_DoubleSpeed_Enable == configStruct->doubleSpeed)
	{
		SET_BIT(spcrTmp, SPI_SPSR_SPI2X);
	}
	else
	{
		result |= SPI_Status_Error;
	}

	/* SPI peripheral enable */
	SET_BIT(spcrTmp, SPI_SPCR_SPE);
	SPI->SPCR = spcrTmp;

	configStruct->status = result;

	return ;
}

void MCAL_SPI_Void_transceive(SPI_Config_t *configStruct, uint8_t *transmitted, uint8_t *received)
{
	/* Get data register in case that interrupt is enabled and user tries */
	/* to read the data */
	*received = SPI->SPDR;

	/* Put data in data register to be exchanged */
	SPI->SPDR = *transmitted;

	if(SPI_Interrupt_Disable == configStruct->interruptEnable)
	{
		/* Wait for transmission complete */
		while(FALSE == GET_BIT(SPI->SPSR, SPI_SPSR_SPIF));
		*received = SPI->SPDR;
		configStruct->status = SPI_Status_Ok;
	}
	else
	{
		configStruct->status = SPI_Status_WaitingOnInterrupt;
	}

	if(TRUE == GET_BIT(SPI->SPSR, SPI_SPSR_WCOL))
	{
		configStruct->status = SPI_Status_WriteCollision;
	}
	else
	{
	}

	return ;
}

void MCAL_SPI_Void_SetCallBackFunction(void (*pCallBackFunction)(void))
{
	txCompleteCallBack = pCallBackFunction;

	return;
}

ISR(SPI_STC_vect)
{
	if(NULL != txCompleteCallBack)
	{
		txCompleteCallBack();
	}
	else
	{
	}
}

/*******************************************************************************
 *  END OF FILE: spi_prog.c
 ******************************************************************************/
