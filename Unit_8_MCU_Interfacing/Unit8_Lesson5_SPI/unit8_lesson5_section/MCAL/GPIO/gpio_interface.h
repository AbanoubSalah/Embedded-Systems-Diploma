/*******************************************************************************
 * gpio_interface.h
 *
 *  Created on: Apr 1, 2023
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
	uint8_t GPIO_PinNumber;		/* Specifies the GPIO pins to be configured 				  */
								/* This parameters must be a value of @ref GPIO_PINS_define	  */

	uint8_t GPIO_Mode;			/* Specifies the operating mode for the selected pins.		  */
								/* This parameter must be set based on @ref GPIO_Mode_define  */
} GPIO_PinConfig_t;

typedef struct{
	union{
		vuint8_t reg;
		struct{
			vuint8_t bit0 :1;
			vuint8_t bit1 :1;
			vuint8_t bit2 :1;
			vuint8_t bit3 :1;
			vuint8_t bit4 :1;
			vuint8_t bit5 :1;
			vuint8_t bit6 :1;
			vuint8_t bit7 :1;
		}bits;
	} PIN;
	union{
		vuint8_t reg;
		struct{
			vuint8_t bit0 :1;
			vuint8_t bit1 :1;
			vuint8_t bit2 :1;
			vuint8_t bit3 :1;
			vuint8_t bit4 :1;
			vuint8_t bit5 :1;
			vuint8_t bit6 :1;
			vuint8_t bit7 :1;
		}bits;
	} DDR;
	union{
		vuint8_t reg;
		struct{
			vuint8_t bit0 :1;
			vuint8_t bit1 :1;
			vuint8_t bit2 :1;
			vuint8_t bit3 :1;
			vuint8_t bit4 :1;
			vuint8_t bit5 :1;
			vuint8_t bit6 :1;
			vuint8_t bit7 :1;
		}bits;
	} PORT;
} GPIO_TypeDef_t;


/*******************************************************************************
 * Peripheral instances
 ******************************************************************************/
#define GPIOA 				((GPIO_TypeDef_t *) GPIOA_BASE)
#define GPIOB  				((GPIO_TypeDef_t *) GPIOB_BASE)
#define GPIOC 				((GPIO_TypeDef_t *) GPIOC_BASE)
#define GPIOD 				((GPIO_TypeDef_t *) GPIOD_BASE)

/*******************************************************************************
 * Macros Configuration References
 ******************************************************************************/

/* @ref GPIO_PINS_define */
#define GPIO_PIN_0						((uint8_t) 0x0001U) /* Pin 0 selected    */
#define GPIO_PIN_1						((uint8_t) 0x0002U) /* Pin 1 selected    */
#define GPIO_PIN_2						((uint8_t) 0x0004U) /* Pin 2 selected    */
#define GPIO_PIN_3						((uint8_t) 0x0008U) /* Pin 3 selected    */
#define GPIO_PIN_4						((uint8_t) 0x0010U) /* Pin 4 selected    */
#define GPIO_PIN_5						((uint8_t) 0x0020U) /* Pin 5 selected    */
#define GPIO_PIN_6						((uint8_t) 0x0040U) /* Pin 6 selected    */
#define GPIO_PIN_7						((uint8_t) 0x0080U) /* Pin 7 selected    */

#define GPIO_ALL_PINS					((uint8_t) 0xFFU)	  /* All pins selected */

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

/*******************************************************************************
 * Fn                - MCAL_GPIO_Init
 *
 * Brief             - Initializes the GPIOx PINy according to the specified
 *                     parameters in the PinConfig
 *
 * Param [in]        - GPIOx where x can be (A..D depending on device used) to
 *                     select the GPIO Peripheral
 *
 * Param [in]        - a Pointer to GPIO_PinConfig_t structure that contains
 *					   the configuration information for the specified GPIO PIN
 *
 * Retval            - None
 *
 * Note              - None
 ******************************************************************************/
void MCAL_GPIO_Init(GPIO_TypeDef_t *, GPIO_PinConfig_t *);

/*******************************************************************************
 * @Fn				- MCAL_GPIO_DeInit
 *
 * @brief			- Reset all the GPIO Registers
 *
 * @param [in] 		- GPIOx where x can be (A..D depending on device used)
 *					  to select GPIO peripheral
 *
 * @retval 			- None
 *
 * Note				- None
 ******************************************************************************/
void MCAL_GPIO_DeInit(GPIO_TypeDef_t *);

/*******************************************************************************
 * @Fn				- MCAL_GPIO_ReadPin
 *
 * @brief			- Read Specific PIN
 *
 * @param [in] 		- GPIOx where x can be (A..D depending on device used)
 * 					  to select GPIO peripheral
 *
 * @param [in] 		- Pin number: Set Pin Number according to
 * 					  @ref GPIO_PINS_define
 *
 * @retval 			- The input pin value
 * 					  (two values based on @ref GPIO_PIN_state)
 *
 * Note				- None
 ******************************************************************************/
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef_t *, uint8_t);

/*******************************************************************************
* Fn                - MCAL_GPIO_ReadPort
*
* Brief             - Read specific PORT
*
* Param [in]        - GPIOx where x can be (A..D depending on device used) to
*                     select the GPIO Peripheral
*
* Retval            - The input port value
*
* Note              -None
*******************************************************************************/
uint8_t MCAL_GPIO_ReadPort(GPIO_TypeDef_t *);

/*******************************************************************************
* Fn                - MCAL_GPIO_WritePort
*
* Brief             - Write on specific PIN
*
* Param [in]        - GPIOx where x can be (A..D depending on device used) to
*                     select the GPIO Peripheral
*
* Param [in]        - Pin number specifies the port pin to write on it, set pin
*                     number according @ref GPIO_PINS_define
*
* Param [in]        - Pin value
*
* Retval            - None
*
* Note              - None
*******************************************************************************/
void MCAL_GPIO_WritePin(GPIO_TypeDef_t *, uint8_t, uint8_t);

/*******************************************************************************
 * @Fn				- MCAL_GPIO_WritePort
 *
 * @brief			- Write on Specific PORT
 *
 * @param [in] 		- GPIOx where x can be (A..D depending on device used)
 *					  to select GPIO peripheral
 *
 * @param [in] 		- Port value
 *
 * @retval 			- None
 *
 * Note				- None
 ******************************************************************************/
void MCAL_GPIO_WritePort(GPIO_TypeDef_t *, uint8_t);

/*******************************************************************************
* Fn                - MCAL_GPIO_TogglePin
*
* Brief             - Toggle a specific pin in GPIOx
*
* Param [in]        - GPIOx where x can be (A..D depending on device used) to
*                     select the GPIO Peripheral
*
* Param [in]        - Pin number specifies the port pin to toggle it, set pin
*                     number according @ref GPIO_PINS_define
*
* Retval            - None
*
* Note              - None
*******************************************************************************/
void MCAL_GPIO_TogglePin(GPIO_TypeDef_t *, uint8_t);

#endif /* MCAL_GPIO_GPIO_INTERFACE_H_ */

/******************************************************************************
 *  END OF FILE: gpio_interface.h
 ******************************************************************************/
