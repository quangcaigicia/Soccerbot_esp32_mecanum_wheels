class Motor
{
public:
  // Constructor that sets pwmProperties, the pin modes and initializes the pins to low
  // Pass in 0 for the last 2 parameters if you don't need to change the power
  Motor(int pinForward,int pinBackward,int enablepin_EN,int pwmChannel);
  // Method to move the motor forward with a given speed (0-255)
  void forward(int speed);
  // Method to move the motor backward with a given speed (0-255)
  void backward(int speed);
  // Method to stop the motor
  void stop();
  // Method to move the motor omnidirectionally using joystick data
  // x, y, rx, ry: Left and right joystick data
  // Constrain the speed in a range
  // in_min, in_max: data value from joystick
  // out_min, out_max: PWM value
  // min_opperate_speed { Min_V = Max_V * (min_speed / 255_pwm) }
  // speed_min_max: constrain motor speed
  // F.L, F.R, R.L, R.R: Motor_number respectively
  void set_motor_omnidirectional(int x, int y, int rx, int in_min, int in_max, int min_opperate_speed, int speed_max, int motor_number);
private:
  // The pin numbers for the motor
  int _pinForward;
  int _pinBackward;
  int _pwmChannel;
  int _enablepin_EN;
  //
};
