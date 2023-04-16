/*******************************************************************************
 * rcc_prog.c
 *
 *  Created on: Apr 3, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "rcc_config.h"
#include "rcc_interface.h"
#include "rcc_private.h"

void MCAL_RCC_Void_InitClock(RCC_ClkSrcName_et clkSrcName, RCC_HSESrc_et HSESrc, RCC_PLLSrc_et PLLSrc)
{

	switch(clkSrcName)
	{
		case RCC_ClkSrc_HSI:
			/* Configure system to use HSI clock */
			SET_BIT(RCC->CR , RCC_CR_HSION);
			RCC->CFGR &= (0b11 << RCC_CFGR_SW);

			/* Wait for the HSI clock to be ready */
			while(FALSE == (GET_BIT(RCC->CR, RCC_CR_HSIRDY)));
			break;
		case RCC_ClkSrc_HSE:
			/* Configure system to use HSE clock */
			RCC->CFGR &= (0b11 << RCC_CFGR_SW);
			RCC->CFGR |= (0b01 << RCC_CFGR_SW);
			SET_BIT(RCC->CR , RCC_CR_HSEON);

			if(RCC_HSE_CRYSTAL == HSESrc)
			{
				/* External 4-16 MHz oscillator not bypassed */
				CLR_BIT(RCC->CR, RCC_CR_HSEBYP);
			}
			else if(RCC_HSE_RC == HSESrc)
			{
				/* External 4-16 MHz oscillator bypassed with external clock */
				SET_BIT(RCC->CR, RCC_CR_HSEBYP);
			}
			else
			{
				while(TRUE);
			}

			/* Wait for the HSE clock to be ready */
			while(FALSE == (GET_BIT(RCC->CR, RCC_CR_HSERDY)));
			break;
		case RCC_ClkSrc_PLL:
			/* Disable PLL*/
			CLR_BIT(RCC->CR, RCC_CR_PLLON);

			/* Wait for PLL ready */
			while(FALSE == GET_BIT(RCC->CR, RCC_CR_PLLRDY));

			if(RCC_PLLSrc_HSE == PLLSrc)
			{
				/* Configure system to use HSE clock */
				SET_BIT(RCC->CR, RCC_CR_HSEON);

				/* Wait for the HSE clock to be ready */
				while(FALSE == (GET_BIT(RCC->CR, RCC_CR_HSERDY)));

				/* PLL from HSE select */
				SET_BIT(RCC->CFGR, RCC_CFGR_PLLSRC);

				if(RCC_HSE_CRYSTAL == HSESrc)
				{
					/* External 4-16 MHz oscillator not bypassed */
					CLR_BIT(RCC->CR, RCC_CR_HSEBYP);
				}
				else if(RCC_HSE_RC == HSESrc)
				{
					/* External 4-16 MHz oscillator bypassed with external clock */
					SET_BIT(RCC->CR, RCC_CR_HSEBYP);
				}
				else
				{
					while(TRUE);
				}
			}
			else if(RCC_PLLSrc_HSI == PLLSrc)
			{
				/* Configure system to use HSI clock */
				SET_BIT(RCC->CR, RCC_CR_HSION);

				/* PLL from HSI select */
				CLR_BIT(RCC->CFGR, RCC_CFGR_PLLSRC);
			}
			else
			{
				while(TRUE);
			}

			/* Enable PLL */
			SET_BIT(RCC->CR, RCC_CR_PLLON);

			/* Wait for PLL ready */
			while(FALSE == GET_BIT(RCC->CR, RCC_CR_PLLRDY));

			/* System clock source select PLL */
			RCC->CFGR &= (0b11 << RCC_CFGR_SW);
			RCC->CFGR |= (0b10 << RCC_CFGR_SW);
			break;
		default:
			while(TRUE);
			break;
	}

	return ;
}

void MCAL_RCC_Void_EnableClock(RCC_BusName_et busName , uint8_t perNum)
{
	switch(busName)
	{
		case RCC_BusName_AHB:
			SET_BIT(RCC->AHBENR, perNum);
			break;
		case RCC_BusName_APB1:
			SET_BIT(RCC->APB1ENR, perNum);
			break;
		case RCC_BusName_APB2:
			SET_BIT(RCC->APB2ENR, perNum);
			break;
		default:
			while(TRUE);
			break;
	}

	return ;
}

void MCAL_RCC_Void_DisableClock(RCC_BusName_et busName, uint8_t perNum)
{
	switch(busName)
	{
			case RCC_BusName_AHB:
				CLR_BIT(RCC->AHBENR, perNum);
				break;
			case RCC_BusName_APB1:
				CLR_BIT(RCC->APB1ENR, perNum);
				break;
			case RCC_BusName_APB2:
				CLR_BIT(RCC->APB2ENR, perNum);
				break;
			default:
				while(TRUE);
				break;
		}

	return ;
}

void MCAL_RCC_Void_OutMCO(RCC_MCOSrc_et MCOSrc)
{
	switch(MCOSrc)
	{
		/* Since MCOSrc contains the 3-bits value for MCO
		 * We only need the value to be in range so using switch case
		 * To fall through the cases */
		case RRC_MCO_No_Clock:
		case RRC_MCO_SYSCLK:
		case RRC_MCO_HSI:
		case RRC_MCO_HSE:
		case RRC_MCO_PLL_2:
			RCC->CFGR &= ~(0b111 << RCC_CFGR_MCO);
			RCC->CFGR |= (MCOSrc << 24);
			break ;
		default:
			while(TRUE);
			break;
	 }

	 return ;
}

uint32_t MCAL_RCC_U32_GetSystemFrequency(void)
{
	uint32_t sysClk = RCC_HSI_CLK;
	uint8_t SWSValue = ((RCC->CFGR & (0b11 << RCC_CFGR_SWS)) >> RCC_CFGR_SWS);

	switch(SWSValue)
	{
		case 0:
			sysClk = RCC_HSI_CLK;
			break;
		case 1:
			sysClk = RCC_HSE_CLK;
			break;
		case 2:
			if(FALSE == GET_BIT(RCC->CFGR, RCC_CFGR_PLLSRC))
			{
				/* HSI oscillator clock / 2 selected as PLL input clock */
				sysClk >>= 1;
			}
			else
			{
				/* HSE oscillator clock selected as PLL input clock */
				sysClk = RCC_HSE_CLK;
			}
			break;
		default:
			while(TRUE);
			break;
	}

	return sysClk;
}

uint32_t MCAL_RCC_U32_GetBusFrequency(RCC_BusName_et busName)
{
	uint32_t sysClk = MCAL_RCC_U32_GetSystemFrequency();
	uint8_t preScalerDiv = 0;

	switch(busName)
	{
		case RCC_BusName_AHB:
			/* Get 4-bits AHB pre-scaler */
			preScalerDiv = (0x0000000F & (RCC->CFGR >> RCC_CFGR_HPRE));
			if(preScalerDiv >= 8)
			{
				/* All pre-scaler in form 0b1xxx we need to subtract 0b0111 */
				/* By doing so the number becomes like shifting instead of */
				/* multiplying by two */
				preScalerDiv -= 7;
			}
			else
			{
				/* no pre-scaling */
				preScalerDiv = 0;
			}
			break;
		case RCC_BusName_APB1:
			/* Get 3-bits APB1 pre-scaler */
			preScalerDiv = (0x00000007 & (RCC->CFGR >> RCC_CFGR_PPRE1));
			if(preScalerDiv >= 4)
			{
				/* All pre-scaler in form 0b1xx we need to subtract 0b011 */
				/* By doing so the number becomes like shifting instead of */
				/* multiplying by two */
				preScalerDiv -= 3;
			}
			else
			{
				/* no pre-scaling */
				preScalerDiv = 0;
			}
			break;
		case RCC_BusName_APB2:
			/* Get 3-bits APB2 pre-scaler */
			preScalerDiv = (0x00000007 & (RCC->CFGR >> RCC_CFGR_PPRE2));
			if(preScalerDiv >= 4)
			{
				/* All pre-scaler in form 0b1xx we need to subtract 0b011 */
				/* By doing so the number becomes like shifting instead of */
				/* multiplying by two */
				preScalerDiv -= 3;
			}
			else
			{
				/* no pre-scaling */
				preScalerDiv = 0;
			}
			break;
		default:
			while(TRUE);
			break;
	}

	/* return scaled system clock */
	return (sysClk >> preScalerDiv);
}

void MCAL_RCC_Void_ResetPeripheral(RCC_BusName_et busName, uint8_t peripheralPosition)
{
	switch(busName)
	{
		case RCC_BusName_APB1:
			SET_BIT(RCC->APB1RSTR, peripheralPosition);
			break;
		case RCC_BusName_APB2:
			SET_BIT(RCC->APB2RSTR, peripheralPosition);
			break;
		default:
			while(TRUE);
			break;
	}

	return ;
}
/******************************************************************************
 *  END OF FILE: rcc_prog.c
 ******************************************************************************/
