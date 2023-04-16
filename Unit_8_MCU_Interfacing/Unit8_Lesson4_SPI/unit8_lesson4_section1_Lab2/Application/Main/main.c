/*******************************************************************************
 * main.c
 *
 *  Created on: Apr 2, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

#include "gpio_interface.h"
#include "spi_interface.h"
#include "max7221_interface.h"

static void delay(uint16_t t);

int main(void)
{
	const uint8_t charSet[16] = {0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B, 0x77, 0x1F, 0x4E, 0x3D, 0x4F, 0x47};
	uint8_t counter = 0, displayIndex;
	SPI_Config_t configSPI;

	/* MCAL initializations */
	GPIO_PinConfig_t configGPIO = {GPIO_ALL_PINS, GPIO_MODE_OUTPUT};
	MCAL_GPIO_Init(GPIOA, &configGPIO);
	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);

	configSPI.interruptEnable = SPI_Interrupt_Disable;
	configSPI.interruptCallBack = NULL;
	configSPI.dataOrder = SPI_DataOrder_MSB_First;
	configSPI.modeSelect = SPI_Master_Slave_Select_Master;
	configSPI.clockPolarity = SPI_ClockPolarity_Idle_Low;
	configSPI.clockPhase = SPI_ClockPhase_Sample_Leading_setup_trailing;
	configSPI.clockRate = SPI_ClockRate_4;
	configSPI.doubleSpeed = SPI_DoubleSpeed_Disable;
	MCAL_SPI_Void_Init(&configSPI);

	 /* decode all displays 11111111 */
	HAL_MAX7221_Void_Execute(&configSPI, MAX7221_Command_DecodeMode, MAX7221_Digit_None);

	/* Set Scan Limit (digit0 to digit7) */
	HAL_MAX7221_Void_Execute(&configSPI, MAX7221_Command_ScanLimit, 7);

	/* set to max intensity */
	HAL_MAX7221_Void_Execute(&configSPI, MAX7221_Command_Intensity, 15);

	/* Turn-on display */
	HAL_MAX7221_Void_Execute(&configSPI, MAX7221_Command_Shutdown, MAX7221_ShutdownMode_NormalOperation);

	/* Loop forever */
	while(TRUE)
	{
		for(displayIndex = 1; displayIndex < 9; displayIndex++)
		{
			HAL_MAX7221_Void_Execute(&configSPI, displayIndex, charSet[counter]);
			counter++;
			counter %= 16;
			delay(0x0005);
		}
	}

	return 0;
}

static void delay(uint16_t t)
{
	vuint16_t i, j;

	for(i = 0; i < 0xFFF; i++)
	{
		for(j = 0; j < t; j++);
	}

	return ;
}

/*******************************************************************************
 *  END OF FILE: main.c
 ******************************************************************************/
