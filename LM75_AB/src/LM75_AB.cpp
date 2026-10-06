//=============================================================
// LM75 Temperature sensor library for MakerSpace presentation.
//
// This demo library only does the following:
//
// Initialises the LM75.
// Finalises the LM75.
// Reads the product id code.
// Reads the current temperature.
//
// The LM75 can do a lot more!
//
// Norman Dunbar.
// 16 June 2026.
//=============================================================

#include <LM75_AB.h>

// Initialises the LM75 sensor with a bus speed as required.
void LM75_begin(const int address, uint32_t clockHZ) {
    Wire.begin(address);
    Wire.setClock(clockHZ);
}


// Shuts down the Wire bus for the LM75. This is needed in
// sketches where the bus might be needed by another sensor.
// In this simple demo, it is never called.
void LM75_end() {
    Wire.end();
}


// Configures the LM75 with the register we wish to
// read from, until changed. Ends the write transaction
// when done.
void LM75_setRegister(const int address, const int reg) {
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.endTransmission(true);
}


// Returns the product ID byte for the LM75 sensor 
// attached. If not present will return 0xFF instead.
uint8_t LM75_getProductId(const int address) {
    uint8_t productID;

    // Select the product id register.
    LM75_setRegister(address, LM75_PRODUCT_ID_REG);

    // Theres only one byte.
    Wire.requestFrom(address, 1, true);

    // Fetch it.
    if (Wire.available()) 
        productID = Wire.read();

    // Reset default register to temperature.
    LM75_setRegister(address, LM75_TEMPERATURE_REG);

    // Return the product id.
    return productID;
}

// Retrieves the two bytes (11 bits) making up the current
// temperature.
float LM75_getCurrentTemperature(const int address) {
    // Storage for result
    int8_t tempData[2];
    int16_t result = 0;

    // Two bytes required.
    Wire.requestFrom(address, 2, true);

    // Fetch degrees & fractions as an 11 bit value.
    // Multiply by 0.125 to convert to degrees Celcius.
    if (Wire.available()) {
        tempData[0] = Wire.read();
        tempData[1] = Wire.read() & 0b11100000; // Bits 7--5.
        result = ((int16_t)(tempData[0])<<3) + (tempData[1] >> 5);
    }

    return result * 0.125;
}

