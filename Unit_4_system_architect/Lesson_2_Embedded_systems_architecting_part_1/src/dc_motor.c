/**
 * @file dc_motor.c
 * @brief This file is the implementation for DC motor module
 *
 * @author Abanoub Salah
 * @date August 2, 2022
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include "dc_motor.h"

/* DC motor module parameters */
static uint32 DCMotor_speed;

/* Enumeration state type for DC motor status */
enum {
	DCMotor_state_idle,
	DCMotor_state_busy
} DCMotor_state_id;

/* Pointer to DC motor function */
void (*DCMotor_state)(void);

/* Initializing DC motor module */
void DCMotor_init(void)
{
	/* Initiating PWM Driver */
	printf("DCMotor_init\n");
}

/* Set speed signal from collision detector to PWM module */
void DCMotor_SetSpeed(sint32 s)
{
	DCMotor_speed = s;
	DCMotor_state = STATE(DCMotor_state_busy);
	printf("CollisionAvoidance —> DCMotor DCMotor(), speed = %d\n",
			DCMotor_speed);
}

/* Define idle state */
STATE_define(DCMotor_state_idle)
{
	DCMotor_state_id = DCMotor_state_idle;

	/* Setting DC motor speed using PWM driver */
	printf("DCMotor_state_idle state: speed = %d\n\n", DCMotor_speed);
}

/* Define busy state */
STATE_define(DCMotor_state_busy)
{
	/* status set */
	DCMotor_state_id = DCMotor_state_busy;

	/* Setting DC motor speed using PWM driver */
	printf("DCMotor_state_busy state: speed = %d\n\n", DCMotor_speed);
	DCMotor_state = STATE(DCMotor_state_idle);
}
