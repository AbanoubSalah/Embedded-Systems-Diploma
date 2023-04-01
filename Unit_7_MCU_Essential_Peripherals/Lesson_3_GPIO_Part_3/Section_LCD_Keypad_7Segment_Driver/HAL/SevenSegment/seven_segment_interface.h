/*******************************************************************************
 * seven_segment_interface.h
 *
 *  Created on: Mar 29, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

#ifndef  HAL_SEVEN_SEGMENT_SEVEN_SEGMENT_INTERFACE_H_
#define  HAL_SEVEN_SEGMENT_SEVEN_SEGMENT_INTERFACE_H_

/*============================================================================================*/
/*   INCLUDES   */
/*============================================================================================*/
#include "gpio_interface.h"

#include "../../Libraries/bit_math.h"
#include "../../Libraries/platform_types.h"

/*============================================================================================*/
/*   PROTOTYPES   */
/*============================================================================================*/
void HAL_SevenSegment_Void_Init(void);
void HAL_SevenSegment_Void_Display(uint8);
void HAL_SevenSegment_Void_Reset(void);

#endif /* HAL_SEVEN_SEGMENT_SEVEN_SEGMENT_INTERFACE_H_ */

/*******************************************************************************
 *  END OF FILE: seven_segment_interface.h
 ******************************************************************************/
