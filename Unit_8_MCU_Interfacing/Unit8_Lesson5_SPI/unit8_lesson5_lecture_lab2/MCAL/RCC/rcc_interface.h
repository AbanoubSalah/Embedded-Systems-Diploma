/*******************************************************************************
 * rcc_interface.h
 *
 *  Created on: Apr 3, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

#ifndef MCAL_RCC_RCC_INTERFACE_H_
#define MCAL_RCC_RCC_INTERFACE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "stm32F103c6.h"
#include "platform_types.h"
#include "bit_math.h"
#include "gpio_interface.h"

/* @ref AHB_Peripheral_En */
typedef enum
{
	RCC_AHB_Peripheral_En_DMA1EN = 0U,
	RCC_AHB_Peripheral_En_DMA2EN = 1U,
	RCC_AHB_Peripheral_En_SRAMEN = 2U,
	RCC_AHB_Peripheral_En_FLITFEN = 4U,
	RCC_AHB_Peripheral_En_CRCEN = 6U,
	RCC_AHB_Peripheral_En_FSMCEN = 8U,
	RCC_AHB_Peripheral_En_SDIO = 10U,
} RCC_AHB_Peripheral_En_et;

/* @ref RCC_APB2_Peripheral_En */
typedef enum
{
	RCC_APB2_Peripheral_En_AFIOEN = 0U,
	RCC_APB2_Peripheral_En_IOPAEN = 2U,
	RCC_APB2_Peripheral_En_IOPBEN = 3U,
	RCC_APB2_Peripheral_En_IOPCEN = 4U,
	RCC_APB2_Peripheral_En_IOPDEN = 5U,
	RCC_APB2_Peripheral_En_IOPEEN = 6U,
	RCC_APB2_Peripheral_En_IOPFEN = 7U,
	RCC_APB2_Peripheral_En_IOPGEN = 8U,
	RCC_APB2_Peripheral_En_ADC1EN = 9U,
	RCC_APB2_Peripheral_En_ADC2EN = 10U,
	RCC_APB2_Peripheral_En_TIM1EN = 11U,
	RCC_APB2_Peripheral_En_SPI1EN = 12U,
	RCC_APB2_Peripheral_En_TIM8EN = 13U,
	RCC_APB2_Peripheral_En_USART1EN = 14U,
	RCC_APB2_Peripheral_En_ADC3EN = 15U,
	RCC_APB2_Peripheral_En_TIM9EN = 19U,
	RCC_APB2_Peripheral_En_TIM10EN = 20U,
	RCC_APB2_Peripheral_En_TIM11EN = 21U,
} RCC_APB2_Peripheral_En_et;

/* @ref RCC_APB1_Peripheral_En */
typedef enum
{
	RCC_APB1_Peripheral_En_TIM2EN = 0U,
	RCC_APB1_Peripheral_En_TIM3EN = 1U,
	RCC_APB1_Peripheral_En_TIM4EN = 2U,
	RCC_APB1_Peripheral_En_TIM5EN = 3U,
	RCC_APB1_Peripheral_En_TIM6EN = 4U,
	RCC_APB1_Peripheral_En_TIM7EN = 5U,
	RCC_APB1_Peripheral_En_TIM12EN = 6U,
	RCC_APB1_Peripheral_En_TIM13EN = 7U,
	RCC_APB1_Peripheral_En_TIM14EN = 8U,
	RCC_APB1_Peripheral_En_WWDGEN = 11U,
	RCC_APB1_Peripheral_En_SPI2EN = 14U,
	RCC_APB1_Peripheral_En_SPI3EN = 15U,
	RCC_APB1_Peripheral_En_USART2EN = 17U,
	RCC_APB1_Peripheral_En_USART3EN = 18U,
	RCC_APB1_Peripheral_En_UART4EN = 19U,
	RCC_APB1_Peripheral_En_UART5EN = 20U,
	RCC_APB1_Peripheral_En_I2C1EN = 21U,
	RCC_APB1_Peripheral_En_I2C2EN = 22U,
	RCC_APB1_Peripheral_En_USBEN = 23U,
	RCC_APB1_Peripheral_En_CANEN = 25U,
	RCC_APB1_Peripheral_En_BKPEN = 27U,
	RCC_APB1_Peripheral_En_PWREN = 28U,
	RCC_APB1_Peripheral_En_DACEN = 29U,
} RCC_APB1_Peripheral_En_et;

/* @ref AHB_PreScaler */
typedef enum
{
	RCC_AHB_Pre1 = 7U,
	RCC_AHB_Pre2,
	RCC_AHB_Pre4,
	RCC_AHB_Pre8,
	RCC_AHB_Pre16,
	RCC_AHB_Pre64,
	RCC_AHB_Pre128,
	RCC_AHB_Pre256,
	RCC_AHB_Pre512,	
} RCC_AHB_PreScaler_et;

/* @ref APB1_PreScaler */
typedef enum
{
	RCC_ABP1_Pre1 = 3U,
	RCC_ABP1_Pre2,
	RCC_ABP1_Pre4,
	RCC_ABP1_Pre8,
	RCC_ABP1_Pre16,
} RCC_APB1_PRESCALER_et;
	
/* @ref RCC_APB2_PreScaler */
typedef enum
{
	RCC_ABP2_Pre1 = 3U,
	RCC_ABP2_Pre2,
	RCC_ABP2_Pre4,
	RCC_ABP2_Pre8,
	RCC_ABP2_Pre16,
} RCC_APB2_PreScaler_et;
	
/* @ref RCC_BusName */
typedef enum
{
	RCC_BusName_AHB = 0U,
	RCC_BusName_APB1,
	RCC_BusName_APB2,
} RCC_BusName_et;
	  
/* @ref RCC_ClkSrcName */
typedef enum
{
	RCC_ClkSrc_HSE = 0U,
	RCC_ClkSrc_HSI,
	RCC_ClkSrc_PLL,
} RCC_ClkSrcName_et;

/* @ref RCC_PLLSrc */
typedef enum
{
	RCC_PLLSrc_HSE = 0U,
	RCC_PLLSrc_HSI,
} RCC_PLLSrc_et;

/* @ref RCC_HSESrc */
typedef enum
{
	RCC_HSE_CRYSTAL  = 0U,
	RCC_HSE_RC,
} RCC_HSESrc_et;

/* @ref RCC_MCOSrc */
typedef enum
{
	RRC_MCO_No_Clock = 3U,
	RRC_MCO_SYSCLK,
	RRC_MCO_HSI,
	RRC_MCO_HSE,
	RRC_MCO_PLL_2,
} RCC_MCOSrc_et;

/* @ref APB2_PERIPHERAL_RST */
typedef enum
{
	RCC_APB2_Peripheral_RST_AFIORST = 0U,
	RCC_APB2_Peripheral_RST_IOPARST = 2U,
	RCC_APB2_Peripheral_RST_IOPBRST = 3U,
	RCC_APB2_Peripheral_RST_IOPCRST = 4U,
	RCC_APB2_Peripheral_RST_IOPDRST = 5U,
	RCC_APB2_Peripheral_RST_IOPERST = 6U,
	RCC_APB2_Peripheral_RST_IOPFRST = 7U,
	RCC_APB2_Peripheral_RST_IOPGRST = 8U,
	RCC_APB2_Peripheral_RST_ADC1RST = 9U,
	RCC_APB2_Peripheral_RST_ADC2RST = 10U,
	RCC_APB2_Peripheral_RST_TIM1RST = 11U,
	RCC_APB2_Peripheral_RST_SPI1RST = 12U,
	RCC_APB2_Peripheral_RST_TIM8RST = 13U,
	RCC_APB2_Peripheral_RST_USART1RST = 14U,
	RCC_APB2_Peripheral_RST_ADC3RST = 15U,
	RCC_APB2_Peripheral_RST_TIM9RST = 19U,
	RCC_APB2_Peripheral_RST_TIM10RST = 20U,
	RCC_APB2_Peripheral_RST_TIM11RST = 21U,
} RCC_APB2_Peripheral_RST_et;

/* @ref APB1_Peripheral_RST */
typedef enum
{
	RCC_APB1_Peripheral_RST_TIM2RST = 0U,
	RCC_APB1_Peripheral_RST_TIM3RST = 1U,
	RCC_APB1_Peripheral_RST_TIM4RST = 2U,
	RCC_APB1_Peripheral_RST_TIM5RST = 3U,
	RCC_APB1_Peripheral_RST_TIM6RST = 4U,
	RCC_APB1_Peripheral_RST_TIM7RST = 5U,
	RCC_APB1_Peripheral_RST_TIM12RST = 6U,
	RCC_APB1_Peripheral_RST_TIM13RST = 7U,
	RCC_APB1_Peripheral_RST_TIM14RST = 8U,
	RCC_APB1_Peripheral_RST_WWDGRST = 11U,
	RCC_APB1_Peripheral_RST_SPI2RST = 14U,
	RCC_APB1_Peripheral_RST_SPI3RST = 15U,
	RCC_APB1_Peripheral_RST_USART2RST = 17U,
	RCC_APB1_Peripheral_RST_USART3RST = 18U,
	RCC_APB1_Peripheral_RST_UART4RST = 19U,
	RCC_APB1_Peripheral_RST_UART5RST = 20U,
	RCC_APB1_Peripheral_RST_I2C1RST = 21U,
	RCC_APB1_Peripheral_RST_I2C2RST = 22U,
	RCC_APB1_Peripheral_RST_USBRST = 23U,
	RCC_APB1_Peripheral_RST_CANRST = 25U,
	RCC_APB1_Peripheral_RST_BKPRST = 27U,
	RCC_APB1_Peripheral_RST_PWRRST = 28U,
	RCC_APB1_Peripheral_RST_DACRST = 29U,
} RCC_APB1_Peripheral_RST_et;

/*******************************************************************************
 * APIs Supported by "MCAL RCC DRIVER"
 ******************************************************************************/

/*******************************************************************************
* Fn                - MCAL_RCC_Void_InitClock
*
* Brief             - Initiate system clock using provided parameters
*
* Param [in]        - Clock source @ref RCC_CLKSrcName
*
* Param [in]		- Source for HSE @ref RCC_HSESrc
*
* Param [in]		- Source for PLL @ref RCC_PLLSrc
*
* Retval            - None
*
* Note              - Initiation done for "clock source" other parameters may
*					  not be used but nevertheless required
*******************************************************************************/
void MCAL_RCC_Void_InitClock(RCC_ClkSrcName_et, RCC_HSESrc_et, RCC_PLLSrc_et);

/*******************************************************************************
* Fn                - MCAL_RCC_Void_EnableClock
*
* Brief             - Enable clock for provided peripheral
*
* Param [in]        - Bus name @ref RCC_BusName
*
* Param [in]        - Peripheral Name @ref RCC_AHB_Peripheral_En
* 									  @ref RCC_APB1_Peripheral_En
* 									  @ref RCC_APB2_Peripheral_En
*
* Retval            - None
*
* Note              - None
*******************************************************************************/
void MCAL_RCC_Void_EnableClock(RCC_BusName_et, uint8_t);

/*******************************************************************************
* Fn                - MCAL_RCC_Void_DisableClock
*
* Brief             - Disable clock for provided peripheral
*
* Param [in]        - Bus name @ref RCC_BusName
*
* Param [in]        - Peripheral Name @ref RCC_AHB_Peripheral_En
* 									  @ref RCC_APB1_Peripheral_En
* 									  @ref RCC_APB2_Peripheral_En
*
* Retval            - None
*
* Note              - None
*******************************************************************************/
void MCAL_RCC_Void_DisableClock(RCC_BusName_et, uint8_t);

/*******************************************************************************
* Fn                - MCAL_RCC_Void_OutMCO
*
* Brief             - Micro-controller clock output to pins MCO
*
* Param [in]        - MCO clock source @ref RCC_MCOSrc
*
* Retval            - None
*
* Note              - This clock output may have some truncated cycles
*					  at startup or during MCO clock source switching.
*					  When the System Clock is selected to output to the
*					  MCO pin, make sure that this clock does not
*					  exceed 50 MHz (the maximum IO speed)
*******************************************************************************/
void MCAL_RCC_Void_OutMCO(RCC_MCOSrc_et);

/*******************************************************************************
* Fn                - MCAL_RCC_U32_GetSystemFrequency
*
* Brief             - Return system clock in [Hz]
*
* Retval            - System clock inn [Hz]
*
* Note              - None
*******************************************************************************/
uint32_t MCAL_RCC_U32_GetSystemFrequency(void);

/*******************************************************************************
* Fn                - MCAL_RCC_U32_GetBusFrequency
*
* Brief             - Return bus working clock in [Hz]
*
* Param [in]        - Bus name @ref RCC_BusName
*
* Retval            - Bus frequency in [Hz]
*
* Note              - None
*******************************************************************************/
uint32_t MCAL_RCC_U32_GetBusFrequency(RCC_BusName_et);

/*******************************************************************************
* Fn                - MCAL_RCC_Void_ResetPeripheral
*
* Brief             - Reset specific peripheral registers
*
* Param [in]        - Bus name @ref RCC_BusName
*
* Param [in]        - Peripheral Name @ref RCC_APB1_Peripheral_RST
* 									  @ref RCC_APB2_Peripheral_RST
*
* Retval            - None
*
* Note              - None
*******************************************************************************/
void MCAL_RCC_Void_ResetPeripheral(RCC_BusName_et, uint8_t);

#endif /* MCAL_RCC_RCC_INTERFACE_H_ */

/******************************************************************************
 *  END OF FILE: rcc_interface.h
 ******************************************************************************/
