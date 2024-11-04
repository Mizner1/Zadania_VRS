/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "i2c.h"
#include "usart.h"
#include "gpio.h"
//#include "LPS25HB.h"
#include "../LPS25HB/LPS25HB.h"
//#include "HTS221.h"
#include "../HTS221/HTS221.h"
#include "usart.h"
#include "stm32f3xx_hal.h"
#include <string.h>


void SystemClock_Config(void);

int main(void)
{


  HAL_Init();
  __HAL_RCC_GPIOB_CLK_ENABLE(); // Povolenie hodinového signálu pre GPIOB
  SystemClock_Config();

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // Output push-pull
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct); // Inicializácia GPIOB, PIN 3

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART2_UART_Init();

  //testujem ci sa program dostal az sem
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET); // Zapnutie LED
  HAL_Delay(200); // Pauza 0,2 sekundy
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET); // Vypnutie LED
  HAL_Delay(500); // Pauza 0,5 sekundy

  //inicializuje senzory, tu sa to zasekne
  LPS25HB_Init(i2c_master_read_bytes, i2c_master_write_bytes);
  HTS221_Init(i2c_master_read_bytes, i2c_master_write_bytes);

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET); // Zapnutie LED
  HAL_Delay(200); // Pauza 0,2 sekundy
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET); // Vypnutie LED
  HAL_Delay(500); // Pauza 0,5 sekundy

  // Nastavenie počiatočného tlaku
  float initial_pressure = LPS25HB_ReadPressure();
  LPS25HB_SetReferencePressure(initial_pressure);

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET); // Zapnutie LED
  HAL_Delay(200); // Pauza 0,2 sekundy
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET); // Vypnutie LED
  HAL_Delay(500); // Pauza 0,5 sekundy

  while (1)
  {
	  float current_pressure = LPS25HB_ReadPressure();
	  float altitude = LPS25HB_CalculateAltitude(current_pressure);
	  float temperature = HTS221_ReadTemperature();
	  float humidity = HTS221_ReadHumidity();

	  USART_SendString("Testovacia sprava\n");
	  // Odoslanie formátovaných dát cez USART
	  //USART_SendFormattedData(temperature, humidity, current_pressure, altitude);

	  //LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_3);  // Zapnutie LED
	  //HAL_Delay(200);                              // Pauza 0,2 sekundy
	  //LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_3); // Vypnutie LED

	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET); // Zapnutie LED
	  HAL_Delay(200); // Pauza 0,2 sekundy
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET); // Vypnutie LED

	  HAL_Delay(1000);
  }

}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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
