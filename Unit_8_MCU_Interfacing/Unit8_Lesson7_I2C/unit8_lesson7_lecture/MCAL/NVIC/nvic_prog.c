/*******************************************************************************
 * exti_prog.c
 *
 *  Created on: Mar 30, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "nvic_interface.h"
#include "nvic_private.h"
#include "nvic_config.h"

void MCAL_NVIC_Void_EnableIRQ(NVIC_IRQ_t interruptNumber)
{
	uint8_t regNumber, bitPosition;
	
	if((interruptNumber >= 0) && (interruptNumber < NVIC_MAX_INTERRUPT_COUNT))
	{
		/* Registers are partitioned as 1 bit per interrupt with	*/
		/* 32 bit per register 										*/
		/* regNumber is how many interrupts in 32 dividing by 32	*/
		/* equivalent: to shifting right by 5 						*/
		/* bitPosition: is how far the interrupt is from 0 to 32	*/
		/* scale hence modulo by 32									*/
		regNumber = (interruptNumber >> 5);
		bitPosition = (interruptNumber % 32);

		NVIC->ISER[regNumber] = (1U << bitPosition);
	}
	else 
	{
	}
	
	return ;
}

void MCAL_NVIC_Void_DisableIRQ(NVIC_IRQ_t interruptNumber)
{
	uint8_t regNumber, bitPosition;
	
	if((interruptNumber >= 0) && (interruptNumber < NVIC_MAX_INTERRUPT_COUNT))
	{
		/* Registers are partitioned as 1 bit per interrupt with	*/
		/* 32 bit per register 										*/
		/* regNumber is how many interrupts in 32 dividing by 32	*/
		/* equivalent: to shifting right by 5 						*/
		/* bitPosition: is how far the interrupt is from 0 to 32	*/
		/* scale hence modulo by 32									*/
		regNumber = (interruptNumber >> 5);
		bitPosition = (interruptNumber % 32);

		NVIC->ICER[regNumber] = (1U << bitPosition);
	}
	else 
	{
	}
	
	return ;
}

void MCAL_NVIC_Void_SetPending(NVIC_IRQ_t interruptNumber)
{
	uint8_t regNumber, bitPosition;
	
	if((interruptNumber >= 0) && (interruptNumber < NVIC_MAX_INTERRUPT_COUNT))
	{
		/* Registers are partitioned as 1 bit per interrupt with	*/
		/* 32 bit per register 										*/
		/* regNumber is how many interrupts in 32 dividing by 32	*/
		/* equivalent: to shifting right by 5 						*/
		/* bitPosition: is how far the interrupt is from 0 to 32	*/
		/* scale hence modulo by 32									*/
		regNumber = (interruptNumber >> 5);
		bitPosition = (interruptNumber % 32);

		NVIC->ISPR[regNumber] = (1U << bitPosition);
	}
	else 
	{
	}
	
	return ;
}

void MCAL_NVIC_Void_ClearSetPending(NVIC_IRQ_t interruptNumber)
{
	uint8_t regNumber, bitPosition;
	
	if((interruptNumber >= 0) && (interruptNumber < NVIC_MAX_INTERRUPT_COUNT))
	{
		/* Registers are partitioned as 1 bit per interrupt with	*/
		/* 32 bit per register 										*/
		/* regNumber is how many interrupts in 32 dividing by 32	*/
		/* equivalent: to shifting right by 5 						*/
		/* bitPosition: is how far the interrupt is from 0 to 32	*/
		/* scale hence modulo by 32									*/
		regNumber = (interruptNumber >> 5);
		bitPosition = (interruptNumber % 32);

		NVIC->ICPR[regNumber] = (1U << bitPosition);
	}
	else 
	{
	}
	
	return ;
}

uint8_t MCAL_NVIC_U8_GetActiveFlag(NVIC_IRQ_t interruptNumber)
{
	uint8_t regNumber, bitPosition;
	uint8_t isFlagActive = GPIO_PIN_RESET;
	
	if((interruptNumber >= 0) && (interruptNumber < NVIC_MAX_INTERRUPT_COUNT))
	{
		/* Registers are partitioned as 1 bit per interrupt with	*/
		/* 32 bit per register 										*/
		/* regNumber is how many interrupts in 32 dividing by 32	*/
		/* equivalent: to shifting right by 5 						*/
		/* bitPosition: is how far the interrupt is from 0 to 32	*/
		/* scale hence modulo by 32									*/
		regNumber = (interruptNumber >> 5);
		bitPosition = (interruptNumber % 32);

		isFlagActive = GET_BIT(NVIC->IABR[regNumber], bitPosition);
		
		if(isFlagActive == TRUE)
		{
			isFlagActive = GPIO_PIN_SET;
		}
		else
		{
			isFlagActive = GPIO_PIN_RESET;
		}
	}
	else 
	{
	}
	
	return isFlagActive;
}

void MCAL_NVIC_Void_SetGroupPriority(NVIC_IRQ_t interruptNumber,uint8_t group, uint8_t subGroup)
{
	
	SCB_AIRCR = (NVIC_VECTKEY | (NVIC_PRIORITY_GROUP_SUB << 8));
	
#if NVIC_PRIORITY_GROUP_SUB == GROUP16_SUB0
	NVIC->IPR[interruptNumber] = (group << 0);
#elif NVIC_PRIORITY_GROUP_SUB == GROUP8_SUB2
	NVIC->IPR[interruptNumber] = ((group << 1) | subGroup);
#elif NVIC_PRIORITY_GROUP_SUB == GROUP4_SUB4
	NVIC->IPR[interruptNumber] = ((group << 2) | subGroup);
#elif NVIC_PRIORITY_GROUP_SUB == GROUP2_SUB8
	NVIC->IPR[interruptNumber] = ((group << 3) | subGroup);
#elif NVIC_PRIORITY_GROUP_SUB == GROUP0_SUB16
	NVIC->IPR[interruptNumber] = (subGroup << 4);
#endif	
	
	return ;
}

/******************************************************************************
 *  END OF FILE: nvic_prog.c
 ******************************************************************************/
