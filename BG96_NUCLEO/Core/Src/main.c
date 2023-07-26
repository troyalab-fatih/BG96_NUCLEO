/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint8_t data_buffer[100]; // data buffer
uint8_t recvd_data; // receive buffer
uint32_t count=0; // count how many bytes are received

uint8_t komut_gonder_devam_flag = 0;

uint64_t timeout_sayac_basla = 0;
uint64_t timeout_sayac_basla_2 = 0;
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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */


  char *user_data = "AT\r\n";





  HAL_UART_Receive_IT (&huart1, &recvd_data, 1); //receive data from data buffer interrupt mode


  HAL_Delay(5000);
  HAL_UART_Transmit(&huart1, (uint8_t*)user_data, strlen(user_data),10);// Sending in normal mode
  /* USER CODE END 2 */


  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */



    user_data = "ATI\r\n";
    HAL_UART_Transmit(&huart1, (uint8_t*)user_data, strlen(user_data),10);// Sending in normal mode
    HAL_Delay(2000);

    user_data = "AT+CPIN?\r\n";
    HAL_UART_Transmit(&huart1, (uint8_t*)user_data, strlen(user_data),10);// Sending in normal mode
    HAL_Delay(2000);

    user_data = "AT+CFUN=1\r\n";
    HAL_UART_Transmit(&huart1, (uint8_t*)user_data, strlen(user_data),10);// Sending in normal mode
    HAL_Delay(2000);

    user_data = "AT+COPS?\r\n";
    HAL_UART_Transmit(&huart1, (uint8_t*)user_data, strlen(user_data),10);// Sending in normal mode
    HAL_Delay(5000);


//----------------------------- IP


    user_data = "AT+CGDCONT=1,\"IP\",\"internet\"\r\n";
    HAL_UART_Transmit(&huart1, (uint8_t*)user_data, strlen(user_data),10);// Sending in normal mode
    HAL_Delay(4000);

    user_data = "AT+CREG=1\r\n";
    HAL_UART_Transmit(&huart1, (uint8_t*)user_data, strlen(user_data),10);// Sending in normal mode
    HAL_Delay(2000);

    user_data = "AT+CREG?\r\n";
    HAL_UART_Transmit(&huart1, (uint8_t*)user_data, strlen(user_data),10);// Sending in normal mode
    HAL_Delay(2000);

    user_data = "AT+CEREG?\r\n";
    HAL_UART_Transmit(&huart1, (uint8_t*)user_data, strlen(user_data),10);// Sending in normal mode
    HAL_Delay(2000);

    user_data = "AT+CGREG?\r\n";
    HAL_UART_Transmit(&huart1, (uint8_t*)user_data, strlen(user_data),10);// Sending in normal mode
    HAL_Delay(6000);

    user_data = "AT+QIACT=1\r\n";
    HAL_UART_Transmit(&huart1, (uint8_t*)user_data, strlen(user_data),10);// Sending in normal mode
    HAL_Delay(6000);

    user_data = "AT+CGPADDR\r\n";
    HAL_UART_Transmit(&huart1, (uint8_t*)user_data, strlen(user_data),10);// Sending in normal mode
    HAL_Delay(3000);

    user_data = "AT+QPING=1,\"8.8.8.8\"\r\n";
    HAL_UART_Transmit(&huart1, (uint8_t*)user_data, strlen(user_data),10);// Sending in normal mode
    HAL_Delay(6000);



    //--------------------MQTT


    user_data = "AT+QMTOPEN=0,\"3.144.39.189\",1883\r\n";
    HAL_UART_Transmit(&huart1, (uint8_t*)user_data, strlen(user_data),10);// Sending in normal mode
    HAL_Delay(4000);

    user_data = "AT+QMTCONN=0,\"troyalab_f\",\"troyalab_f\",\"troyalab_f\"\r\n";
    HAL_UART_Transmit(&huart1, (uint8_t*)user_data, strlen(user_data),10);// Sending in normal mode
    HAL_Delay(4000);

    user_data = "AT+QMTPUB=0,0,0,0,\"v1/devices/me/telemetry\"\r\n";
    HAL_UART_Transmit(&huart1, (uint8_t*)user_data, strlen(user_data),10);// Sending in normal mode
    HAL_Delay(4000);

    user_data = "{\"fatih\":6.00,\"furkan\":34.00}\r\n";
    HAL_UART_Transmit(&huart1, (uint8_t*)user_data, strlen(user_data),10);// Sending in normal mode
    HAL_Delay(1000);

    char ctrlz = 0x1A;
    HAL_UART_Transmit(&huart1, (uint8_t *)&ctrlz, 1, 10);// Sending in normal mode
    HAL_Delay(2000);



	  //	  if(komut_gonder_devam_flag == 1)
//	  {
//		  komut_gonder_devam_flag = 0;
//
//		  HAL_UART_Transmit(&huart1, (uint8_t*)user_data, strlen(user_data),10);// Sending in normal mode
//		  //timeout_sayac_basla = 0;
//	  }
//	  else
//	  {
//		  timeout_sayac_basla = HAL_GetTick();
//		  if(timeout_sayac_basla = 25000)
//		  {
//			  HAL_UART_Transmit(&huart1, (uint8_t*)user_data, strlen(user_data),10);// Sending in normal mode
//		  }
//	  }

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

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_GREEN_Pin */
  GPIO_InitStruct.Pin = LED_GREEN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LED_GREEN_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

//	 if(recvd_data == '\n') //when enter is pressed go to this condition
//	 {
//		 data_buffer[count++]='\n';
//
//		 if(data_buffer[count-2] == '\r') //when enter is pressed go to this condition
//		 {
//			 if(data_buffer[count-3] == '\r')
//			 {
//				 // gonderilen mesaj
//			 }
//			 else // alinan mesaj
//			 {
//				 komut_gonder_devam_flag = 1;
//			 }
//			 HAL_UART_Receive_IT(&huart1, &recvd_data, 1); //start next data receive interrupt
//		 }
//		 HAL_UART_Receive_IT(&huart1, &recvd_data, 1); //start next data receive interrupt
//
//		 //HAL_UART_Transmit(&huart1,data_buffer,count,HAL_MAX_DELAY); //transmit the full sentence again
//		 //memset(data_buffer, 0, count); // enpty the data buffer
//	 }
//	 else
//	 {
//		 data_buffer[count++] = recvd_data; // every time when interrput is happen, received 1 byte of data
//		 //return TROYALAB_ERROR;
//	 }
//
//	 HAL_UART_Receive_IT(&huart1, &recvd_data, 1); //start next data receive interrupt
//

}




/* USER CODE END 4 */

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
