#ifndef rpmsensor_h
#define rpmsensor_h

// initialize RPM sensor
void initializeRPMSensor();

// Update period, frequency and RPM variables in the interrupt
void fallInterrupt();

// get flywheel RPM
float getFlywheelRPM();

// get flywheel frequency
float getFlywheelFrequency();

#endif