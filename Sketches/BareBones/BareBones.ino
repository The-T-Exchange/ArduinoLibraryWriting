//===============================================================
// LM75 Temperature sensor demo for MakerSpace presentation.
//
// Shows how much messing about with I2C/TWI there is in order
// to read the temperature and product id from an LM75A/B sensor.
//
// The LM75A/B can do a lot more than shown here, for the sake of
// brevity, I'm not getting in too deep!
//
//
// Norman Dunbar.
// 16 June 2026.
//===============================================================

#include <Wire.h>


// Function prototypes.
void LM75_begin(const int address, uint32_t clockHZ);
void LM75_end();
void LM75_setRegister(const int address, const int reg);
uint8_t LM75_getProductId(const int address);
float LM75_getCurrentTemperature(const int address);


// Where is my sensor?
const int LM75_ADDRESS = 0x4F;

// Bus speed in Hz.
const uint32_t LM75_CLOCK_HZ = 100000;    // 100 KHz.

// LM75 registers.
const int LM75_TEMPERATURE_REG = 0;
const int LM75_PRODUCT_ID_REG = 7;

// Product ID is unknown.
const uint8_t LM75_UNKNOWN_ID = 255;


//===============================================================
//                                                          SETUP
//===============================================================
void setup() {
    uint8_t productID;

    // Start up I2C as a controller. Talking to the sensor
    // at 100 KHz.
    LM75_begin(LM75_ADDRESS, LM75_CLOCK_HZ);

    // Need the Serial Monitor for output.
    Serial.begin(9600);
    Serial.println("LM75 Temperature Sensor");
    Serial.print("LM75 Product ID: ");

    productID = LM75_getProductId(LM75_ADDRESS);
    if (productID == LM75_UNKNOWN_ID)
        Serial.println("Unknown");
    else
        Serial.println(productID);
}


//===============================================================
//                                                           LOOP
//===============================================================
void loop() {

    // Read the temperature.
    float result = LM75_getCurrentTemperature(LM75_ADDRESS);

    // Print it out with much messing with Serial!
    Serial.print("Temperature: ");
    Serial.print(result);
    Serial.println(" degrees C.");

    // Delay is usually a bad thing, but here we are not doing
    // anything else, 
    delay(1500);
}


// Initailises the LM75 sensor with a bus speed as required.
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
        tempData[1] = Wire.read() & 0b11100000; // Bits 7--5 only.
        result = ((int16_t)(tempData[0])<<3) + (tempData[1] >> 5);
    }

    return result * 0.125;
}


