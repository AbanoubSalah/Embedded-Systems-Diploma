/**
 * @file collision_avoidance.c
 * @brief This file is the implementation for collision avoidance module
 *
 * @author Abanoub Salah
 * @date August 2, 2022
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include "collision_avoidance.h"

/* Collision detection module parameters */
static sint32 CollisionAvoidance_speed = 0;
static sint32 CollisionAvoidance_distance = 0;
static sint32 CollisionAvoidance_threshold = 50;

/* Enumeration state type for collision detection status */
enum
{
	CollisionAvoidance_state_waiting,
	CollisionAvoidance_state_driving
} CollisionAvoidance_state_id;

/* Pointer to collision avoidance function */
void (*CollisionAvoidance_state)(void);

/* generate random value between min and max */
static sint32 GenerateRandomNumber(sint32 min, sint32 max, sint32 count)
{
	sint32 randNumber = 0;

	for (sint32 i = 0; i < count; i++)
	{
		randNumber = (rand() % (max - min + 1)) + min;
	}

	return randNumber;
}

/* Set distance signal from sensor to collision detector */
void ultraSonic_SetDistance(sint32 d)
{
	CollisionAvoidance_distance = GenerateRandomNumber(45, 55, 1);
	CollisionAvoidance_state = (CollisionAvoidance_distance <=
			CollisionAvoidance_threshold) ?
					(STATE(CollisionAvoidance_state_waiting)) :
					(STATE(CollisionAvoidance_state_driving));
	printf("ultraSonic —> CollisionAvoidance ultraSonic_DistanceSet(): Distance"
			" = %d\n", CollisionAvoidance_distance);
}

/* Define waiting state */
STATE_define(CollisionAvoidance_state_waiting)
 {
    /* state name */
	CollisionAvoidance_state_id = CollisionAvoidance_state_waiting;
	printf("CollisionAvoidance_state_waiting State: Distance = %d  Speed = %d"
			"\n", CollisionAvoidance_distance, CollisionAvoidance_speed);

	/* state action */
	CollisionAvoidance_speed = 0;
	DCMotor_SetSpeed(0);

	/* event check */
}

/* Define driving state */
STATE_define(CollisionAvoidance_state_driving)
 {
	/* state name */
	CollisionAvoidance_state_id = CollisionAvoidance_state_driving;
	printf ("CollisionAvoidance_state_waiting State: Distance = %d  Speed = %d"
			"\n", CollisionAvoidance_distance, CollisionAvoidance_speed);

	/* state action */
	CollisionAvoidance_speed = 30;
	DCMotor_SetSpeed(30);

	/* event check */
}
