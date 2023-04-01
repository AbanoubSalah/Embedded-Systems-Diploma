/*******************************************************************************
 * gpio_interface.h
 *
 *  Created on: Mar 27, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

#ifndef MCAL_GPIO_GPIO_INTERFACE_H_
#define MCAL_GPIO_GPIO_INTERFACE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "stm32F103c6.h"

/*******************************************************************************
 * User type definitions (structures)
 ******************************************************************************/
typedef struct
{
	uint16 GPIO_PinNumber;		/* Specifies the GPIO pins to be configured 				  */
								/* This parameters must be a value of @ref GPIO_PINS_define	  */

	uint8	 GPIO_Mode;			/* Specifies the operating mode for the selected pins.		  */
								/* This parameter must be set based on @ref GPIO_Mode_define  */

	uint8	 GPIO_OutputSpeed;	/* Specifies the speed for the selected pins.				  */
								/* This parameter must be set based on @ref GPIO_SPEED_define */
} GPIO_PinConfig_t;

/*******************************************************************************
 * Macros Configuration References
 ******************************************************************************/

/* @ref GPIO_PINS_define */
#define GPIO_PIN_0						((uint16_t) 0x0001U) /* Pin 0 selected    */
#define GPIO_PIN_1						((uint16_t) 0x0002U) /* Pin 1 selected    */
#define GPIO_PIN_2						((uint16_t) 0x0004U) /* Pin 2 selected    */
#define GPIO_PIN_3						((uint16_t) 0x0008U) /* Pin 3 selected    */
#define GPIO_PIN_4						((uint16_t) 0x0010U) /* Pin 4 selected    */
#define GPIO_PIN_5						((uint16_t) 0x0020U) /* Pin 5 selected    */
#define GPIO_PIN_6						((uint16_t) 0x0040U) /* Pin 6 selected    */
#define GPIO_PIN_7						((uint16_t) 0x0080U) /* Pin 7 selected    */
#define GPIO_PIN_8						((uint16_t) 0x0100U) /* Pin 8 selected    */
#define GPIO_PIN_9						((uint16_t) 0x0200U) /* Pin 9 selected    */
#define GPIO_PIN_10						((uint16_t) 0x0400U) /* Pin 10 selected   */
#define GPIO_PIN_11						((uint16_t) 0x0800U) /* Pin 11 selected   */
#define GPIO_PIN_12						((uint16_t) 0x1000U) /* Pin 12 selected   */
#define GPIO_PIN_13						((uint16_t) 0x2000U) /* Pin 13 selected   */
#define GPIO_PIN_14						((uint16_t) 0x4000U) /* Pin 14 selected   */
#define GPIO_PIN_15						((uint16_t) 0x8000U) /* Pin 15 selected   */

#define GPIO_ALL_PINS					((uint16_t) 0xFFFFU) /* All pins selected */

#define GPIO_PIN_MASK					(0x0000FFFFUL)		 /* PIN mask for assert test */

/* @ref GPIO_Mode_define					*/
/* 0: Analog mode							*/
/* 1: Floating input (reset state)			*/
/* 2: Input with pull-up					*/
/* 3: Input with pull-down					*/
/* 4: General purpose output push-pull		*/
/* 5: General purpose output Open-drain		*/
/* 6: Alternate function output Push-pull   */
/* 7: Alternate function output Open-drain  */
/* 8: Alternate function input				*/

#define GPIO_MODE_ANALOG				(0x00000000U) /* Analog mode 							*/
#define GPIO_MODE_INPUT_FLO				(0x00000001U) /* Floating input 						*/
#define GPIO_MODE_INPUT_PU				(0x00000002U) /* Input with pull-up 					*/
#define GPIO_MODE_INPUT_PD				(0x00000003U) /* Input with pull-down 					*/
#define GPIO_MODE_OUTPUT_PP				(0x00000004U) /* General purpose output push-pull 		*/
#define GPIO_MODE_OUTPUT_OD				(0x00000005U) /* General purpose output Open-drain 		*/
#define GPIO_MODE_OUTPUT_AF_PP			(0x00000006U) /* Alternate function output Push-pull 	*/
#define GPIO_MODE_OUTPUT_AF_OD			(0x00000007U) /* Alternate function output Open-drain 	*/
#define GPIO_MODE_AF_INPUT				(0x00000008U) /* Alternate function input 				*/

/* @ref GPIO_SPEED_define				*/
/* 1: Output mode, max speed 10 MHz.	*/
/* 2: Output mode, max speed 2 MHz.		*/
/* 3: Output mode, max speed 50 MHz.	*/

#define GPIO_SPEED_10M					(0x00000001U) /* Output mode, max speed 10 MHz. */
#define GPIO_SPEED_2M					(0x00000002U) /* Output mode, max speed 2 MHz. 	*/
#define GPIO_SPEED_50M					(0x00000003U) /* Output mode, max speed 50 MHz. */

/* @ref GPIO_PIN_state */
#define GPIO_PIN_SET  					1
#define GPIO_PIN_RESET  				0

/* @ref GPIO_RETURN_LOCK */
#define GPIO_RETURN_LOCK_ENABLED 		1
#define GPIO_RETURN_LOCK_ERROR	 		0

/* ------------------------------------ */
/* Peripheral register: GPIO			*/
/* ------------------------------------ */

typedef struct
{
	 vuint32 CRL;
	 vuint32 CRH;
	 vuint32 IDR;
	 vuint32 ODR;
	 vuint32 BSRR;
	 vuint32 BRR;
	 vuint32 LCKR;
} GPIO_TypeDef;

/* ------------------------------------ */
/* Peripheral Instants:     			*/
/* ------------------------------------ */

#define GPIOA			((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB			((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC			((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD			((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE			((GPIO_TypeDef *) GPIOE_BASE)

/*******************************************************************************
 * APIs Supported by "MCAL GPIO DRIVER"
 ******************************************************************************/

void MCAL_GPIO_Init (GPIO_TypeDef *GPIOx, GPIO_PinConfig_t *PinConfig);
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx);

uint8 MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16 PinNumber);
uint16 MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx);

void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16 PinNumber, uint8 Value);
void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx, uint16 Value);

void MCAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16 PinNumber);

uint8 MCAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16 PinNumber);


#endif /* MCAL_GPIO_GPIO_INTERFACE_H_ */

/******************************************************************************
 *  END OF FILE: gpio_interface.h
 ******************************************************************************/
