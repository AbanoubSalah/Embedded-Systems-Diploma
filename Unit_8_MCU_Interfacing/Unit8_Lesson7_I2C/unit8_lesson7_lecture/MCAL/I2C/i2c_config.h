/*******************************************************************************
 * i2c_config.h
 *
 *  Created on: Apr 12, 2023
 *      Author: Abanoub Salah
 ******************************************************************************/

#ifndef MCAL_I2C_I2C_CONFIG_H_
#define MCAL_I2C_I2C_CONFIG_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define I2C_PERIPHERALS_COUNT					2U
#define HERTZ_PER_MEGAHERTZ						1000000UL
#define MICROSECONDS_PER_SECONDS				1000000UL
#define APB2_MAX_FREQUENCY						50000000UL
#define I2C_MIN_FREQUENCY						2000000UL
#define I2C_MIN_FREQUENCY						2000000UL
#define I2C_SM_MAX_FREQUENCY					100000UL

/*******************************************************************************
 * Pins definitions
 ******************************************************************************/
#define SPI_SDA_PORT							GPIOB
#define SPI_SCL_PORT							GPIOB

#define SPI_SDA_PIN								GPIO
#define SPI_SCL_PIN								GPIO_PIN_6

#define DELAY(x)								for(vuint8_t j = 0; j < x; j++){for(vuint8_t i = 0; i < 0xFF; i++);}

#endif /* MCAL_I2C_I2C_CONFIG_H_ */

/*******************************************************************************
 *  END OF FILE: i2c_config.h
 ******************************************************************************/
