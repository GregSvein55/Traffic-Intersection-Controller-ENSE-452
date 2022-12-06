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
#include <stdlib.h>
#include "Lights.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
void transmitText(const char*);
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
 UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* Definitions for StateController */
osThreadId_t StateControllerHandle;
const osThreadAttr_t StateController_attributes = {
  .name = "StateController",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for CLI */
osThreadId_t CLIHandle;
const osThreadAttr_t CLI_attributes = {
  .name = "CLI",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for StatusUpdate */
osThreadId_t StatusUpdateHandle;
const osThreadAttr_t StatusUpdate_attributes = {
  .name = "StatusUpdate",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for CommandQueue */
osMessageQueueId_t CommandQueueHandle;
const osMessageQueueAttr_t CommandQueue_attributes = {
  .name = "CommandQueue"
};
/* Definitions for MessageQueue */
osMessageQueueId_t MessageQueueHandle;
const osMessageQueueAttr_t MessageQueue_attributes = {
  .name = "MessageQueue"
};
/* USER CODE BEGIN PV */


uint8_t cliBufferRX[10];
uint8_t save[100];


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);
void StartStateController(void *argument);
void StartCLI(void *argument);
void StartStatusUpdate(void *argument);

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



  transmitText("\x1b[2J");//clear screen
  transmitText("\x1b[0;0H");//go to top
  transmitText("TRAFFIC LIGHT CONTROLLER\r\n");
  HAL_Delay(2000);

  //Formats the screen to show counter and create a scroll window
  transmitText("\x1b[2J");//clear screen
  transmitText("\x1b[0;0H");//go to top
  transmitText("Mode: Initialization");
  transmitText("\x1b[9;0H");//go to row 9
  transmitText("Enter \"help\" for a list of commands");
  transmitText("\x1b[10;r");//making a scroll window
  transmitText("\x1b[10;0H");// go to scroll window

  transmitText("\n-> ");
  transmitText("\x1b[?25h");//show cursor
  transmitText("\x1b[s");//save cursor



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

  /* Create the queue(s) */
  /* creation of CommandQueue */
  CommandQueueHandle = osMessageQueueNew (1, sizeof(uint16_t), &CommandQueue_attributes);

  /* creation of MessageQueue */
  MessageQueueHandle = osMessageQueueNew (1, sizeof(uint16_t), &MessageQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of StateController */
  StateControllerHandle = osThreadNew(StartStateController, NULL, &StateController_attributes);

  /* creation of CLI */
  CLIHandle = osThreadNew(StartCLI, NULL, &CLI_attributes);

  /* creation of StatusUpdate */
  StatusUpdateHandle = osThreadNew(StartStatusUpdate, NULL, &StatusUpdate_attributes);

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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, R1_Pin|R2_Pin|T1_Pin|W1_Pin
                          |W2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, G1_Pin|G2_Pin|Y1_Pin|Y2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : R1_Pin R2_Pin T1_Pin W1_Pin
                           W2_Pin */
  GPIO_InitStruct.Pin = R1_Pin|R2_Pin|T1_Pin|W1_Pin
                          |W2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : G1_Pin G2_Pin Y1_Pin Y2_Pin */
  GPIO_InitStruct.Pin = G1_Pin|G2_Pin|Y1_Pin|Y2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void transmitText(const char* str){

		uint8_t cliBufferTX[100];

		strcpy((char *)cliBufferTX, (char *) str);
		HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char *)cliBufferTX), 1000);
}
/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartStateController */
/**
  * @brief  Function implementing the StateController thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartStateController */
void StartStateController(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
		char state = 'z';
		uint16_t cmd = 111;
		uint16_t msg = cmd;
		int period = 500;
		int acceleration = 1;
		/* Infinite loop */
		for(;;)
		{

			if(osMessageQueueGet(CommandQueueHandle, &cmd, NULL, 0U) == osOK)
			{
				if(cmd != msg && cmd > 100)
				{
					if(cmd == 101)//Failsafe mode
					{
						state = 'x';
					}
					else if(cmd == 102)//static cycle mode
					{
						state = 'a';
					}
					else if(cmd == 105)//Low Volume Mode: Runs twice as fast so nobody is waiting long
					{
						acceleration = 2;
						state = 'a';

					}
					else if(cmd == 106)//Fixed Cycle Mode
					{
						state = 'a';

					}
					else if(cmd == 107)//pri ped
					{
						state = 'm';

					}
					else if(cmd == 108)//sec ped
					{
						state = 'n';

					}
					else if(cmd == 109)//pri erv
					{
						state = 'o';

					}
					else if(cmd == 110)//sec erv
					{
						state = 'p';

					}
					msg = cmd;
				}
				else if(cmd != msg && cmd > 0)
				{
					acceleration = cmd;
				}
			}

			if(osMessageQueuePut(MessageQueueHandle, &msg, 1U, 0U)!= osOK)
			{
				Error_Handler();
			}

			period = periodSet(state, acceleration);
			state = lightSet(state);



			osDelay(period);
		}
		osThreadTerminate(NULL);
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartCLI */
/**
* @brief Function implementing the CLI thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartCLI */
void StartCLI(void *argument)
{
  /* USER CODE BEGIN StartCLI */

	int x = 0;
	uint16_t cmd = 0;
	char* cmdStr;
	char* arg;
	uint8_t get[100];


  /* Infinite loop */
  for(;;)
  {
	  if(HAL_UART_Receive(&huart2, cliBufferRX, 1, 300) == HAL_OK)
	  		{
	  			transmitText("\x1b[u");//return cursor
	  			transmitText("\x1b[?25h");//show cursor

	  			if(cliBufferRX[0] == '\b')
	  			{
	  				transmitText("\b \b");

	  			}
	  			else
	  			{
	  				save[x] = cliBufferRX[0];
	  				transmitText(cliBufferRX);

	  			}

	  			transmitText("\x1b[s");//save cursor

	  			//backspace
	  			if(cliBufferRX[0] == '\b')
	  			{
	  				x--;
	  			}
	  			else
	  			{
	  				x++;
	  			}


	  			if(cliBufferRX[0] == '\r')//when user hits enter
	  			{
	  				transmitText("\r\n");
	  				save[x-1] = '\0';
	  				while(x < 100 && save[x] != '\0')//nulling out the rest of the buffer
	  				{
	  					save[x] = '\0';
	  					x++;
	  				}

	  				strcpy((char *)get, (const char *)save);//getting command
	  				arg = strtok((char *)save, " ");
	  				cmdStr = arg;
	  				arg = strtok(NULL, " ");

	  				if(arg == NULL && strcmp((char *)cmdStr, "help") == 0)
	  				{
	  					cmd = 103;
	  					transmitText("1. \"mode fsm\" switches controller to Failsafe mode\r\n");
	  					transmitText("\n2. \"mode scm\" switches controller to Static Cycle mode\r\n");
	  					transmitText("\n3. \"atm x\" enters accelerated test mode with multiplication factor x, when 0 < x < 101\r\n");
	  					transmitText("\n4. \"mode lvm\" switches controller to Low Volume Mode, which means no turning light\r\n");
	  					transmitText("\n5. \"mode fcm\" switched controller to Fixed Cycle Mode, and can now accept pedestrian and ERV inputs\r\n");
	  					transmitText("\n6. \"clear\" clears the scroll screen of its command history and brings the cursor back to the top\r\n");
	  					transmitText("FSM Commands:\r\n");
	  					transmitText(" - event pp: Primary Pedestrian\r\n");
	  					transmitText(" - event sp: Secondary Pedestrian\r\n");
	  					transmitText(" - event pev: Primary Emergency Vehicle\r\n");
	  					transmitText(" - event sev: Secondary Emergency Vehicle\r\n");
	  				}
	  				else if(arg == NULL && strcmp((char *)cmdStr, "clear") == 0)
	  				{
	  					cmd = 104;
	  					transmitText("\x1b[2J");//clear screen
	  					transmitText("\x1b[0;0H");//go to top
	  					transmitText("Mode: ");
	  					transmitText("\x1b[9;0H");//go to row 9
	  					transmitText("Enter \"help\" for a list of commands");
	  					transmitText("\x1b[10;r");//make a scroll window
	  					transmitText("\x1b[10;0H");//go to the scroll window
	  					transmitText("\x1b[?25h");//show cursor
	  					if(osMessageQueuePut(CommandQueueHandle, &cmd, 1U, 0U)!= osOK)
	  					{
	  						Error_Handler();
	  					}
	  				}
	  				else if(cmdStr == NULL)
	  				{
	  					cmd = 103;
	  				}
	  				else if(strtok(NULL, " ") == NULL)
	  				{
	  					if(atoi(arg) >= 1 && atoi(arg) <= 100 && strcmp((char *)cmdStr, "atm") == 0)
	  					{
	  						cmd = (uint16_t)atoi(arg);
	  						transmitText("Entering accelerated test mode.\r\n");
	  						if(osMessageQueuePut(CommandQueueHandle, &cmd, 1U, 0U)!= osOK)
	  						{
	  							Error_Handler();
	  						}
	  					}
	  					else if(strcmp((char *)cmdStr, "mode") == 0 && strcmp((char *)arg, "fsm") == 0)
	  					{
	  						cmd = 101;
	  						transmitText("Switching to Failsafe mode.\r\n");
	  						if(osMessageQueuePut(CommandQueueHandle, &cmd, 1U, 0U)!= osOK)
	  						{
	  							Error_Handler();
	  						}
	  					}
	  					else if(strcmp((char *)cmdStr, "mode") == 0 && strcmp((char *)arg, "scm") == 0)
	  					{
	  						cmd = 102;
	  						transmitText("Switching to Static Cycle mode.\r\n");
	  						if(osMessageQueuePut(CommandQueueHandle, &cmd, 1U, 0U)!= osOK)
	  						{
	  							Error_Handler();
	  						}
	  					}
	  					else if(strcmp((char *)cmdStr, "mode") == 0 && strcmp((char *)arg, "lvm") == 0)
	  					{
	  						cmd = 105;
	  						transmitText("Switching to Low Volume mode.\r\n");
	  						if(osMessageQueuePut(CommandQueueHandle, &cmd, 1U, 0U)!= osOK)
	  						{
	  							Error_Handler();
	  						}
	  					}
	  					else if(strcmp((char *)cmdStr, "mode") == 0 && strcmp((char *)arg, "fcm") == 0)
	  					{
	  						cmd = 106;
	  						transmitText("Switching to Fixed Cycle mode.\r\n");
	  						if(osMessageQueuePut(CommandQueueHandle, &cmd, 1U, 0U)!= osOK)
	  						{
	  							Error_Handler();
	  						}
	  					}
		  				//FCM Commands, can only run in fixed cycle mode
		  				else if(strcmp((char *)cmdStr, "event") == 0 && strcmp((char *)arg, "pp") == 0 && cmd >= 106)//Pri ped
		  				{
	  						cmd = 107;
	  						transmitText("Primary Pedestrian input received\r\n");
	  						if(osMessageQueuePut(CommandQueueHandle, &cmd, 1U, 0U)!= osOK)
	  						{
	  							Error_Handler();
	  						}
		  				}
		  				else if(strcmp((char *)cmdStr, "event") == 0 && strcmp((char *)arg, "sp") == 0 && cmd >= 106)//sec ped
		  				{
	  						cmd = 108;
	  						transmitText("Secondary Pedestrian input received\r\n");
	  						if(osMessageQueuePut(CommandQueueHandle, &cmd, 1U, 0U)!= osOK)
	  						{
	  							Error_Handler();
	  						}
		  				}
		  				else if(strcmp((char *)cmdStr, "event") == 0 && strcmp((char *)arg, "pev") == 0 && cmd >= 106)//pri erv
		  				{
	  						cmd = 109;
	  						transmitText("Primary ERV input received\r\n");
	  						if(osMessageQueuePut(CommandQueueHandle, &cmd, 1U, 0U)!= osOK)
	  						{
	  							Error_Handler();
	  						}		  				}
		  				else if(strcmp((char *)cmdStr, "event") == 0 && strcmp((char *)arg, "sev") == 0 && cmd >= 106)//sec erv
		  				{
	  						cmd = 110;
	  						transmitText("Secondary ERV input received\r\n");
	  						if(osMessageQueuePut(CommandQueueHandle, &cmd, 1U, 0U)!= osOK)
	  						{
	  							Error_Handler();
	  						}
		  				}

	  					else
	  					{
	  						cmd = 103;
	  						transmitText("Invalid command: ");
	  						transmitText((char *)get);
	  						transmitText("\r\n");
	  					}

	  				}

	  				else
	  				{
	  					cmd = 103;
	  					transmitText("Invalid command: ");
	  					transmitText((char *)get);
	  					transmitText("\r\n");
	  				}

	  				x = 0;
	  				for(int i = 0; i < 20; i++)
	  				{
	  					save[i] = '\0';
	  				}
	  				transmitText("\r\n-> ");

	  				transmitText("\x1b[s");//save cursor
	  				osDelay(10);
	  			}
	  		}
	  }
	  osThreadTerminate(NULL);
  /* USER CODE END StartCLI */
}

/* USER CODE BEGIN Header_StartStatusUpdate */
/**
* @brief Function implementing the StatusUpdate thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartStatusUpdate */
void StartStatusUpdate(void *argument)
{
  /* USER CODE BEGIN StartStatusUpdate */
  /* Infinite loop */
  for(;;)
  {
	  uint16_t msg = 111;
	  	uint16_t mode = msg;
	    /* Infinite loop */
	  		if(osMessageQueueGet(MessageQueueHandle, &msg, NULL, 0U) == osOK)
	  		{
	  			if(msg != mode)
	  			{
	  				if(msg == 104)
	  				{
	  					msg = mode;
	  				}

	  				transmitText("\x1b[s");//save cursor
	  				transmitText("\x1b[?25l");//hide cursor
	  				transmitText("\x1b[0;7H");//go to mode
	  				transmitText("                           ");
	  				transmitText("\x1b[0;7H");// go to mode
	  				if(msg == 102)
	  				{
	  					transmitText("Static Cycle mode");
	  				}
	  				else if(msg == 105){
	  					transmitText("Low Volume mode");
	  				}
	  				else if(msg >= 106 && msg < 111){
	  					transmitText("Fixed Cycle mode");
	  				}
	  				else if (msg == 101)
	  				{
	  					transmitText("Failsafe mode");
	  				}
	  				mode = msg;

	  				transmitText("\x1b[u");//return cursor
	  				transmitText("\x1b[?25h");//show cursor
	  			}

	  		}

	  		osDelay(10);
	  	}
	  	osThreadTerminate(NULL);
  /* USER CODE END StartStatusUpdate */
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
