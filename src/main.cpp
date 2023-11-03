#include <Arduino.h>
#include <BluetoothSerial.h>
#include <DabbleESP32.h>
#include <PS4Controller.h>
#include <ezLED.h>

// Remove_Paired_Devices
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "esp_err.h"

// Include classes
#include "motor.h"

// create an ezLED object for the LED
ezLED led(BUILTIN_LED);

// Assign value
Motor motor1(19, 18, 22, 0); // Direction pin for motor A
Motor motor2(17, 16, 23, 1); // Direction pin for motor B
Motor motor3(25, 33, 15, 2); // Direction pin for motor C
Motor motor4(27, 26, 14, 3); // Direction pin for motor C

// ps4
#define BUTTONS 0

bool printed = true; // print once
bool deviceConnected;
int x;

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
  return;
}
void onDisConnect()
{
  Serial.println("Disconnected!");
}

void connectPS4Controller()
{
  // change mac address to ps4's mac
  PS4.begin("E0:2B:E9:54:91:87");
  Serial.println("Ready PS4.\n");
  PS4.attachOnConnect(onConnect);
  PS4.attachOnDisconnect(onDisConnect);
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
  // connectPS4Controller();
  pinMode(LED_BUILTIN, OUTPUT); // Build in led
  // SerialBT.begin("ESP32-noob");
  delay(500);
}

void led_conection()
{
  Serial.print("Connected...");
  led.blinkInPeriod(250, 750, 5000);
  deviceConnected = true;
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

Button getButtonPressed()
{
  if (GamePad.isUpPressed() || PS4.Right())
  {
    // Serial.print("Up");
    return UP;
  }
  if (GamePad.isDownPressed() || PS4.Down())
  {
    // Serial.print("Down");
    return DOWN;
  }
  if (GamePad.isLeftPressed() || PS4.Left())
  {
    // Serial.print("Left");
    return LEFT;
  }
  if (GamePad.isRightPressed())
  {
    // Serial.print("Right");
    return RIGHT;
  }
  if (GamePad.isSquarePressed())
  {
    return SQUARE;
  }
  if (GamePad.isCirclePressed())
  {
    return CIRCLE;
  }
  if (GamePad.isCrossPressed())
  {
    return CROSS;
  }
  if (GamePad.isTrianglePressed())
  {
    return TRIANGLE;
  }
  if (GamePad.isStartPressed())
  {
    return START;
  }
  if (GamePad.isSelectPressed())
  {
    return SELECT;
  }
  return NONE;
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
  while (Dabble.isAppConnected())
  {

    // check connection by turning on BuildIn_led
    if (printed)
    {
      led_conection();
      printed = false;
    }
    switch (getButtonPressed())
    {
    case UP:
      moveForward(255);
      break;
    case DOWN:
      moveBackward(255);
      break;
    case LEFT:
      moveSidewaysLeft(255);
      break;
    case RIGHT:
      moveSidewaysRight(255);
      break;

    default:
      stopMovement();
      break;
    }
    // delay(3);
    return;
  }

  //------------------------------ Using Ps4 Controller ----------------------------------------//
  while (PS4.isConnected())
  {
    switch (getButtonPressed())
    {
    case UP:

      break;

    default:
      break;
    }
  }
}
