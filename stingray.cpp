#include <Arduino.h>
#include <Servo.h>
#include "stingray.h"
#include "config.h"

Servo servo;

void initializeServo() {
    // Set servo pin as output
    pinMode(PIN_SERVO, OUTPUT);

    // Attach servo to pin
    servo.attach(PIN_SERVO);

    // Set initial position
    servo.write(SERVO_START_POS_DEG);
}

void setServoAngle(int servoAngle) {
    // Set servo position
    servo.write(constrain(servoAngle, SERVO_START_POS_DEG, SERVO_END_POS_DEG));
}