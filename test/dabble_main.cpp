//** This code power the esp32 that uses 2 driver to controll 4 wheel independently
//** PS4 and Dabble compatable
//** To calculate the speed for your motor min_V = max_V * speed / 255 <<-- you can change this value by changing the resolution in motor.cpp
//**

#include <Arduino.h>

// DabbleESP32
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

// Custom headers
#include "motor.h"

int16_t speed{0};
int8_t joystick_mode{0};

/* Define the variables for the joystick values
   x, y are left joystick and rx, ry are for right joystick*/
float x{0}, y{0}, rx{0};

Motor motor1(17, 5, 16, 1);  // Direction pin and pwm channel for motor A
Motor motor2(27, 26, 14, 2);  // Direction pin and pwm channel for motor B
Motor motor3(19, 18, 21, 3); // Direction pin and pwm channel for motor C
Motor motor4(23, 22, 25, 4); // Direction pin and pwm channel for motor C

// PS4 check connection
void onConnect()
{
    Serial.println("Connected!");
}
void onDisConnect()
{
    Serial.println("Disconnected!");
}
// set up ps4 bluetooth mac
// void connectPS4Controller()
// {
//     // change mac address to ps4's mac
//     PS4.attachOnConnect(onConnect);
//     PS4.attachOnDisconnect(onDisConnect);
//     PS4.begin("E0:2B:E9:54:91:87");
//     Serial.println("Ready PS4.\n");
// }
// set up dabble bluetooth
void connectDabble()
{
    Dabble.begin("Mẹc Xe Đẹc");
    Serial.println("Ready Dabble.\n");
}

void setup()
{
    Serial.begin(115200);
    connectDabble();
}

//------------------------------ Motor Functions ----------------------------------------//
void moveForward(int speed)
{
    motor1.forward(speed);
    motor2.forward(speed);
    motor3.forward(speed);
    motor4.forward(speed);
}

void moveBackward(int speed)
{
    motor1.backward(speed);
    motor2.backward(speed);
    motor3.backward(speed);
    motor4.backward(speed);
}

void moveSidewaysRight(int speed)
{
    motor1.forward(speed);
    motor2.backward(speed);
    motor3.backward(speed);
    motor4.forward(speed);
}

void moveSidewaysLeft(int speed)
{
    motor1.backward(speed);
    motor2.forward(speed);
    motor3.forward(speed);
    motor4.backward(speed);
}

// Move Diagonal
void moveDiagonalForwardRight(int speed)
{
    motor1.forward(speed);
    motor4.forward(speed);
}

void moveDiagonalForwardLeft(int speed)
{
    motor2.forward(speed);
    motor3.forward(speed);
}

void moveDiagonalBackwardRight(int speed)
{
    motor2.backward(speed);
    motor3.backward(speed);
}

void moveDiagonalBackwardLeft(int speed)
{
    motor1.backward(speed);
    motor4.backward(speed);
}

// Pivot ( on one side)
void movePivotForwardRight(int speed)
{
    motor1.forward(speed);
    motor3.forward(speed);
}

void movePivotForwardLeft(int speed)
{
    motor2.forward(speed);
    motor4.forward(speed);
}

void movePivotBackwardRight(int speed)
{
    motor1.backward(speed);
    motor3.backward(speed);
}

void movePivotBackwardLeft(int speed)
{
    motor2.backward(speed);
    motor4.backward(speed);
}

// Rotate
void moveRotateRight(int speed)
{
    motor1.forward(speed);
    motor2.backward(speed);
    motor3.forward(speed);
    motor4.backward(speed);
}

void moveRotateLeft(int speed)
{
    motor1.backward(speed);
    motor2.forward(speed);
    motor3.backward(speed);
    motor4.forward(speed);
}
// Pitvot Sideways
void movePivotSidewaysRight(int speed)
{
    motor1.forward(speed);
    motor2.backward(speed);
}

void movePivotSidewaysLeft(int speed)
{
    motor1.backward(speed);
    motor2.forward(speed);
}

void movePivotSidewaysRightReverse(int speed)
{
    motor3.backward(speed);
    motor4.forward(speed);
}

void movePivotSidewaysLeftReverse(int speed)
{
    motor3.forward(speed);
    motor4.backward(speed);
}

void stopMovement()
{
    motor1.stop();
    motor2.stop();
    motor3.stop();
    motor4.stop();
}

// changing the speed of motor
void changeSpeed()
{
    if (speed == 255)
    {
        speed = 75;
    }
    else
    {
        speed = 255;
    }
    Serial.println("Speed: ");
    Serial.print(speed);
    delay(200);
}



// Define a function to map a value from one range to another
int16_t map_value(int8_t x, int8_t in_min, int8_t in_max, int16_t out_min, int16_t out_max)
{
    // For some reason, Dabble joystick data is different (example: Max_-x = 7, Max_x = 6)
    // Constrain input value
    if (x > 6)
    {
        x = 6;
    }
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void loop()
{

    //------------------------------ Using Dabble ----------------------------------------//
    Dabble.processInput(); // this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
    if (Dabble.isAppConnected())
    {
        if (GamePad.isSelectPressed()) // switching between button and joystick mode by pressing Select
        {
            joystick_mode = !joystick_mode;
            delay(200);
        }
        if (GamePad.isStartPressed()) // change speed +5 by pressing Start
        {
            changeSpeed();
        }
            // joystick mode using angle //
        if (joystick_mode){
            int16_t a = GamePad.getAngle();
            int16_t speed = map_value(GamePad.getRadius(),0,6,0,255);
            if (a>=75 && a<= 105){moveForward(speed);Serial.print(a);Serial.print(speed);}
            else if (a >= 120 && a <= 150){moveDiagonalForwardLeft(speed);}
            else if (a >= 165 && a <= 195){moveSidewaysLeft(speed);}
            else if (a >= 210 && a <= 240){moveDiagonalBackwardLeft(speed);}
            else if (a >= 255 && a <= 285){moveBackward(speed);}
            else if (a >= 300 && a <= 330){moveDiagonalBackwardRight(speed);}
            else if (a >= 345 && a <= 15){moveSidewaysRight(speed);}
            else if (a >= 30 && a <= 60){moveDiagonalForwardRight(speed);}
            else stopMovement();
        }

    // joystick mode using xy  // 
        else 
        {
            if (GamePad.isCirclePressed())
            {
                rx = speed;
            }
            else if (GamePad.isSquarePressed())
            {
                rx = -speed;
            }
            else {
                rx = 0;
            }

            x = GamePad.getXaxisData();
            y = GamePad.getYaxisData();
            motor1.set_motor_omnidirectional(x, y, rx, 0, -6, 6, 75, -140, 140, 1);
            motor2.set_motor_omnidirectional(x, y, rx, 0, -6, 6, 75, -140, 140, 2);
            motor3.set_motor_omnidirectional(x, y, rx, 0, -6, 6, 75, -140, 140, 3);
            motor4.set_motor_omnidirectional(x, y, rx, 0, -6, 6, 75, -140, 140, 4);

          
        }
    }
}
