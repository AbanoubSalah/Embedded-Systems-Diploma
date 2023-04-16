/*******************************************************************************
 * usart_private.h
 *
 *  Created on: Apr 3, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

#ifndef MCAL_USART_USART_PRIVATE_H_
#define MCAL_USART_USART_PRIVATE_H_

/*******************************************************************************
 * Defines
 ******************************************************************************/
#define USART_NUL_CHARACTER				'\0'
#define USART_CR1_INTERRUPTS_MASK		(0x01F0UL)

/* Status register bits */
#define USART_SR_PE				    0U
#define USART_SR_FE				    1U
#define USART_SR_NE				    2U
#define USART_SR_ORE			    3U
#define USART_SR_IDIE			    4U
#define USART_SR_RXNE			    5U
#define USART_SR_TC				    6U
#define USART_SR_TXE			    7U
#define USART_SR_LBD			    8U
#define USART_SR_CTS			    9U

/* Baud rate register bits */
#define USART_BRR_DIV_Fraction		0U
#define USART_BRR_DIV_Mantissa		4U

/* Control register-1 bits */
#define USART_CR1_SBK				0U
#define USART_CR1_RWU				1U
#define USART_CR1_RE				2U
#define USART_CR1_TE				3U
#define USART_CR1_IDLEIE			4U
#define USART_CR1_RXNEIE			5U
#define USART_CR1_TCIE				6U
#define USART_CR1_TXEIE				7U
#define USART_CR1_PEIE				8U
#define USART_CR1_PS				9U
#define USART_CR1_PCE				10U
#define USART_CR1_WAKE				11
#define USART_CR1_M					12
#define USART_CR1_UE				13

/* Control register-2 bits */
#define USART_CR2_ADD				0
#define USART_CR2_LBDL				5
#define USART_CR2_LBDIE				6
#define USART_CR2_LBCL				8
#define USART_CR2_CPHA				9
#define USART_CR2_CPOL				10
#define USART_CR2_CLKEN				11
#define USART_CR2_STOP				12
#define USART_CR2_LINEN				14

/* Control register-3 bits */
#define USART_CR3_EIE				0
#define USART_CR3_IREN				1
#define USART_CR3_IRLP				2
#define USART_CR3_HDSEL				3
#define USART_CR3_NACK				4
#define USART_CR3_SCEN				5
#define USART_CR3_DMAR				6
#define USART_CR3_DMAT				7
#define USART_CR3_RTSE				8
#define USART_CR3_CTSE				9
#define USART_CR3_CTSIE				10

#endif /* MCAL_USART_USART_PRIVATE_H_ */

/******************************************************************************
 *  END OF FILE: usart_private.h
 ******************************************************************************/
