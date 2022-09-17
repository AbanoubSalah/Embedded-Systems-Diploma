/**********************************************************************************************************************
 * @file alarm_monitor.c
 * @brief This file is the implementation of the pressure sensor driver
 *
 * @author Abanoub Salah
 * @date September 13, 2022
 * *********************************************************************************************************************/

#include "alarm_monitor.h"

/* Defining pressure sensor status */
AlarmMonitor_statuses AlarmMonitor_status;

/* Pointer to alarm monitor state function */
void (*AlarmMonitor_state)(void);

STATE_define(AlarmMonitor_off)
{
	/* State action */
	AlarmMonitor_status = AlarmMonitor_off;
	
	AlarmActuator_StopAlarm();
	
	/* Check for event and update the state */
	if(MainAlgorithm_HighPressureDetected() == TRUE)
	{
		AlarmMonitor_state = STATE(AlarmMonitor_on);
	}
}

STATE_define(AlarmMonitor_on)
{
	/* State action */
	AlarmMonitor_status = AlarmMonitor_on;
	
	AlarmActuator_StartAlarm();
	
	/* Check for event and update the state */
	AlarmMonitor_state = STATE(AlarmMonitor_waiting);
}

STATE_define(AlarmMonitor_waiting)
{
	/* State action */
	AlarmMonitor_status = AlarmMonitor_waiting;
	
	Delay(ALARM_MONITOR_WAIT_TIME);
	
	/* Check for event and update the state */
	AlarmMonitor_state = STATE(AlarmMonitor_off);
}

/**********************************************************************************************************************
 *  END OF FILE: alarm_monitor.c
 *********************************************************************************************************************/
