/*******************************************************************************
 * main.c
 *
 *  Created on: Apr 2, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

#include "gpio_interface.h"
#include "spi_interface.h"

/*******************************************************************************
 * USE_AS_MASTER: Used to choose between compiling the program as SPI master or
 * 				  as a slave
 *
 * 		 OPTIONS: slave			0
 * 		  		  master		1
 ******************************************************************************/
#define USE_AS_MASTER			1

static void delay(uint16_t t);

int main(void)
{
	uint8_t txNumber, rxNumber;

	/* MCAL initializations */
	GPIO_PinConfig_t configGPIO = {GPIO_ALL_PINS, GPIO_MODE_OUTPUT};
	MCAL_GPIO_Init(GPIOA, &configGPIO);

	SPI_Config_t configSPI;
	configSPI.interruptEnable = SPI_Interrupt_Disable;
	configSPI.interruptCallBack = NULL;
	configSPI.dataOrder = SPI_DataOrder_MSB_First;
	configSPI.clockPolarity = SPI_ClockPolarity_Idle_Low;
	configSPI.clockPhase = SPI_ClockPhase_Sample_Leading_setup_trailing;
	configSPI.clockRate = SPI_ClockRate_4;
	configSPI.doubleSpeed = SPI_DoubleSpeed_Disable;
#if USE_AS_MASTER == 0
	configSPI.modeSelect = SPI_Master_Slave_Select_Slave;
#elif USE_AS_MASTER == 1
	configSPI.modeSelect = SPI_Master_Slave_Select_Master;
	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
#endif
	MCAL_SPI_Void_Init(&configSPI);

	/* Loop forever */
	while(TRUE)
	{
#if USE_AS_MASTER == 0
		for(txNumber = 0xFF; txNumber >= 0x00; txNumber--)
#elif USE_AS_MASTER == 1
		for(txNumber = 0; txNumber <= 0xFF; txNumber++)
#endif
		{
			delay(10);
			MCAL_SPI_Void_transceive(&configSPI, &txNumber, &rxNumber);
			MCAL_GPIO_WritePort(GPIOA, rxNumber);
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
