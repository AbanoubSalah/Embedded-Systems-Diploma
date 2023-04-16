/*******************************************************************************
 * @file bit_math.h
 * @brief This file is the bit manipulation macros
 *
 * @author Abanoub Salah
 * @date March 20, 2023
 ******************************************************************************/

#ifndef LIBRARIES_BIT_MATH_H_
#define LIBRARIES_BIT_MATH_H_

#define SET_BIT(REG,BIT)        REG |=  (1U << BIT)
#define CLR_BIT(REG,BIT)        REG &= ~(1U << BIT)
#define TOG_BIT(REG,BIT)        REG ^=  (1U << BIT)
#define GET_BIT(REG,BIT)        (1U & (REG >> BIT))

#endif /* LIBRARIES_BIT_MATH_H_ */

/******************************************************************************
 *  END OF FILE: bit_math.h
 ******************************************************************************/
