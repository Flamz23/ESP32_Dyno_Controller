#ifndef pickup_h
#define pickup_h

// initialize inductive pickup sensor
void initializeInductivePickup();

// Update period, frequency and RPM variables in the interrupt
void fallInterruptB();

// get inductive pickup sensor RPM
float getInductivePickupRPM();

// get inductive pickup sensor frequency
float getInductivePickupFrequency();

#endif