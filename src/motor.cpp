#include <motor.h>
#include <Arduino.h>

// Constructor that sets pwmProperties, the pin modes and initializes the pins to low
Motor::Motor(int pinForward,int pinBackward,int enablepin_EN,int pwmChannel)
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
    const int freq = 1000; // 75,3-battery,900gram / 2000,2-battery,1700gram
    const int resolution = 8;
    // configure LED PWM functionalitites
    ledcSetup(_pwmChannel, freq, resolution);
    // attach the channel to the GPIO to be controlled / comment this out if you don't need to controll pwm
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

//------------------------------ Mecanum Joystick movement ----------------------------------------//
// Define the variables for the motor speeds
int speed_omnidirectional{0};
int out_min{0};
int out_max{0};
int motor_number{0};

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

// Define a function to map a value from one range to another
float map_value(float x, float in_min, float in_max, float out_min, float out_max)
{
    if (x > in_max)
    {
        x = in_max;
    }
    else if ( x < in_min)
    {  
        x = in_min;
    }

    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Define a function to calculate the motor speeds from the joystick values
void calculate_speeds(int x, int y, int rx, int in_min, int in_max, int out_min, int out_max, int motor_number)
{
    // Map the joystick values from in_min-in_max to your desirer PWM min-max value
    x = map_value(x, in_min, in_max, out_min, out_max);
    y = map_value(y, in_min, in_max, out_min, out_max);
    rx = map_value(rx, in_min, in_max, out_min, out_max);

    

    // Calculate the motor speeds using the mecanum wheel kinematics
    switch (motor_number)
    {
    case 1:
        speed_omnidirectional = y + x + rx; // Front-left motor speed
        break;
    case 2:
        speed_omnidirectional = y - x - rx; // Front-right motor speed
        break;
    case 3:
        speed_omnidirectional = y - x + rx; // Back-left motor speed
        break;
    case 4:
        speed_omnidirectional = y + x - rx; // Back-right motor speed
        break;
    default:
        break;
    }
    
}

// Method to move the motor omnidirectional using joystick and return the speed
void Motor::set_motor_omnidirectional(int x, int y, int rx, int in_min, int in_max, int min_opperate_speed, int speed_max, int motor_number)
{
    out_min = -speed_max + min_opperate_speed;
    out_max = speed_max - min_opperate_speed;
    calculate_speeds(x, y, rx, in_min, in_max, out_min, out_max, motor_number);
    // Update the speed to where the motor can opperate
    if (min_opperate_speed != 0 && speed_omnidirectional != 0)
    {
        if (speed_omnidirectional > 0)
        {
            speed_omnidirectional += min_opperate_speed;
        }
        else
        {
            speed_omnidirectional -= min_opperate_speed;
        }
    }

    // Constrain the speed to the range -255 to 255
    speed_omnidirectional = constrain_value(speed_omnidirectional, -speed_max, speed_max);


    // Set the direction and speed of the motor 
    if (speed_omnidirectional > 0)
    {
        digitalWrite(_pinForward, HIGH);
        digitalWrite(_pinBackward, LOW);
        ledcWrite(_pwmChannel, speed_omnidirectional);
    }
    else if (speed_omnidirectional < 0)
    {
        digitalWrite(_pinForward, LOW);
        digitalWrite(_pinBackward, HIGH);
        ledcWrite(_pwmChannel, -speed_omnidirectional);
    }
    else
    {
        digitalWrite(_pinForward, LOW);
        digitalWrite(_pinBackward, LOW);
        ledcWrite(_pwmChannel, 0);
    }

    // Serial print Speed
    // Serial.print("Speed: ");
    // Serial.print(speed_omnidirectional);
    // Serial.print(" Motor: ");
    // Serial.print(motor_number);
    // Serial.print('\t');
    // if (motor_number == 4)
    //     Serial.println();
}