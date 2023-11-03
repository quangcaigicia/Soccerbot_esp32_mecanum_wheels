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
    const int freq = 30000;
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
