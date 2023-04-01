/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

typedef volatile unsigned int vuint32;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* STM32F103C6 MCU register addresses */
#define GPIOA_BASE 			0x40010800
#define GPIOA_CRL			(*(vuint32 *)(GPIOA_BASE + 0x00)
#define GPIOA_CRH 			(*(vuint32 *)(GPIOA_BASE + 0x04)
#define GPIOA_IDR			(*(vuint32 *)(GPIOA_BASE + 0x08)
#define GPIOA_ODR 			(*(vuint32 *)(GPIOA_BASE + 0x0C)

#define GPIOB_BASE 			0x40010C00
#define GPIOB_CRL			(*(vuint32 *)(GPIOB_BASE + 0x00))
#define GPIOB_CRH 			(*(vuint32 *)(GPIOB_BASE + 0x04))
#define GPIOB_IDR			(*(vuint32 *)(GPIOB_BASE + 0x08))
#define GPIOB_ODR 			(*(vuint32 *)(GPIOB_BASE + 0x0C))

#define RCC_BASE 			0x40021000
#define RCC_APB2ENR 		(*(vuint32 *)(RCC_BASE + 0x18))

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

static void SystemClock_Config(void);
static void GPIO_Init(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  
  /* Initalizing GPIOA */
  GPIO_Init();
	
  /* USER CODE BEGIN 2 */
  
  int delay = 0;

  /* LEDs are initially off */
  GPIOB_ODR |= (1 << 1);
  GPIOB_ODR |= (1 << 13);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while(1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    if(((GPIOA_IDR & (1 << 1)) >> 1) == 0)
    {
	  /* Toggle PB1 */
      GPIOB_ODR ^= (1 << 1);
      while(((GPIOA_IDR & (1 << 1)) >> 1) == 0);
    }

    if(((GPIOA_IDR & (1 << 13)) >> 13) == 1)
    {
	  /* Toggle PB13 */
      GPIOB_ODR ^= (1 << 13);
      for(delay = 0; delay < 10000; ++delay);
    }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
static void SystemClock_Config(void)
{ 
  /* Enable Clock for GPIOA */
  RCC_APB2ENR |= (1 << 2);
  /* Enable Clock for GPIOB */
  RCC_APB2ENR |= (1 << 3);
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void GPIO_Init(void)
{
  /* Set PA1 as a floating input */
  GPIOA_CRL |= (0b0100 << 4);

  /* Set PA13 as a floating input */
  GPIOA_CRH |= (0b0100 << 20);

  /* Set PB1 as a push-pull output */
  GPIOB_CRL &= ~(0b1111 << 4);
  GPIOB_CRL |= (0b0001 << 4);

  /* Set PB13 as a push-pull output */
  GPIOB_CRH &= ~(0b1111 << 20);
  GPIOB_CRH |= (0b0001 << 20);
}
