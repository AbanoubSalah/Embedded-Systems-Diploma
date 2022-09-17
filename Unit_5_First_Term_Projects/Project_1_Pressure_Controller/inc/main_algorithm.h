/**********************************************************************************************************************
 * @file main_algorithm.h
 * @brief This file contains states definitions for the Pressure Controller project
 *
 * @author Abanoub Salah
 * @date September 13, 2022
 * *********************************************************************************************************************/

#ifndef MAIN_ALGORITHM_H_
#define MAIN_ALGORITHM_H_

#include "platform_types.h"
#include "state.h"

/* Defining main algorithm statuses enumeration */
typedef enum
{
	MainAlgorithm_highPresure,
} MainAlgorithm_statuses;

/* Main algorithm statuses prototypes */
STATE_define(MainAlgorithm_highPresure);

/* Main algorithm current state */
extern void (*MainAlgorithm_state)(void);

/******************************************************************************
 * @brief Notify that a high pressure is detected
 *
 * Notify that a high pressure is detected by comparing
 * current sensor reading with a pre-defined threshold
 *
 * @param None
 *
 * @returns boolean					High pressure detected decision	TRUE
																	False
 *******************************************************************************/
boolean MainAlgorithm_HighPressureDetected(void);

#endif /* MAIN_ALGORITHM_H_ */


/**********************************************************************************************************************
 *  END OF FILE: main_algorithm.h
 *********************************************************************************************************************/
