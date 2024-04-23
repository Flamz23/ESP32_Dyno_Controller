#include <Arduino.h>
#include "bme280.h"
#include "config.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme; // I2C

void initializeBME280() {
    Serial.println("BME280 Initializing");
    if(!bme.begin(0x77)) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!\n");
        while(1);
    }
    Serial.println("BME280 Initialized Success");
}

double getBME280Temperature() {
    return bme.readTemperature();
}

double getBME280Pressure() {
    return bme.readPressure() / 100.0F;
}

double getBME280Humidity() {
    return bme.readHumidity();
}