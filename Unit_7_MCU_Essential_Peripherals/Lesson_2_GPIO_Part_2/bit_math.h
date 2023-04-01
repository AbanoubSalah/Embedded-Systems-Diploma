/*******************************************************************************
 * @file bit_math.h
 * @brief This file is the bit manipulation macros
 *
 * @author Abanoub Salah
 * @date March 20, 2023
 *
 ******************************************************************************/

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(REG,BIT)        REG |=  (1 << BIT)
#define CLR_BIT(REG,BIT)        REG &= ~(1 << BIT)
#define TOG_BIT(REG,BIT)        REG ^=  (1 << BIT)
#define GET_BIT(REG,BIT)        (1 & (REG >> BIT))

#endif /* bit_math.h */
