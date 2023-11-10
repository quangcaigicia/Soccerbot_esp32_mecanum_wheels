#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

#include <Arduino.h>
#include <BluetoothSerial.h>
#include <PS4Controller.h>
#include <ezLED.h>

// Remove_Paired_Devices
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "esp_err.h"

// Custom headers
#include "motor.h"

ezLED led(BUILTIN_LED); // create an ezLED object for the LED

int buttonState{0};     // variable for reading the pushbutton status
int lastButtonState{0}; // variable for storing the last button state
int mode{0};            // changing controlled mode
int speed{200};
bool deviceConnected{false};
int joystick_mode{0};
unsigned long lastDebounceTime{0}; // the last time the button state changed
unsigned long debounceDelay{50};   // the debounce time in milliseconds

/* Define the variables for the joystick values
   x, y are left joystick and rx, ry are for right joystick*/
int x{}, y{}, rx{0}, ry{0};

Motor motor1(19, 18, 22, 0); // Direction pin and pwm channel for motor A
Motor motor2(17, 16, 23, 1); // Direction pin and pwm channel for motor B
Motor motor3(33, 25, 15, 2); // Direction pin and pwm channel for motor C
Motor motor4(27, 26, 14, 3); // Direction pin and pwm channel for motor C

//------------------------------ Removing Paired Devices ----------------------------------------//
// Create a BluetoothSerial object
BluetoothSerial SerialBT;

// Define the MAC address of the ESP32
const char *mac = "1a:2b:3c:01:01:01";

// Define a function to remove the paired devices
void removePairedDevices()
{
    // Get the number of bonded devices
    int count = esp_bt_gap_get_bond_device_num();
    // Create an array to store the device addresses
    uint8_t pairedDeviceBtAddr[20][6];
    // Get the list of bonded devices
    esp_bt_gap_get_bond_device_list(&count, pairedDeviceBtAddr);
    // Loop through the list and remove each device
    for (int i = 0; i < count; i++)
    {
        // Remove the device and check the return value
        esp_err_t result = esp_bt_gap_remove_bond_device(pairedDeviceBtAddr[i]);
        // Print the result to the serial monitor
        Serial.print("Removing device “); Serial.print(i + 1); Serial.print(”: ");
        Serial.println(result == ESP_OK ? "Success" : "Failed");
    }
}

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
void connectPS4Controller()
{
    // change mac address to ps4's mac
    PS4.attachOnConnect(onConnect);
    PS4.attachOnDisconnect(onDisConnect);
    PS4.begin("E0:2B:E9:54:91:87");
    Serial.println("Ready PS4.\n");
}
// set up dabble bluetooth
void connectDabble()
{
    Dabble.begin("Dr.Hiển");
    Serial.println("Ready Dabble.\n");
}

void setup()
{
    Serial.begin(115200);
    removePairedDevices();
    connectDabble();
    connectPS4Controller();
    pinMode(LED_BUILTIN, OUTPUT); // Build in led
    // SerialBT.begin("ESP32-noob");
}
// Blink builtin Led when device is connected
void builtinled_conection(bool deviceConnected)
{
    if (deviceConnected == true)
    {
        Serial.print("Connected...");
        led.blinkInPeriod(250, 750, 5000);
        delay(3);
    }
    else if (deviceConnected == false)
    {
        Serial.print("Disconnected...");
        led.blinkInPeriod(250, 750, 5000);
        delay(3);
    }
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
    if (speed < 255)
    {
        speed += 5;
    }
    else
    {
        speed = 5;
    }
    Serial.println("Speed: ");
    Serial.print(speed);
    delay(200);
}

//------------------------------ Onidirectional movement ----------------------------------------//
// Define the variables for the motor speeds
int motor1_speed{0}, motor2_speed{0}, motor3_speed{}, motor4_speed{};

// Define a function to map a value from one range to another
int map_value(int x, int in_min, int in_max, int out_min, int out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Define a function to calculate the motor speeds from the joystick values
void calculate_speeds(int x, int y, int rx, int ry)
{
    // Map the joystick values from -6-6 to -255-255
    x = map_value(x, -6, 6, -255, 255);
    y = map_value(y, -6, 6, -255, 255);
    rx = map_value(rx, -6, 6, -255, 255);
    ry = map_value(ry, -6, 6, -255, 255);
    // Calculate the motor speeds using the mecanum wheel kinematics
    motor1_speed = y + x + rx; // Front-left motor speed
    motor2_speed = y - x - rx; // Front-right motor speed
    motor3_speed = y - x + rx; // Back-left motor speed
    motor4_speed = y + x - rx; // Back-right motor speed
}

void loop()
{
    led.loop();
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

        // Buttons mode
        if (!joystick_mode)
        {
            if (GamePad.isUpPressed())
            {
                Serial.print("Up");
                moveForward(speed);
            }
            else if (GamePad.isDownPressed())
            {
                moveBackward(speed);
            }
            else if (GamePad.isLeftPressed())
            {
                moveSidewaysLeft(speed);
            }
            else if (GamePad.isRightPressed())
            {
                moveSidewaysRight(speed);
            }
            else
            {
                stopMovement();
            }
        }
        else // Joystick mode
        {
            x = GamePad.getx_axis();
            y = GamePad.gety_axis();
            calculate_speeds(x, y, rx, ry);
            // Set the motor speeds
            motor1.set_motor(motor1_speed, -255, 255);
            motor2.set_motor(motor2_speed, -255, 255);
            motor3.set_motor(motor3_speed, -255, 255);
            motor4.set_motor(motor4_speed, -255, 255);
        }

        // check connection by turning on BuildIn_led
        if (!deviceConnected)
        {
            builtinled_conection(true);
            deviceConnected = true;
        }
        return;
    }
//------------------------------ Using Ps4 Controller ----------------------------------------//
b:

    led.loop();
    if (PS4.isConnected())
    {
        for (int i; i < 1; i += 1)
        {
            builtinled_conection(true);
            Serial.println("PS4 cconnected...");
        }
        goto b;
    }
}
