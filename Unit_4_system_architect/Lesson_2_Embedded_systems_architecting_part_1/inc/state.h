/**
 * @file state.h
 * @brief This file is the interface to state module
 *
 * @author Abanoub Salah
 * @date August 2, 2022
 *
 */

#ifndef STATE_H_
#define STATE_H_

#include "platform_types.h"

/* Macros to define states name and function prototype */
#define STATE_define(stateFn) void ST_##stateFn(void)
#define STATE(stateFn) ST_##stateFn

/* States connection functions */
void ultraSonic_SetDistance(sint32 d);
void DCMotor_SetSpeed(sint32 s);

#endif /* STATE_H_ */
