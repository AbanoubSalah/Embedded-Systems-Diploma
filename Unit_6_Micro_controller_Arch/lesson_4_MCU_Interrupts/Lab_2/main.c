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
#define GPIOx_CRL   		*(vuint32 *)(GPIOA_BASE + 0x00)
#define GPIOA_CRH 			*(vuint32 *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR 			*(vuint32 *)(GPIOA_BASE + 0x0C)

#define RCC_BASE 			0x40021000
#define RCC_CR      		*(vuint32 *)(RCC_BASE + 0x00)
#define RCC_CFGR    		*(vuint32 *)(RCC_BASE + 0x04)
#define RCC_APB2ENR 		*(vuint32 *)(RCC_BASE + 0x18)

#define EXTI_BASE   		0x40010400
#define EXTI_IMR    		*(vuint32 *)(EXTI_BASE + 0x00)
#define EXTI_RTSR   		*(vuint32 *)(EXTI_BASE + 0x08)
#define EXTI_PR     		*(vuint32 *)(EXTI_BASE + 0x14)

#define NVIC_ISER0  		*(vuint32 *)(0xE000E100)

#define AFIO_BASE   		0x4001000
#define AFIO_EXTICR1 		*(vuint32 *)(AFIO_BASE + 0x08)

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
  
  /* Initalizing EXTI0 */
  EXTI_init();
	
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while(1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
static void SystemClock_Config(void)
{  
  /* PLL selected as System clock */
  RCC_CFGR |= (0b10 << 0);
  /* Set APB1 Prescale to 2 */
  RCC_CFGR |= (0b100 << 8);
  /* Set APB2 Prescale to 4 */
  RCC_CFGR |= (0b101 << 11);
  /* PLL multiplication factor by 8 */
  RCC_CFGR |= (0b0110 << 18);
  
  /* Alternate function clock enable */
  RCC_APB2ENR |= (1 << 0);
  /* Enable Clock for GPIOA */
  RCC_APB2ENR |= (1 << 2);
  /* Enable PLL */
  RCC_CR |= (1 << 24);
}

/**
  * @brief External interrupt Initialization
  * @param None
  * @retval None
  */
void EXTI_init(void)
{
	/* EXTI0 enable */
    EXTI_IMR |= (1 << 0);
	/* Enabled rising trigger for EXTI0 */
    EXTI_RTSR |= (1 << 0);
	/* Enable IRQ6 (*EXTI0) */
    NVIC_ISER0 |= (1 << 6);
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void GPIO_Init(void)
{

  GPIOA_CRH &= (0xFF0FFFFF);
  GPIOA_CRH |= (0x00200000);

  /* Floating input */
  GPIOx_CRL |= (1<<2);

  /* PA0 external interrupt configuration register */
  AFIO_EXTICR1 = (0x0);
}

/**
  * @brief External interrupt 0 handler
  * @param None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{
    /* Toggle pin 13 */
    GPIOA_ODR ^= (1 << 13);

    /* Clear EXTI0 pending status */
    EXTI_PR |= (1 << 0);
}