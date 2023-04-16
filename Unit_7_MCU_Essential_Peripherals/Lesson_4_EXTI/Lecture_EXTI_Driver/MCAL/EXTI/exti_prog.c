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
#include "exti_config.h"
#include "exti_interface.h"
#include "exti_private.h"

/* Array of a pointer to a function that takes nothing and returns nothing */
static void (* IRQCallbacks[NVIC_NUMBER_OF_INTERRUPT_LINES])(void) = {NULL};

void MCAL_EXTI_Void_Init(EXTI_PinConfig_t *EXTIConfig)
{
	updateEXTI(EXTIConfig);
}

void MCAL_EXTI_Void_DeInit(void)
{
	/* Load registers default values */
	EXTI->IMR = 0x00000000;
	EXTI->EMR = 0x00000000;
	EXTI->RTSR = 0x00000000;
	EXTI->FTSR = 0x00000000;
	EXTI->SWIER = 0x00000000;
	EXTI->PR = 0xFFFFFFFF;
	
	return ;
}

void MCAL_EXTI_Void_Update(EXTI_PinConfig_t *EXTIConfig)
{
	updateEXTI(EXTIConfig);
}

static void updateEXTI(EXTI_PinConfig_t *EXTIConfig)
{
	/* Configure GPIO pins as i/p floating */
	GPIO_PinConfig_t PinConfig;

	PinConfig.GPIO_PinNumber = EXTIConfig->Pin.GPIOPin;
	PinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLO;

	MCAL_GPIO_Init(EXTIConfig->Pin.GPIOx, &PinConfig);

	/* Configure AFIO to connect EXTI line with specified port */
	uint8_t regIndex = (EXTIConfig->Pin.InputLineNumber / 4);
	uint8_t bitPosition = ((EXTIConfig->Pin.InputLineNumber % 4) << 2);
	uint8 relativeToGPIOA = 0;

	if(GPIOB == EXTIConfig->Pin.GPIOx){ relativeToGPIOA += 1; }
	else if(GPIOC == EXTIConfig->Pin.GPIOx){ relativeToGPIOA += 2; }
	else if(GPIOD == EXTIConfig->Pin.GPIOx){ relativeToGPIOA += 3; }
	else if(GPIOE == EXTIConfig->Pin.GPIOx){ relativeToGPIOA += 4; }
	else
	{
		while(TRUE);
	}

	AFIO->EXTICR[regIndex] &= ~(relativeToGPIOA << bitPosition);
	AFIO->EXTICR[regIndex] |= (relativeToGPIOA << bitPosition);

	/* Set EXTI Trigger */
	if(EXTI_RISING == EXTIConfig->TriggerCase)
	{
		SET_BIT(EXTI->RTSR, EXTIConfig->Pin.InputLineNumber);
		CLR_BIT(EXTI->FTSR, EXTIConfig->Pin.InputLineNumber);
	}
	else if(EXTI_FALLING == EXTIConfig->TriggerCase)
	{
		CLR_BIT(EXTI->RTSR, EXTIConfig->Pin.InputLineNumber);
		SET_BIT(EXTI->FTSR, EXTIConfig->Pin.InputLineNumber);
	}
	else if(EXTI_ON_CHANGE == EXTIConfig->TriggerCase)
	{
		SET_BIT(EXTI->RTSR, EXTIConfig->Pin.InputLineNumber);
		SET_BIT(EXTI->FTSR, EXTIConfig->Pin.InputLineNumber);
	}
	else
	{
		while(TRUE);
	}

	/* Set IRQ Callback function */
	IRQCallbacks[EXTIConfig->Pin.InputLineNumber] = EXTIConfig->Ptr_IRQCallBack;

	/* Set IRQ state */
	if(EXTI_IRQ_ENABLE == EXTIConfig->IRQEnabled)
	{
		SET_BIT(EXTI->IMR, EXTIConfig->Pin.InputLineNumber);
	}
	else if(EXTI_IRQ_DISABLE == EXTIConfig->Ptr_IRQCallBack)
	{
		CLR_BIT(EXTI->IMR, EXTIConfig->Pin.InputLineNumber);
	}
	else
	{
		while(TRUE);
	}

	return ;
}

/*******************************************************************************
 * Interrupt request handlers
 ******************************************************************************/
void EXTI0_IRQHandler (void)
{
	/* Clear pending Register */
	SET_BIT(EXTI->PR, 0);

	/* Call Callback function */
	if(NULL != IRQCallbacks[0])
		IRQCallbacks[01]();
	else
	{
		while(TRUE);
	}
}

void EXTI1_IRQHandler (void)
{
	/* Clear pending Register */
	SET_BIT(EXTI->PR, 1);

	/* Call Callback function */
	if(NULL != IRQCallbacks[1])
		IRQCallbacks[1]();
	else
	{
		while(TRUE);
	}
}

void EXTI2_IRQHandler (void)
{
	/* Clear pending Register */
	SET_BIT(EXTI->PR, 2);

	/* Call Callback function */
	if(NULL != IRQCallbacks[2])
		IRQCallbacks[2]();
	else
	{
		while(TRUE);
	}
}

void EXTI3_IRQHandler (void)
{
	/* Clear pending Register */
	SET_BIT(EXTI->PR, 3);

	/* Call Callback function */
	if(NULL != IRQCallbacks[3])
		IRQCallbacks[3]();
	else
	{
		while(TRUE);
	}
}

void EXTI4_IRQHandler (void)
{
	/* Clear pending Register */
	SET_BIT(EXTI->PR, 4);

	/* Call Callback function */
	if(NULL != IRQCallbacks[4])
		IRQCallbacks[4]();
	else
	{
		while(TRUE);
	}
}

void EXTI9_5_IRQHandler(void)
{
	uint8 counter;

	for(counter = 5; counter < 10; counter ++)
	{
		if(GPIO_PIN_SET == GET_BIT(EXTI->PR, counter))
		{
			/* Clear pending Register */
			//SET_BIT(EXTI->PR, counter);

			/* Call Callback function */
			if(NULL != IRQCallbacks[counter])
				IRQCallbacks[counter]();
			else
			{
				while(TRUE);
			}
		}
		else
		{
		}
	}
}

void EXTI15_10_IRQHandler (void)
{
	uint8 counter;

	for(counter = 10; counter < 16; counter ++)
	{
		if(GPIO_PIN_SET == GET_BIT(EXTI->PR, counter))
		{
			/* Clear pending Register */
			SET_BIT(EXTI->PR, counter);

			/* Call Callback function */
			if(NULL != IRQCallbacks[counter])
				IRQCallbacks[counter]();
			else
			{
				while(TRUE);
			}
		}
		else
		{
		}
	}
}

/******************************************************************************
 *  END OF FILE: exti_prog.c
 ******************************************************************************/
