/*******************************************************************************
 * nvic_private.h
 *
 *  Created on: Mar 30, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

#ifndef MCAL_NVIC_NVIC_PRIVATE_H_
#define MCAL_NVIC_NVIC_PRIVATE_H_

#define NVIC_VECTKEY				0x5FAU
#define GROUP16_SUB0				3U
#define GROUP8_SUB2					4U
#define GROUP4_SUB4					5U
#define GROUP2_SUB8					6U
#define GROUP0_SUB16				7U

#define SCB_AIRCR					(*(vuint32_t *)(0xE000ED0C))

#endif  /* MCAL_NVIC_NVIC_PRIVATE_H_ */

/******************************************************************************
 *  END OF FILE: nvic_private.h
 ******************************************************************************/
