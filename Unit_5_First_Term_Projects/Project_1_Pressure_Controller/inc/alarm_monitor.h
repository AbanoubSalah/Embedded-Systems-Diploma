/**********************************************************************************************************************
 * @file alarm_monitor.h
 * @brief This file contains alarm monitor interface for the Pressure Controller project
 *
 * @author Abanoub Salah
 * @date September 13, 2022
 * *********************************************************************************************************************/

#ifndef ALARM_MONITOR_H_
#define ALARM_MONITOR_H_

#include "platform_types.h"
#include "state.h"
#include "driver.h"

/* Defining pressure sensor statuses enumeration */
typedef enum
{
	AlarmMonitor_off,
	AlarmMonitor_on,
	AlarmMonitor_waiting,
} AlarmMonitor_statuses;

/* Alarm monitor statuses prototypes */
STATE_define(AlarmMonitor_off);
STATE_define(AlarmMonitor_on);
STATE_define(AlarmMonitor_waiting);

/* Alarm monitor current state */
extern void (*AlarmMonitor_state)(void);

#endif /* ALARM_MONITOR_H_ */


/**********************************************************************************************************************
 *  END OF FILE: alarm_monitor.h
 *********************************************************************************************************************/
