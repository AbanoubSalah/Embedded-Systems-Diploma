/**********************************************************************************************************************
 * @file driver.h
 * @brief This file contains the interface of the GPIO peripheral for the  STM32F103C6 μ-controller
 *
 * @author Engr. Keroles Shenouda
 * @date January 16, 2021
 * *********************************************************************************************************************/

#ifndef DRIVER_H_
#define DRIVER_H_

#include "platform_types.h"

#define SET_BIT(ADDRESS,BIT)   ADDRESS |=  (1<<BIT)
#define RESET_BIT(ADDRESS,BIT) ADDRESS &= ~(1<<BIT)
#define TOGGLE_BIT(ADDRESS,BIT)  ADDRESS ^=  (1<<BIT)
#define READ_BIT(ADDRESS,BIT) ((ADDRESS) &   (1<<(BIT)))

#define GPIO_PORTA 0x40010800U
#define BASE_RCC   0x40021000U

#define APB2ENR   *(volatile uint32_t *)(BASE_RCC + 0x18U)

#define GPIOA_CRL *(volatile uint32_t *)(GPIO_PORTA + 0x00U)
#define GPIOA_CRH *(volatile uint32_t *)(GPIO_PORTA + 0X04U)
#define GPIOA_IDR *(volatile uint32_t *)(GPIO_PORTA + 0x08U)
#define GPIOA_ODR *(volatile uint32_t *)(GPIO_PORTA + 0x0CU)

/******************************************************************************
 * @brief Add a delay load
 *
 * Add a delay load using for loop
 *
 * @param nCount						The loop counter
 *
 * @returns None
 *******************************************************************************/
void Delay(vuint32 nCount);

/******************************************************************************
 * @brief Gets the current pressure value
 *
 * Gets current pressure value by reading the GPIO lower byte
 * of the port
 *
 * @param None
 *
 * @returns uint32						Current port value
 *******************************************************************************/
uint32 getPressureVal(void);


/******************************************************************************
 * @brief Sets the actuator alarm
 *
 * Sets the actuator alarm by setting the corresponding bit as high
 *
 * @param boolean						The pin state	TRUE
 *														FALSE
 *
 * @returns None
 *******************************************************************************/
void Set_Alarm_actuator(boolean state);

/******************************************************************************
 * @brief Initialize the GPIO peripheral
 *
 * Initialize the GPIO peripheral
 *
 * @param None
 *
 * @returns None
 *******************************************************************************/
void GPIO_Init(void);

#endif /* DRIVER_H_ */

/**********************************************************************************************************************
 *  END OF FILE: driver.h
 *********************************************************************************************************************/
