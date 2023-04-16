/*******************************************************************************
 * uart_private.h
 *
 *  Created on: Apr 2, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

#ifndef MCAL_UART_UART_PRIVATE_H_
#define MCAL_UART_UART_PRIVATE_H_

/*******************************************************************************
 * Defines
 ******************************************************************************/
#define NUL					 '\0'

/*******************************************************************************
 *   User type definitions (structures)
 ******************************************************************************/
typedef struct
{
	vuint8_t UBRRL;
	vuint8_t UCSRB;
	vuint8_t UCSRA;
	vuint8_t UDR;
	vuint8_t reserved0[19];
	vuint8_t UBRRH_UCSRC;
} UART_Typedef_t;

/*******************************************************************************
 * Peripheral instances
 ******************************************************************************/
#define UART				 ((UART_Typedef_t *) UART_BASE)

/*******************************************************************************
 * Peripheral bits
 ******************************************************************************/

/* UCSRA bits */
#define RXC_BIT              7
#define TXC_BIT				 6
#define UDRE_BIT			 5
#define fE_BIT	             4
#define DOR_BIT				 3
#define PE_BIT				 2
#define U2X_BIT				 1
#define MPCM_BIT             0

/* UCSRB bits */
#define RXCIE_BIT            7
#define TXCIE_BIT            6
#define UDRIE_BIT            5
#define RXEN_BIT             4
#define TXEN_BIT             3
#define UCSZ2_BIT            2
#define RXB8_BIT             1
#define TXB8_BIT             0

/* UCSRC bits */
#define URSEL_BIT			 7
#define UMSEL_BIT			 6
#define UPM1_BIT             5
#define UPM0_BIT             4
#define USBS_BIT             3
#define UCSZ1_BIT            2
#define UCSZ0_BIT            1
#define UCPOL_BIT            0

/*******************************************************************************
 * Configuration Macros
 ******************************************************************************/

/* UART_PARITY_MODE Options */
#define RX_ENABLE			 0
#define TX_ENABLE			 1
#define TX_RX_ENABLE		 2
#define TX_RX_DISABLE		 3

/* UART_TX_RX_ENABLE Options */
#define DISABLE_PARITY       0
#define EVEN_PARITY          1
#define ODD_PARITY           2

/* UART_IRQ_ENABLE Options */
#define IRQ_DIASABLE		 0
#define RXCIE_IRQ			 1
#define TXCIE_IRQ			 2
#define RXCIE_TXCIE_IRQ		 3

#endif /* MCAL_UART_UART_PRIVATE_H_ */

/******************************************************************************
 *  END OF FILE: uart_private.h
 ******************************************************************************/
