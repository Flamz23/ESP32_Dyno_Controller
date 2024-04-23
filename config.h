#ifndef config_h
#define config_h

// Pin definitions
#define PIN_SERVO 9
#define PIN_IND_PICKUP_SENSOR 2 // dont change
#define PIN_CONTROL_ENABLE 6
#define PIN_RPM_SENSOR 3 // dont change
#define PIN_CCU 5

// Servo definitions
#define SERVO_START_POS_DEG 102 // closed throttle position
#define SERVO_END_POS_DEG 120 // open throttle position
#define SERVO_DELAY_MS 20

// Inductive pickup definitions
#define ENGINE_IDLE_RPM 5000
#define ENGINE_MAX_RPM 20000
#define ENGINE_MAX_RPM 0

// Serial communication definitions
#define SERIAL_BAUD_RATE 115200

// RPM sensor definitions
#define TRIGGER_WHEEL_DIV 8.0

#endif