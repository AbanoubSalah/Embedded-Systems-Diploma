/*******************************************************************************
 * @file           : main.c
 * @author         : Abanoub Salah
 * @brief          : Send a message through UART to MCU w/ echo using interrupt
 ******************************************************************************/

#include "gpio_interface.h"
#include "rcc_interface.h"
#include "nvic_interface.h"
#include "usart_interface.h"

uint16_t data;
static USART_Config_t configUART1;

static void MCAL_Init(void);
static void USART1_CallBack(void);

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
	MCAL_RCC_Void_EnableClock(RCC_BusName_APB2, RCC_APB2_Peripheral_En_USART1EN);

	/* UART1 pins A9 and A10 configuration */
	GPIO_PinConfig_t UART1PinsConfig = {GPIO_PIN_10, GPIO_MODE_INPUT_PU, GPIO_SPEED_50M};
	MCAL_GPIO_Init(GPIOA, &UART1PinsConfig);
	UART1PinsConfig.GPIO_PinNumber = GPIO_PIN_9;
	UART1PinsConfig.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
	MCAL_GPIO_Init(GPIOA, &UART1PinsConfig);

	/* Activating interrupt line in NVIC */
	MCAL_NVIC_Void_EnableIRQ(NVIC_IRQ_USART1);

	/* USART1 configuration */
	configUART1.USARTx = USART1;
	configUART1.BaudRate = USART_BaudRate_9600;
	configUART1.HWFlowControl = USART_HWFlowControl_NONE;
	configUART1.IRQEnable = USART_IRQEnable_RXNE;
	configUART1.pIRQCallBack = USART1_CallBack;
	configUART1.Parity = USART_Parity_Disable;
	configUART1.payloadLength = USART_PayloadLength_8B;
	configUART1.StopBits = USART_StopBits_1;
	configUART1.USARTMode = USART_Mode_TX_RX;

	MCAL_USART_Void_Init(&configUART1);

	return ;
}

static void USART1_CallBack(void)
{
	MCAL_USART_Void_Receive(&configUART1, &data, USART_Mechanism_Polling);
	MCAL_USART_Void_Send(&configUART1, &data, USART_Mechanism_Polling);

	return ;
}
