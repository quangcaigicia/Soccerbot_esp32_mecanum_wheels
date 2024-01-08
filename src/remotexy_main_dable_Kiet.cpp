#include <Arduino.h>
/*
   The example shows how any data stream can be used.
   Any class inherited from the Arduino Stream class can be connected to RemoteXY
   
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.11 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.11.4 or later version;
     - for iOS 1.9.1 or later version;  
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////


#include "WiFi.h"  
// #include "BLEDevice.h"
// #include "BluetoothSerial.h"
#include <RemoteXY.h>

// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 55 bytes
  { 255,6,0,0,0,48,0,16,19,0,5,32,246,15,35,35,2,26,31,1,
  0,76,5,18,18,2,31,0,1,0,58,25,17,17,2,31,0,1,0,96,
  25,17,17,2,31,0,1,0,76,44,17,17,2,31,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  int8_t joystick_1_x; // from -100 to 100  
  int8_t joystick_1_y; // from -100 to 100  
  uint8_t button_1; // =1 if button pressed, else =0 
  uint8_t button_2; // =1 if button pressed, else =0 
  uint8_t button_3; // =1 if button pressed, else =0 
  uint8_t button_4; // =1 if button pressed, else =0 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#include <motor.h>

int min_speed{155};
int max_speed{255};
int solanoid{15};
int x{0}, y{0}, rx{0};

Motor motor1(27, 26, 25, 4); // Direction pin and pwm channel for motor A
Motor motor2(22, 21, 23, 5); // Direction pin and pwm channel for motor B
Motor motor3(12, 14, 13, 6); // Direction pin and pwm channel for motor C
Motor motor4(18, 19, 5, 7);  // Direction pin and pwm channel for motor C 

CRemoteXY *remotexy;

void remotexy_connect()
{
  remotexy = new CRemoteXY (
    RemoteXY_CONF_PROGMEM, 
    &RemoteXY, 

    new CRemoteXYConnectionServer (
      new CRemoteXYComm_WiFiPoint (
        "Be Thao Toc Vang Dang Yeu",       // REMOTEXY_WIFI_SSID
        "emdilaychongnhe"),        // REMOTEXY_WIFI_PASSWORD
      6377                  // REMOTEXY_SERVER_PORT
    )
  );

  // Bluetooth Low Energy
  // remotexy = new CRemoteXY (
  //   RemoteXY_CONF_PROGMEM, 
  //   &RemoteXY, 
  //   new CRemoteXYStream_BLEDevice (
  //     "Be Thao Toc Vang Dang Yeu"      
  //   )
  //     );
  // remotexy->setPassword("emdilaychongnhe");

  // Bluetooth Classic
  // remotexy = new CRemoteXY (
  //   RemoteXY_CONF_PROGMEM, 
  //   &RemoteXY, 
  //   new CRemoteXYStream_BluetoothSerial (
  //     "Be Thao Toc Vang Dang Yeu"      
  //   )
  // ); 
  // remotexy->setPassword("emdilaychongnhe");
}

void setup() 
{
  remotexy_connect();
  pinMode(solanoid,OUTPUT);
  digitalWrite(solanoid,LOW);
}

void loop() 
{
  remotexy->handler ();
  
  if (RemoteXY.joystick_1_x < 10 && RemoteXY.joystick_1_x > -10)
  {
    x = 0;
  }
  else
  {
  x = RemoteXY.joystick_1_x;
  }
  if (RemoteXY.joystick_1_y < 10 && RemoteXY.joystick_1_y > -10)
  {
    y = 0;
  }
  else
  {
  y = RemoteXY.joystick_1_y;
  }

  if (RemoteXY.button_1!=0)
  {
    digitalWrite(solanoid,HIGH);
  }
  else
  {
    digitalWrite(solanoid,LOW);
  }
  if (RemoteXY.button_2!=0)
  {
    rx = -80;
  }
  else if(RemoteXY.button_3!=0)
  {
    rx = 80;
  }
  else
  {
    rx = 0;
  }

  motor1.set_motor_omnidirectional(x, y, rx, -100, 100, min_speed, max_speed, 1);
  motor2.set_motor_omnidirectional(x, y, rx, -100, 100, min_speed, max_speed, 2);
  motor3.set_motor_omnidirectional(x, y, rx, -100, 100, min_speed, max_speed, 3);
  motor4.set_motor_omnidirectional(x, y, rx, -100, 100, min_speed, max_speed, 4);
}