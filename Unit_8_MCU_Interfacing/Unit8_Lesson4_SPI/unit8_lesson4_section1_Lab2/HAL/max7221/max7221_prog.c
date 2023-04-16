/*******************************************************************************
 * MAX7221_prog.c
 *
 *  Created on: Apr 9, 2023
 *      Author: Abanoub Salah
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "max7221_config.h"
#include "max7221_interface.h"
#include "max7221_private.h"

void HAL_MAX7221_Void_Execute(SPI_Config_t *configSPI, MAX7221_Command_et command, uint8_t data)
{
	uint8_t dummyBuffer;

	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
	MCAL_SPI_Void_transceive(configSPI, &command, &dummyBuffer);
	MCAL_SPI_Void_transceive(configSPI, &data, &dummyBuffer);
	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);

	return ;
}

/******************************************************************************
 *  END OF FILE: max7221_prog.c
 ******************************************************************************/
