/*******************************************************************************
 * max7221_interface.h
 *
 *  Created on: Apr 9, 2023
 *      Author: Abanoub Salah
 ******************************************************************************/

#ifndef HAL_MAX7221_MAX7221_INTERFACE_H_
#define HAL_MAX7221_MAX7221_INTERFACE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "atmega32.h"
#include "platform_types.h"
#include "bit_math.h"
#include "gpio_interface.h"
#include "spi_interface.h"

/* @ref MAX7221_Digit_et */
typedef enum
{
	MAX7221_Digit_None = 0x00,
	MAX7221_Digit_0 = 0x01,
	MAX7221_Digit_1 = 0x02,
	MAX7221_Digit_2 = 0x04,
	MAX7221_Digit_3 = 0x08,
	MAX7221_Digit_4 = 0x10,
	MAX7221_Digit_5 = 0x20,
	MAX7221_Digit_6 = 0x40,
	MAX7221_Digit_7 = 0x80,
	MAX7221_Digit_All = 0xFF,
} MAX7221_Digit_et;

/* @ref MAX7221_ShutdownMode_et */
typedef enum
{
	MAX7221_ShutdownMode_Shutdown = 0x00,
	MAX7221_ShutdownMode_NormalOperation = 0x01,

} MAX7221_ShutdownMode_et;

/* @ref MAX7221_DisplayTestMode_et */
typedef enum
{
	MAX7221_DisplayTestMode_NormalOperation = 0x00,
	MAX7221_DisplayTestMode_DisplayTestMode = 0x01,

} MAX7221_DisplayTestMode_et;

/* @ref MAX7221_Command */
typedef enum
{
	MAX7221_Command_NoOperation = 0x00,			/* No operation command used when cascading multiple max7221 */
	MAX7221_Command_Digit0 = 0x01,				/* o/p to digit 1 */
	MAX7221_Command_Digit1 = 0x02,				/* o/p to digit 2 */
	MAX7221_Command_Digit2 = 0x03,				/* o/p to digit 3 */
	MAX7221_Command_Digit3 = 0x04,				/* o/p to digit 4 */
	MAX7221_Command_Digit4 = 0x05,				/* o/p to digit 5 */
	MAX7221_Command_Digit5 = 0x06,				/* o/p to digit 6 */
	MAX7221_Command_Digit6 = 0x07,				/* o/p to digit 7 */
	MAX7221_Command_Digit7 = 0x08,				/* o/p to digit 8 */
	MAX7221_Command_DecodeMode = 0x09,			/* Turn on BCD for specific digit @ref MAX7221_Digit_et or o/p 8-bits as is */
	MAX7221_Command_Intensity = 0x0A,			/* Set screen intensity by software take a number 0..15 (4-bits) corresponding to 1/16..15/16 % max intensity */
	MAX7221_Command_ScanLimit = 0x0B,			/* Scan limit to digit x where x can be 0..7 N.B. less scan limit draws more current to the digits so you need to increase R_SET */
	MAX7221_Command_Shutdown = 0x0C,			/* @ref MAX7221_ShutdownMode_et */
	MAX7221_Command_DisplayTest = 0x0F,			/* Override register to scan 8-digits at 15/16 duty cycle @ref MAX7221_DisplayTestMode_et */
} MAX7221_Command_et;


/*******************************************************************************
 * Fn                - HAL_MAX7221_Void_Execute
 *
 * Brief             - Send a command through port to the IC
 *
 * Param [in]        - SPI configuration structure
 *
 * Param [in]        - a Command to be sent @ref MAX7221_Command
 *
 * Param [in]        - Command argument/data
 *
 * Retval            - None
 *
 * Note              - None
 ******************************************************************************/
void HAL_MAX7221_Void_Execute(SPI_Config_t *, MAX7221_Command_et, uint8_t);

#endif /* HAL_MAX7221_MAX7221_INTERFACE_H_ */

/*******************************************************************************
 *  END OF FILE: max7221_interface.h
 ******************************************************************************/
