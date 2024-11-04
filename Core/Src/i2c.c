// 4.11.2024 9:52

#include "i2c.h"

I2C_HandleTypeDef hi2c1;

// I2C1 init function
void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x2000090E;
  hi2c1.Init.OwnAddress1 = 2;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  // Configure Analogue filter
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  // Configure Digital filter
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(i2cHandle->Instance==I2C1)
  {

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // I2C1 clock enable
    __HAL_RCC_I2C1_CLK_ENABLE();

    // I2C1 interrupt Init
    HAL_NVIC_SetPriority(I2C1_EV_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
  }
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle)
{

  if(i2cHandle->Instance==I2C1)
  {

    // Peripheral clock disable
    __HAL_RCC_I2C1_CLK_DISABLE();

    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_7);

    // I2C1 interrupt Deinit
    HAL_NVIC_DisableIRQ(I2C1_EV_IRQn);
  }
}

extern I2C_HandleTypeDef hi2c1;

HAL_StatusTypeDef i2c_master_read_bytes(uint16_t DevAddress, uint16_t RegAddress, uint8_t* pData, uint16_t Size) {
    // Single alebo multi-byte čítanie na základe hodnoty Size
    if (Size > 1) {
        // Multi-byte čítanie (napr. pre viacero registrov alebo 16-bitové dáta)
        return HAL_I2C_Mem_Read(&hi2c1, DevAddress, RegAddress, I2C_MEMADD_SIZE_8BIT, pData, Size, HAL_MAX_DELAY);
    } else {
        // Single-byte čítanie
        return HAL_I2C_Mem_Read(&hi2c1, DevAddress, RegAddress, I2C_MEMADD_SIZE_8BIT, pData, 1, HAL_MAX_DELAY);
    }
}

HAL_StatusTypeDef i2c_master_write_bytes(uint16_t DevAddress, uint16_t RegAddress, uint8_t* pData, uint16_t Size) {
    // Single alebo multi-byte zápis na základe hodnoty Size
    if (Size > 1) {
        // Multi-byte zápis
        return HAL_I2C_Mem_Write(&hi2c1, DevAddress, RegAddress, I2C_MEMADD_SIZE_8BIT, pData, Size, HAL_MAX_DELAY);
    } else {
        // Single-byte zápis
        return HAL_I2C_Mem_Write(&hi2c1, DevAddress, RegAddress, I2C_MEMADD_SIZE_8BIT, pData, 1, HAL_MAX_DELAY);
    }
}


