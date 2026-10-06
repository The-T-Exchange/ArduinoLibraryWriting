#ifndef LM75_AB_H
#define LM75_AB_H

#include <Wire.h>

// LM75 Registers.
const uint8_t LM75_TEMPERATURE_REG  = 0;
const uint8_t LM75_CONFIG_REG       = 1;
const uint8_t LM75_T_HYST_REG       = 2;
const uint8_t LM75_T_OS_REG         = 3;
const uint8_t LM75_PRODUCT_ID_REG   = 7;


// LM75 Configuration bits.

// Fault counts. How many faults before OS output pin is active?
const uint8_t LM75_FAULTS_1		= 0 << 3;
const uint8_t LM75_FAULTS_2		= 1 << 3;
const uint8_t LM75_FAULTS_4		= 2 << 3;
const uint8_t LM75_FAULTS_6		= 3 << 3;

// OS pin polarity. Active high or low?
const uint8_t LM75_OS_POLARITY_LOW	= 0 << 2;
const uint8_t LM75_OS_POLARITY_HIGH	= 1 << 2;

// Comparator or interrupt mode for OS?
const uint8_t LM75_COMPARATOR_MODE	= 0 << 1;
const uint8_t LM75_INTERRUPT_MODE 	= 1 << 1;

// Shutdown settings.
const uint8_t LM75_LOW_POWER_ENABLE	 = 1 << 0;
const uint8_t LM75_LOW_POWER_DISABLE = 0 << 0;


// Function prototypes.
void LM75_begin(const int address, uint32_t clockHZ);
void LM75_end();
void LM75_setRegister(const int address, const int reg);
uint8_t LM75_getProductId(const int address);
float LM75_getCurrentTemperature(const int address);

// Product ID is unknown.
const uint8_t LM75_UNKNOWN_ID = 255;


#endif // LM75_AB_H
