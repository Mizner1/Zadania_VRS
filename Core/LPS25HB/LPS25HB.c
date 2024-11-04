/*
 * LPS25HB.c
 *
 *  Created on: Nov 3, 2024
 *      Author: marti
 */
#include "LPS25HB.h"
#include <stdint.h>
#include "i2c.h"

#define AIR_DENSITY 1.225  // Hustota vzduchu v kg/m³ pri hladine mora
#define GRAVITY 9.81       // Gravitacné zrýchlenie v m/s²
static float reference_pressure = 0.0;

/* Statické ukazatele na I2C funkcie */
static void (*i2c_read)(uint8_t, uint8_t, uint8_t*, uint16_t);
static void (*i2c_write)(uint8_t, uint8_t, uint8_t*, uint16_t);

// Pridajme na začiatok deklaráciu funkcie na zapisovanie do registra
uint8_t LPS25HB_WriteRegister(uint8_t reg_address, uint8_t data)
{
    i2c_write(LPS25HB_ADDRESS, reg_address, &data, 1);
}

/* Inicializačná funkcia */
uint8_t LPS25HB_Init(void (*read_callback)(uint8_t, uint8_t, uint8_t*, uint16_t),
                     void (*write_callback)(uint8_t, uint8_t, uint8_t*, uint16_t))
{
    uint8_t who_am_i = 0;

    // Priradíme ukazatele na I2C callbacky
    i2c_read = read_callback;
    i2c_write = write_callback;

    // Overenie WHO_AM_I
    i2c_read(0x5C, LPS25HB_WHO_AM_I_REG, &who_am_i, 1);
    if (who_am_i != LPS25HB_WHO_AM_I_VALUE) {
        return 1;  // chyba, nesprávna hodnota
    }

    // Konfigurácia CTRL_REG1: nastavíme senzor na aktívny režim a obnovovaciu frekvenciu
    uint8_t config = 0x90; // napr. zapnutie, 12.5 Hz
    i2c_write(0x5C, LPS25HB_CTRL_REG1, &config, 1);

    return 0;  // senzor je pripravený
}

float LPS25HB_ReadPressure(void)
{
    uint8_t press_out[3];
    int32_t pressure_raw;

    // Vyčítanie troch bajtov tlaku
    i2c_read(0x5C, LPS25HB_PRESS_OUT_XL, press_out, 3);

    // Spojenie troch bajtov do jedného 24-bitového čísla
    pressure_raw = ((int32_t)press_out[2] << 16) | ((int32_t)press_out[1] << 8) | press_out[0];

    // Prevod na hPa podľa dokumentácie
    return pressure_raw / 4096.0f;
}

// Inicializuje počiatočný tlak, ktorý sa použije ako referenčný bod
void LPS25HB_SetReferencePressure(float initial_pressure) {
    reference_pressure = initial_pressure;
}

// Funkcia na výpočet relatívnej výšky na základe aktuálneho tlaku
float LPS25HB_CalculateAltitude(float current_pressure) {
    if (reference_pressure == 0.0) {
        // Zabránime výpočtu, ak ešte nebola inicializovaná počiatočná hodnota tlaku
        return 0.0;
    }
    return (reference_pressure - current_pressure) / (AIR_DENSITY * GRAVITY);
}

