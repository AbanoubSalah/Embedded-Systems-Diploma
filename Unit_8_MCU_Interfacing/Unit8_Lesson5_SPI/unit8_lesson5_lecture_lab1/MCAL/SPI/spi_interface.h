/*******************************************************************************
 * spi_interface.h
 *
 *  Created on: Apr 10, 2023
 *      Author: Abanoub Salah
 ******************************************************************************/

#ifndef MCAL_SPI_SPI_INTERFACE_H_
#define MCAL_SPI_SPI_INTERFACE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "stm32F103c6.h"
#include "platform_types.h"
#include "bit_math.h"
#include "gpio_interface.h"
#include "rcc_interface.h"

/*******************************************************************************
 * SPI configuration enumerations & structures definitions
 ******************************************************************************/

/* @ref SPI_MasterSelection */
typedef enum
{
	SPI_MasterSelection_Slave = 0x0000,
	SPI_MasterSelection_Master = 0x0004,
} SPI_MasterSelection_et;

/* @ref SPI_CommunicationMode */
typedef enum
{
	SPI_CommunicationMode_2line_unidirectionalTxRx = 0x0000,
	SPI_CommunicationMode_2line_unidirectionalRx = 0x0400,
	SPI_CommunicationMode_1line_bidirectionalRx = 0x8000,
	SPI_CommunicationMode_1line_bidirectionalTx = 0xC000,
} SPI_CommunicationMode_et;

/* @ref SPI_FrameFormat */
typedef enum
{
	SPI_FrameFormat_MSB_First = 0x0000,
	SPI_FrameFormat_LSB_First = 0x0080,
} SPI_FrameFormat_et;

/* @ref SPI_DataFrameFormat */
typedef enum
{
	SPI_DataFrameFormat_8Bit = 0x0000,
	SPI_DataFrameFormat_16Bit = 0x0800,
} SPI_DataFrameFormat_et;

/* @ref SPI_ClockPolarity */
typedef enum
{
  SPI_ClockPolarity_Idle_Low = 0x0000,
  SPI_ClockPolarity_Idle_High = 0x0002,
} SPI_ClockPolarity_et;

/* @ref SPI_ClockPhase */
typedef enum
{
  SPI_ClockPhase_Sample_Leading_setup_trailing = 0x0000,
  SPI_ClockPhase_setup_Leading_sample_trailing = 0x0001,
} SPI_ClockPhase_et;

/* @ref SPI_NSS */
typedef enum
{
	SPI_NSS_SlaveHardware = 0x0000,
	SPI_NSS_MasterHardwareOutputDisable = 0x0000,
	SPI_NSS_MasterHardwareOutputEnable = 0x0004,
	SPI_NSS_SoftwareSSIReset = 0x0200,
	SPI_NSS_SoftwareSSISet = 0x0300,
} SPI_NSS_et;

/* @ref SPI_Prescaler */
typedef enum
{
	SPI_Prescaler_2 = 0x0000,
	SPI_Prescaler_4 = 0x0001,
	SPI_Prescaler_8 = 0x0002,
	SPI_Prescaler_16 = 0x0003,
	SPI_Prescaler_32 = 0x0004,
	SPI_Prescaler_64 = 0x0005,
	SPI_Prescaler_128 = 0x0006,
	SPI_Prescaler_256 = 0x0007,
} SPI_Prescaler_et;

/* @ref SPI_IRQEnable */
typedef enum
{
	SPI_IRQEnable_NONE = 0x0000,
	SPI_IRQEnable_ERRIE = 0x0020,
	SPI_IRQEnable_RXNEIE = 0x0040,
	SPI_IRQEnable_TXEIE = 0x0080,
} SPI_IRQEnable_et;

/* @ref SPI_Status */
typedef enum
{
	SPI_Status_Ok = 0x0000,
	SPI_Status_Error = 0x0001,
	SPI_Status_CRCError = 0x0010,
	SPI_Status_ModFault = 0x0020,
	SPI_Status_Overrun = 0x0040,
} SPI_Status_et;

/* @ref SPI_Mechanism */
typedef enum
{
	SPI_Mechanism_Polling = 0x0000,
	SPI_Mechanism_Interrupt = 0x0001,
} SPI_Mechanism_et;

/* @ref SPI_Config */
typedef struct
{
	SPI_TypeDef_t *SPIx;						/* specifies SPI Peripheral instance where x = 1 or 2 */
	SPI_MasterSelection_et masterSelection;		/* specifies SPI operating mode @ref SPI_MasterSelection */
	SPI_CommunicationMode_et communicationMode;	/* specifies SPI bi-directional mode  @ref SPI_CommunicationMode */
	SPI_FrameFormat_et frameFormat;				/* specifies MSB transmit first or LSB transmit first  @ref SPI_FrameFormat */
	SPI_DataFrameFormat_et dataFrameFormat;		/* specifies frame size @ref SPI_DataFrameFormat */
	SPI_ClockPolarity_et clockPolarity;			/* specifies SPI clock Polarity @ref SPI_ClockPolarity */
	SPI_ClockPhase_et clockPhase;				/* specifies SPI clock Phase @ref SPI_ClockPhase */
	SPI_NSS_et NSS;								/* specifies slave select management @ref SPI_NSS */
	SPI_Prescaler_et clockPreScaler;			/* specifies SPI baud rate @ref SPI_Prescaler */
	SPI_IRQEnable_et IRQ_Enable;				/* specifies SPI Interrupt Requests @ref SPI_IRQEnable N.B. multiple flags can be or-ed together to enable different interrupt */
	SPI_Status_et status;						/* specifies SPI last operation exit code @ref SPI_Status */
	void (* pIRQCallBack)();					/* specifies the callback Function that serve the IRQ */
} SPI_Config_t;

/*******************************************************************************
 * APIs Supported by "MCAL SPI DRIVER"
 ******************************************************************************/

/*******************************************************************************
* Fn                - MCAL_SPI_Void_Init
*
* Brief             - Initiate SPI peripheral using provided parameters
*
* Param [in]        - SPI configuration structure @ref SPI_Config
*
* Retval            - None
*
* Note              - None
*******************************************************************************/
void MCAL_SPI_Void_Init(SPI_Config_t *);

/*******************************************************************************
* Fn                - MCAL_SPI_Void_DeInit
*
* Brief             - De-Initiate SPI peripheral
*
* Param [in]        - SPI configuration structure @ref SPI_Config
*
* Retval            - None
*
* Note              - None
*******************************************************************************/
void MCAL_SPI_Void_DeInit(SPI_Config_t *);

/*******************************************************************************
* Fn                - MCAL_SPI_Void_Receive
*
* Brief             - Receive 8/16 bit of data
*
* Param [in]        - SPI configuration structure @ref SPI_Config
*
* Param [in]        - Pointer to receive buffer
*
* Param [in]        - Receiving mechanism @ref SPI_Mechanism
*
* Retval            - None
*
* Note              - None
*******************************************************************************/
void MCAL_SPI_Void_Receive(SPI_Config_t *, uint16_t *, SPI_Mechanism_et);

/*******************************************************************************
* Fn                - MCAL_SPI_Void_Send
*
* Brief             - Send 8/16 bit of data
*
* Param [in]        - SPI configuration structure @ref SPI_Config
*
* Param [in]        - Pointer to transmit buffer
*
* Param [in]        - Receiving mechanism @ref SPI_Mechanism
*
* Retval            - None
*
* Note              - None
*******************************************************************************/
void MCAL_SPI_Void_Send(SPI_Config_t *, uint16_t *, SPI_Mechanism_et);

/*******************************************************************************
* Fn                - MCAL_SPI_Void_Transceive
*
* Brief             - Exchange 8/16 bit of data
*
* Param [in]        - SPI configuration structure @ref SPI_Config
*
* Param [in]        - Pointer to exchange buffer
*
* Param [in]        - Receiving mechanism @ref SPI_Mechanism
*
* Retval            - None
*
* Note              - None
*******************************************************************************/
void MCAL_SPI_Void_Transceive(SPI_Config_t *, uint16_t *, SPI_Mechanism_et);

#endif /* MCAL_SPI_SPI_INTERFACE_H_ */

/*******************************************************************************
 *  END OF FILE: spi_interface.h
 ******************************************************************************/
