/*******************************************************************************
 * @file           : main.c
 * @author         : Abanoub Salah
 * @brief          : Send a message to UART -> MCU -> SPI
 ******************************************************************************/

#include "gpio_interface.h"
#include "rcc_interface.h"
#include "nvic_interface.h"
#include "spi_interface.h"
#include "usart_interface.h"

/*******************************************************************************
 * Global variables
 ******************************************************************************/
uint16_t data;

static SPI_Config_t configSPI1;
static USART_Config_t configUART1;

static void MCAL_Init(void);
static void UART1CallBack(void);

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
	MCAL_NVIC_Void_EnableIRQ(NVIC_IRQ_USART1);

	/* SPI1 GPIO Configuration */
	GPIO_PinConfig_t SPI1PinsConfig = {GPIO_PIN_4, GPIO_MODE_OUTPUT_AF_PP, GPIO_SPEED_50M};
	MCAL_GPIO_Init(GPIOA, &SPI1PinsConfig);
	SPI1PinsConfig.GPIO_PinNumber = GPIO_PIN_5;
	MCAL_GPIO_Init(GPIOA, &SPI1PinsConfig);
	SPI1PinsConfig.GPIO_PinNumber = GPIO_PIN_7;
	MCAL_GPIO_Init(GPIOA, &SPI1PinsConfig);
	SPI1PinsConfig.GPIO_PinNumber = GPIO_PIN_6;
	SPI1PinsConfig.GPIO_Mode = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(GPIOA, &SPI1PinsConfig);

	/* SPI1 Configuration */
	configSPI1.SPIx = SPI1;
	configSPI1.masterSelection = SPI_MasterSelection_Master;
	configSPI1.communicationMode = SPI_CommunicationMode_2line_unidirectionalTxRx;
	configSPI1.frameFormat = SPI_FrameFormat_MSB_First;
	configSPI1.dataFrameFormat = SPI_DataFrameFormat_8Bit;
	configSPI1.clockPolarity = SPI_ClockPolarity_Idle_Low;
	configSPI1.clockPhase = SPI_ClockPhase_Sample_Leading_setup_trailing;
	configSPI1.NSS = SPI_NSS_MasterHardwareOutputEnable;
	configSPI1.clockPreScaler = SPI_Prescaler_2;
	configSPI1.IRQ_Enable = SPI_IRQEnable_NONE;
	configSPI1.pIRQCallBack = NULL;
	MCAL_SPI_Void_Init(&configSPI1);

	/* UART1 pins A9 and A10 configuration */
	GPIO_PinConfig_t UART1PinsConfig = {GPIO_PIN_10, GPIO_MODE_INPUT_PU, GPIO_SPEED_50M};
	MCAL_GPIO_Init(GPIOA, &UART1PinsConfig);
	UART1PinsConfig.GPIO_PinNumber = GPIO_PIN_9;
	UART1PinsConfig.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
	MCAL_GPIO_Init(GPIOA, &UART1PinsConfig);

	/* UART1 configuration */
	configUART1.USARTx = USART1;
	configUART1.BaudRate = USART_BaudRate_115200;
	configUART1.HWFlowControl = USART_HWFlowControl_NONE;
	configUART1.IRQEnable = USART_IRQEnable_RXNE;
	configUART1.pIRQCallBack = UART1CallBack;
	configUART1.Parity = USART_Parity_Disable;
	configUART1.payloadLength = USART_PayloadLength_8B;
	configUART1.StopBits = USART_StopBits_1;
	configUART1.USARTMode = USART_Mode_TX_RX;
	MCAL_USART_Void_Init(&configUART1);

	return ;
}


static void UART1CallBack(void)
{
	/* Get data from UART and echo it back */
	MCAL_USART_Void_Receive(&configUART1, &data, USART_Mechanism_Interrupt);
	MCAL_USART_Void_Send(&configUART1, &data, USART_Mechanism_Polling);

	/* Send received data through SPI */
	MCAL_SPI_Void_Send(&configSPI1, &data, SPI_Mechanism_Interrupt);

	return ;
}
