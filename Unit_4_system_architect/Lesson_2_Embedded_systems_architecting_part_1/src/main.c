/**
 * @file main.c
 * @brief This file is the driver for collision avoidance state machine
 *
 * @author Abanoub Salah
 * @date August 2, 2022
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include "state.h"
#include "ultrasonic_sensor.h"
#include "collision_avoidance.h"
#include "dc_motor.h"

void setup()
{
	/* Initiate all the drivers */
	ultraSonic_init();
	DCMotor_init();

	/* Initiate IRQ */
	/* Initiate HAL drivers: Ultrasonic driver & DC Motor driver */
	/* Initiate Collision Avoidance Block */
	/* set state pointer for each block */
    CollisionAvoidance_state = STATE(CollisionAvoidance_state_waiting);
    ultraSonic_state = STATE(ultraSonic_state_busy);
    DCMotor_state = STATE(DCMotor_state_idle);
}

int main()
{
	setup();

	while(TRUE)
	{
		/* call state function for each block */
		ultraSonic_state();
		CollisionAvoidance_state();
		DCMotor_state();
		/* Time delay */
		for(vuint32_t i = 0 ; i < 1000; ++i);
	}

	return EXIT_SUCCESS;
}
