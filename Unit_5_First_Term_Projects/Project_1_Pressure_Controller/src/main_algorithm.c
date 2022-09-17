/**********************************************************************************************************************
 * @file main_algorithm.c
 * @brief This file is the implementation of the main algorithm of the pressure controller project
 *
 * @author Abanoub Salah
 * @date September 13, 2022
 * *********************************************************************************************************************/

#include "main_algorithm.h"

/* Defining main algorithm status */
MainAlgorithm_statuses MainAlgorithm_status;

/* Pointer to main algorithm state function */
void (*MainAlgorithm_state)(void);

/* Main algorithm parameters */
static uint32 MainAlgorithm_pressureVa1ue;
const static uint32 MainAlgorithm_pressureThreshold = MAIN_ALGORITHM_PRESSURE_THRESHOLD;

STATE_define(MainAlgorithm_highPresure)
{
	/* State action */
	MainAlgorithm_status = MainAlgorithm_highPresure;
	
	/* Get pressure reading from pressure sensor */
	MainAlgorithm_pressureVa1ue = PressureSensor_GetPressureValue();
	
	/* Check for event and update the state */
	MainAlgorithm_state = STATE(MainAlgorithm_highPresure);
}

boolean MainAlgorithm_HighPressureDetected(void)
{
	boolean isPressureHigh = (boolean) FALSE;
	/* Check current pressure value with the threshold */
	if(MainAlgorithm_pressureVa1ue > MainAlgorithm_pressureThreshold)
	{
		isPressureHigh = (boolean) TRUE;
	}
	
	return isPressureHigh;
}

/**********************************************************************************************************************
 *  END OF FILE: main_algorithm.c
 *********************************************************************************************************************/
