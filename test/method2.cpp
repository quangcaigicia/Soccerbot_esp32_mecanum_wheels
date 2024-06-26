#include <Arduino.h>
#include <math.h>
#include <iostream>

// DabbleESP32
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

int theta{};
int power{};
int turn{};
double siN{};
double coS{};
double maX{};
int motor1{};
int motor2{};
int motor3{};
int motor4{};

void setup(){
  Serial.begin(115200);      // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin("MyEsp32"); 
}

void loop()
{
    siN = sin(theta - PI / 4);
    coS = cos(theta - PI / 4);
    maX = max(abs(siN), abs(coS)); // scale the motor to max speed
    std::cout << siN << "" << coS << '\n';

    // speed value range from -1 to 1
    motor1 = power * coS / maX + turn;
    motor2 = power * siN / maX - turn;
    motor3 = power * siN / maX + turn;
    motor4 = power * coS / maX - turn;

    int x; // joystick
    int y; // joystick

    theta = atan2(y, x); // == tan-1(y/x) radians
    power = hypot(x, y); // find the hypotenuse of a right angled triangle.

    if ((power + abs(turn)) > 1)
    {
        motor1 /= power + turn;
        motor2 /= power + turn;
        motor3 /= power + turn;
        motor4 /= power + turn;
        
    }
Serial.print(motor1);
}