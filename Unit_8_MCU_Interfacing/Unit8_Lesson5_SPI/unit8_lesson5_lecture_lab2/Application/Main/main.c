/*******************************************************************************
 * @file           : main.c
 * @author         : Abanoub Salah
 * @brief          : Send a message w/ interrupts only through:
 *					 UART1 (w/ echo) -> MCU1 -> SPI1
 *					 -> SPI2 -> MCU2 -> UART2 (w/ echo)
 ******************************************************************************/

#include "gpio_interface.h"
#include "rcc_interface.h"
#include "nvic_interface.h"
#include "spi_interface.h"
#include "usart_interface.h"

/*******************************************************************************
 * USE_AS_MASTER: Used to choose between compiling the program as SPI master or
 * 				  as a slave
 *
 * 		 OPTIONS: slave			0
 * 		  		  master		1
 ******************************************************************************/
#define USE_AS_MASTER			0

/*******************************************************************************
 * Global variables
 ******************************************************************************/
uint16_t data = 0;

static SPI_Config_t configSPI1;
static USART_Config_t configUART1;

static void MCAL_Init(void);

#if USE_AS_MASTER == 0
static void SPI1CallBack(void);
#elif USE_AS_MASTER == 1
static void UART1CallBack(void);
#endif

int main(void)
{
	MCAL_Init();

	/* Loop forever */
	while(TRUE)
	{
	}

	return 0;
}

static void MCAL_Init(void)
{
	/* Clock Enable */
	MCAL_RCC_Void_EnableClock(RCC_BusName_APB2, RCC_APB2_Peripheral_En_IOPAEN);
	MCAL_RCC_Void_EnableClock(RCC_BusName_APB2, RCC_APB2_Peripheral_En_AFIOEN);
	MCAL_RCC_Void_EnableClock(RCC_BusName_APB2, RCC_APB2_Peripheral_En_SPI1EN);
	MCAL_RCC_Void_EnableClock(RCC_BusName_APB2, RCC_APB2_Peripheral_En_USART1EN);
#if	USE_AS_MASTER == 0
	MCAL_NVIC_Void_EnableIRQ(NVIC_IRQ_SPI1);
#elif	USE_AS_MASTER == 1
	MCAL_NVIC_Void_EnableIRQ(NVIC_IRQ_USART1);
#endif

	/* SPI1 GPIO Configuration */
#if	USE_AS_MASTER == 0
	GPIO_PinConfig_t configSPI1Pins = {GPIO_PIN_5, GPIO_MODE_INPUT_FLO, GPIO_SPEED_50M};
	MCAL_GPIO_Init(GPIOA, &configSPI1Pins);
	configSPI1Pins.GPIO_PinNumber = GPIO_PIN_7;
	MCAL_GPIO_Init(GPIOA, &configSPI1Pins);
	configSPI1Pins.GPIO_PinNumber = GPIO_PIN_6;
	configSPI1Pins.GPIO_Mode = GPIO_MODE_OUTPUT_AF_OD;
	MCAL_GPIO_Init(GPIOA, &configSPI1Pins);
#elif USE_AS_MASTER == 1
	GPIO_PinConfig_t configSPI1Pins = {GPIO_PIN_4, GPIO_MODE_OUTPUT_AF_PP, GPIO_SPEED_50M};
	MCAL_GPIO_Init(GPIOA, &configSPI1Pins);
	configSPI1Pins.GPIO_PinNumber = GPIO_PIN_5;
	MCAL_GPIO_Init(GPIOA, &configSPI1Pins);
	configSPI1Pins.GPIO_PinNumber = GPIO_PIN_7;
	MCAL_GPIO_Init(GPIOA, &configSPI1Pins);
	configSPI1Pins.GPIO_PinNumber = GPIO_PIN_6;
	configSPI1Pins.GPIO_Mode = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(GPIOA, &configSPI1Pins);
#endif


	/* SPI1 Configuration */
	configSPI1.SPIx = SPI1;
	configSPI1.communicationMode = SPI_CommunicationMode_2line_unidirectionalTxRx;
	configSPI1.frameFormat = SPI_FrameFormat_MSB_First;
	configSPI1.dataFrameFormat = SPI_DataFrameFormat_8Bit;
	configSPI1.clockPolarity = SPI_ClockPolarity_Idle_Low;
	configSPI1.clockPhase = SPI_ClockPhase_Sample_Leading_setup_trailing;
	configSPI1.clockPreScaler = SPI_Prescaler_2;
#if	USE_AS_MASTER == 0
	configSPI1.masterSelection = SPI_MasterSelection_Slave;
	configSPI1.NSS = SPI_NSS_SoftwareSSISet;
	configSPI1.IRQ_Enable = SPI_IRQEnable_TXEIE;
	configSPI1.pIRQCallBack = SPI1CallBack;
#elif	USE_AS_MASTER == 1
	configSPI1.masterSelection = SPI_MasterSelection_Master;
	configSPI1.NSS = SPI_NSS_MasterHardwareOutputEnable;
	configSPI1.IRQ_Enable = SPI_IRQEnable_NONE;
	configSPI1.pIRQCallBack = NULL;
#endif

	MCAL_SPI_Void_Init(&configSPI1);

	/* UART1 pins A9 and A10 configuration */
	GPIO_PinConfig_t UART1PinsConfig = {GPIO_PIN_10, GPIO_MODE_INPUT_FLO, GPIO_SPEED_50M};
	MCAL_GPIO_Init(GPIOA, &UART1PinsConfig);
	UART1PinsConfig.GPIO_PinNumber = GPIO_PIN_9;
	UART1PinsConfig.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
	MCAL_GPIO_Init(GPIOA, &UART1PinsConfig);

	/* UART1 configuration */
	configUART1.USARTx = USART1;
	configUART1.BaudRate = USART_BaudRate_115200;
	configUART1.HWFlowControl = USART_HWFlowControl_NONE;
	configUART1.Parity = USART_Parity_Disable;
	configUART1.payloadLength = USART_PayloadLength_8B;
	configUART1.StopBits = USART_StopBits_1;
#if USE_AS_MASTER == 0
	configUART1.IRQEnable = USART_IRQEnable_NONE;
	configUART1.pIRQCallBack = NULL;
	configUART1.USARTMode = USART_Mode_TX;
#elif USE_AS_MASTER == 1
	configUART1.IRQEnable = USART_IRQEnable_RXNE;
	configUART1.pIRQCallBack = UART1CallBack;
	configUART1.USARTMode = USART_Mode_TX_RX;
#endif

	MCAL_USART_Void_Init(&configUART1);

	return ;
}
#if USE_AS_MASTER == 0
static void SPI1CallBack(void)
{
	//if(SPI_Status_Ok == configSPI1.status)
	{
		/* Receive data */
		MCAL_SPI_Void_Receive(&configSPI1, &data, SPI_Mechanism_Polling);

		/* Send it to the UART */
		MCAL_USART_Void_Send(&configUART1, &data, USART_Mechanism_Polling);
	}
}
#elif USE_AS_MASTER == 1
static void UART1CallBack(void)
{
	/* Get data from UART and echo it back */
	MCAL_USART_Void_Receive(&configUART1, &data, USART_Mechanism_Interrupt);
	MCAL_USART_Void_Send(&configUART1, &data, USART_Mechanism_Polling);

	/* Send received data through SPI */
	MCAL_SPI_Void_Send(&configSPI1, &data, SPI_Mechanism_Polling);

	return ;
}
#endif
