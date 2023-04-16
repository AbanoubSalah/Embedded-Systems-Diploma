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
	uint16_t GPIO_PinNumber;	/* Specifies the GPIO pins to be configured 				  */
								/* This parameters must be a value of @ref GPIO_PINS_define	  */

	uint8_t	 GPIO_Mode;			/* Specifies the operating mode for the selected pins.		  */
								/* This parameter must be set based on @ref GPIO_Mode_define  */

	uint8_t	 GPIO_OutputSpeed;	/* Specifies the speed for the selected pins.				  */
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

#define GPIO_PIN_MASK					(0x0000FFFFUL)	   /* PIN mask for assert test */

/* @ref GPIO_Mode_define					*/
/* 0: Analog mode							*/
/* 1: Input Floating (reset state)			*/
/* 2: Input pull-up							*/
/* 3: Input pull-down						*/
/* 4: General purpose output push-pull		*/
/* 5: General purpose output Open-drain		*/
/* 6: Alternate function output Push-pull   */
/* 7: Alternate function output Open-drain  */
/* 8: Alternate function input				*/

#define GPIO_MODE_ANALOG				(0x00000000U) /* Analog mode 							*/
#define GPIO_MODE_INPUT_FLO				(0x00000001U) /* Input Floating 						*/
#define GPIO_MODE_INPUT_PU				(0x00000002U) /* Input pull-up 							*/
#define GPIO_MODE_INPUT_PD				(0x00000003U) /* Input pull-down 						*/
#define GPIO_MODE_OUTPUT_PP				(0x00000004U) /* General purpose output push-pull 		*/
#define GPIO_MODE_OUTPUT_OD				(0x00000005U) /* General purpose output Open-drain 		*/
#define GPIO_MODE_OUTPUT_AF_PP			(0x00000006U) /* Alternate function output Push-pull 	*/
#define GPIO_MODE_OUTPUT_AF_OD			(0x00000007U) /* Alternate function output Open-drain 	*/
#define GPIO_MODE_INPUT_AF				(0x00000008U) /* Alternate function input 				*/

/* @ref GPIO_SPEED_define				*/
/* 1: Output mode, max speed 10 MHz.	*/
/* 2: Output mode, max speed 2 MHz.		*/
/* 3: Output mode, max speed 50 MHz.	*/

#define GPIO_SPEED_10M					(0x00000001U) /* Output mode, max speed 10 MHz. */
#define GPIO_SPEED_2M					(0x00000002U) /* Output mode, max speed 2 MHz. 	*/
#define GPIO_SPEED_50M					(0x00000003U) /* Output mode, max speed 50 MHz. */

/* @ref GPIO_PIN_state */
#define GPIO_PIN_SET  					1U
#define GPIO_PIN_RESET  				0U

/* @ref GPIO_RETURN_LOCK */
#define GPIO_RETURN_LOCK_ENABLED 		1U
#define GPIO_RETURN_LOCK_ERROR	 		0U

/*******************************************************************************
 * APIs Supported by "MCAL GPIO DRIVER"
 ******************************************************************************/

/*******************************************************************************
 * Fn                - MCAL_GPIO_Init
 *
 * Brief             - Initializes the GPIOx PINy according to the specified
 *                     parameters in the PinConfig
 *
 * Param [in]        - GPIOx where x can be (A..E depending on device used) to
 *                     select the GPIO Peripheral
 *
 * Param [in]        - Pointer to GPIO_PinConfig_t structure that contains
 *					   the configuration information for the specified GPIO pin
 *
 * Retval            - None
 *
 * Note              - STM32F103C6 MCU has GPIO A,B,C,D and E Modules but LQFP4
 *                     package has only GPIO A,B and part of C AND D exported as
 *                     external PINs from the MCU
 ******************************************************************************/
void MCAL_GPIO_Init (GPIO_TypeDef_t *, GPIO_PinConfig_t *);

/*******************************************************************************
 * @Fn				- MCAL_GPIO_DeInit
 *
 * @brief			- Reset all the GPIO Registers
 *
 * @param [in] 		- GPIOx where x can be (A..E depending on device used)
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
 * @param [in] 		- GPIOx where x can be (A..E depending on device used)
 * 					  to select GPIO peripheral
 *
 * @param [in] 		- Pin number Set Pin Number according to
 * 					  @ref GPIO_PINS_define
 *
 * @retval 			- The input pin value
 * 					  (two values based on @ref GPIO_PIN_state)
 *
 * Note				- None
 ******************************************************************************/
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef_t *, uint16_t);

/*******************************************************************************
* Fn                - MCAL_GPIO_ReadPort
*
* Brief             - Read specific PORT
*
* Param [in]        - GPIOx where x can be (A..E depending on device used) to
*                     select the GPIO Peripheral
*
* Retval            - The input port value
*
* Note              - None
*******************************************************************************/
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef_t *);

/*******************************************************************************
* Fn                - MCAL_GPIO_WritePort
*
* Brief             - Write on specific PIN
*
* Param [in]        - GPIOx where x can be (A..E depending on device used) to
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
void MCAL_GPIO_WritePin(GPIO_TypeDef_t *, uint16_t, uint8_t);

/*******************************************************************************
 * @Fn				- MCAL_GPIO_WritePort
 *
 * @brief			- Write on Specific PORT
 *
 * @param [in] 		- GPIOx where x can be (A..E depending on device used)
 *					  to select GPIO peripheral
 *
 * @param [in] 		- Port value
 *
 * @retval 			- None
 *
 * Note				- None
 ******************************************************************************/
void MCAL_GPIO_WritePort(GPIO_TypeDef_t *, uint16_t);

/*******************************************************************************
* Fn                - MCAL_GPIO_TogglePin
*
* Brief             - Toggle a specific pin in GPIOx
*
* Param [in]        - GPIOx where x can be (A..E depending on device used) to
*                     select the GPIO Peripheral
*
* Param [in]        - Pin number specifies the port pin to toggle it, set pin
*                     number according @ref GPIO_PINS_define
*
* Retval            - None
*
* Note              - None
*******************************************************************************/
void MCAL_GPIO_TogglePin(GPIO_TypeDef_t *, uint16_t);

/*******************************************************************************
 * Fn                - MCAL_GPIO_LockPin
 *
 * Brief             - The locking mechanism allows the IO configuration to be
 *                     frozen.
 *
 * Param [in]        - GPIOx where x can be (A..E depending on device used) to
 *                     select the GPIO Peripheral.
 *
 * Param [in]        - Pin number specifies the port pin to lock it, set pin
 *                     number according @ref GPIO_PINS_define.
 *
 * Retval            - Done if PinConfig is locked or ERROR if pin not locked
 *                     Return_t is defined at @ref GLOBAL_ENUM.
 *
 * Note              - During the LOCK Key Writing sequence, the value of
 *                     LCK[15:0] must not change. Any error in the lock
 *                     sequence will abort the lock.
*******************************************************************************/
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef_t *, uint16_t);


#endif /* MCAL_GPIO_GPIO_INTERFACE_H_ */

/******************************************************************************
 *  END OF FILE: gpio_interface.h
 ******************************************************************************/
