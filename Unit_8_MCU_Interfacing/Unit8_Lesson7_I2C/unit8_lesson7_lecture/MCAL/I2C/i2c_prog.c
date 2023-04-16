/*******************************************************************************
 * i2c_prog.c
 *
 *  Created on: Apr 12, 2023
 *      Author: Abanoub Salah
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "i2c_config.h"
#include "i2c_interface.h"
#include "i2c_private.h"

static void (*interruptCallBacks[I2C_PERIPHERALS_COUNT])(I2C_SlaveCallBackStatus_et) = {NULL};

void MCAL_I2C_Void_Init(I2C_Config_t *I2C_Config)
{
	vuint16_t cr1Tmp = 0x0000, cr2Tmp = 0x0000;
	vuint16_t oar1Tmp = 0x0000, oar2Tmp = 0x0000;
	vuint16_t ccrTmp = 0x0000;
	vuint16_t triseTmp = 0x0000;
	vuint32_t currentPeripheralClock;

	/* Enable the I2C clock (done on main initialization) */

	/* Check for peripheral address validity */
	if((I2C1 != I2C_Config->I2Cx) && (I2C2 != I2C_Config->I2Cx))
	{
		I2C_Config->status = I2C_Status_Error;
		return ;
	}
	else
	{
	}

	/* Configure I2C mode */
	if(I2C_Mode_I2C == I2C_Config->mode)
	{	/* I2C mode configuration */

		/* I2C mode */
		cr1Tmp |= (I2C_Config->mode << I2C_CR1_SMBUS);

		/* Get APB1 bus frequency which I2C is on */
		currentPeripheralClock = MCAL_RCC_U32_GetBusFrequency(RCC_BusName_APB1);

		if((I2C_MIN_FREQUENCY > currentPeripheralClock) || (APB2_MAX_FREQUENCY < currentPeripheralClock))
		{
			I2C_Config->status = I2C_Status_Error;
			return ;
		}
		else
		{
		}

		/* Set peripheral clock frequency */
		cr2Tmp |= (uint16_t)(((currentPeripheralClock / HERTZ_PER_MEGAHERTZ) & I2C_CR2_FREQUENCY_MASK) << I2C_CR2_FREQ_5_0);

		/* Enable I2C peripheral */
		SET_BIT(cr1Tmp, I2C_CR1_PE);

		/* Configure standard/fast mode speed */
		if(I2C_SM_MAX_FREQUENCY >= I2C_Config->clockSpeed)
		{	/* Standard mode */
			/* Standard mode calculation */
			/* CCR = currentPeripheralClock / (I2C_Frequency * 2) */

			ccrTmp = ((uint16_t)((currentPeripheralClock / (I2C_Config->clockSpeed << 1)) & I2C_CCR_VALUE_MASK) << I2C_CCR_CCR_11_0);

			/* Rise time Configuration */
			/* For SM I2C: maximum allowed SCL rise time = 1E3 ns */
			/* If peripheral clock = currentPeripheralClock */
			/* Then rise time equals */
			/* (1E3(ns) * currentPeripheralClock(Hz) / 1E9(ns/s)) */
			/* then increment it by one */
			triseTmp = ((currentPeripheralClock / MICROSECONDS_PER_SECONDS) + 1);
		}
		else
		{	/* Fast Mode not supported */
			I2C_Config->status = I2C_Status_Error;
			return ;
		}

		/* Acknowledge enable/disable */
		if((I2C_AcknowledgeControl_Enable == I2C_Config->ackControl) || (I2C_AcknowledgeControl_Disable == I2C_Config->ackControl))
		{
			cr1Tmp |= (I2C_Config->ackControl << I2C_CR1_ACK);
		}
		else
		{
			I2C_Config->status = I2C_Status_Error;
			return ;
		}

		/* General call enable/disable */
		if((I2C_GeneralCall_Enable == I2C_Config->generalCall) || (I2C_GeneralCall_Disable == I2C_Config->generalCall))
		{
			cr1Tmp |= (I2C_Config->generalCall << I2C_CR1_ENGC);
		}
		else
		{
			I2C_Config->status = I2C_Status_Error;
			return ;
		}

		/* Stretch mode enable/disable */
		if((I2C_StretchMode_Enable == I2C_Config->stretchMode) || (I2C_StretchMode_Disable == I2C_Config->stretchMode))
		{
			cr1Tmp |= (I2C_Config->stretchMode << I2C_CR1_NOSTRETCH);
		}
		else
		{
			I2C_Config->status = I2C_Status_Error;
			return ;
		}

		/* Set first address */
		if(I2C_SlaveAddressMode_7Bit == I2C_Config->slaveAddress.addressMode)
		{	/* 7-Bit address */
			oar1Tmp |= (uint16_t)(((I2C_Config->slaveAddress.firstAddress) & I2C_7BIT_ADDRESS_MASK) << I2C_OAR1_ADD_7_1);
			CLR_BIT(oar1Tmp, I2C_OAR1_ADDMODE);
		}
		else if(I2C_SlaveAddressMode_10Bit == I2C_Config->slaveAddress.addressMode)
		{	/* 10-Bit address */
			oar1Tmp |= (uint16_t)(((I2C_Config->slaveAddress.firstAddress) & I2C_10BIT_ADDRESS_MASK) << I2C_OAR1_ADD_0);
			SET_BIT(oar1Tmp, I2C_OAR1_ADDMODE);
		}
		else
		{	/* Wrong parameter */
			I2C_Config->status = I2C_Status_Error;
			return ;
		}

		/* Slave dual addressing mode */
		if(I2C_DualAddress_Enable == I2C_Config->slaveAddress.dualAddressMode)
		{
			/* Enable dual addressing mode */
			SET_BIT(oar2Tmp,  I2C_OAR2_ENDUAL);

			/* Set second address */
			oar2Tmp |= (((I2C_Config->slaveAddress.secondAddress) & I2C_7BIT_ADDRESS_MASK) << I2C_OAR2_ADD2_7_1);
		}
		else
		{
		}
	}
	else
	{	/* SMBus mode configuration not sported */
		I2C_Config->status = I2C_Status_Error;
		return ;
	}

	/* Set interrupt */
	if(I2C_IRQEnable_Enable == I2C_Config->IRQEnable)
	{
		if(I2C1 == I2C_Config->I2Cx)
		{
			interruptCallBacks[0] = I2C_Config->pSlaveCallBack;
		}
		else if(I2C2 == I2C_Config->I2Cx)
		{
			interruptCallBacks[1] = I2C_Config->pSlaveCallBack;
		}
		else
		{
		}

		/* Enable IRQ */
		cr2Tmp |= ((1U << I2C_CR2_ITERREN) | (1U << I2C_CR2_ITEVTEN) | (1U << I2C_CR2_ITBUFEN));
	}
	else
	{
	}

	I2C_Config->I2Cx->CCR = ccrTmp;
	I2C_Config->I2Cx->TRISE = triseTmp;
	I2C_Config->I2Cx->OAR1 = oar1Tmp;
	I2C_Config->I2Cx->OAR2 = oar2Tmp;
	I2C_Config->I2Cx->SR1 = 0;
	I2C_Config->I2Cx->SR2 = 0;
	I2C_Config->I2Cx->CR2 = cr2Tmp;
	I2C_Config->I2Cx->CR1 = cr1Tmp;

	I2C_Config->status = I2C_Status_Ok;

	return ;
}

void MCAL_I2C_Void_DeInit(I2C_Config_t *I2C_Config)
{
	if(I2C1 == I2C_Config->I2Cx)
	{
		MCAL_RCC_Void_ResetPeripheral(RCC_BusName_APB1, RCC_APB1_Peripheral_RST_I2C1RST);
	}
	else if(I2C2 == I2C_Config->I2Cx)
	{
		MCAL_RCC_Void_ResetPeripheral(RCC_BusName_APB1, RCC_APB1_Peripheral_RST_I2C2RST);
	}
	else
	{
		I2C_Config->status = I2C_Status_Error;
		return ;
	}

	return ;
}

void MCAL_I2C_Void_MasterTx(I2C_Config_t *I2C_Config, uint16_t slaveAddress, uint8_t *pTxData, uint8_t dataLength, I2C_StopCondition_et stopCondition, I2C_StartCondition_et startCondition)
{
	/* Generate start condition */
	I2C_Void_GenerateStartCondition(I2C_Config, startCondition);
	if(I2C_Status_Ok != I2C_Config->status)
	{
		I2C_Config->status = I2C_Status_Error;
		return ;
	}
	else
	{
	}

	/* Reading SR1 before writing to DR for SB clearing */
	(void)I2C_Config->I2Cx->SR1;
	/* Send slave address */
	I2C_Void_SendAddress(I2C_Config, slaveAddress, I2C_RWOperation_Write);
	if(I2C_Status_Ok != I2C_Config->status)
	{
		return ;
	}
	else
	{
	}

	/* Loop inside the data to send it */
	while(0 != (dataLength--))
	{
		/* Write to DR register the data to be sent */
		I2C_Config->I2Cx->DR = *(pTxData++);

		/* Wait on TxE event */
		if(FALSE == I2C_U8_GetEventStatus(I2C_Config, I2C_EVENT_SR1_BTF, TRUE, I2C_TYPICAL_TIMEOUT))
		{
			I2C_Config->status = I2C_Status_Error;
			break ;
		}
		else
		{
		}
	}

	/* Stop condition */
	I2C_Void_GenerateStopCondition(I2C_Config, stopCondition);

	return ;
}


void MCAL_I2C_Void_MasterRx(I2C_Config_t *I2C_Config, uint16_t slaveAddress, uint8_t *pRxData, uint8_t dataLength, I2C_StopCondition_et stopCondition, I2C_StartCondition_et startCondition)
{
	/* Start condition */
	I2C_Void_GenerateStartCondition(I2C_Config, startCondition);
	if(I2C_Status_Ok != I2C_Config->status)
	{
		I2C_Config->status = I2C_Status_Error;
		return ;
	}
	else
	{
	}

	/* Reading SR1 before writing to DR for SB clearing */
	(void)I2C_Config->I2Cx->SR1;
	/* Send slave address */
	I2C_Void_SendAddress(I2C_Config, slaveAddress, I2C_RWOperation_Read);
	if(I2C_Status_Ok != I2C_Config->status)
	{
		return ;
	}
	else
	{
	}

	/* Auto send ACK enable */
	I2C_Void_GenerateAck(I2C_Config, I2C_AcknowledgeControl_Enable);

	/* Loop through receiving the data until data length is zero */
	for(; dataLength > 0; dataLength--)
	{
		if(dataLength == 1)
		{
			/* Send NACK to terminate connection since this is the last byte */
			I2C_Void_GenerateAck(I2C_Config, I2C_AcknowledgeControl_Disable);
		}
		else
		{
		}

		/* Wait for data reception */
		if(FALSE == I2C_U8_GetEventStatus(I2C_Config, I2C_EVENT_SR1_RXNE, TRUE, I2C_TYPICAL_TIMEOUT))
		{
			I2C_Config->status = I2C_Status_Error;
			return ;
		}
		else
		{
		}

		/* Read data from data register */
		*pRxData = (uint8_t)(I2C_Config->I2Cx->DR);

		/* Increment buffer pointer */
		pRxData++;
	}

	I2C_Void_GenerateStopCondition(I2C_Config, stopCondition);
	I2C_Void_GenerateAck(I2C_Config, I2C_Config->ackControl);
	I2C_Config->status = I2C_Status_Ok;

	return ;
}

void MCAL_I2C_Void_SlaveTx(I2C_Config_t *I2C_Config, uint8_t *txData)
{
	I2C_Config->I2Cx->DR = *txData;
}

void MCAL_I2C_Void_SlaveRx(I2C_Config_t *I2C_Config, uint8_t *pRxData)
{
	*pRxData = (uint8_t)(I2C_Config->I2Cx->DR);

	return ;
}

static void I2C_Void_GenerateStartCondition(I2C_Config_t *I2C_Config, I2C_StartCondition_et startCondition)
{
	if(I2C_StartCondition_Disable == startCondition)
	{
		CLR_BIT(I2C_Config->I2Cx->CR1, I2C_CR1_START);
	}

	else if((I2C_StartCondition_Enable == startCondition) || (I2C_StartCondition_Repeated == startCondition))
	{
		SET_BIT(I2C_Config->I2Cx->CR1, I2C_CR1_START);

		/* Wait on start event */
		if(FALSE == I2C_U8_GetEventStatus(I2C_Config, (I2C_EVENT_SR2_BUSY | I2C_EVENT_SR2_MSL | I2C_EVENT_SR1_SB), TRUE, I2C_TYPICAL_TIMEOUT))
		{
			CLR_BIT(I2C_Config->I2Cx->CR1, I2C_CR1_START);
			I2C_Config->status = I2C_Status_Error;

			return ;
		}
		else
		{
		}
	}
	else
	{
		I2C_Config->status = I2C_Status_Error;
		return;
	}

	I2C_Config->status = I2C_Status_Ok;

	return ;
}

static void I2C_Void_GenerateStopCondition(I2C_Config_t *I2C_Config, I2C_StopCondition_et stopCondition)
{
	if(I2C_StopCondition_Disable == stopCondition)
	{
		CLR_BIT(I2C_Config->I2Cx->CR1, I2C_CR1_STOP);
	}
	else if(I2C_StopCondition_Enable == stopCondition)
	{
		SET_BIT(I2C_Config->I2Cx->CR1, I2C_CR1_STOP);

		/* Wait on TxE event */
		if(FALSE == I2C_U8_GetEventStatus(I2C_Config, I2C_EVENT_SR1_STOPF, TRUE, I2C_TYPICAL_TIMEOUT))
		{
			I2C_Config->status = I2C_Status_Error;
			return ;
		}
		else
		{
		}
	}
	else
	{
		I2C_Config->status = I2C_Status_Error;
	}

	I2C_Config->status = I2C_Status_Ok;

	return ;
}

static void I2C_Void_SendAddress(I2C_Config_t *I2C_Config, uint16_t address, I2C_RWOperation_et operation)
{
	if((I2C_RWOperation_Read == operation) || (I2C_RWOperation_Write == operation))
	{
		I2C_Config->I2Cx->DR = (uint8_t)((address << 1U) | operation);

		/* Wait on address sent event */
		if(FALSE == I2C_U8_GetEventStatus(I2C_Config, I2C_EVENT_SR1_ADDR, TRUE, I2C_TYPICAL_TIMEOUT))
		{
			I2C_Config->status = I2C_Status_Error;
			return ;
		}
		else
		{
		}
	}
	else
	{
		I2C_Config->status = I2C_Status_Error;
		return ;
	}

	I2C_Config->status = I2C_Status_Ok;

	return ;
}

static void I2C_Void_GenerateAck(I2C_Config_t *I2C_Config, I2C_AcknowledgeControl_et ackState)
{
	if(I2C_AcknowledgeControl_Disable == ackState)
	{
		CLR_BIT(I2C_Config->I2Cx->CR1, I2C_CR1_ACK);
	}
	else if(I2C_AcknowledgeControl_Enable == ackState)
	{
		SET_BIT(I2C_Config->I2Cx->CR1, I2C_CR1_ACK);
	}
	else
	{
		I2C_Config->status = I2C_Status_Error;
	}

	return ;
}

static uint8_t I2C_U8_GetEventStatus(I2C_Config_t *I2C_Config, uint32_t event, uint8_t expetedState, uint32_t timeout)
{
	uint8_t state = I2C_Status_Error;
	vuint32_t statuses = 0x00000000;

	do
	{
		statuses = ((I2C_Config->I2Cx->SR1) | ((I2C_Config->I2Cx->SR2) << 16));
		state = ((event & statuses ) == event);

		if(state == expetedState)
		{
			break;
		}
		else
		{
			DELAY(1);

			if(0 < timeout)
			{
				timeout--;
			}
			else
			{
			}
		}
	} while(0 != timeout);

	return state;
}

void I2C1_EV_IRQHandler(void)
{
	/* Interrupt handling for both master and slave mode of the device */
	uint32_t eventInterruptEnabled, bufferInterruptEnabled, switchingFlag;

	eventInterruptEnabled = (I2C1->CR2 & (I2C_CR2_ITEVTEN));
	bufferInterruptEnabled = (I2C1->CR2 & (I2C_CR2_ITBUFEN));

	/* Stop condition detected -> slave mode */
	switchingFlag = GET_BIT(I2C1->SR1, I2C_SR1_STOPF);
	if(eventInterruptEnabled && switchingFlag)
	{
		interruptCallBacks[0](I2C_SlaveCallBackStatus_Stop);
	}
	else
	{
	}

	/* Received address match */
	switchingFlag = GET_BIT(I2C1->SR1, I2C_SR1_ADDR);
	if(eventInterruptEnabled && switchingFlag)
	{	/* Check master/slave mode */
		if(TRUE == GET_BIT(I2C1->SR2, I2C_SR2_MSL))
		{	/* Master mode */
		}
		else
		{	/* Slave mode */
			interruptCallBacks[0](I2C_SlaveCallBackStatus_AddressMatched);
		}

	}

	/* Data register empty */
	switchingFlag = GET_BIT(I2C1->SR1, I2C_SR1_TXE);
	if(eventInterruptEnabled && bufferInterruptEnabled && switchingFlag)				// In case TXE=1, ITEVTEN=1, ITBUFEN=1
	{	/* Check master/slave mode */
		if(TRUE == GET_BIT(I2C1->SR2, I2C_SR2_MSL))
		{	/* Master mode */
		}
		else
		{	/* Slave mode */
			if(TRUE == GET_BIT(I2C1->SR2, I2C_SR2_TRA))
			{	/* Check if slave in transmit mode */
				interruptCallBacks[0](I2C_SlaveCallBackStatus_DataRequested);
			}
			else
			{
			}
		}
	}

	/* Data register not empty */
	switchingFlag = GET_BIT(I2C1->SR1, I2C_SR1_RXNE);
	if(eventInterruptEnabled && bufferInterruptEnabled && switchingFlag)				// In case RXNE=1, ITEVTEN=1, ITBUFEN=1
	{	/* Check master/slave mode */
		if(TRUE == GET_BIT(I2C1->SR2, I2C_SR2_MSL))
		{	/* Master mode */
		}
		else
		{	/* Slave mode */
			if(FALSE == GET_BIT(I2C1->SR2, I2C_SR2_TRA))
			{
				interruptCallBacks[0](I2C_SlaveCallBackStatus_DataReceived);
			}
		}
	}
}

void I2C1_ER_IRQHandler(void)
{

}


void I2C2_EV_IRQHandler(void)
{

}


void I2C2_ER_IRQHandler(void)
{

}

/*******************************************************************************
 *  END OF FILE: i2c_prog.c
 ******************************************************************************/
