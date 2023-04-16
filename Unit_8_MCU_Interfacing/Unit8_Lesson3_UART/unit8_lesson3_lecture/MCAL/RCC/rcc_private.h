/*******************************************************************************
 * rcc_private.h
 *
 *  Created on: Apr 3, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

#ifndef MCAL_RCC_RCC_PRIVATE_H_
#define MCAL_RCC_RCC_PRIVATE_H_

/* Control register bits */
#define RCC_CR_HSION		0
#define RCC_CR_HSIRDY		1
#define RCC_CR_HSITRIM		3
#define RCC_CR_HSICAL		8
#define RCC_CR_HSEON		16
#define RCC_CR_HSERDY		17
#define RCC_CR_HSEBYP		18
#define RCC_CR_CSSON		19
#define RCC_CR_PLLON		24
#define RCC_CR_PLLRDY		25

/* Clock configuration register bits */
#define RCC_CFGR_SW						0
#define RCC_CFGR_SWS					2
#define RCC_CFGR_HPRE					4
#define RCC_CFGR_PPRE1					8
#define RCC_CFGR_PPRE2					11
#define RCC_CFGR_ADCPRE					14
#define RCC_CFGR_PLLSRC					16
#define RCC_CFGR_PLLXTPRE				17
#define RCC_CFGR_PLLMUL					18
#define RCC_CFGR_USBPRE					22
#define RCC_CFGR_MCO					24

#endif /* MCAL_RCC_RCC_PRIVATE_H_ */

/******************************************************************************
 *  END OF FILE: rcc_private.h
 ******************************************************************************/
