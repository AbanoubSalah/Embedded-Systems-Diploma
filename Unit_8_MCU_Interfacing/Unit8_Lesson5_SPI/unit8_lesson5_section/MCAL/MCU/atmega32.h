/*******************************************************************************
 * atmega32.h
 *
 *  Created on: Apr 2, 2023
 *      Author: Abanoub Salah
 ******************************************************************************/

#ifndef MCAL_MCU_ATMEGA32_H_
#define MCAL_MCU_ATMEGA32_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "platform_types.h"

/*******************************************************************************
 * Base addresses for memories
 ******************************************************************************/
#define FLASH_MEMORY_BASE		0x00U
#define SRAM_BASE				0x60U
#define GPIOA_BASE				0x39U
#define GPIOB_BASE				0x36U
#define GPIOC_BASE				0x33U
#define GPIOD_BASE				0x30U
#define UART_BASE				0x29U
#define SPI_BASE				0x2DU

/*******************************************************************************
 * Interrupt definitions
 ******************************************************************************/
/* Note: ISR definition only works with GNU GCC */
#define ISR(vector,...)            \
void vector (void) __attribute__ ((__signal__,__used__, __externally_visible__))__VA_ARGS__ ; \
void vector (void)

/* Enable/Disable global interrupt */
#define sei()  __asm__ __volatile__ ("sei" ::)
#define cli()  __asm__ __volatile__ ("cli" ::)

/* SPI vector numbers */
#define SPI_STC_vect			__vector_12

/* USART vector numbers */
#define USART_RXC_vect			__vector_13
#define USART_TXC_vect			__vector_15

#endif /* MCAL_MCU_ATMEGA32_H_ */

/*******************************************************************************
 *  END OF FILE: atmega32.h
 ******************************************************************************/
