/*******************************************************************************
 * gpio_interface.h
 *
 *  Created on: Apr 30, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

#ifndef MCAL_GPIO_GPIO_INTERFACE_H_
#define MCAL_GPIO_GPIO_INTERFACE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "atmega32.h"

/*******************************************************************************
 * User type definitions (structures)
 ******************************************************************************/
typedef struct
{
	uint8 GPIO_PinNumber;		/* Specifies the GPIO pins to be configured 				  */
								/* This parameters must be a value of @ref GPIO_PINS_define	  */

	uint8 GPIO_Mode;			/* Specifies the operating mode for the selected pins.		  */
								/* This parameter must be set based on @ref GPIO_Mode_define  */
} GPIO_PinConfig;

typedef struct{
	union{
		vuint8 reg;
		struct{
			vuint8 bit0 :1;
			vuint8 bit1 :1;
			vuint8 bit2 :1;
			vuint8 bit3 :1;
			vuint8 bit4 :1;
			vuint8 bit5 :1;
			vuint8 bit6 :1;
			vuint8 bit7 :1;
		}bits;
	} PIN;
	union{
		vuint8 reg;
		struct{
			vuint8 bit0 :1;
			vuint8 bit1 :1;
			vuint8 bit2 :1;
			vuint8 bit3 :1;
			vuint8 bit4 :1;
			vuint8 bit5 :1;
			vuint8 bit6 :1;
			vuint8 bit7 :1;
		}bits;
	} DDR;
	union{
		vuint8 reg;
		struct{
			vuint8 bit0 :1;
			vuint8 bit1 :1;
			vuint8 bit2 :1;
			vuint8 bit3 :1;
			vuint8 bit4 :1;
			vuint8 bit5 :1;
			vuint8 bit6 :1;
			vuint8 bit7 :1;
		}bits;
	} PORT;
} GPIO_TypeDef;


/*******************************************************************************
 * Peripheral instances
 ******************************************************************************/
#define GPIOA 				((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB  				((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC 				((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD 				((GPIO_TypeDef *) GPIOD_BASE)

/*******************************************************************************
 * Macros Configuration References
 ******************************************************************************/

/* @ref GPIO_PINS_define */
#define GPIO_PIN_0						((uint8) 0x0001U) /* Pin 0 selected    */
#define GPIO_PIN_1						((uint8) 0x0002U) /* Pin 1 selected    */
#define GPIO_PIN_2						((uint8) 0x0004U) /* Pin 2 selected    */
#define GPIO_PIN_3						((uint8) 0x0008U) /* Pin 3 selected    */
#define GPIO_PIN_4						((uint8) 0x0010U) /* Pin 4 selected    */
#define GPIO_PIN_5						((uint8) 0x0020U) /* Pin 5 selected    */
#define GPIO_PIN_6						((uint8) 0x0040U) /* Pin 6 selected    */
#define GPIO_PIN_7						((uint8) 0x0080U) /* Pin 7 selected    */

#define GPIO_ALL_PINS					((uint8) 0xFFU)	  /* All pins selected */

/* @ref GPIO_Mode_define	*/
/* 0: Input high-z			*/
/* 1: Input with pull-up	*/
/* 2: Output sink-source	*/

#define GPIO_MODE_INPUT_HIGHZ			(0x00U) /* High-z Input				*/
#define GPIO_MODE_INPUT_PU				(0x01U) /* Input with pull-up		*/
#define GPIO_MODE_OUTPUT				(0x02U) /* Input with pull-down		*/

/* @ref GPIO_PIN_state */
#define GPIO_PIN_SET  					1
#define GPIO_PIN_RESET  				0

/*******************************************************************************
 * APIs Supported by "MCAL GPIO DRIVER"
 ******************************************************************************/

void MCAL_GPIO_Init (GPIO_TypeDef *GPIOx, GPIO_PinConfig *PinConfig);
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx);

uint8 MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint8 PinNumber);
uint8 MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx);

void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint8 PinNumber, uint8 Value);
void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx, uint8 Value);

void MCAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint8 PinNumber);

#endif /* MCAL_GPIO_GPIO_INTERFACE_H_ */

/******************************************************************************
 *  END OF FILE: gpio_interface.h
 ******************************************************************************/
