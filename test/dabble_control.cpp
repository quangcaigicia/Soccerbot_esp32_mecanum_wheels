//** This code power the esp32 that uses 2 driver to controll 4 wheel independently
//** Dabble compatable
//** To calculate the speed for your motor min_V = max_V * speed / 255 <<-- you can change this value by changing the resolution in motor.cpp
//**

#include <Arduino.h>
// #include <PS4Controller.h>

// DabbleESP32
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

// Custom headers
#include "motor.h"


int speed{0};
int joystick_mode{};


/* Define the variables for the joystick values
   x, y are left joystick and rx, ry are for right joystick*/
float x{0}, y{0}, rx{0};

Motor motor1(19, 18, 5, 1);  // Direction pin and pwm channel for motor A
Motor motor2(26, 27, 14, 2);  // Direction pin and pwm channel for motor B
Motor motor3(22, 21, 23, 3); // Direction pin and pwm channel for motor C
Motor motor4(25, 33, 32, 4); // Direction pin and pwm channel for motor C

// set up dabble bluetooth
void connectDabble()
{
    Dabble.begin("Mẹc Xe Đẹc");
    Serial.println("Ready Dabble.\n");
}

void setup()
{
    connectDabble();
}

void loop()
{
    //------------------------------ Using Dabble ----------------------------------------//
    Dabble.processInput(); // this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
    if (Dabble.isAppConnected())
    {
        {
            if (GamePad.isCirclePressed())
            {
                rx = 255;
            }
            else if (GamePad.isSquarePressed())
            {
                rx = -255;    
            }
            else {
                rx = 0;
            }

            x = GamePad.getXaxisData();
            y = GamePad.getYaxisData();
            motor1.set_motor_omnidirectional(x, y, rx, -6, 6, 130, 255, 1);
            motor2.set_motor_omnidirectional(x, y, rx, -6, 6, 130, 255, 2);
            motor3.set_motor_omnidirectional(x, y, rx, -6, 6, 130, 255, 3);
            motor4.set_motor_omnidirectional(x, y, rx, -6, 6, 130, 255, 4);
        }
    }
} 
