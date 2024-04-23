#ifndef bme280_h
#define bme280_h

// initialize BME280 sensor
void initializeBME280();

// get temperature from BME280 sensor
double getBME280Temperature();

// get pressure from BME280 sensor
double getBME280Pressure();

// get humidity from BME280 sensor
double getBME280Humidity();

#endif
