/*
 * HTS221.h
 *
 *  Created on: Nov 3, 2024
 *      Author: marti
 */

#ifndef HTS221_H_
#define HTS221_H_

#include <stdint.h>  // Pre uint8_t, uint16_t, atď.

// Adresy registrov
#define HTS221_ADDRESS            0x5F  // I2C adresa HTS221 (pozri datasheet pre prípadné odlišnosti)
#define HTS221_WHO_AM_I           0x0F  // Register WHO_AM_I
#define HTS221_CTRL_REG1          0x20  // Ovládací register 1
#define HTS221_TEMP_OUT_L         0x2A  // Register pre nižší bajt teploty
#define HTS221_TEMP_OUT_H         0x2B  // Register pre vyšší bajt teploty
#define HTS221_HUMIDITY_OUT_L     0x28  // Register pre nižší bajt vlhkosti
#define HTS221_HUMIDITY_OUT_H     0x29  // Register pre vyšší bajt vlhkosti
#define HTS221_WHO_AM_I_VALUE     0xBC  // Hodnota očakávaná v WHO_AM_I

// Inicializácia senzora
uint8_t HTS221_WriteRegister(uint8_t reg_address, uint8_t data);
uint8_t HTS221_Init(void (*i2c_read)(uint16_t, uint16_t, uint8_t*, uint16_t),
                    void (*i2c_write)(uint16_t, uint16_t, uint8_t*, uint16_t));
//uint8_t HTS221_Init(HAL_StatusTypeDef (*i2c_read)(uint16_t, uint16_t, uint8_t*, uint16_t),
//					HAL_StatusTypeDef (*i2c_write)(uint16_t, uint16_t, uint8_t*, uint16_t));

// Funkcie na čítanie hodnôt
float HTS221_ReadTemperature(void);
float HTS221_ReadHumidity(void);

#endif /* HTS221_H_ */
