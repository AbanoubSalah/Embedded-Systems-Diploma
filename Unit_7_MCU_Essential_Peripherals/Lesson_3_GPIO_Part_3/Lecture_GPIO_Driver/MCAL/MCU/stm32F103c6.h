/*******************************************************************************
 * stm32F103c8tx.h
 *
 *  Created on: Mar 27, 2023
 *      Author: Abanoub Salah
 ******************************************************************************/

#ifndef STM32F103C6_H_
#define STM32F103C6_H_

/* ------------------------------------ */
/* Includes                     		*/
/* ------------------------------------ */

#include "bit_math.h"
#include "platform_types.h"

/* ------------------------------------ */
/* Base addresses for Memories  		*/
/* ------------------------------------ */

#define PERIPHERALS_BASE	0x40000000UL
#define SRAM_BASE			0x20000000UL
#define FLASH_BASE 			0x08000000UL

#define APB1_BUS_BASE     	(PERIPHERALS_BASE)
#define APB2_BUS_BASE     	(PERIPHERALS_BASE + 0x00010000UL)
#define AHB_BUS_BASE      	(PERIPHERALS_BASE + 0x00018000UL)

/* ---------------------------- 		*/
/* Base addresses for AHB Peripherals   */
/* ---------------------------- 		*/

#define RCC_BASE            (AHB_BUS_BASE + 0x00009000UL)

/* ------------------------------------ */
/* Base addresses for APB2 Peripherals	*/
/* ------------------------------------ */

#define AFIO_BASE           (APB2_BUS_BASE + 0x00000000UL)
#define EXTI_BASE           (APB2_BUS_BASE + 0x00000400UL)
#define GPIOA_BASE          (APB2_BUS_BASE + 0x00000800UL)
#define GPIOB_BASE          (APB2_BUS_BASE + 0x00000C00UL)
#define GPIOC_BASE          (APB2_BUS_BASE + 0x00001000UL)
#define GPIOD_BASE          (APB2_BUS_BASE + 0x00001400UL)
#define GPIOE_BASE          (APB2_BUS_BASE + 0x00001800UL)

/* ------------------------------------ */
/* Peripheral register: RCC				*/
/* ------------------------------------ */

typedef struct
{
	 vuint32 CR;
	 vuint32 CFGR;
	 vuint32 CIR;
	 vuint32 APB2RSTR;
	 vuint32 APB1RSTR;
	 vuint32 AHBENR;
	 vuint32 APB2ENR;
	 vuint32 APB1ENR;
	 vuint32 BDCR;
}RCC_TypeDef;

/* ------------------------------------ */
/* Peripheral register: AFIO			*/
/* ------------------------------------ */

typedef struct
{
	 vuint32 EVCR;
	 vuint32 MAPR;
	 vuint32 EXTICR[4];
	 uint32 RESERVED0;
	 vuint32 MAPR2;
}AFIO_TypeDef;

/* ------------------------------------ */
/* Peripheral register: EXTI			*/
/* ------------------------------------ */

typedef struct
{
	 vuint32 IMR;
	 vuint32 EMR;
	 vuint32 RTSR;
	 vuint32 FTSR;
	 vuint32 SWIER;
	 vuint32 PR;
}EXTI_TypeDef;

#define RCC				((RCC_TypeDef *)  RCC_BASE)

#define EXTI			((EXTI_TypeDef *) EXTI_BASE)

#define AFIO			((AFIO_TypeDef *) AFIO_BASE)

/* ------------------------------------ */
/* clock enable Macros:     			*/
/* ------------------------------------ */

#define RCC_GPIOA_CLK_EN()	(SET_BIT(RCC->APB2ENR, 2))
#define RCC_GPIOB_CLK_EN()	(SET_BIT(RCC->APB2ENR, 3))
#define RCC_GPIOC_CLK_EN()	(SET_BIT(RCC->APB2ENR, 4))
#define RCC_GPIOD_CLK_EN()	(SET_BIT(RCC->APB2ENR, 5))
#define RCC_GPIOE_CLK_EN()	(SET_BIT(RCC->APB2ENR, 6))

#define AFIO_CLK_EN()		(SET_BIT(RCC->APB2ENR, 0))

#endif /* STM32F103C6_H_ */

/******************************************************************************
 *  END OF FILE: stm32F103c8tx.h
 ******************************************************************************/
