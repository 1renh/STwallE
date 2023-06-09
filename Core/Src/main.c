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
#include <stdbool.h>
#include "led12a1.h"
#include <stdbool.h>
#include "led1202.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define MAX_CH_CURRENT ((uint8_t)20)
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
extern LED1202_Object_TypeDef LED1202Obj;
uint8_t DevAddrArray[10];
uint8_t NumOfDev = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void MX_I2C1_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

// sets rgb value of LED on position x y (0 ,0 is top right)
void setrgb(int x, int y, int r, int g, int b) {
	if (r >= 0) {
		LED12A1_ChannelEnable(&LED1202Obj,
				(TypeDefChannel) (LED_CHANNEL_0 << (3 * x)),
				(TypedefEnumDevAddr) (LED_DEVICE1 + y));
		LED12A1_AnalogDimming(&LED1202Obj, r, 3 * x,
				(TypedefEnumDevAddr) (LED_DEVICE1 + y));
	}
	if (g >= 0) {
		LED12A1_ChannelEnable(&LED1202Obj,
				(TypeDefChannel) (LED_CHANNEL_0 << (3 * x + 1)),
				(TypedefEnumDevAddr) (LED_DEVICE1 + y));
		LED12A1_AnalogDimming(&LED1202Obj, g, 3 * x + 1,
				(TypedefEnumDevAddr) (LED_DEVICE1 + y));
	}
	if (b >= 0) {
		LED12A1_ChannelEnable(&LED1202Obj,
				(TypeDefChannel) (LED_CHANNEL_0 << (3 * x + 2)),
				(TypedefEnumDevAddr) (LED_DEVICE1 + y));
		LED12A1_AnalogDimming(&LED1202Obj, b, 3 * x + 2,
				(TypedefEnumDevAddr) (LED_DEVICE1 + y));
	}
}

// continuously converts rgb values in 63 bit value
void smoothrgb(int x, int y, int rgb) {
	int div = rgb / 63;
	if (div % 2 == 0) {
		rgb = rgb % 62;
	} else {
		rgb = 62 - (rgb % 62);
	}

	if (rgb <= 20) {
		setrgb(x, y, rgb, 20 - rgb, 0);
	} else if (rgb <= 40) {
		rgb -= 20;
		setrgb(x, y, 20 - rgb, 0, rgb);
	} else {
		rgb -= 40;
		setrgb(x, y, 0, rgb, 20 - rgb);
	}
}

// sets every LED to a specific rgb value
void setrgb_all(int r, int g, int b) {
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			if (r > 0) {
				LED12A1_ChannelEnable(&LED1202Obj,
						(TypeDefChannel) (LED_CHANNEL_0 << (3 * x)),
						(TypedefEnumDevAddr) (LED_DEVICE1 + y));
				LED12A1_AnalogDimming(&LED1202Obj, r, 3 * x,
						(TypedefEnumDevAddr) (LED_DEVICE1 + y));
			}
			if (g > 0) {
				LED12A1_ChannelEnable(&LED1202Obj,
						(TypeDefChannel) (LED_CHANNEL_0 << (3 * x + 1)),
						(TypedefEnumDevAddr) (LED_DEVICE1 + y));
				LED12A1_AnalogDimming(&LED1202Obj, g, 3 * x + 1,
						(TypedefEnumDevAddr) (LED_DEVICE1 + y));
			}
			if (b > 0) {
				LED12A1_ChannelEnable(&LED1202Obj,
						(TypeDefChannel) (LED_CHANNEL_0 << (3 * x + 2)),
						(TypedefEnumDevAddr) (LED_DEVICE1 + y));
				LED12A1_AnalogDimming(&LED1202Obj, b, 3 * x + 2,
						(TypedefEnumDevAddr) (LED_DEVICE1 + y));
			}
		}
	}
}

// sets every LED in a row to a specific rgb value
void setrgb_line(int y, int rgb, int x0, int x1, int x2, int x3) {
	if (y < 0 || y > 3) {
		return;
	}

	if (x3) {
		smoothrgb(0, y, rgb);
	}
	if (x2) {
		smoothrgb(1, y, rgb);
	}
	if (x1) {
		smoothrgb(2, y, rgb);
	}
	if (x0) {
		smoothrgb(3, y, rgb);
	}
}

// task 1: smooth transition
void transition() {
	for (int i = 0; i <= 20; i++) {
		setrgb_all(i, 20 - i, 0);
		HAL_Delay(45);
	}
	for (int i = 0; i <= 20; i++) {
		setrgb_all(20 - i, 0, i);
		HAL_Delay(45);
	}
	for (int i = 0; i <= 20; i++) {
		setrgb_all(0, i, 20 - i);
		HAL_Delay(45);
	}
}

// display bsh on LEDs while using smooth light transition
void bsh() {
	int j = 0;
	for (int i = 0; i < 19; i++) {
		// prints 'b'
		for (int k = 0; k <= 31; k += 2) {
			if (i > 8) {
				j -= 31;
				break;
			}
			setrgb_line(-4 + i, j + k, 		1, 0, 0, 0);
			setrgb_line(-3 + i, j + k + 5, 1, 1, 1, 1);
			setrgb_line(-2 + i, j + k + 10, 1, 0, 0, 1);
			setrgb_line(-1 + i, j + k + 15, 1, 1, 1, 1);
			HAL_Delay(5);
		}
		j += 31;

		// prints 's'
		for (int k = 0; k <= 31; k += 2) {
			if (i > 14 || i < 5) {
				j -= 31;
				break;
			}
			setrgb_line(-10 + i, j + k, 	1, 1, 1, 1);
			setrgb_line(-9 + i, j + k + 5,  1, 0, 0, 0);
			setrgb_line(-8 + i, j + k + 10, 1, 1, 1, 1);
			setrgb_line(-7 + i, j + k + 15, 0, 0, 0, 1);
			setrgb_line(-6 + i, j + k + 20, 1, 1, 1, 1);
			HAL_Delay(5);
		}
		j += 31;

		// prints 'h'
		for (int k = 0; k <= 31; k += 2) {
			if (i < 11) {
				j -= 31;
				break;
			}
			setrgb_line(-15 + i, j + k, 	 1, 0, 0, 0);
			setrgb_line(-14 + i, j + k + 5, 1, 1, 1, 1);
			setrgb_line(-13 + i, j + k + 10, 1, 0, 0, 1);
			setrgb_line(-12 + i, j + k + 15, 1, 0, 0, 1);
			HAL_Delay(5);
		}
		j += 31;

		LED12A1_ChannelDisable(&LED1202Obj, LED_CHANNEL_ALL,
				(TypedefEnumDevAddr) (LED_DEVICE_ALL));
	}
}

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
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
	MX_I2C1_Init();
	MX_TIM2_Init();
	MX_TIM3_Init();
	MX_USART2_UART_Init();
	/* USER CODE BEGIN 2 */

//  MX_I2C1_Init();
	/* USER CODE BEGIN 2 */
	HAL_Delay(100);
	LED12A1_Init();

	NumOfDev = LED12A1_ScanAvailDevice(&LED1202Obj, DevAddrArray);
	for (uint8_t dev = 0; dev < NumOfDev; dev++) {
		LED12A1_DeviceEnable(&LED1202Obj,
				(TypedefEnumDevAddr) (LED_DEVICE1 + dev));
		LED12A1_ChannelDisable(&LED1202Obj, LED_CHANNEL_ALL,
				(TypedefEnumDevAddr) (LED_DEVICE1 + dev));
	}

//  /* USER CODE END 2 */
//  /* Infinite loop */
//  /* USER CODE BEGIN WHILE */
	while (1) {
		transition();
		// bsh();
	}
	/* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

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
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief I2C1 Initialization Function
 * @param None
 * @retval None
 */
void MX_I2C1_Init(void) {

	/* USER CODE BEGIN I2C1_Init 0 */

	/* USER CODE END I2C1_Init 0 */

	/* USER CODE BEGIN I2C1_Init 1 */

	/* USER CODE END I2C1_Init 1 */
	hi2c1.Instance = I2C1;
	hi2c1.Init.Timing = 0x00303D5B;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
		Error_Handler();
	}

	/** Configure Analogue filter
	 */
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE)
			!= HAL_OK) {
		Error_Handler();
	}

	/** Configure Digital filter
	 */
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN I2C1_Init 2 */

	/* USER CODE END I2C1_Init 2 */

}

/**
 * @brief TIM2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM2_Init(void) {

	/* USER CODE BEGIN TIM2_Init 0 */

	/* USER CODE END TIM2_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	/* USER CODE BEGIN TIM2_Init 1 */

	/* USER CODE END TIM2_Init 1 */
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 0;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 4294967295;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK) {
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM2_Init 2 */

	/* USER CODE END TIM2_Init 2 */

}

/**
 * @brief TIM3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM3_Init(void) {

	/* USER CODE BEGIN TIM3_Init 0 */

	/* USER CODE END TIM3_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	/* USER CODE BEGIN TIM3_Init 1 */

	/* USER CODE END TIM3_Init 1 */
	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 0;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 65535;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim3) != HAL_OK) {
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM3_Init 2 */

	/* USER CODE END TIM3_Init 2 */

}

/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART2_UART_Init(void) {

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
	huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart2) != HAL_OK) {
		Error_Handler();
	}
	if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART2_Init 2 */

	/* USER CODE END USART2_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
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

	/*Configure GPIO pin : LED1202_IRQ_Pin */
	GPIO_InitStruct.Pin = LED1202_IRQ_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(LED1202_IRQ_GPIO_Port, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
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
