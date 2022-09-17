/**********************************************************************************************************************
 * @file state.h
 * @brief This file contains states definitions for the Pressure Controller project
 *
 * @author Abanoub Salah
 * @date September 13, 2022
 * *********************************************************************************************************************/


#ifndef STATE_H_
#define STATE_H_

#include "platform_types.h"

/* Main algorithm user defined pressure threshold */
#define MAIN_ALGORITHM_PRESSURE_THRESHOLD				20U

/* Alarm actuator output logic definitions */
#define FLIPPED_LOGIC									1U

#if (FLIPPED_LOGIC == 1)
#define ALARM_ACTUATOR_LOGIC_TRUE						FALSE
#define ALARM_ACTUATOR_LOGIC_FALSE						TRUE
#else
#define ALARM_ACTUATOR_LOGIC_TRUE						TRUE
#define ALARM_ACTUATOR_LOGIC_FALSE						FALSE
#endif

/* Sensor wait time */
#define PRESSURE_SENSOR_WAIT_TIME						0xFU

/* Alarm monitor wait time, note that wait time is 60 seconds by requirements */
#define ALARM_MONITOR_WAIT_TIME							0xFFU

/* Macros to define states name and functions prototype */
#define STATE_define(stateFn) void ST_##stateFn(void)
#define STATE(stateFn) ST_##stateFn

/* States connection functions */

extern uint32 PressureSensor_GetPressureValue(void);
extern void AlarmActuator_StartAlarm(void);
extern void AlarmActuator_StopAlarm(void);
extern boolean MainAlgorithm_HighPressureDetected(void);

#endif /* STATE_H_ */


/**********************************************************************************************************************
 *  END OF FILE: state.h
 *********************************************************************************************************************/
