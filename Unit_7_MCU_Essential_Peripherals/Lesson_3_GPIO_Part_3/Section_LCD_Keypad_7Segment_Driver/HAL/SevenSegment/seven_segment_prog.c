/*******************************************************************************
 * seven_segment_prog.c
 *
 *  Created on: Mar 29, 2023
 *      Author: Abanoub Salah
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "seven_segment_config.h"
#include "seven_segment_interface.h"
#include "seven_segment_private.h"

static uint16 SSPinConfig[SS_PIN_COUNT] = {SS_A_PIN, SS_B_PIN, SS_C_PIN, SS_D_PIN, SS_E_PIN, SS_F_PIN, SS_G_PIN};
static GPIO_TypeDef *SSPortConfig[SS_PIN_COUNT] = {SS_A_PORT, SS_B_PORT, SS_C_PORT, SS_D_PORT, SS_E_PORT, SS_F_PORT, SS_G_PORT};

/* Note for the used 7-segment bits control segments as below	*/
/* bit    : 6 5 4 3 2 1 0										*/
/* segment: a f e d c b g										*/
static uint8 charMap[16] = {0x01, 0x79, 0x24, 0x30, 0x58, 0x12, 0x02, 0x39, 0x00, 0x10, 0x08, 0x42, 0x07, 0x60, 0x06, 0x0E};

/*******************************************************************************
 * Fn                -HAL_SevenSegment_Void_Init
 *
 * Brief             -Initializes the 7-segment pins according to the specified
 *                    parameters in the 7-segment configuration.
 *
 * Param [in]        -None.
 *
 * Retval            -None.
 *
 * Note              -None.
 *
 ******************************************************************************/
void HAL_SevenSegment_Void_Init(void)
{
	GPIO_PinConfig_t pinConfig;
	uint8 pinCounter = 0;

	/* Mode and speed are set one time here since all o/p pins	*/
	/* share the same configuration 							*/
	pinConfig.GPIO_Mode = GPIO_MODE_INPUT_PD;
	pinConfig.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinConfig.GPIO_OutputSpeed = GPIO_SPEED_10M;

	for(pinCounter = 0 ; pinCounter < SS_PIN_COUNT; pinCounter++)
	{
		pinConfig.GPIO_PinNumber = SSPinConfig[pinCounter];
		MCAL_GPIO_Init(SSPortConfig[pinCounter], &pinConfig);
		/* Shutting-off segments */
		MCAL_GPIO_WritePin(SSPortConfig[pinCounter], SSPinConfig[pinCounter], GPIO_PIN_SET);
	}

	return ;
}

/*******************************************************************************
 * Fn                -HAL_SevenSegment_Void_Display
 *
 * Brief             -Displays a single integer or hex number
 *                    on the 7-segment.
 *
 * Param [in]        -: The digit to be displayed.
 *
 * Retval            -None.
 *
 * Note              -None.
 *
 ******************************************************************************/
void HAL_SevenSegment_Void_Display(uint8 num)
{
	uint8 curDisplayedNum = charMap[num];
	uint32 counter;

	if(num > 0xf)
	{
		return ;
	}

	/* Set/Reset segment according to it's bit */
	for(counter = 0; counter < SS_PIN_COUNT; counter++)
	{
		MCAL_GPIO_WritePin(SSPortConfig[counter], SSPinConfig[counter], GET_BIT(curDisplayedNum, counter));
	}

	return ;
}

/*******************************************************************************
 * Fn                -HAL_SevenSegment_Void_Reset
 *
 * Brief             -Turns-off all the 7-segment segments
 *
 * Param [in]        -None.
 *
 * Retval            -None.
 *
 * Note              -None.
 *
 ******************************************************************************/
void HAL_SevenSegment_Void_Reset(void)
{
	uint8 pinCounter;

	/* Looping over the 7-segment pins to shut-off segments */
	for(pinCounter = 0; pinCounter < SS_PIN_COUNT; pinCounter++)
	{
		MCAL_GPIO_WritePin(SSPortConfig[pinCounter], SSPinConfig[pinCounter], GPIO_PIN_SET);
	}

	return ;
}
