/*******************************************************************************
 * lcd_config.h
 *
 *  Created on: Apr 1, 2023
 *      Author: Abanoub Salah
 *
 ******************************************************************************/

#ifndef HAL_LCD_LCD_CONFIG_H_
#define HAL_LCD_LCD_CONFIG_H_

/*******************************************************************************
 * Select micro-controler pins
 ******************************************************************************/
#define LCD_D0_PORT               GPIOA
#define LCD_D1_PORT               GPIOA
#define LCD_D2_PORT               GPIOA
#define LCD_D3_PORT               GPIOA
#define LCD_D4_PORT               GPIOA
#define LCD_D5_PORT               GPIOA
#define LCD_D6_PORT               GPIOA
#define LCD_D7_PORT               GPIOA
#define LCD_RS_PORT               GPIOA
#define LCD_RW_PORT               GPIOA
#define LCD_EN_PORT               GPIOA

#define LCD_D0_PIN                GPIO_PIN_3
#define LCD_D1_PIN                GPIO_PIN_4
#define LCD_D2_PIN                GPIO_PIN_5
#define LCD_D3_PIN                GPIO_PIN_6
#define LCD_D4_PIN                GPIO_PIN_3
#define LCD_D5_PIN                GPIO_PIN_4
#define LCD_D6_PIN                GPIO_PIN_5
#define LCD_D7_PIN                GPIO_PIN_6
#define LCD_RS_PIN                GPIO_PIN_1
#define LCD_RW_PIN                GPIO_PIN_1
#define LCD_EN_PIN                GPIO_PIN_2

/*******************************************************************************
 * LCD_MODE OPTIONS   [ MODE_4_BIT , MODE_8_BIT ]
 ******************************************************************************/
#define LCD_MODE				  MODE_4_BIT

#define DELAY(x)				  delay_ms(x)

#endif /* HAL_LCD_LCD_CONFIG_H_ */

/*******************************************************************************
 *  END OF FILE: lcd_config.h
 ******************************************************************************/
