/*******************************************************************************
 * nvic_private.h
 *
 *  Created on: Mar 30, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

#ifndef MCAL_NVIC_NVIC_PRIVATE_H_
#define MCAL_NVIC_NVIC_PRIVATE_H_

#define NVIC_BASE_ADDRESS 			0xE000E100

#define NVIC_VECTKEY				0x5FA
#define GROUP16_SUB0				3
#define GROUP8_SUB2					4
#define GROUP4_SUB4					5
#define GROUP2_SUB8					6
#define GROUP0_SUB16				7

typedef struct
{
	vuint32 ISER[3];
	vuint32 RESERVED[29U];
	vuint32 ICER[3];
	vuint32 RESERVED0[29U];
	vuint32 ISPR[3];
	vuint32 RESERVED1[29U];
	vuint32 ICPR[3];
	vuint32 RESERVED2[29U];
	vuint32 IABR[3];
	vuint32 RESERVED3[61U];
	vuint8 IPR[81];
	vuint32 RESERVED4[693U];
	vuint32 STIR;
} NVIC_t;

#define NVIC				((NVIC_t *) NVIC_BASE_ADDRESS )
#define SCB_AIRCR			(*(vuint32 *)(0xE000ED0C))

#endif  /* MCAL_NVIC_NVIC_PRIVATE_H_ */

/******************************************************************************
 *  END OF FILE: nvic_private.h
 ******************************************************************************/
