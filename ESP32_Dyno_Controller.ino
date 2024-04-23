#include "stingray.h"
#include "pickup.h"
#include "rpmsensor.h"
#include "ccu.h"
#include "bme280.h"
#include "config.h"
#include <PID_v1.h>

double Setpoint, Input, Output;
double Kp = 5, Ki = 0, Kd = 0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

unsigned long previousMillis1 = 0;

float targetRPM = 6000.0;
float currentRPM = 0.0;
float rpmBuffer[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static int currentServoPosition = 100;

static bool testEnable = false;

void appendToBuffer(float *buffer, float value)
{
    for (int i = 0; i < 11; i++)
    {
        buffer[i] = buffer[i + 1];
    }
    buffer[11] = value;
}

void updateServoPosition()
{
    // if RPM is less than target RPM, increase servo position to open
    if (currentRPM < targetRPM)
    {
        if (currentServoPosition < SERVO_END_POS_DEG)
        {
            currentServoPosition += 2;
        }
    }
    else
    {
        if (currentServoPosition > SERVO_START_POS_DEG)
        {
            currentServoPosition -= 2;
        }
    }
}

void moveServo()
{
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis1 >= SERVO_DELAY_MS)
        ;
    {
        setServoAngle(currentServoPosition);
        previousMillis1 = currentMillis;
    }
}

void setup()
{
    Serial.begin(SERIAL_BAUD_RATE);
    while (!Serial)
    {
        delay(10);
    }
    Serial.println("Serial started");

    initializeInductivePickup();
    initializeRPMSensor();
    initializeServo();
    // initializeBME280();
    initializeCCU();

    pinMode(PIN_CONTROL_ENABLE, INPUT_PULLUP);

    Input = currentRPM;
    Setpoint = targetRPM;

    // //turn the PID on
    // myPID.SetMode(AUTOMATIC);
    // myPID.SetSampleTime(0);
    // myPID.SetOutputLimits(SERVO_START_POS_DEG, SERVO_END_POS_DEG);
}

void loop()
{
    // push new value to buffer
    appendToBuffer(rpmBuffer, getInductivePickupRPM());

    // calculate average
    float sum = 0;
    for (int i = 0; i < 12; i++)
    {
        sum += rpmBuffer[i];
    }
    currentRPM = sum / 12;

    // if (digitalRead(PIN_CONTROL_ENABLE) == HIGH) {
    //     updateServoPosition();
    //     moveServo();
    // }

    // if (digitalRead(PIN_CONTROL_ENABLE) == HIGH) {
    //     Input = currentRPM;
    //     myPID.Compute();
    //     currentServoPosition = constrain(Output, SERVO_START_POS_DEG, SERVO_START_POS_DEG);
    //     moveServo();
    // }

    if (Serial.available())
    {
        char command = Serial.read();
        if (command == '<')
        {
            testEnable = true;
        }
    }

    // Servo sweep test
    if (testEnable)
    {
        int pos;
        for (pos = 100; pos <= 110; pos += 1)
        { // goes from 0 degrees to 180 degrees
            // in steps of 1 degree
            setServoAngle(pos); // tell servo to go to position in variable 'pos'
            delay(20);          // waits 15 ms for the servo to reach the position
        }
        delay(500);
        for (pos = 110; pos >= 100; pos -= 1)
        {                       // goes from 180 degrees to 0 degrees
            setServoAngle(pos); // tell servo to go to position in variable 'pos'
            delay(20);          // waits 15 ms for the servo to reach the position
        }
        delay(500);
    }

    Serial.print(getInductivePickupRPM());
    Serial.print(", ");
    Serial.print(getInductivePickupFrequency());
    Serial.print(", ");
    Serial.print(currentServoPosition);
    Serial.print(", ");
    Serial.print(getFlywheelRPM());
    Serial.print(", ");
    Serial.print(getFlywheelFrequency());
    Serial.println(", ");
    // Serial.print(getBME280Temperature());
    // Serial.print(", ");
    // Serial.print(getBME280Pressure());
    // Serial.print(", ");
    // Serial.println(getBME280Humidity());
}
