/*******************************************************************************
 * nvic_interface.h
 *
 *  Created on: Mar 30, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

#ifndef MCAL_NVIC_NVIC_INTERFACE_H_
#define MCAL_NVIC_NVIC_INTERFACE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "gpio_interface.h"
#include "bit_math.h"
#include "platform_types.h"

/******************************************************************************
 *  Definitions
 ******************************************************************************/

/* @ref NVIC_IRQ */
typedef enum
{
  NVIC_IRQ_NonMaskableInt         = -14,
  NVIC_IRQ_MemoryManagement       = -12,
  NVIC_IRQ_BusFault               = -11,
  NVIC_IRQ_UsageFault             = -10,
  NVIC_IRQ_SVCall                 = -5,
  NVIC_IRQ_DebugMonitor           = -4,
  NVIC_IRQ_PendSV                 = -2,
  NVIC_IRQ_SysTick                = -1,
  NVIC_IRQ_WWDG                   = 0,
  NVIC_IRQ_PVD                    = 1,
  NVIC_IRQ_TAMP_STAMP             = 2,
  NVIC_IRQ_RTC_WKUP               = 3,
  NVIC_IRQ_FLASH                  = 4,
  NVIC_IRQ_RCC                    = 5,
  NVIC_IRQ_EXTI0                  = 6,
  NVIC_IRQ_EXTI1                  = 7,
  NVIC_IRQ_EXTI2                  = 8,
  NVIC_IRQ_EXTI3                  = 9,
  NVIC_IRQ_EXTI4                  = 10,
  NVIC_IRQ_DMA1_Stream0           = 11,
  NVIC_IRQ_DMA1_Stream1           = 12,
  NVIC_IRQ_DMA1_Stream2           = 13,
  NVIC_IRQ_DMA1_Stream3           = 14,
  NVIC_IRQ_DMA1_Stream4           = 15,
  NVIC_IRQ_DMA1_Stream5           = 16,
  NVIC_IRQ_DMA1_Stream6           = 17,
  NVIC_IRQ_ADC1_2                 = 18,
  NVIC_IRQ_CAN1_TX                = 19,
  NVIC_IRQ_CAN1_RX0               = 20,
  NVIC_IRQ_CAN1_RX1               = 21,
  NVIC_IRQ_CAN1_SCE               = 22,
  NVIC_IRQ_EXTI9_5                = 23,
  NVIC_IRQ_TIM1_BRK_TIM9          = 24,
  NVIC_IRQ_TIM1_UP_TIM10          = 25,
  NVIC_IRQ_TIM1_TRG_COM_TIM11     = 26,
  NVIC_IRQ_TIM1_CC                = 27,
  NVIC_IRQ_TIM2                   = 28,
  NVIC_IRQ_TIM3                   = 29,
  NVIC_IRQ_TIM4                   = 30,
  NVIC_IRQ_I2C1_EV                = 31,
  NVIC_IRQ_I2C1_ER                = 32,
  NVIC_IRQ_I2C2_EV                = 33,
  NVIC_IRQ_I2C2_ER                = 34,
  NVIC_IRQ_SPI1                   = 35,
  NVIC_IRQ_SPI2                   = 36,
  NVIC_IRQ_USART1                 = 37,
  NVIC_IRQ_USART2                 = 38,
  NVIC_IRQ_USART3                 = 39,
  NVIC_IRQ_EXTI15_10              = 40,
  NVIC_IRQ_RTC_Alarm              = 41,
  NVIC_IRQ_OTG_FS_WKUP            = 42,
  NVIC_IRQ_TIM8_BRK_TIM12         = 43,
  NVIC_IRQ_TIM8_UP_TIM13          = 44,
  NVIC_IRQ_TIM8_TRG_COM_TIM14     = 45,
  NVIC_IRQ_TIM8_CC                = 46,
  NVIC_IRQ_ADC3_Stream7           = 47,
  NVIC_IRQ_FMC                    = 48,
  NVIC_IRQ_SDIO                   = 49,
  NVIC_IRQ_TIM5                   = 50,
  NVIC_IRQ_SPI3                   = 51,
  NVIC_IRQ_UART4                  = 52,
  NVIC_IRQ_UART5                  = 53,
  NVIC_IRQ_TIM6_DAC               = 54,
  NVIC_IRQ_TIM7                   = 55,
  NVIC_IRQ_DMA2_Stream0           = 56,
  NVIC_IRQ_DMA2_Stream1           = 57,
  NVIC_IRQ_DMA2_Stream2           = 58,
  NVIC_IRQ_DMA2_Stream3           = 59,
  NVIC_IRQ_DMA2_Stream4           = 60,
  NVIC_IRQ_ETH                    = 61,
  NVIC_IRQ_ETH_WKUP               = 62,
  NVIC_IRQ_CAN2_TX                = 63,
  NVIC_IRQ_CAN2_RX0               = 64,
  NVIC_IRQ_CAN2_RX1               = 65,
  NVIC_IRQ_CAN2_SCE               = 66,
  NVIC_IRQ_OTG_FS                 = 67,
  NVIC_IRQ_DMA2_Stream5           = 68,
  NVIC_IRQ_DMA2_Stream6           = 69,
  NVIC_IRQ_DMA2_Stream7           = 70,
  NVIC_IRQ_USART6                 = 71,
  NVIC_IRQ_I2C3_EV                = 72,
  NVIC_IRQ_I2C3_ER                = 73,
  NVIC_IRQ_OTG_HS_EP1_OUT         = 74,
  NVIC_IRQ_OTG_HS_EP1_IN          = 75,
  NVIC_IRQ_OTG_HS_WKUP            = 76,
  NVIC_IRQ_OTG_HS                 = 77,
  NVIC_IRQ_DCMI                   = 78,
  NVIC_IRQ_HASH_RNG               = 80,
  NVIC_IRQ_FPU                    = 81,
  NVIC_IRQ_UART7                  = 82,
  NVIC_IRQ_UART8                  = 83,
  NVIC_IRQ_SPI4                   = 84,
  NVIC_IRQ_SPI5                   = 85,
  NVIC_IRQ_SPI6                   = 86,
  NVIC_IRQ_SAI1                   = 87,
  NVIC_IRQ_LTDC                   = 88,
  NVIC_IRQ_LTDC_ER                = 89,
  NVIC_IRQ_DMA2D                  = 90
} NVIC_IRQ_t;

/*******************************************************************************
 * APIs Supported by "MCAL NVIC DRIVER"
 ******************************************************************************/

/*******************************************************************************
 * Fn                - MCAL_NVIC_Void_EnableIRQ
 *
 * Brief             - Enable specific IRQ number
 *
 * Param [in]        - IRQ number @ref NVIC_IRQ
 *
 * Retval            - None
 *
 * Note              - None
 ******************************************************************************/
void MCAL_NVIC_Void_EnableIRQ(NVIC_IRQ_t);

/*******************************************************************************
 * Fn                - MCAL_NVIC_Void_DisableIRQ
 *
 * Brief             - Disable specific IRQ number
 *
 * Param [in]        - IRQ number @ref NVIC_IRQ_position
 *
 * Retval            - None
 *
 * Note              - None
 ******************************************************************************/
void MCAL_NVIC_Void_DisableIRQ(NVIC_IRQ_t);

/*******************************************************************************
 * Fn                - MCAL_NVIC_Void_SetPending
 *
 * Brief             - Set specific IRQ number as pending to be served
 *					   by the processor
 *
 * Param [in]        - IRQ number @ref NVIC_IRQ_position
 *
 * Retval            - None
 *
 * Note              - None
 ******************************************************************************/
void MCAL_NVIC_Void_SetPending(NVIC_IRQ_t);

/*******************************************************************************
 * Fn                - MCAL_NVIC_Void_SetPending
 *
 * Brief             - Clear specific IRQ number off of pending state
 *
 * Param [in]        - IRQ number @ref NVIC_IRQ_position
 *
 * Retval            -None
 *
 * Note              -None
 ******************************************************************************/
void MCAL_NVIC_Void_ClearSetPending(NVIC_IRQ_t);

/*******************************************************************************
 * Fn                -MCAL_NVIC_U8_GetActiveFlag
 *
 * Brief             - Get specific IRQ number active flag state
 *
 * Param [in]        - IRQ number @ref NVIC_IRQ_position
 *
 * Retval            - Current active state @ref GPIO_PIN_state
 *
 * Note              - None
 ******************************************************************************/
uint8_t MCAL_NVIC_U8_GetActiveFlag(NVIC_IRQ_t);

/*******************************************************************************
 * Fn                - MCAL_NVIC_Void_SetGroupPriority
 *
 * Brief             - Clear specific IRQ number off of pending state
 *
 * Param [in]        - IRQ number @ref NVIC_IRQ_position
 *
 * Param [in]        - Group priority values depend on priority grouping
 *					   set by the configuration values are (0..15) inclusive
 *
 * Param [in]        - Sub-Group priority values depends on priority grouping
 *					   set by the configuration values are (0..15) inclusive
 *
 * Retval            - None
 *
 * Note              - None
 ******************************************************************************/
void MCAL_NVIC_Void_SetGroupPriority(NVIC_IRQ_t, uint8_t, uint8_t);

#endif  /* MCAL_NVIC_NVIC_INTERFACE_H_ */

/******************************************************************************
 *  END OF FILE: nvic_interface.h
 ******************************************************************************/
