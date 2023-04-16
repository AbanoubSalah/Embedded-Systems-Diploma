/*******************************************************************************
 * spi_interface.h
 *
 *  Created on: Apr 11, 2023
 *      Author: Abanoub Salah
 ******************************************************************************/

#ifndef MCAL_SPI_SPI_INTERFACE_H_
#define MCAL_SPI_SPI_INTERFACE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "atmega32.h"
#include "platform_types.h"
#include "bit_math.h"
#include "gpio_interface.h"

/*******************************************************************************
 * SPI configuration enumerations & structures definitions
 ******************************************************************************/

/* @ref SPI_Interrupt */
typedef enum
{
  SPI_Interrupt_Disable = 0,
  SPI_Interrupt_Enable = 1,
} SPI_Interrupt_et;

/* @ref SPI_DataOrder */
typedef enum
{
  SPI_DataOrder_MSB_First = 0,
  SPI_DataOrder_LSB_First = 1,
} SPI_DataOrder_et;

/* @ref SPI_Master_Slave_Select */
typedef enum
{
  SPI_Master_Slave_Select_Slave = 0,
  SPI_Master_Slave_Select_Master = 1,
} SPI_Master_Slave_Select_et;

/* @ref SPI_ClockPolarity */
typedef enum
{
  SPI_ClockPolarity_Idle_Low = 0,
  SPI_ClockPolarity_Idle_High = 1,
} SPI_ClockPolarity_et;

/* @ref SPI_ClockPhase */
typedef enum
{
  SPI_ClockPhase_Sample_Leading_setup_trailing = 0,
  SPI_ClockPhase_setup_Leading_sample_trailing = 1,
} SPI_ClockPhase_et;

/* @ref SPI_ClockRate */
typedef enum
{
  SPI_ClockRate_4 = 0,
  SPI_ClockRate_16 = 1,
  SPI_ClockRate_64 = 2,
  SPI_ClockRate_128 = 3,
} SPI_ClockRate_et;

/* @ref SPI_DoubleSpeed */
typedef enum
{
  SPI_DoubleSpeed_Disable = 0,
  SPI_DoubleSpeed_Enable = 1,
} SPI_DoubleSpeed_et;

/* @ref SPI_Status */
typedef enum
{
	SPI_Status_Ok = 0x00,
	SPI_Status_Error = 0x01,
	SPI_Status_WaitingOnInterrupt = 0x02,
	SPI_Status_WriteCollision = 0x04,
} SPI_Status_et;

/* @ref SPI_Config */
typedef struct
{
  SPI_Interrupt_et interruptEnable;			/* Interrupt enable option @ref SPI_Interrupt */
  void (*interruptCallBack)(void);			/* Interrupt callback function pointer */
  SPI_DataOrder_et dataOrder;				/* Data order option @ref SPI_Interrupt */
  SPI_Master_Slave_Select_et modeSelect;	/* Master/Slave select option @ref SPI_Interrupt */
  SPI_ClockPolarity_et clockPolarity;		/* Clock polarity option @ref SPI_Interrupt */
  SPI_ClockPhase_et clockPhase;				/* Clock phase option @ref SPI_Interrupt */
  SPI_ClockRate_et clockRate;				/* Clock rate option @ref SPI_Interrupt */
  SPI_DoubleSpeed_et doubleSpeed;			/* Double speed enable option @ref SPI_Interrupt */
  SPI_Status_et status;						/* Last SPI operation error code @ref SPI_Interrupt */
} SPI_Config_t;

/*******************************************************************************
 * APIs Supported by "MCAL SPI DRIVER"
 ******************************************************************************/

/*******************************************************************************
 * Fn                - MCAL_SPI_Void_Init
 *
 * Brief             - Initializes the SPI according to the specified
 *                     parameters in the Configuration
 *
 * Param [in]        - Configuration parameter @ref SPI_Config
 *
 * Retval            - None
 *
 * Note              - None
 ******************************************************************************/
void MCAL_SPI_Void_Init(SPI_Config_t *);

/*******************************************************************************
 * Fn                - MCAL_SPI_Void_transceive
 *
 * Brief             - Exchange the given data through SPI
 *
 * Param [in]        - Pointer to data to be sent through
 *
 * Param [in]        - Pointer to data to be receive through
 *
 * Retval            - None
 *
 * Note              - None
 ******************************************************************************/
void MCAL_SPI_Void_transceive(SPI_Config_t *, uint8_t *, uint8_t *);

/*******************************************************************************
 * Fn                - MCAL_SPI_Void_SetCallBackFunction
 *
 * Brief             - Set interrupt callback function
 *
 * Param [in]        - Pointer to callback function
 *
 * Retval            - None
 *
 * Note              - None
 ******************************************************************************/
void MCAL_SPI_Void_SetCallBackFunction(void (*)(void));

#endif /* MCAL_SPI_SPI_INTERFACE_H_ */

/*******************************************************************************
 *  END OF FILE: spi_interface.h
 ******************************************************************************/
