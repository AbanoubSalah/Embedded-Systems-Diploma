/*******************************************************************************
 * eeprom_prog.c
 *
 *  Created on: Apr 10, 2023
 *      Author: Abanoub Salah
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "eeprom_config.h"
#include "eeprom_interface.h"
#include "eeprom_private.h"


void HAL_EEPROM_Void_Init(void)
{
	/* All I2C initializations are done in main  */

	return ;
}

uint8_t HAL_EEPROM_U8_WriteNBytes(I2C_Config_t *configStruct, uint32_t memoryAddress, uint8_t *pData, uint32_t dataLength)
{
	uint32_t i = 0;

	uint8_t buffer[256];

	/* Address high byte */
	buffer[0] = (uint8_t)(memoryAddress >> 8);
	/* Address low byte */
	buffer[1] = (uint8_t)(memoryAddress);

	for(i = 2; i < (dataLength + 2); i++)
	{
		buffer[i]= pData[i-2];
	}

	MCAL_I2C_Void_MasterTx(configStruct, EEPROM_ADDRESS, buffer, (dataLength + 2), I2C_StopCondition_Enable, I2C_StartCondition_Enable);

	return 0;
}

uint8_t HAL_EEPROM_U8_ReadNBytes(I2C_Config_t *configStruct, uint32_t memoryAddress, uint8_t *pData, uint32_t dataLength)
{
	uint8_t buffer[2];

	/* Address high byte */
	buffer[0] = (uint8_t)(memoryAddress >> 8);
	/* Address low byte */
	buffer[1] = (uint8_t)(memoryAddress);

	MCAL_I2C_Void_MasterTx(configStruct, EEPROM_ADDRESS, buffer, 2, I2C_StopCondition_Disable, I2C_StartCondition_Enable);
	MCAL_I2C_Void_MasterRx(configStruct, EEPROM_ADDRESS, pData, dataLength, I2C_StopCondition_Enable, I2C_StartCondition_Repeated);

	return 0;
}

/*******************************************************************************
 *  END OF FILE: eeprom_prog.c
 ******************************************************************************/
