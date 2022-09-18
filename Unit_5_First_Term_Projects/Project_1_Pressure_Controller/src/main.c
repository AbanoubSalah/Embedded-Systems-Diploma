/**********************************************************************************************************************
 * @file main.c
 * @brief This file is the main entry of the pressure controller project
 *
 * @author Abanoub Salah
 * @date September 13, 2022
 * *********************************************************************************************************************/

#include "platform_types.h"
#include "driver.h"
#include "state.h"
#include "main_algorithm.h"
#include "alarm_monitor.h"
#include "pressure_sensor.h"
#include "alarm_actuator.h"

void setup(void)
{
	/* Initiate all the drivers */
	GPIO_Init();
	
	/* Setting initial states */
	Set_Alarm_actuator(ALARM_ACTUATOR_LOGIC_FALSE);
	MainAlgorithm_state = STATE(MainAlgorithm_highPresure);
	AlarmMonitor_state = STATE(AlarmMonitor_off);
	PressureSensor_state = STATE(PressureSensor_init);
	AlarmActuator_state = STATE(AlarmActuator_init);
}

int main()
{
	setup();
	
	while(TRUE)
	{
		/* call state function for each block */
		MainAlgorithm_state();
		AlarmMonitor_state();
		PressureSensor_state();
		AlarmActuator_state();
	}

}

/**********************************************************************************************************************
 *  END OF FILE: main.c
 *********************************************************************************************************************/
