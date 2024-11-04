/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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
#include "gpio.h"

void MX_GPIO_Init(void)
{
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE(); // Povolenie hodinového signálu pre GPIO port B
}

//toto bolo v MX_GPIO_Init
//ak to nefunguje pouzi toto
//LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
//LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);

//GPIO_InitTypeDef GPIO_InitStruct = {0};
//GPIO_InitStruct.Pin = GPIO_PIN_3;
//GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // Output push-pull
//GPIO_InitStruct.Pull = GPIO_NOPULL;
//GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//HAL_GPIO_Init(GPIOB, &GPIO_InitStruct); // Inicializácia GPIOB, PIN 3


//LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_3, LL_GPIO_MODE_OUTPUT);

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
