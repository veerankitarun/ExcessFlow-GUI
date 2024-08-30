#include <Arduino.h>
#include "Valve.h"
#include "SensataPressureSensor.h"
#include "config.h"

// Function Declaration
void readSerial();

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);

    #if MAIN_DEBUG_EN
        Serial.println("Shut Off Valve Arduino Firmware");
    #endif // MAIN_DEBUG_EN

    #if VALVE_EN
        valve_init();
    #endif // VALVE_EN

    #if SPR_EN
        sensata_init();
    #endif // VALVE_EN
} // END OF setup

void loop()
{
    // put your main code here, to run repeatedly:
    readSerial();
}

/**
 * @brief Reads data from the serial
 *
 */
void readSerial()
{
    if (Serial.available())
    {
        String cmd = Serial.readStringUntil('\n'); // Read the line terminated by '\n'

        #if MAIN_DEBUG_EN
            Serial.print("Received Line: ");
            Serial.println(cmd);
        #endif // MAIN_DEBUG
        // Connection Check
        if (cmd == "AT\r")
        {
            Serial.println("OK");
        }
        // Valve Control
        else if (cmd.substring(0, 10) == VALVE_CMD)
        {
            int valvepin = cmd.charAt(10) - '0';
            int action = cmd.charAt(12) - '0';
            #if VALVE_DEBUG_EN
                Serial.print("valvepin: "); Serial.println(valvepin);
                Serial.print("action: "); Serial.println(action);
                Serial.print("Length: "); Serial.println(cmd.length());
            #endif // VALVE_DEBUG_EN
            #if VALVE_EN
                if (cmd.length() == 14 && cmd.charAt(11) == ',')
                {
                    valve_ctrl(valvepin, action);                
                }
                else if (cmd.length() == 12)
                {
                    valve_ctrl(valvepin);
                }
                else
                {
                    Serial.println("ERROR");
                }       
            #else
                Serial.println("+VALVE_EN: 0");
                Serial.println("OK");
            #endif // VALVE_EN
        }
        // Sensata Pressure Sensor 
        else if (cmd.substring(0, 8) == SPR_GET_PRESS)
        {
            #if SPR_EN
                // AT+TSPR=1,0 for single measurement
                if (cmd.substring(8, cmd.length()) == "1,0\r")
                {
                    #if SPR_DEBUG_EN
                        Serial.println("Single measurement reading...");                       
                    #endif 
                    sensata_measure(false); 
                }
                else if (cmd.substring(8, cmd.length()) == "1,1\r")
                {
                    #if SPR_DEBUG_EN
                        Serial.println("Continuous measurement reading...");                       
                    #endif 
                    while(true)
                    {
                        sensata_measure(true);
                        if (Serial.available())
                        {
                            cmd = Serial.readStringUntil('\n');
                            if (cmd.substring(8, cmd.length()) == "0\r")
                            {
                                Serial.println("OK");
                                break;
                            }
                            else
                            {
                                Serial.println("ERROR");
                            }
                        }
                        delay(1000);
                    }
                }
                else
                {
                    Serial.println("ERROR");
                }
            #else
                Serial.println("+SPR_EN: 0");
                Serial.println("OK");
            #endif // VALVE_EN
        }
        else
        {
            Serial.println("ERROR");
        }
    }
}// END OF readserial
       
