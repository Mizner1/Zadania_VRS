/*
 * LPS25HB.h
 *
 *  Created on: Nov 3, 2024
 *      Author: marti
 */

#ifndef LPS25HB_H_
#define LPS25HB_H_

#include <stdint.h>  // Pre uint8_t, uint16_t, atď.

/* Adresy registrov */
#define LPS25HB_ADDRESS			   0x5C
#define LPS25HB_WHO_AM_I_REG       0x0F
#define LPS25HB_CTRL_REG1          0x20
#define LPS25HB_PRESS_OUT_XL       0x28
#define LPS25HB_PRESS_OUT_L        0x29
#define LPS25HB_PRESS_OUT_H        0x2A
#define LPS25HB_TEMP_OUT_L         0x2B
#define LPS25HB_TEMP_OUT_H         0x2C

/* Hodnoty registrov */
#define LPS25HB_WHO_AM_I_VALUE     0xBD

/* Deklarácie funkcií */
uint8_t LPS25HB_WriteRegister(uint8_t reg_address, uint8_t data);
uint8_t LPS25HB_Init(void (*i2c_read)(uint8_t, uint8_t, uint8_t*, uint16_t),
                     void (*i2c_write)(uint8_t, uint8_t, uint8_t*, uint16_t));
float LPS25HB_ReadPressure(void);
void LPS25HB_SetReferencePressure(float initial_pressure);
float LPS25HB_CalculateAltitude(float current_pressure);
//float LPS25HB_ReadTemperature(void);

#endif /* LPS25HB_H_ */
