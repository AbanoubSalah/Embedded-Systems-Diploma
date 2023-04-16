/*******************************************************************************
 * spi_private.h
 *
 *  Created on: Apr 11, 2023
 *      Author: Abanoub Salah
 ******************************************************************************/

#ifndef MCAL_SPI_SPI_PRIVATE_H_
#define MCAL_SPI_SPI_PRIVATE_H_

/*******************************************************************************
 * Includes
******************************************************************************/
#include "atmega32.h"

/*******************************************************************************
 *   User type definitions (structures)
 ******************************************************************************/
typedef struct
{
	vuint8_t SPCR;
	vuint8_t SPSR;
	vuint8_t SPDR;
} SPI_Typedef_t;

/*******************************************************************************
 * Peripheral instances
 ******************************************************************************/
#define SPI				 ((SPI_Typedef_t *) SPI_BASE)

/*******************************************************************************
 * Peripheral bits
 ******************************************************************************/

/* SPCR bits */
#define SPI_SPCR_SPR0		0
#define SPI_SPCR_SPR1		1
#define SPI_SPCR_CPHA		2
#define SPI_SPCR_CPOL		3
#define SPI_SPCR_MSTR		4
#define SPI_SPCR_DORD		5
#define SPI_SPCR_SPE		6
#define SPI_SPCR_SPIE		7

/* SPSR bits */
#define SPI_SPSR_SPI2X		0
#define SPI_SPSR_WCOL		6
#define SPI_SPSR_SPIF		7

#endif /* MCAL_SPI_SPI_PRIVATE_H_ */

/******************************************************************************
 *  END OF FILE: spi_private.h
 ******************************************************************************/
