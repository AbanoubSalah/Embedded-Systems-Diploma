/**********************************************************************************************************************
 * @file alarm_actuator.c
 * @brief This file is the implementation of the alarm actuator driver
 *
 * @author Abanoub Salah
 * @date September 13, 2022
 * *********************************************************************************************************************/

#include "alarm_actuator.h"
#include "driver.h"

/* Defining alarm actuator status */
AlarmActuator_statuses AlarmActuator_status;

/* Pointer to alarm actuator state function */
void (*AlarmActuator_state)(void);

STATE_define(AlarmActuator_off)
{
	/* State action */
	AlarmActuator_status = AlarmActuator_off;
	
	Set_Alarm_actuator(ALARM_ACTUATOR_LOGIC_FALSE);
	
	/* Check for event and update the state */
	AlarmActuator_state = STATE(AlarmActuator_waiting);
}

STATE_define(AlarmActuator_on)
{
	/* State action */
	AlarmActuator_status = AlarmActuator_on;
	
	Set_Alarm_actuator(ALARM_ACTUATOR_LOGIC_TRUE);
	
	/* Check for event and update the state */
	AlarmActuator_state = STATE(AlarmActuator_waiting);
}

STATE_define(AlarmActuator_init)
{
	/* Alarm actuator initialization procedures to put it in known state */
	/* State action */
	AlarmActuator_status = AlarmActuator_init;
	
	/* Check for event and update the state */
	AlarmActuator_state = STATE(AlarmActuator_waiting);
}

STATE_define(AlarmActuator_waiting)
{
	/* State action */
	AlarmActuator_status = AlarmActuator_waiting;
}

void AlarmActuator_StartAlarm(void)
{
	/* Update current State */
	AlarmActuator_state = STATE(AlarmActuator_on);
}

void AlarmActuator_StopAlarm(void)
{
	/* Update current State */
	AlarmActuator_state = STATE(AlarmActuator_off);
}

/**********************************************************************************************************************
 *  END OF FILE: alarm_actuator.c
 *********************************************************************************************************************/
