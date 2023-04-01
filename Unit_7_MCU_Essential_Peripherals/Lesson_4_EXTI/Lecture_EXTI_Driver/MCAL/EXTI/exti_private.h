/*******************************************************************************
 * exti_private.h
 *
 *  Created on: Mar 30, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

#ifndef MCAL_EXTI_EXTI_PRIVATE_H_
#define MCAL_EXTI_EXTI_PRIVATE_H_

typedef struct
{
	volatile uint32   IMR;
    volatile uint32   EMR;
    volatile uint32   RTSR;
    volatile uint32   FTSR;
    volatile uint32   SWIER;
    volatile uint32   PR;
}EXTI_t;


#define EXTI			((EXTI_TypeDef *) EXTI_BASE)

static void updateEXTI(EXTI_PinConfig_t* EXTI_Config);

#endif /* MCAL_EXTI_EXTI_PRIVATE_H_ */

/******************************************************************************
 *  END OF FILE: exti_private.h
 ******************************************************************************/
