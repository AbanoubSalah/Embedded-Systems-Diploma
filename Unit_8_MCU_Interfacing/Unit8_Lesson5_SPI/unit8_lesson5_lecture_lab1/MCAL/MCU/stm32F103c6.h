/*******************************************************************************
 * stm32F103c8tx.h
 *
 *  Created on: Mar 27, 2023
 *      Author: Abanoub Salah
 ******************************************************************************/

#ifndef MCAL_MCU_STM32F103C6_H_
#define MCAL_MCU_STM32F103C6_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "bit_math.h"
#include "platform_types.h"

/*******************************************************************************
 * Base addresses for Memories
 ******************************************************************************/

#define PRIVATE_PERIPHERALS_BASE		0xE0000000UL
#define PERIPHERALS_BASE				0x40000000UL
#define SRAM_BASE						0x20000000UL
#define FLASH_BASE 						0x08000000UL

#define APB1_BUS_BASE     				(PERIPHERALS_BASE)
#define APB2_BUS_BASE     				(PERIPHERALS_BASE + 0x00010000UL)
#define AHB_BUS_BASE      				(PERIPHERALS_BASE + 0x00018000UL)
#define NVIC_BASE_ADDRESS 				(PRIVATE_PERIPHERALS_BASE + 0x0000E100UL)

/*******************************************************************************
 * Base addresses for AHB Peripherals
 ******************************************************************************/
#define RCC_BASE            			(AHB_BUS_BASE + 0x00009000UL)

/*******************************************************************************
 * Base addresses for APB2 Peripherals
 ******************************************************************************/

#define AFIO_BASE           (APB2_BUS_BASE + 0x00000000UL)
#define EXTI_BASE           (APB2_BUS_BASE + 0x00000400UL)
#define GPIOA_BASE          (APB2_BUS_BASE + 0x00000800UL)
#define GPIOB_BASE          (APB2_BUS_BASE + 0x00000C00UL)
#define GPIOC_BASE          (APB2_BUS_BASE + 0x00001000UL)
#define GPIOD_BASE          (APB2_BUS_BASE + 0x00001400UL)
#define GPIOE_BASE          (APB2_BUS_BASE + 0x00001800UL)
#define SPI1_BASE			(APB2_BUS_BASE + 0x00003000UL)
#define USART1_BASE         (APB2_BUS_BASE + 0x00003800UL)

/*******************************************************************************
 * Base addresses for APB1 Peripherals
 ******************************************************************************/

#define SPI2_BASE			(APB2_BUS_BASE + 0x00003800UL)
#define USART2_BASE         (APB1_BUS_BASE + 0x00004400UL)
#define USART3_BASE         (APB1_BUS_BASE + 0x00004800UL)
#define I2C1_BASE         	(APB1_BUS_BASE + 0x00005400UL)
#define I2C2_BASE         	(APB1_BUS_BASE + 0x00005800UL)

/*******************************************************************************
 * Peripheral register: GPIO
 ******************************************************************************/

typedef struct
{
	 vuint32_t CRL;
	 vuint32_t CRH;
	 vuint32_t IDR;
	 vuint32_t ODR;
	 vuint32_t BSRR;
	 vuint32_t BRR;
	 vuint32_t LCKR;
} GPIO_TypeDef_t;

/*******************************************************************************
 * Peripheral register: RCC
 ******************************************************************************/

typedef struct
{
	 vuint32_t CR;
	 vuint32_t CFGR;
	 vuint32_t CIR;
	 vuint32_t APB2RSTR;
	 vuint32_t APB1RSTR;
	 vuint32_t AHBENR;
	 vuint32_t APB2ENR;
	 vuint32_t APB1ENR;
	 vuint32_t BDCR;
	 vuint32_t CSR;
} RCC_TypeDef_t;

/*******************************************************************************
 * Peripheral register: AFIO
 ******************************************************************************/

typedef struct
{
	 vuint32_t EVCR;
	 vuint32_t MAPR;
	 vuint32_t EXTICR[4];
	 uint32_t RESERVED0;
	 vuint32_t MAPR2;
}AFIO_TypeDef_t;

/*******************************************************************************
 * Peripheral register: EXTI
 ******************************************************************************/

typedef struct
{
	 vuint32_t IMR;
	 vuint32_t EMR;
	 vuint32_t RTSR;
	 vuint32_t FTSR;
	 vuint32_t SWIER;
	 vuint32_t PR;
}EXTI_TypeDef_t;

/*******************************************************************************
 * Peripheral register: NVIC
 ******************************************************************************/
typedef struct
{
	vuint32_t ISER[3];
	vuint32_t RESERVED[29U];
	vuint32_t ICER[3];
	vuint32_t RESERVED0[29U];
	vuint32_t ISPR[3];
	vuint32_t RESERVED1[29U];
	vuint32_t ICPR[3];
	vuint32_t RESERVED2[29U];
	vuint32_t IABR[3];
	vuint32_t RESERVED3[61U];
	vuint8_t IPR[81];
	vuint32_t RESERVED4[693U];
	vuint32_t STIR;
} NVIC_TypeDef_t;

/*******************************************************************************
 * Peripheral register: SPI
 ******************************************************************************/

typedef struct
{
	vuint32_t CR1;
	vuint32_t CR2;
	vuint32_t SR;
	vuint32_t DR;
	vuint32_t CRCPR;
	vuint32_t RXCRCR;
	vuint32_t TXCRCR;
	vuint32_t I2SCFGR;
	vuint32_t I2SPR;

} SPI_TypeDef_t;

/*******************************************************************************
 * Peripheral register: USART
 ******************************************************************************/
typedef struct
{
	vuint32_t SR;
	vuint32_t DR;
	vuint32_t BRR;
	vuint32_t CR1;
	vuint32_t CR2;
	vuint32_t CR3;
	vuint32_t GTPR;
} USART_TypeDef_t;

/*******************************************************************************
 * Peripheral register: I2C
 ******************************************************************************/

typedef struct
{
	 vuint32_t CR1;
	 vuint32_t CR2;
	 vuint32_t OAR1;
	 vuint32_t OAR2;
	 vuint32_t DR;
	 vuint32_t SR1;
	 vuint32_t SR2;
	 vuint32_t CCR;
	 vuint32_t TRISE;
} I2C_TypeDef_t;

/*******************************************************************************
 * Peripheral instances
 ******************************************************************************/

#define GPIOA			((GPIO_TypeDef_t *) GPIOA_BASE)
#define GPIOB			((GPIO_TypeDef_t *) GPIOB_BASE)
#define GPIOC			((GPIO_TypeDef_t *) GPIOC_BASE)
#define GPIOD			((GPIO_TypeDef_t *) GPIOD_BASE)
#define GPIOE			((GPIO_TypeDef_t *) GPIOE_BASE)

#define RCC				((RCC_TypeDef_t *) RCC_BASE)
#define EXTI			((EXTI_TypeDef_t *) EXTI_BASE)
#define AFIO			((AFIO_TypeDef_t *) AFIO_BASE)
#define NVIC			((NVIC_TypeDef_t *) NVIC_BASE_ADDRESS)

#define SPI1			((SPI_TypeDef_t *) SPI1_BASE)
#define SPI2			((SPI_TypeDef_t *) SPI2_BASE)

#define USART1			((USART_TypeDef_t *) USART1_BASE)
#define USART2			((USART_TypeDef_t *) USART2_BASE)
#define USART3			((USART_TypeDef_t *) USART3_BASE)

#define I2C1			((I2C_TypeDef_t *) I2C1_BASE)
#define I2C2			((I2C_TypeDef_t *) I2C2_BASE)

#endif /* MCAL_MCU_STM32F103C6_H_ */

/*******************************************************************************
 *  END OF FILE: stm32F103c8tx.h
 ******************************************************************************/
