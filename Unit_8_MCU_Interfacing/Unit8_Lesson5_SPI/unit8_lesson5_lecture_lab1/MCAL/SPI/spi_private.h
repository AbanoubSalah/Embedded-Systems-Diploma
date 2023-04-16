/*******************************************************************************
 * spi_private.h
 *
 *  Created on: Apr 10, 2023
 *      Author: Abanoub Salah
 ******************************************************************************/

#ifndef MCAL_SPI_SPI_PRIVATE_H_
#define MCAL_SPI_SPI_PRIVATE_H_

/*******************************************************************************
 * Includes
******************************************************************************/
#include "stm32F103c6.h"

/*******************************************************************************
 * Peripheral bits
 ******************************************************************************/

/* Control Register-1 bits */
#define SPI_CR1_BIDI_MODE_BIT					15U
#define SPI_CR1_BIDI_OE_BIT						14U
#define SPI_CR1_CRC_EN_BIT						13U
#define SPI_CR1_CRC_NEXT_BIT					12U
#define SPI_CR1_DFF_BIT							11U
#define SPI_CR1_RX_ONLY_BIT						10U
#define SPI_CR1_SSM_BIT							9U
#define SPI_CR1_SSI_BIT							8U
#define SPI_CR1_LSB_FIRST_BIT					7U
#define SPI_CR1_SPE_BIT							6U
#define SPI_CR1_BR_BIT							3U
#define SPI_CR1_MSTR_BIT						2U
#define SPI_CR1_CPOL_BIT						1U
#define SPI_CR1_CPHA_BIT						0U

/* Control Register-2 bits */
#define SPI_CR2_TXEIE_BIT						7U
#define SPI_CR2_RXNEIE_BIT						6U
#define SPI_CR2_ERRIE_BIT						5U
#define SPI_CR2_SSOE_BIT						2U
#define SPI_CR2_TXDMAEN_BIT						1U
#define SPI_CR2_RXDMAEN_BIT						0U

/* Status Register bits */
#define SPI_SR_BSY_BIT							7U
#define SPI_SR_OVR_BIT							6U
#define SPI_SR_MODF_BIT							5U
#define SPI_SR_CRC_ERR_BIT						4U
#define SPI_SR_UDR_BIT							3U
#define SPI_SR_CHSIDE_BIT						2U
#define SPI_SR_TXE_BIT							1U
#define SPI_SR_RXNE_BIT							0U

#define SPI_SR_ERROR_FLAGS_MASK					(0x70U)

#endif /* MCAL_SPI_SPI_PRIVATE_H_ */

/******************************************************************************
 *  END OF FILE: spi_private.h
 ******************************************************************************/
