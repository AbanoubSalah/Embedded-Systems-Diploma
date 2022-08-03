/**
 * @file ultrasonic_sensor.c
 * @brief This file is the interface to ultra-sonic motor module
 *
 * @author Abanoub Salah
 * @date August 2, 2022
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "ultrasonic_sensor.h"

/* ultra-Sonic sensor module parameters */
static sint32 ultraSonic_distance;

/* Enumeration state type for ultra-Sonic sensor status */
enum
{
	ultraSonic_state_busy
}ultraSonic_state_id;

/* Pointer to ultra-Sonic sensor function */
void (*ultraSonic_state)(void);

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

/* Initializing ultra-Sonic sensor module */
void ultraSonic_init(void)
{
	/* call the ultraSonic Driver or Functions */
	printf("ultraSonic_init\n");
}

/* Define busy state */
STATE_define(ultraSonic_state_busy)
{
	/* state name */
	ultraSonic_state_id = ultraSonic_state_busy;

	/* read from the US */
	ultraSonic_distance = GenerateRandomNumber(45, 55, 1);
	printf("ultraSonic_state_busy state: distance = %d\n", ultraSonic_distance);

	ultraSonic_SetDistance(ultraSonic_distance);
	ultraSonic_state = STATE(ultraSonic_state_busy);
}
