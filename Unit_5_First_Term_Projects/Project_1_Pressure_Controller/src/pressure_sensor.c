/**********************************************************************************************************************
 * @file pressure_sensor.c
 * @brief This file is the implementation of the pressure sensor driver
 *
 * @author Abanoub Salah
 * @date September 13, 2022
 * *********************************************************************************************************************/

#include "pressure_sensor.h"
#include "driver.h"

/* Defining pressure sensor status */
PressureSensor_statuses PressureSensor_status;

/* Pointer to pressure sensor state function */
void (*PressureSensor_state)(void);

static uint32 PressureSensor_PressureValue;

STATE_define(PressureSensor_init)
{
	/* Pressure sensor initialization procedures to put it in initiation state */
	/* State action */
	PressureSensor_status = PressureSensor_init;
	
	/* Check for event and update the state */
	PressureSensor_state = STATE(PressureSensor_reading);
}

STATE_define(PressureSensor_reading)
{
	/* State action */
	PressureSensor_status = PressureSensor_reading;
	
	/* Get the current sensor reading */
	PressureSensor_PressureValue = getPressureVal();
	
	/* Check for event and update the state */
	PressureSensor_state = STATE(PressureSensor_waiting);
}

STATE_define(PressureSensor_waiting)
{
	/* State action */
	PressureSensor_status = PressureSensor_waiting;
	
	/* Waiting for pressure sensor data */
	Delay(PRESSURE_SENSOR_WAIT_TIME);
	
	/* Check for event and update the state */
	PressureSensor_state = STATE(PressureSensor_reading);
}

uint32 PressureSensor_GetPressureValue(void)
{
	/* return saved pressure sensor reading */
	return PressureSensor_PressureValue;
}

/**********************************************************************************************************************
 *  END OF FILE: pressure_sensor.c
 *********************************************************************************************************************/
