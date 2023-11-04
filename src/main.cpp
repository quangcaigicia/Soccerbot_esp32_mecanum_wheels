#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

#include <Arduino.h>
#include <Arduino.h>
#include <BluetoothSerial.h>
#include <PS4Controller.h>
#include <ezLED.h>

// Remove_Paired_Devices
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "esp_err.h"

// Custom classes
#include "motor.h"

// create an ezLED object for the LED
ezLED led(BUILTIN_LED);

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

void connectPS4Controller()
{
  // change mac address to ps4's mac
  PS4.attachOnConnect(onConnect);
  PS4.attachOnDisconnect(onDisConnect);
  PS4.begin("E0:2B:E9:54:91:87");
  Serial.println("Ready PS4.\n");
}

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

void builtinled_conection(bool deviceConnected)
{
  if (deviceConnected == true)
  {
    Serial.print("Connected...");
    led.blinkInPeriod(250, 750, 5000);
    delay(500);
  }
  else
  {
    Serial.print("Disconnected...");
    led.blinkInPeriod(250, 750, 5000);
    delay(500);
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

void stopMovement()
{
  motor1.stop();
  motor2.stop();
  motor3.stop();
  motor4.stop();
}

void loop()
{
  led.loop();
  //------------------------------ Using Dabble ----------------------------------------//
  Dabble.processInput(); // this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  if (Dabble.isAppConnected())
  {
    if (GamePad.isUpPressed())
    {
      Serial.print("Up");
      moveForward(255);
    }
    else if (GamePad.isDownPressed())
    {
      moveBackward(255);
    }
    else if (GamePad.isLeftPressed())
    {
      moveSidewaysLeft(255);
    }
    else if (GamePad.isRightPressed())
    {
      moveSidewaysRight(255);
    }
    else
    {
      stopMovement();
    }

    // check connection by turning on BuildIn_led
    for (int i; i < 1; i += 1)
    {
      builtinled_conection(true);
      Serial.println("Dabble cconnected...");
      delay(3);
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
      Serial.println("Dabble cconnected...");
      delay(3);
    }
    goto b;
  }
}
