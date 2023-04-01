/*******************************************************************************
 * exti_interface.h
 *
 *  Created on: Mar 30, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

#ifndef MCAL_EXTI_EXTI_INTERFACE_H_
#define MCAL_EXTI_EXTI_INTERFACE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "gpio_interface.h"
#include "bit_math.h"
#include "platform_types.h"

typedef struct
{
	uint16 InputLineNumber;
	GPIO_TypeDef *GPIOx;
	uint16 GPIOPin;
}EXTI_GPIO_Mapping_t;

typedef struct
{
	EXTI_GPIO_Mapping_t Pin;
	uint8 TriggerCase;
	uint8 IRQEnabled;
	void(*Ptr_IRQCallBack)(void);
}EXTI_PinConfig_t;

/*******************************************************************************
 * Configuration Macros
 ******************************************************************************/

/* @ref EXTI_LINE */
#define EXTI_LINE0		0
#define EXTI_LINE1		1
#define EXTI_LINE2		2
#define EXTI_LINE3		3
#define EXTI_LINE4		4
#define EXTI_LINE5		5
#define EXTI_LINE6		6
#define EXTI_LINE7		7
#define EXTI_LINE8		8
#define EXTI_LINE9		9
#define EXTI_LINE10		10
#define EXTI_LINE11		11
#define EXTI_LINE12		12
#define EXTI_LINE13		13
#define EXTI_LINE14		14
#define EXTI_LINE15		15

/* @ref EXTI_IRQ */
#define EXTI_IRQ_ENABLE					1
#define EXTI_IRQ_DISABLE				0

/* @ref EXTI_Trigger */

#define EXTI_FALLING					0
#define EXTI_RISING						1
#define EXTI_ON_CHANGE					2

void MCAL_EXTI_Void_Init(EXTI_PinConfig_t* EXTI_Config);
void MCAL_EXTI_Void_DeInit(void);
void MCAL_EXTI_Void_Update(EXTI_PinConfig_t* EXTI_Config);

#endif /* MCAL_EXTI_EXTI_INTERFACE_H_ */

/******************************************************************************
 *  END OF FILE: exti_interface.h
 ******************************************************************************/
