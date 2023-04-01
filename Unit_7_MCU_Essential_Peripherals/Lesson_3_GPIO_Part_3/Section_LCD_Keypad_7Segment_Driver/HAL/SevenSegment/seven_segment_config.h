/*******************************************************************************
 * seven_segment_config.h
 *
 *  Created on: Mar 29, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

#ifndef  HAL_LCD_SEVEN_SEGMENT_INTERFACE_H_
#define  HAL_LCD_SEVEN_SEGMENT_INTERFACE_H_

/*******************************************************************************
 * Defines
 ******************************************************************************/
#define SS_A_PORT           		GPIOB
#define SS_B_PORT           		GPIOB
#define SS_C_PORT           		GPIOB
#define SS_D_PORT           		GPIOB
#define SS_E_PORT           		GPIOB
#define SS_F_PORT           		GPIOB
#define SS_G_PORT           		GPIOB

#define SS_A_PIN            		GPIO_PIN_9
#define SS_B_PIN            		GPIO_PIN_10
#define SS_C_PIN            		GPIO_PIN_11
#define SS_D_PIN            		GPIO_PIN_12
#define SS_E_PIN            		GPIO_PIN_13
#define SS_F_PIN            		GPIO_PIN_14
#define SS_G_PIN            		GPIO_PIN_15

#define SS_PIN_COUNT				7

#endif /* HAL_LCD_SEVEN_SEGMENT_CONFIG_H_ */

/*******************************************************************************
 *  END OF FILE: seven_segment_config.h
 ******************************************************************************/
