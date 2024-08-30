/**
 ******************************************************************************
 * @file    Valve.cpp
 * @authors  Eugene Mwangi, Gladys Gachoka
 * @date    10/01/2024
 * @brief   Manages communication with DRV8833 Motor Driver
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2024 PayGo Energy, Inc.</center></h2>
 ******************************************************************************
 */

#include "Valve.h"

/**
 * @brief initialize the motor driver input pins
 */
void valve_init()
{
    // Configure the motor control pins
    pinMode(DUT_IN1_PIN, OUTPUT);
    pinMode(DUT_IN2_PIN, OUTPUT);
    pinMode(INLET_IN1_PIN, OUTPUT);
    pinMode(INLET_IN2_PIN, OUTPUT);
    pinMode(OUTLET_IN1_PIN, OUTPUT);
    pinMode(OUTLET_IN2_PIN, OUTPUT);

    digitalWrite(DUT_IN1_PIN, LOW);
    digitalWrite(DUT_IN2_PIN, LOW);
    digitalWrite(INLET_IN1_PIN, LOW);
    digitalWrite(INLET_IN2_PIN, LOW);
    digitalWrite(OUTLET_IN1_PIN, LOW);
    digitalWrite(OUTLET_IN2_PIN, LOW);

    #if VALVE_DEBUG_EN
        Serial.println("Valve Module Successfully Initialized!");
    #endif // VALVE_DEBUG_EN
}

/**
 * @brief controls the rotation of the selected valve depending on user input provided serially
 *
 * @param valvepin: valve to control
 * @param action: action to do (either OPEN or CLOSE)
 */
int dut_valve = 1;
int inlet_valve = 2;
int outlet_valve = 3;
int all_valves_close = 0;
int all_valves_open = 1;

int open_action = 1;
int close_action = 0;

void valve_ctrl(int valvepin)
{
    if (valvepin == all_valves_close)
    {
        #if VALVE_DEBUG_EN
            Serial.println("Closing all valves...");
        #endif // VALVE_DEBUG_EN
        digitalWrite(DUT_IN1_PIN, LOW);
        digitalWrite(DUT_IN2_PIN, HIGH);
        digitalWrite(INLET_IN1_PIN, LOW);
        digitalWrite(INLET_IN2_PIN, HIGH);
        digitalWrite(OUTLET_IN1_PIN, LOW);
        digitalWrite(OUTLET_IN2_PIN, HIGH);
        delay(VALVE_DELAY);
        digitalWrite(DUT_IN1_PIN, LOW);
        digitalWrite(DUT_IN2_PIN, LOW);
        digitalWrite(INLET_IN1_PIN, LOW);
        digitalWrite(INLET_IN2_PIN, LOW);
        digitalWrite(OUTLET_IN1_PIN, LOW);
        digitalWrite(OUTLET_IN2_PIN, LOW);
        Serial.println("OK");
    }
    else if (valvepin == all_valves_open)
    {
        #if VALVE_DEBUG_EN
            Serial.println("Opening all valves...");
        #endif // VALVE_DEBUG_EN
        digitalWrite(DUT_IN1_PIN, HIGH);
        digitalWrite(DUT_IN2_PIN, LOW);
        digitalWrite(INLET_IN1_PIN, HIGH);
        digitalWrite(INLET_IN2_PIN, LOW);
        digitalWrite(OUTLET_IN1_PIN, HIGH);
        digitalWrite(OUTLET_IN2_PIN, LOW);
        delay(VALVE_DELAY);
        digitalWrite(DUT_IN1_PIN, LOW);
        digitalWrite(DUT_IN2_PIN, LOW);
        digitalWrite(INLET_IN1_PIN, LOW);
        digitalWrite(INLET_IN2_PIN, LOW);
        digitalWrite(OUTLET_IN1_PIN, LOW);
        digitalWrite(OUTLET_IN2_PIN, LOW);
        Serial.println("OK");
    }
    else
    {
        Serial.println("ERROR");
    }
}

void valve_ctrl(int valvepin, int action)
{
    if (valvepin == dut_valve) //  DUT VALVE CONTROL
    {
        if (action == open_action) // OPEN DUT VALVE
        {
            #if VALVE_DEBUG_EN
                Serial.println("Opening the DUT valve...");
            #endif // VALVE_DEBUG_EN
            digitalWrite(DUT_IN1_PIN, HIGH);
            digitalWrite(DUT_IN2_PIN, LOW);
            delay(VALVE_DELAY);
            digitalWrite(DUT_IN1_PIN, LOW);
            digitalWrite(DUT_IN2_PIN, LOW);
            Serial.println("OK");
            delay(500);
        }
        else if (action == close_action) // CLOSE DUT VALVE
        {
            #if VALVE_DEBUG_EN
                Serial.println("Closing the DUT valve...");
            #endif 
            digitalWrite(DUT_IN1_PIN, LOW);
            digitalWrite(DUT_IN2_PIN, HIGH);
            delay(VALVE_DELAY);
            digitalWrite(DUT_IN1_PIN, LOW);
            digitalWrite(DUT_IN2_PIN, LOW);
            Serial.println("OK");
            delay(500);
        }
    }
    else if (valvepin == inlet_valve) //  INLET VALVE CONTROL
    {
        if (action == open_action) // OPEN INLET VALVE
        {
            #if VALVE_DEBUG_EN
                Serial.println("Opening the INLET valve...");
            #endif 
            digitalWrite(INLET_IN1_PIN, HIGH);
            digitalWrite(INLET_IN2_PIN, LOW);
            delay(VALVE_DELAY);
            digitalWrite(INLET_IN1_PIN, LOW);
            digitalWrite(INLET_IN2_PIN, LOW);
            Serial.println("OK");
            delay(500);
        }
        else if (action == close_action) // CLOSE INLET VALVE
        {
            #if VALVE_DEBUG_EN
                Serial.println("Closing the INLET valve...");
            #endif
            digitalWrite(INLET_IN1_PIN, LOW);
            digitalWrite(INLET_IN2_PIN, HIGH);
            delay(VALVE_DELAY);
            digitalWrite(INLET_IN1_PIN, LOW);
            digitalWrite(INLET_IN2_PIN, LOW);
            Serial.println("OK");
            delay(500);
        }
    }
    else if (valvepin == outlet_valve) //  OUTLET VALVE CONTROL
    {
        if (action == open_action) // OPEN OUTLET VALVE
        {
            #if VALVE_DEBUG_EN
                Serial.println("Opening the OUTLET valve...");
            #endif 
            digitalWrite(OUTLET_IN1_PIN, HIGH);
            digitalWrite(OUTLET_IN2_PIN, LOW);
            delay(VALVE_DELAY);
            digitalWrite(OUTLET_IN1_PIN, LOW);
            digitalWrite(OUTLET_IN2_PIN, LOW);
            Serial.println("OK");
            delay(500);
        }
        else if (action == close_action) // CLOSE OUTLET VALVE
        {
            #if VALVE_DEBUG_EN
                Serial.println("Closing the OUTLET valve...");
            #endif 
            digitalWrite(OUTLET_IN1_PIN, LOW);
            digitalWrite(OUTLET_IN2_PIN, HIGH);
            delay(VALVE_DELAY);
            digitalWrite(OUTLET_IN1_PIN, LOW);
            digitalWrite(OUTLET_IN2_PIN, LOW);
            Serial.println("OK");
            delay(500);
        }
    }
    else
    {
        Serial.println("ERROR");
    }

}// END OF valve_ctrl