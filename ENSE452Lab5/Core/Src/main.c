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
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include <stdio.h>
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
 UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* Definitions for blink01 */
osThreadId_t blink01Handle;
const osThreadAttr_t blink01_attributes = {
  .name = "blink01",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for blink02 */
osThreadId_t blink02Handle;
const osThreadAttr_t blink02_attributes = {
  .name = "blink02",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for StatusTask */
osThreadId_t StatusTaskHandle;
const osThreadAttr_t StatusTask_attributes = {
  .name = "StatusTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* USER CODE BEGIN PV */


uint8_t cliBufferTX[56];
uint8_t cliBufferRX[10];
uint8_t inputTXBuffer[50];
int period = 500;
int periodSet = 0;
uint8_t periodString[10];



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);
void StartBlink01(void *argument);
void StartBlink02(void *argument);
void StartStatusTask(void *argument);

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
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

//clearing screen
  strcpy((char *)cliBufferTX, "\x1b[2J");
  HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char *)cliBufferTX), 1000);

//going to top
  strcpy((char *)cliBufferTX, "\x1b[0;0H");
  HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char *)cliBufferTX), 1000);

  strcpy((char *)cliBufferTX, "Welcome to the CLI!\r\n");
  HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char *)cliBufferTX), 1000);

  HAL_Delay(2000);

  //Formats the screen to show counter and create a scroll window
//clears screen
  strcpy((char *)cliBufferTX, "\x1b[2J");
  HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char *)cliBufferTX), 1000);

//go to top
  strcpy((char *)cliBufferTX, "\x1b[0;0H");
  HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char *)cliBufferTX), 1000);

  strcpy((char *)cliBufferTX, "Period: ");
  HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char *)cliBufferTX), 1000);

  strcpy((char *)cliBufferTX, "500");
  HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char *)cliBufferTX), 1000);

//go down
  strcpy((char *)cliBufferTX, "\x1b[9;0H");
  HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char *)cliBufferTX), 1000);

  strcpy((char *)cliBufferTX, "To change the period of the LED, enter 'period x', where x is the new period");
  HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char *)cliBufferTX), 1000);

//make a scroll  window
  strcpy((char *)cliBufferTX, "\x1b[10;r");
  HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char *)cliBufferTX), 1000);

//moving to scroll window
  strcpy((char *)cliBufferTX, "\x1b[10;0H");
  HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char *)cliBufferTX), 1000);

  strcpy((char *)cliBufferTX, "=> ");
  HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char *)cliBufferTX), 1000);

//saving spot
  strcpy((char *)cliBufferTX, "\x1b[s");
  HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char *)cliBufferTX), 1000);



  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of blink01 */
  blink01Handle = osThreadNew(StartBlink01, NULL, &blink01_attributes);

  /* creation of blink02 */
  blink02Handle = osThreadNew(StartBlink02, NULL, &blink02_attributes);

  /* creation of StatusTask */
  StatusTaskHandle = osThreadNew(StartStatusTask, NULL, &StatusTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  	  	  	  	  	  	  	  	  //DO NOT PUT CODE IN HERE
	  	  	  	  	  	  	  	  	  //osKernelStart(); will never exit
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartBlink01 */
/**
  * @brief  Function implementing the blink01 thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartBlink01 */
void StartBlink01(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    osDelay(period);
  }
  osThreadTerminate(NULL);
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartBlink02 */
/**
* @brief Function implementing the blink02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartBlink02 */
void StartBlink02(void *argument)           //CLI TASK I just didn't change the name from the demo
{
  /* USER CODE BEGIN StartBlink02 */
	int x;
	uint8_t input[20];
  /* Infinite loop */
  for(;;)
  {
	  x = 0;



	  	  	  while(cliBufferTX[0] != '\r')
	  	  	  {
	   			  if(HAL_UART_Receive(&huart2, cliBufferRX, 1, 300) == HAL_OK)
	  			  {
	   				  if(cliBufferRX[0] == '\b')
	 	  				  {
	 	  					  cliBufferTX[0] = cliBufferRX[0];
	 	  					  cliBufferTX[1] = ' ';
	 	  					  cliBufferTX[2] = '\b';
	 	  					  HAL_UART_Transmit(&huart2, cliBufferTX, 3, 1000);
	 	  					  x--;
	 	  				  }
	 	  				  else
	 	  				  {
	 	  					  cliBufferTX[0] = cliBufferRX[0];
	 	  					  input[x] = cliBufferRX[0];
	 	  					  HAL_UART_Transmit(&huart2, cliBufferTX, 1, 1000);
	 	  					  x++;
	 	  				  }
	  			  	  }
	  	  	   }

	  	  	  	  char *command;
	  	  	 	  char *token;


	  	  	 	  strcpy((char *)cliBufferTX, "\r\n");//making space
	  	  	 	  HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char *)cliBufferTX), 1000);


	  	  	 	  while(x < 20 && input[x] != '\0')//Nulling out the rest of the string
	  	  	 		{
	  	  	 			input[x] = '\0';
	  	  	 			x++;
	  	  	 		}

 				  token = strtok((char *)input, " ");//getting command
	  			  command = token;
	  	  		  token = strtok(NULL, " ");//getting period
	  			  if(strcmp(command, "period") == 0 && atoi(token) > 0)//checking command is correct
	  			  {
	  	  				  period = atoi(token);//assigning the period
	  	  				  periodSet = 1;//telling the CLI to update the period
	 			  }
				  else if(input[0] != '\r')//error checking
	  			  {
	 	  			  strcpy((char *)cliBufferTX, "\nError. Try again.\r\n");
	 	  			  HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char *)cliBufferTX), 1000);
	  	  		  }


	  	  		  for(int i = 0; i < 20; i++)//clearing input
	  	  		  {
	  	  			input[i] = '\0';
	  	  		  }

	  	  		  strcpy((char *)cliBufferTX, "=> ");
 	  			  HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char *)cliBufferTX), 1000);

 	  			  strcpy((char *)cliBufferTX, "\x1b[s");//save spot
 	  			  HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char *)cliBufferTX), 1000);




    osDelay(1);
  }

  //In case the task loop accidentally exits
  osThreadTerminate(NULL);
  /* USER CODE END StartBlink02 */
}

/* USER CODE BEGIN Header_StartStatusTask */
/**
* @brief Function implementing the StatusTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartStatusTask */
void StartStatusTask(void *argument)
{
  /* USER CODE BEGIN StartStatusTask */
  /* Infinite loop */
  for(;;)
  {
	  if(periodSet == 1)
	  {
	  		  sprintf((char *)periodString, "%d", period);

	  		  //go to counter
	  		  strcpy((char *)cliBufferTX, "\x1b[0;9H");
	  		  HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char *)cliBufferTX), 1000);

	  		  //blank out
	  		  strcpy((char *)cliBufferTX, "                       ");
	  		  HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char *)cliBufferTX), 1000);

	  		  //go to counter
	  		  strcpy((char *)cliBufferTX, "\x1b[0;9H");
	  		  HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char *)cliBufferTX), 1000);

	  		  //printing the period to CLI
	  		  strcpy((char *)cliBufferTX, (const char *)periodString);
	  		  HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char *)cliBufferTX), 1000);


		      strcpy((char *)cliBufferTX, "\x1b[u");//return to curs
	  		  HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char *)cliBufferTX), 1000);

	  		  periodSet = 0;//reset
	  }
	  osDelay(1);
  }
  osThreadTerminate(NULL);
  /* USER CODE END StartStatusTask */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM4 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM4) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  //In case the task loop accidentally exits
  osThreadTerminate(NULL);
  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
