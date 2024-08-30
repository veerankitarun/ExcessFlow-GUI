#ifndef _CONFIG_h
#define _CONFIG_h
// DUT SOV MOTOR DRIVER CONTROL PINS
#define DUT_IN1_PIN         47 // (-)
#define DUT_IN2_PIN         45 // (+)

// INLET SOV MOTOR DRIVER CONTROL PINS
#define INLET_IN1_PIN         31 // (-)
#define INLET_IN2_PIN         29 // (+)

// OUTLET SOV MOTOR DRIVER CONTROL PINS
#define OUTLET_IN1_PIN         35 // (-)
#define OUTLET_IN2_PIN         33 // (+)

// VALVE SERIAL COMMANDS
#define VALVE_CMD      "AT+TVALVE="

// DEBUG ENABLE
#define VALVE_DEBUG_EN       0
#define SPR_DEBUG_EN         0
#define MAIN_DEBUG_EN        0

// MODULE ENABLE
#define VALVE_EN        1
#define SPR_EN          1

// DELAY SETTINGS (in milliseconds)
#define VALVE_DELAY     1000

// SENSATA PRESSURE SENSOR SERIAL COMMANDS
#define SPR_GET_PRESS   "AT+TSPR="

#endif // _CONFIG_h