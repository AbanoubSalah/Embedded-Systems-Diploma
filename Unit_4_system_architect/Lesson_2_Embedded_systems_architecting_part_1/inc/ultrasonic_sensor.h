/**
 * @file ultrasonic_sesnsor.h
 * @brief This file is the interface to ultra-sonic motor module
 *
 * @author Abanoub Salah
 * @date August 2, 2022
 *
 */

#ifndef ULTRASONIC_SENSOR_H_
#define ULTRASONIC_SENSOR_H_

#include "state.h"

/* ultraSonic sensor current state */
extern void (*ultraSonic_state)(void);

/* ultraSonic sensor initialization prototype */
void ultraSonic_init(void);

/* ultraSonic sensor states prototypes */
STATE_define(ultraSonic_state_busy);

#endif /* ULTRASONIC_SENSOR_H_ */
