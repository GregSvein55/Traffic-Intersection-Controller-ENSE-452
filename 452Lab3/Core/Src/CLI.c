
#include "CLI.h"

bool isCompleteLine(char rx[10])
{

	if(rx[0] == '\r')
	{
		return true;
	}
	else
	{
		return false;
	}
}

void copyCharTo(char rx[10], char input[20], int coun)
{

		  if(rx[0] == '\b')
		  {
			  printString("\b \b");

		  }
		  else
		  {
			  input[coun] = rx[0];
			  printString(rx);

		  }
}

void executeCommand(char input[20])
{


		  strcpy((char *)cliBufferTX, "\nEnter a command for the LED:\r\n");
		  HAL_UART_Transmit(&huart3, cliBufferTX, strlen((char *)cliBufferTX), 1000);


		  if(input[0] == 'h' && input[1] == 'e' && input[2] == 'l' && input[3] == 'p' && input[4] == '\r')
		  {
			  printString("\n1. \"on\" turns the green LED on\r\n");
			  printString("\n2. \"off\" turns the green LED off\r\n");
			  printString("\n3. \"query\" returns the state of the green LED\r\n");

		  }
		  else if(input[0] == 'o' && input[1] == 'n' && input[2] == '\r')
		  {
			  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == 1)
			  {
				  printString("\nThe LED is already on!\r\n");
			  }
			  else
			  {
				  printString("\nDone!\r\n");
			  }

			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);


		  }
		  else if(input[0] == 'o' && input[1] == 'f' && input[2] == 'f' && input[3] == '\r')
		  {
			  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == 1)
			  {
				  printString("\nDone!\r\n");
			  }
			  else
			  {
				  printString("\nThe LED is already off!\r\n");
			  }

			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
		  }
		  else if(input[0] == 'q' && input[1] == 'u' && input[2] == 'e' && input[3] == 'r' && input[4] == 'y' && input[5] == '\r')
		  {
			  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == 1)
			  {
				  printString("\nThe LED is on!\r\n");
			  }
			  else
			  {
				  printString("\nThe LED is off!\r\n");
			  }

		  }
		  else if(input[0] != '\r')
		  {
			  strcpy((char *)cliBufferTX, "\nError. Try again.\r\n");
			  HAL_UART_Transmit(&huart3, cliBufferTX, strlen((char *)cliBufferTX), 1000);
		  }

}



void printString(const char* mess)
{
	int i = 0;
	HAL_StatusTypeDef  st;

	while(huart3.gState == HAL_UART_STATE_BUSY_TX){}

	for(const char* p = mess; *p; ++p)
	{
		cliBufferTX[i] = *p;
		i++;
	}

	st = HAL_UART_Transmit(&huart3, cliBufferTX, i, 1000);
	if(st != HAL_OK)
	{
		Error_Handler();
	}

}





