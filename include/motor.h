class Motor
{
public:
  // Constructor that sets pwmProperties, the pin modes and initializes the pins to low
  // Pass in 0 for the last 2 parameters if you don't need to change the power
  Motor(int pinForward, int pinBackward, int enablepin_EN, int pwmChannel);
  // Method to move the motor forward with a given speed (0-255)
  // *Our motor seem to only work from 180-255
  void forward(int speed);
  // Method to move the motor backward with a given speed (0-255)
  // *Our motor seem to only work from 180-255
  void backward(int speed);
  // Method to move the motor
  void stop();

private:
  // The pin numbers for the motor
  int _pinForward;
  int _pinBackward;
  int _pwmChannel;
  int _enablepin_EN;
};
