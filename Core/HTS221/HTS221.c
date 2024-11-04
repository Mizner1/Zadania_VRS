/*
 * HTS221.c
 *
 *  Created on: Nov 3, 2024
 *      Author: marti
 */

#include "HTS221.h"
#include <stdint.h>
#include "i2c.h"

// Ukazovatele na callback funkcie
static void (*i2c_read)(uint8_t, uint8_t, uint8_t*, uint16_t) = 0;
static void (*i2c_write)(uint8_t, uint8_t, uint8_t*, uint16_t) = 0;

// Pridajme na začiatok deklaráciu funkcie na zapisovanie do registra
uint8_t HTS221_WriteRegister(uint8_t reg_address, uint8_t data)
{
    i2c_write(HTS221_ADDRESS, reg_address, &data, 1);
}

uint8_t HTS221_Init(void (*read_callback)(uint8_t, uint8_t, uint8_t*, uint16_t),
                    void (*write_callback)(uint8_t, uint8_t, uint8_t*, uint16_t)) {
    // Uloženie callback funkcií
    i2c_read = read_callback;
    i2c_write = write_callback;

    uint8_t who_am_i = 0;
    i2c_read(HTS221_ADDRESS, HTS221_WHO_AM_I, &who_am_i, 1);

    // Skontrolovať, či WHO_AM_I vracia očakávanú hodnotu
    if (who_am_i != HTS221_WHO_AM_I_VALUE) {
        return 0; // chyba pri inicializácii
    }

    // Nastaviť senzor: zapnúť, nastaviť frekvenciu (podľa dokumentácie)
    uint8_t ctrl_reg1 = 0x81;  // Power on, 1 Hz update rate (podľa potreby)
    i2c_write(HTS221_ADDRESS, HTS221_CTRL_REG1, &ctrl_reg1, 1);

    return 1; // inicializácia úspešná
}

float HTS221_ReadTemperature(void) {
    uint8_t temp_out_l, temp_out_h;
    int16_t temp_out;

    // Čítanie teplotných registrov
    i2c_read(HTS221_ADDRESS, HTS221_TEMP_OUT_L, &temp_out_l, 1);
    i2c_read(HTS221_ADDRESS, HTS221_TEMP_OUT_H, &temp_out_h, 1);

    // Kombinácia bajtov do 16-bitovej hodnoty
    temp_out = (int16_t)(temp_out_h << 8 | temp_out_l);

    // Konverzia na °C (podľa kalibračných hodnôt v datasheete)
    float temperature = (float)temp_out / 480.0 + 42.5; // Príklad, uprav podľa dokumentácie
    return temperature;
}

float HTS221_ReadHumidity(void) {
    uint8_t hum_out_l, hum_out_h;
    int16_t hum_out;

    // Čítanie vlhkostných registrov
    i2c_read(HTS221_ADDRESS, HTS221_HUMIDITY_OUT_L, &hum_out_l, 1);
    i2c_read(HTS221_ADDRESS, HTS221_HUMIDITY_OUT_H, &hum_out_h, 1);

    // Kombinácia bajtov do 16-bitovej hodnoty
    hum_out = (int16_t)(hum_out_h << 8 | hum_out_l);

    // Konverzia na % RH (podľa kalibračných hodnôt v datasheete)
    float humidity = (float)hum_out / 65536.0 * 100.0; // Príklad, uprav podľa dokumentácie
    return humidity;
}
