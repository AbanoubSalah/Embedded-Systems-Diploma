/**********************************************************************************************************************
 * @file alarm_actuator.h
 * @brief This file contains alarm actuator interface for the Pressure Controller project
 *
 * @author Abanoub Salah
 * @date September 13, 2022
 * *********************************************************************************************************************/

#ifndef ALARM_ACTUATOR_H_
#define ALARM_ACTUATOR_H_

#include "platform_types.h"
#include "state.h"

/* Defining alarm actuator statuses enumeration */
typedef enum
{
	AlarmActuator_off,
	AlarmActuator_on,
	AlarmActuator_init,
	AlarmActuator_waiting,
} AlarmActuator_statuses;

/* Alarm actuator statuses prototypes */
STATE_define(AlarmActuator_off);
STATE_define(AlarmActuator_on);
STATE_define(AlarmActuator_init);
STATE_define(AlarmActuator_waiting);

/* Alarm actuator current state */
extern void (*AlarmActuator_state)(void);

/******************************************************************************
 * @brief Starts the alarm
 *
 * Starts the alarm by setting a pin high
 *
 * @param None
 *
 * @returns None
 *******************************************************************************/
void AlarmActuator_StartAlarm(void);

/******************************************************************************
 * @brief Stops the alarm
 *
 * Stops the alarm by setting a pin high
 *
 * @param None
 *
 * @returns None
 *******************************************************************************/
void AlarmActuator_StopAlarm(void);

#endif /* ALARM_ACTUATOR_H_ */


/**********************************************************************************************************************
 *  END OF FILE: alarm_actuator.h
 *********************************************************************************************************************/
