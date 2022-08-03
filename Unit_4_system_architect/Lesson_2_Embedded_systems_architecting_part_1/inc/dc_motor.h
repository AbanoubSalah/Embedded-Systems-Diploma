/**
 * @file dc_motor.h
 * @brief This file is the interface to DC motor module
 *
 * @author Abanoub Salah
 * @date August 2, 2022
 *
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "state.h"

/* DC motor current state */
extern void (*DCMotor_state)(void);

/* DC motor initialization prototype */
void DCMotor_init();

/* DC motor states prototypes */
STATE_define(DCMotor_state_idle);
STATE_define(DCMotor_state_busy);

#endif /* DC_MOTOR_H_ */
