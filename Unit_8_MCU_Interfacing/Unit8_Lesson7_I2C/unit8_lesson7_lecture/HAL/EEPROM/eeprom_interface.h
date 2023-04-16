/*******************************************************************************
 * eeprom_interface.h
 *
 *  Created on: Apr 13, 2023
 *      Author: Abanoub Salah
 ******************************************************************************/

#ifndef HAL_EEPROM_EEPROM_INTERFACE_H_
#define HAL_EEPROM_EEPROM_INTERFACE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "platform_types.h"
#include "bit_math.h"
#include "i2c_interface.h"

/*******************************************************************************
 * APIs Supported by "HAL EEPROM driver"
 ******************************************************************************/

/*******************************************************************************
* Fn                - HAL_EEPROM_Void_Init
*
* Brief             - Initialize EEPROM
*
* Param [in]        - None
*
* Retval            - None
*
* Note              - Initializations are expected to be done in main
*******************************************************************************/
void HAL_EEPROM_Void_Init(void);

/*******************************************************************************
* Fn                - HAL_EEPROM_U8_WriteNBytes
*
* Brief             - Write n-bytes to EEPROM provided address
*
* Param [in]        - I2C configuration structure
*
* Param [in]        - EEPROM address to write to
*
* Param [in]        - Pointer to data to be written
*
* Param [in]        - Length of data
*
* Retval            - None
*
* Note              - None
*******************************************************************************/
uint8_t HAL_EEPROM_U8_WriteNBytes(I2C_Config_t *, uint32_t, uint8_t *, uint32_t);

/*******************************************************************************
* Fn                - HAL_EEPROM_U8_ReadNBytes
*
* Brief             - Read n-bytes from EEPROM from provided address
*
* Param [in]        - I2C configuration structure
*
* Param [in]        - EEPROM address to read from
*
* Param [in]        - Pointer to buffer to be written to
*
* Param [in]        - Length of data
*
* Retval            - None
*
* Note              - None
*******************************************************************************/
uint8_t HAL_EEPROM_U8_ReadNBytes(I2C_Config_t *, uint32_t, uint8_t *, uint32_t);

#endif /* HAL_EEPROM_EEPROM_INTERFACE_H_ */

/*******************************************************************************
 *  END OF FILE: eeprom_interface.h
 ******************************************************************************/
