/**********************************************************************************************************************
 * @file pressure_sensor.h
 * @brief This file contains pressure sensor interface for the Pressure Controller project
 *
 * @author Abanoub Salah
 * @date September 13, 2022
 * *********************************************************************************************************************/

#ifndef PRESSURE_SENSOR_H_
#define PRESSURE_SENSOR_H_

#include "platform_types.h"
#include "state.h"

/* Defining pressure sensor statuses enumeration */
typedef enum
{
	PressureSensor_init,
	PressureSensor_reading,
	PressureSensor_waiting,
} PressureSensor_statuses;

/* Pressure sensor statuses prototypes */
STATE_define(PressureSensor_init);
STATE_define(PressureSensor_reading);
STATE_define(PressureSensor_waiting);

/* Pressure sensor current state */
extern void (*PressureSensor_state)(void);

/******************************************************************************
 * @brief Gets the pressure reading
 *
 * Gets the pressure reading from the pressure sensor
 *
 * @param None
 *
 * @returns uint32					Pressure reading
 *******************************************************************************/
uint32 PressureSensor_GetPressureValue(void);

#endif /* PRESSURE_SENSOR_H_ */


/**********************************************************************************************************************
 *  END OF FILE: pressure_sensor.h
 *********************************************************************************************************************/
