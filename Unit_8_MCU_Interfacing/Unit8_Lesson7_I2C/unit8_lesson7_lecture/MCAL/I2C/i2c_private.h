/*******************************************************************************
 * i2c_private.h
 *
 *  Created on: Apr 12, 2023
 *      Author: Abanoub Salah
 ******************************************************************************/

#ifndef MCAL_I2C_I2C_PRIVATE_H_
#define MCAL_I2C_I2C_PRIVATE_H_

/*******************************************************************************
 * Includes
******************************************************************************/
#include "stm32F103c6.h"

/*******************************************************************************
 * Macro definitions
 ******************************************************************************/
#define I2C_7BIT_ADDRESS_MASK		0X7F
#define I2C_10BIT_ADDRESS_MASK		0X3FF
#define I2C_CR2_FREQUENCY_MASK		0x003F
#define I2C_CCR_VALUE_MASK			0x0FFF

/*******************************************************************************
 * Peripheral bits
 ******************************************************************************/

/* Control Register-1 bits */
#define I2C_CR1_SWRST				15U
#define I2C_CR1_ALERT				13U
#define I2C_CR1_PEC					12U
#define I2C_CR1_POS					11U
#define I2C_CR1_ACK					10U
#define I2C_CR1_STOP				9U
#define I2C_CR1_START				8U
#define I2C_CR1_NOSTRETCH			7U
#define I2C_CR1_ENGC				6U
#define I2C_CR1_ENPEC				5U
#define I2C_CR1_ENARP				4U
#define I2C_CR1_SMBTYPE				3U
#define I2C_CR1_SMBUS				1U
#define I2C_CR1_PE					0U

/* Control Register-2 bits */
#define I2C_CR2_LAST				12U
#define I2C_CR2_DMAEN				11U
#define I2C_CR2_ITBUFEN				10U
#define I2C_CR2_ITEVTEN				9U
#define I2C_CR2_ITERREN				8U
#define I2C_CR2_FREQ_5_0			0U

/* Own address register-1 bits */
#define I2C_OAR1_ADDMODE			15U
#define I2C_OAR1_ADD_9_8			8U
#define I2C_OAR1_ADD_7_1			1U
#define I2C_OAR1_ADD_0				0U

/* Own address register-2 bits */
#define I2C_OAR2_ADD2_7_1			1U
#define I2C_OAR2_ENDUAL				0U

/* Status register-1 bits */
#define I2C_SR1_SMBALERT			15U
#define I2C_SR1_TIMEOUT				14U
#define I2C_SR1_PECERR				12U
#define I2C_SR1_OVR					11U
#define I2C_SR1_AF					10U
#define I2C_SR1_ARLO				9U
#define I2C_SR1_BERR				8U
#define I2C_SR1_TXE					7U
#define I2C_SR1_RXNE				6U
#define I2C_SR1_STOPF				4U
#define I2C_SR1_ADD10				3U
#define I2C_SR1_BTF					2U
#define I2C_SR1_ADDR				1U
#define I2C_SR1_SB					0U

/* Status register-1 bits */
#define I2C_SR2_DUALF				7U
#define I2C_SR2_SMBHOST				6U
#define I2C_SR2_SMBDEFAULT			5U
#define I2C_SR2_GENCALL				4U
#define I2C_SR2_TRA					2U
#define I2C_SR2_BUSY				1U
#define I2C_SR2_MSL					0U

/* Clock control register bits */
#define I2C_CCR_F_S					15U
#define I2C_CCR_DUTY				14U
#define I2C_CCR_CCR_11_0			0U

static void I2C_Void_GenerateStartCondition(I2C_Config_t *, I2C_StartCondition_et);
static void I2C_Void_GenerateStopCondition(I2C_Config_t *, I2C_StopCondition_et);
static void I2C_Void_SendAddress(I2C_Config_t *, uint16_t, I2C_RWOperation_et);
static void I2C_Void_GenerateAck(I2C_Config_t *, I2C_AcknowledgeControl_et);
static uint8_t I2C_U8_GetEventStatus(I2C_Config_t *, uint32_t, uint8_t, uint32_t);

#endif /* MCAL_I2C_I2C_PRIVATE_H_ */

/*******************************************************************************
 *  END OF FILE: i2c_private.h
 ******************************************************************************/
