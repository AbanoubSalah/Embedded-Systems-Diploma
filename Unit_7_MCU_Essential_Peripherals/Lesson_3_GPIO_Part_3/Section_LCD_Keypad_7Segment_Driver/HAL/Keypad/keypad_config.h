/*******************************************************************************
 * keypad_config.h
 *
 *  Created on: Mar 29, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

#ifndef HAL_KEYPAD_KEYPAD_CONFIG_H_
#define HAL_KEYPAD_KEYPAD_CONFIG_H_

/*******************************************************************************
 * Select micro-controler pins
 ******************************************************************************/
#define KEYPAD_C0_PORT				GPIOB
#define KEYPAD_C1_PORT				GPIOB
#define KEYPAD_C2_PORT				GPIOB
#define KEYPAD_C3_PORT				GPIOB
#define KEYPAD_R0_PORT				GPIOB
#define KEYPAD_R1_PORT				GPIOB
#define KEYPAD_R2_PORT				GPIOB
#define KEYPAD_R3_PORT				GPIOB

#define KEYPAD_R0_PIN				GPIO_PIN_0
#define KEYPAD_R1_PIN				GPIO_PIN_1
#define KEYPAD_R2_PIN				GPIO_PIN_3
#define KEYPAD_R3_PIN				GPIO_PIN_4
#define KEYPAD_C0_PIN				GPIO_PIN_5
#define KEYPAD_C1_PIN				GPIO_PIN_6
#define KEYPAD_C2_PIN				GPIO_PIN_7
#define KEYPAD_C3_PIN				GPIO_PIN_8

/*******************************************************************************
 * Select keypad_debouncing_time in milli-seconds
 ******************************************************************************/
#define KEYPAD_DEBOUNCING_TIME   	20

/*******************************************************************************
 *   Select keypad model
 *
 *   KEYPAD_MODEL_A :  {'7' , '8' , '9', '/'}
 *			           {'4' , '5' , '6', 'x'}
 *					   {'1' , '2' , '3', '-'}
 *					   {'C' , '0' , '=', '+'}
 *
 *   KEYPAD_MODEL_B :  {'7' , '8' , '9', '/'}
 *			           {'4' , '5' , '6', 'x'}
 *					   {'1' , '2' , '3', '-'}
 *					   {'C' , '0' , '=', '+'}
 *
 ******************************************************************************/
#define KEYPAD_MODEL             	KEYPAD_MODEL_A
#define KEYPAD_COL_NUMBER          	(4)
#define KEYPAD_ROW_NUMBER          	(4)
#define DELAY(x)					delay_ms(x)

#endif /* HAL_KEYPAD_KEYPAD_CONFIG_H_ */

/*******************************************************************************
 *  END OF FILE: keypad_config.h
 ******************************************************************************/
