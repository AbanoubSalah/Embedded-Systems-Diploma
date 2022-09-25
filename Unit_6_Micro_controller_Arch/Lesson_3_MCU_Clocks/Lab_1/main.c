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
#define GPIOA_CRH 			*(vuint32 *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR 			*(vuint32 *)(GPIOA_BASE + 0x0C)

#define RCC_BASE 			0x40021000
#define RCC_APB2ENR 		*(vuint32 *)(RCC_BASE + 0x18)

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

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while(1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	
	/* Set Port A Pin 13 */
	GPIOA_ODR |= (1 << 13);
	/* Delay */
	for(vuint32 i = 0; i < 5000; ++i);
	/* Clear Port A Pin 13 */
	GPIOA_ODR &= ~(1 << 13);
	/* Delay */
	for(vuint32 i = 0; i < 5000; ++i);
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
  RCC_APB2ENR |= (1<<2);
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  GPIOA_CRH &= (0xFF0FFFFF);
  GPIOA_CRH |= (0x00200000);
}
