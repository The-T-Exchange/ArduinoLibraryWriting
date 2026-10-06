//===============================================================
// LM75_AB Temperature sensor library example. Written as part of
// a presentation to the Findhorn T-Exchange Makerspace. 
//
// Uses the LM75_AB library, developed for the presentation, to
// access the LM75 sensor.

// Simply dispays the current temperature. Assumes that the LM75
// is at address 0x4F but this can be easily changed.
//
// Temperatutre is written to Serial every 5 seconds.
//
// Norman Dunbar.
// 16 June 2026.
//===============================================================

#include <LM75_AB.h>

// Where is my sensor?
const int LM75_ADDRESS = 0x4F;

// Bus speed in Hz.
const uint32_t LM75_CLOCK_HZ = 100000;    // 100 KHz.


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
    delay(5000);
}
