class Motor
{
public:
  // Constructor that sets pwmProperties, the pin modes and initializes the pins to low
  // Pass in 0 for the last 2 parameters if you don't need to change the power
  Motor(int pinForward, int pinBackward, int enablepin_EN, int pwmChannel);
  // Method to move the motor forward with a given speed (0-255)
  void forward(int speed);
  // Method to move the motor backward with a given speed (0-255)
  void backward(int speed);
  // Method to stop the motor
  void stop();
  // Method to move the motor depend on the given speed
  // and constrain the speed in a range
  void set_motor(int speed, int min, int max);

private:
  // The pin numbers for the motor
  int _pinForward;
  int _pinBackward;
  int _pwmChannel;
  int _enablepin_EN;
};
