#include <Arduino.h>
#include "ccu.h"
#include "config.h"

void initializeCCU() {
    // Set CCU pin as output
    pinMode(PIN_CCU, OUTPUT);
}

void setCCUDemand(int demand) {
    analogWrite(PIN_CCU, demand);
}