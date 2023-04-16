/*******************************************************************************
 * i2c_interface.h
 *
 *  Created on: Apr 12, 2023
 *      Author: Abanoub Salah
 ******************************************************************************/

#ifndef MCAL_I2C_I2C_INTERFACE_H_
#define MCAL_I2C_I2C_INTERFACE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "stm32F103c6.h"
#include "platform_types.h"
#include "bit_math.h"
#include "gpio_interface.h"
#include "rcc_interface.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define I2C_MAX_TIMEOUT								(0xFFFFFFFF)
#define I2C_TYPICAL_TIMEOUT							(0xFF)

/* I2C events flags definitions */
#define I2C_EVENT_SR1_SB							(0x00000001UL)
#define I2C_EVENT_SR1_ADDR							(0x00000002UL)
#define I2C_EVENT_SR1_BTF							(0x00000004UL)
#define I2C_EVENT_SR1_ADD10							(0x00000008UL)
#define I2C_EVENT_SR1_STOPF							(0x00000010UL)
#define I2C_EVENT_SR1_RXNE							(0x00000040UL)
#define I2C_EVENT_SR1_TXE							(0x00000080UL)
#define I2C_EVENT_SR2_MSL							(0x00010000UL)
#define I2C_EVENT_SR2_BUSY							(0x00020000UL)
#define I2C_EVENT_SR2_TRA							(0x00040000UL)
#define I2C_EVENT_SR2_GENCALL						(0x00100000UL)


/*******************************************************************************
 * SPI configuration enumerations & structures definitions
 ******************************************************************************/

/* @ref I2C_StretchMode */
typedef enum
{
	I2C_StretchMode_Enable = 0U,
	I2C_StretchMode_Disable = 1U,
} I2C_StretchMode_et;

/* @ref I2C_GeneralCall */
typedef enum
{
	I2C_GeneralCall_Disable = 0U,
	I2C_GeneralCall_Enable = 1U,
} I2C_GeneralCall_et;

/* @ref I2C_Speed */
typedef enum
{
	I2C_Speed_standardMode = 0U,
	I2C_Speed_FastMode = 1U,
} I2C_Speed_et;

/* @ref I2C_Mode */
typedef enum
{
	I2C_Mode_I2C = 0U,
	I2C_Mode_SMBus = 1U,
} I2C_Mode_et;

/* @ref I2C_AckControl */
typedef enum
{
	I2C_AcknowledgeControl_Disable = 0U,
	I2C_AcknowledgeControl_Enable = 1U,
} I2C_AcknowledgeControl_et;

/* @ref I2C_SlaveAddressMode */
typedef enum
{
	I2C_SlaveAddressMode_7Bit = 0U,
	I2C_SlaveAddressMode_10Bit = 1U,
} I2C_SlaveAddressMode_et;

/* @ref I2C_DualAddress */
typedef enum
{
	I2C_DualAddress_Disable = 0U,
	I2C_DualAddress_Enable = 1U,
} I2C_DualAddress_et;

/* @ref I2C_slave_address */
typedef struct
{
	uint16_t firstAddress;						/* First address 7/10 bits */
	uint8_t secondAddress;						/* Second optional address 7-bits */
	I2C_SlaveAddressMode_et addressMode;		/* Addressing mode @ref I2C_SlaveAddressMode */
	I2C_DualAddress_et dualAddressMode;			/* Dual addressing mode @ref I2C_DualAddress */
} I2C_slave_address_st;

/* @ref I2C_IRQEnable */
typedef enum
{
	I2C_IRQEnable_Disable = 0,
	I2C_IRQEnable_Enable = 1,
} I2C_IRQEnable_et;

/* @ref I2C_SlaveCallBackStatus_et */
typedef enum
{
	I2C_SlaveCallBackStatus_Stop,
	I2C_SlaveCallBackStatus_AddressMatched,
	I2C_SlaveCallBackStatus_DataRequested,
	I2C_SlaveCallBackStatus_DataReceived,
} I2C_SlaveCallBackStatus_et;

/* @ref I2C_Status */
typedef enum
{
	I2C_Status_Ok = 0x00,
	I2C_Status_Error = 0xFF,
} I2C_Status_et;

/* @ref I2C_Config */
typedef struct
{
	I2C_TypeDef_t *I2Cx;								/* Specifies I2C peripheral instance where x = 1 or 2 */
	uint32_t clockSpeed;								/* Specifies I2C clock speed in Hz */
	I2C_StretchMode_et stretchMode;						/* Enable/Disable clock stretching in slave mode @ref I2C_StretchMode */
	I2C_GeneralCall_et generalCall;						/* Enable/Disable general call @ref I2C_GeneralCall */
	I2C_Speed_et speed;									/* Specifies I2C speed standard/fast mode  @ref I2C_Speed */
	I2C_Mode_et mode;									/* specifies SMBus/I2C mode @ref I2C_Mode */
	I2C_AcknowledgeControl_et ackControl;				/* Enable/Disable ACK by Hardware @ref I2C_AckControl */
	I2C_slave_address_st slaveAddress;					/* Slave address Configuration @ref I2C_slave_address */
	I2C_IRQEnable_et IRQEnable;                			/* Enable/Disable IRQ @ref I2C_IRQEnable */
	void(*pSlaveCallBack)(I2C_SlaveCallBackStatus_et);	/* Set callback Function which will be called on IRQ */
	I2C_Status_et status;								/* specifies I2C last operation exit code @ref I2C_Status */
} I2C_Config_t;

/* @ref I2C_StartCondition */
typedef enum
{
	I2C_StartCondition_Disable = 0,
	I2C_StartCondition_Enable,
	I2C_StartCondition_Repeated,
} I2C_StartCondition_et;

/* @ref I2C_StopCondition */
typedef enum
{
	I2C_StopCondition_Disable = 0,
	I2C_StopCondition_Enable,
} I2C_StopCondition_et;

typedef enum
{
	I2C_RWOperation_Write = 0,
	I2C_RWOperation_Read = 1,
} I2C_RWOperation_et;

/*******************************************************************************
 * APIs Supported by "MCAL I2C Driver"
 ******************************************************************************/

/*******************************************************************************
* Fn                - MCAL_I2C_Void_Init
*
* Brief             - Initialize I2C peripheral
*
* Param [in]        - Configuration structure @ref I2C_Config
*
* Retval            - None
*
* Note              - None
*******************************************************************************/
void MCAL_I2C_Void_Init(I2C_Config_t *I2C_Config);

/*******************************************************************************
* Fn                - MCAL_I2C_Void_DeInit
*
* Brief             - De-initialize I2C peripheral
*
* Param [in]        - Configuration structure @ref I2C_Config
*
* Retval            - None
*
* Note              - None
*******************************************************************************/
void MCAL_I2C_Void_DeInit(I2C_Config_t *);

/*******************************************************************************
* Fn                - MCAL_I2C_Void_MasterTx
*
* Brief             - Master transmit over I2C bus
*
* Param [in]        - Configuration structure @ref I2C_Config
*
* Param [in]        - Slave address
*
* Param [in]        - Pointer to transmit data
*
* Param [in]        - Data length
*
* Param [in]        - Stop condition @ref I2C_StopCondition
*
* Param [in]        - Start condition @ref I2C_StartCondition
*
* Retval            - None
*
* Note              - None
*******************************************************************************/
void MCAL_I2C_Void_MasterTx(I2C_Config_t *, uint16_t, uint8_t *, uint8_t, I2C_StopCondition_et, I2C_StartCondition_et);

/*******************************************************************************
* Fn                - MCAL_I2C_Void_MasterRx
*
* Brief             - Master receive over I2C bus
*
* Param [in]        - Configuration structure @ref I2C_Config
*
* Param [in]        - Slave address
*
* Param [in]        - Pointer to send data
*
* Param [in]        - Data length
*
* Param [in]        - Stop condition @ref I2C_StopCondition
*
* Param [in]        - Start condition @ref I2C_StartCondition
*
* Retval            - None
*
* Note              - None
*******************************************************************************/
void MCAL_I2C_Void_MasterRx(I2C_Config_t *, uint16_t, uint8_t *, uint8_t, I2C_StopCondition_et, I2C_StartCondition_et);

/*******************************************************************************
* Fn                - MCAL_I2C_Void_SlaveTx
*
* Brief             - Slave transmit over I2C bus
*
* Param [in]        - Configuration structure @ref I2C_Config
*
* Param [in]        - Pointer to transmit data
*
* Retval            - None
*
* Note              - None
*******************************************************************************/
void MCAL_I2C_Void_SlaveTx(I2C_Config_t *, uint8_t *);

/*******************************************************************************
* Fn                - MCAL_I2C_Void_SlaveRx
*
* Brief             - Slave receive over I2C bus
*
* Param [in]        - Configuration structure @ref I2C_Config
*
* Param [in]        - Pointer to receive data
*
* Retval            - None
*
* Note              - None
*******************************************************************************/
void MCAL_I2C_Void_SlaveRx(I2C_Config_t *, uint8_t *);

#endif /* MCAL_I2C_I2C_INTERFACE_H_ */

/*******************************************************************************
 *  END OF FILE: i2c_interface.h
 ******************************************************************************/
