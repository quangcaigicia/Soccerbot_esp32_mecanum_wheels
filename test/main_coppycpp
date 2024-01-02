//** This code power the esp32 that uses 2 driver to controll 4 wheel independently
//** PS4 and Dabble compatable
//** To calculate the speed for your motor min_V = max_V * speed / 255 <<-- you can change this value by changing the resolution in motor.cpp
//**

#include <Arduino.h>
// #include <PS4Controller.h>
#include <ezLED.h>

// DabbleESP32
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

// Custom headers
#include "motor.h"

ezLED led(BUILTIN_LED); // create an ezLED object for the LED

// #include <millisDelay.h>
// bool solanoid_auto{false};
// millisDelay solanoid_isonDelay{};
// millisDelay solanoid_Delay{};
// int solanoid_count{0}; 
// int solanoid_once{0}; // activate solanoid only once
// millisDelay solanoid_onceDelay{};

int const solanoid{15};
int speed{255};
bool deviceConnected{false};
bool joystick_mode{true};


/* Define the variables for the joystick values
   x, y are left joystick and rx, ry are for right joystick*/
float x{0}, y{0}, rx{0};

Motor motor1(27, 26, 25, 1); // Direction pin and pwm channel for motor A
Motor motor2(22, 21, 23, 2); // Direction pin and pwm channel for motor B
Motor motor3(12, 14, 13, 3); // Direction pin and pwm channel for motor C
Motor motor4(18, 19, 5, 4);  // Direction pin and pwm channel for motor C

// Motor motor1(19, 18, 5, 1);  // Direction pin and pwm channel for motor A
// Motor motor2(12, 14, 13, 2);  // Direction pin and pwm channel for motor B
// Motor motor3(22, 21, 23, 3); // Direction pin and pwm channel for motor C
// Motor motor4(27, 26, 25, 4); // Direction pin and pwm channel for motor C

// PS4 check connection
// void onConnect()
// {
//     Serial.println("Connected!");
// }
// void onDisConnect()
// {
//     Serial.println("Disconnected!");
// }
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
    Dabble.begin("Bé Thảo Tóc Vàng");
    Serial.println("Ready Dabble.\n");
}

void setup()
{
    Serial.begin(115200);
    connectDabble();
    // connectPS4Controller();
    pinMode(LED_BUILTIN, OUTPUT); // Build in led
    pinMode(solanoid, OUTPUT);
    digitalWrite(solanoid, LOW);
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
    motor2.stop();
    motor3.stop();
    motor4.forward(speed);
}

void moveDiagonalForwardLeft(int speed)
{
    motor1.stop();
    motor2.forward(speed);
    motor3.forward(speed);
    motor4.stop();
}

void moveDiagonalBackwardRight(int speed)
{
    motor1.stop();
    motor2.backward(speed);
    motor3.backward(speed);
    motor4.stop();
}

void moveDiagonalBackwardLeft(int speed)
{
    motor1.backward(speed);
    motor2.stop();
    motor3.stop();
    motor4.backward(speed);
}

// Pivot ( on one side)
void movePivotForwardRight(int speed)
{
    motor1.forward(speed);
    motor2.stop();
    motor3.forward(speed);
    motor4.stop();
}

void movePivotForwardLeft(int speed)
{
    motor1.stop();
    motor2.forward(speed);
    motor3.stop();
    motor4.forward(speed);
}

void movePivotBackwardRight(int speed)
{
    motor1.backward(speed);
    motor2.stop();
    motor3.backward(speed);
    motor4.stop();
}

void movePivotBackwardLeft(int speed)
{
    motor1.stop();
    motor2.backward(speed);
    motor3.stop();
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
    motor3.stop();
    motor4.stop();
}

void movePivotSidewaysLeft(int speed)
{
    motor1.backward(speed);
    motor2.forward(speed);
    motor3.stop();
    motor4.stop();
}

void movePivotSidewaysRightReverse(int speed)
{ 
    motor1.stop();
    motor2.stop();
    motor3.backward(speed);
    motor4.forward(speed);
}

void movePivotSidewaysLeftReverse(int speed)
{
    motor1.stop();
    motor2.stop();
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

// Blink builtin Led when device is connected
void builtinled_conection(
    bool deviceConnected)
{
    if (deviceConnected == true)
    {
        Serial.print("Connected...");
        led.blinkInPeriod(250, 750, 5000);
        delay(3);
    }
    else
    {
        Serial.print("Disconnected...");
        led.blinkInPeriod(250, 750, 5000);
        deviceConnected = false;
        delay(3);
    }
}

// Define a function to map a value from one range to another
int map_value(int x, int in_min, int in_max, int out_min, int out_max)
{
    // For some reason, Dabble joystick data is different (example: Max_-x = 7, Max_x = 6)
    // Constrain input value
    if (x > in_max)
    {
        x = in_max;
    }
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void loop()
{
    led.loop();

    //------------------------------ Using Dabble ----------------------------------------//
    Dabble.processInput(); // this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
    if (Dabble.isAppConnected())
    {
        // if (GamePad.isSelectPressed()) // switching between button and joystick mode by pressing Select
        // {
        //     joystick_mode = !joystick_mode;
        //     delay(200);
        // }
        //          Solanoid Auto           //
        // if (GamePad.isStartPressed())
        // {
        //     solanoid_auto = !solanoid_auto;
        //     delay(200);
        // }
        // if (solanoid_auto)
        // {
        //      if (solanoid_Delay.remaining() == 0)
        //     {
        //         solanoid_Delay.start(30000);
        //         solanoid_isonDelay.start(200);
        //         solanoid_count = 0;
        //     }
        //     if (solanoid_count < 5) 
        //     {
        //         if (solanoid_isonDelay.remaining() == 0)
        //         {
        //             Serial.print("Solanoid");
        //             digitalWrite(solanoid, HIGH);
        //             solanoid_isonDelay.restart();
        //         }
        //         if (solanoid_isonDelay.remaining() <= 100)
        //         {
        //             digitalWrite(solanoid, LOW);
        //             solanoid_count += 1;
        //         }
        //     }
        // }
        // else 
        // {
        //     solanoid_Delay.finish();
        //     solanoid_isonDelay.finish();
        //     solanoid_count = 0;
        // }
        //          Solanoid            //
        if (GamePad.isTrianglePressed())
        {
            digitalWrite(solanoid, HIGH);
            
        }
        else
        {
            digitalWrite(solanoid, LOW);
        }


        // joystick mode using angle //
        // if (!joystick_mode)
        // {
        //     switch ((GamePad.getAngle()) | (GamePad.isSquarePressed()? 3 : 0) | (GamePad.isCirclePressed()? 4 : 0))
        //     {
        //         case 75:
        //         case 90:
        //         case 105:
        //             switch ((GamePad.isSquarePressed()? 1 : 0) | (GamePad.isCirclePressed()? 2 : 0))
        //             {
        //                 case 1:
        //                     movePivotForwardLeft(speed);
        //                     break;
        //                 case 2:
        //                     movePivotForwardRight(speed);
        //                 default:
        //                     moveForward(speed);
        //                      break;
        //             }
                    
        //         case 120:
        //         case 135:
        //         case 150:
        //             moveDiagonalForwardLeft(speed);
        //         break;
        //         case 165:
        //         case 180:
        //         case 195:
        //             switch ((GamePad.isSquarePressed()? 1 : 0) | (GamePad.isCirclePressed()? 2 : 0))
        //             {
        //                 case 1:
        //                     movePivotSidewaysLeft(speed);
        //                     break;
        //                 case 2:
        //                     movePivotSidewaysRight(speed);
        //                     break;
        //                     default:
        //                 moveSidewaysLeft(speed);
        //                     break;
        //             }
                
        //         break;
        //         case 210:
        //         case 225:
        //         case 240:
        //             moveDiagonalBackwardLeft(speed);
        //         break;
        //         case 255:
        //         case 270:
        //         case 285:
        //              switch ((GamePad.isSquarePressed()? 1 : 0) | (GamePad.isCirclePressed()? 2 : 0))
        //             {
        //                 case 1:
        //                     movePivotBackwardLeft(speed);
        //                     break;
        //                 case 2:
        //                     movePivotBackwardRight(speed);
        //                     break;
        //                 default:
        //                     moveBackward(speed);
        //                     break;
        //             }
                
        //             break;
        //         case 300:
        //         case 315:
        //         case 330:
        //             moveDiagonalBackwardRight(speed);
        //             break;
        //         case 345:
        //         case 15:
        //         switch ((GamePad.isSquarePressed()? 1 : 0) | (GamePad.isCirclePressed()? 2 : 0))
        //             {
        //                 case 1:
        //                     movePivotSidewaysLeftReverse(speed);
        //                     break;
        //                 case 2:
        //                     movePivotSidewaysRightReverse(speed);
        //                     break;
        //                 default:
        //                     moveSidewaysRight(speed);
        //                     break;
        //             }
        //             break;
        //         case 30:
        //         case 45:
        //         case 60:
        //             moveDiagonalForwardRight(speed);
        //             break;

        //         case 3: 
        //             moveRotateLeft(speed);
        //             break;
        //         case 4:
        //             moveRotateRight(speed);
        //             break;
        //         default:
        //             stopMovement();
        //             break;
        //     }
        // }

            
        

    // // joystick mode using xy  //  
    if (joystick_mode)
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
            motor1.set_motor_omnidirectional(x, y, rx, -6, 6, 140, 255, 1);
            motor2.set_motor_omnidirectional(x, y, rx, -6, 6, 140, 255, 2);
            motor3.set_motor_omnidirectional(x, y, rx, -6, 6, 140, 255, 3);
            motor4.set_motor_omnidirectional(x, y, rx, -6, 6, 140, 255, 4);
        }
        // check connection by turning on BuildIn_led
        if (!deviceConnected)
        {
            builtinled_conection(true);
        }
        deviceConnected = true;
    }
}
