#include <motor.h>
#include <Arduino.h>

// Constructor that sets pwmProperties, the pin modes and initializes the pins to low
Motor::Motor(int pinForward, int pinBackward, int enablepin_EN, int pwmChannel)
{
    _pinForward = pinForward;
    _pinBackward = pinBackward;
    pinMode(_pinForward, OUTPUT);
    pinMode(_pinBackward, OUTPUT);
    digitalWrite(_pinForward, LOW);
    digitalWrite(_pinBackward, LOW);

    // Setting PWM properties
    _pwmChannel = pwmChannel;
    _enablepin_EN = enablepin_EN;
    const int freq = 1000; // default 30000
    const int resolution = 8;
    // configure LED PWM functionalitites
    ledcSetup(_pwmChannel, freq, resolution);
    // attach the channel to the GPIO to be controlled
    ledcAttachPin(enablepin_EN, _pwmChannel);
}
// Method to move the motor forward with a given speed
void Motor::forward(int speed)
{
    // Set the forward pin to high and the backward pin to low
    digitalWrite(_pinForward, HIGH);
    digitalWrite(_pinBackward, LOW);
    // Use ledcWrite to control the speed of the motor
    ledcWrite(_pwmChannel, speed);
}

// Method to move the motor backward with a given speed
void Motor::backward(int speed)
{
    // Set the forward pin to low and the backward pin to high
    digitalWrite(_pinForward, LOW);
    digitalWrite(_pinBackward, HIGH);
    // Use ledcWrite to control the speed of the motor
    ledcWrite(_pwmChannel, speed);
}

// Method to move the motor backward with a given speed
void Motor::stop()
{
    // Set the forward pin to low and the backward pin to high
    digitalWrite(_pinForward, LOW);
    digitalWrite(_pinBackward, LOW);
    // Use ledcWrite to control the speed of the motor
    ledcWrite(_pwmChannel, 0);
}

// Define a function to constrain a value within a range
int constrain_value(int x, int min, int max)
{
    if (x < min)
    {
        return min;
    }
    else if (x > max)
    {
        return max;
    }
    else
    {
        return x;
    }
}

// Method to move the motor depend on the given speed
// and constrain the speed in a range
void Motor::set_motor(int speed, int min, int max)
{
    // Constrain the speed to the range -255 to 255
    speed = constrain_value(speed, -255, 255);
    // Set the direction and speed of the motor
    if (speed > 0)
    {
        digitalWrite(_pinForward, HIGH);
        digitalWrite(_pinBackward, LOW);
        ledcWrite(_pwmChannel, speed);
    }
    else if (speed < 0)
    {
        digitalWrite(_pinForward, LOW);
        digitalWrite(_pinBackward, HIGH);
        ledcWrite(_pwmChannel, speed);
    }
    else
    {
        digitalWrite(_pinForward, LOW);
        digitalWrite(_pinBackward, LOW);
        ledcWrite(_pwmChannel, 0);
    }
}
