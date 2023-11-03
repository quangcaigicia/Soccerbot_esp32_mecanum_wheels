#include <Arduino.h>
#include <motor.h>
// #include <DabbleESP32.h>

// Assign value
Motor motor1(19, 18, 22, 0); // Direction pin for motor A
Motor motor2(17, 16, 23, 1); // Direction pin for motor B
Motor motor3(25, 33, 15, 2); // Direction pin for motor C
Motor motor4(27, 26, 14, 3); // Direction pin for motor C

// void connectDabble()
// {
//     Dabble.begin("Dr.Hiển");
//     Serial.println("Ready Dabble.\n");
// }

void setup()
{
    Serial.begin(115200);
    // connectDabble();
}

//------------------------------ Mapping Button ----------------------------------------//
enum Button
{
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SQUARE,
    CIRCLE,
    CROSS,
    TRIANGLE,
    START,
    SELECT
};

// Button getButtonPressed()
// {
//     if (GamePad.isUpPressed())
//     {
//         // Serial.print("Up");
//         return UP;
//     }
//     if (GamePad.isDownPressed())
//     {
//         // Serial.print("Down");
//         return DOWN;
//     }
//     if (GamePad.isLeftPressed())
//     {
//         // Serial.print("Left");
//         return LEFT;
//     }
//     if (GamePad.isRightPressed())
//     {
//         // Serial.print("Right");
//         return RIGHT;
//     }
//     if (GamePad.isSquarePressed())
//     {
//         return SQUARE;
//     }
//     if (GamePad.isCirclePressed())
//     {
//         return CIRCLE;
//     }
//     if (GamePad.isCrossPressed())
//     {
//         return CROSS;
//     }
//     if (GamePad.isTrianglePressed())
//     {
//         return TRIANGLE;
//     }
//     if (GamePad.isStartPressed())
//     {
//         return START;
//     }
//     if (GamePad.isSelectPressed())
//     {
//         return SELECT;
//     }
//     return NONE;
// }

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

void stopMovement()
{
    motor1.stop();
    motor2.stop();
    motor3.stop();
    motor4.stop();
}

void loop()
{
    //------------------------------ Using Dabble ----------------------------------------//
    // Dabble.processInput(); // this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
    moveForward(255);
    delay(1000);
    moveBackward(255);
    delay(1000);
    moveSidewaysLeft(255);
    delay(1000);
    moveSidewaysRight(255);
    delay(1000);
    return;
}
