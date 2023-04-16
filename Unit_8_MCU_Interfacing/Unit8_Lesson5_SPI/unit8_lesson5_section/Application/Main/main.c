/*******************************************************************************
 * main.c
 *
 *  Created on: Apr 11, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

#include "gpio_interface.h"
#include "spi_interface.h"
#include "lcd_interface.h"

/*******************************************************************************
 * USE_AS_MASTER: Used to choose between compiling the program as SPI master or
 * 				  as a slave
 *
 * 		 OPTIONS: slave			0
 * 		  		  master		1
 ******************************************************************************/
#define USE_AS_MASTER			1

/*******************************************************************************
 * Global variables
 ******************************************************************************/
static uint8_t localCounter = 0x00, remoteCounter = 0x00;
static uint8_t updateLCDFg = 0;

static SPI_Config_t configSPI;

static void MCAL_Init(void);

#if USE_AS_MASTER == 0
static void SPI1CallBack(void);
#endif

#if USE_AS_MASTER == 1
static void delay(uint16_t t);
#endif

int main(void)
{
	MCAL_Init();
#if USE_AS_MASTER == 0
	localCounter = 0x00;
	HAL_LCD_Void_WriteString((uint8_t *)"Slave");
	MCAL_SPI_Void_transceive(&configSPI, &localCounter, &remoteCounter);
#elif USE_AS_MASTER == 1
	localCounter = 0xFF;
	HAL_LCD_Void_WriteString((uint8_t *)"Master");
#endif
	/* Loop forever */
	while(TRUE)
	{
#if USE_AS_MASTER == 1
		delay(0x1F);
		MCAL_SPI_Void_transceive(&configSPI, &localCounter, &remoteCounter);
		localCounter--;
		updateLCDFg = 1;
#endif
		if(1 == updateLCDFg)
		{
			updateLCDFg = 0;
			HAL_LCD_Void_GoTo(1, 0);
			HAL_LCD_Void_WriteString((uint8_t *)"   ");
			HAL_LCD_Void_GoTo(1, 0);
			HAL_LCD_Void_WriteNumber(remoteCounter);
		}
	}

	return 0;
}

static void MCAL_Init(void)
{
	/* MCAL initializations */
	configSPI.dataOrder = SPI_DataOrder_MSB_First;
	configSPI.clockPolarity = SPI_ClockPolarity_Idle_Low;
	configSPI.clockPhase = SPI_ClockPhase_Sample_Leading_setup_trailing;
	configSPI.clockRate = SPI_ClockRate_4;
	configSPI.doubleSpeed = SPI_DoubleSpeed_Disable;
#if USE_AS_MASTER == 0
	configSPI.interruptEnable = SPI_Interrupt_Enable;
	configSPI.interruptCallBack = SPI1CallBack;
	configSPI.modeSelect = SPI_Master_Slave_Select_Slave;
#elif USE_AS_MASTER == 1
	configSPI.interruptEnable = SPI_Interrupt_Disable;
	configSPI.interruptCallBack = NULL;
	configSPI.modeSelect = SPI_Master_Slave_Select_Master;
#endif
	MCAL_SPI_Void_Init(&configSPI);

	/* HAL initializations */
	HAL_LCD_Void_Init();

	/* Enable global interrupt */
	sei();

	return ;
}

#if USE_AS_MASTER == 0
static void SPI1CallBack(void)
{
	if(SPI_Status_WaitingOnInterrupt == configSPI.status)
	{
		localCounter++;
		updateLCDFg = 1;
		/* Receive data */
		MCAL_SPI_Void_transceive(&configSPI, &localCounter, &remoteCounter);
	}
	else
	{
	}
}
#endif

#if USE_AS_MASTER == 1
static void delay(uint16_t t)
{
	vuint16_t i, j;

	for(i = 0; i < 0xFFF; i++)
	{
		for(j = 0; j < t; j++);
	}

	return ;
}
#endif

/*******************************************************************************
 *  END OF FILE: main.h
 ******************************************************************************/
