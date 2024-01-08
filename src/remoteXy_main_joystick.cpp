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
uint8_t RemoteXY_CONF[] =   // 59 bytes
  { 255,5,0,0,0,52,0,16,24,0,5,32,246,17,35,35,190,25,31,5,
  32,75,17,35,35,190,25,31,129,0,26,0,46,6,17,84,104,101,32,82,
  111,117,110,100,32,84,97,98,108,101,0,3,131,39,23,23,8,37,26 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  int8_t joystick_left_x; // from -100 to 100  
  int8_t joystick_left_y; // from -100 to 100  
  int8_t joystick_right_x; // from -100 to 100  
  int8_t joystick_right_y; // from -100 to 100  
  uint8_t select_speed; // =0 if select position A, =1 if position B, =2 if position C, ... 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#include <motor.h>

int min_speed{80};
int max_speed{200};
int x{0}, y{0}, rx{0};

// Xe 60mm
// Motor motor1(27, 26, 25, 4); 
// Motor motor2(14, 12, 13, 5);
// Motor motor3(21, 22, 23, 6);  
// Motor motor4(18, 19, 5, 7); 

// Xe 80mm
Motor motor1(26, 27, 25, 4);
Motor motor2(12, 14, 13, 5);
Motor motor3(21, 22, 23, 6);
Motor motor4(19, 18, 5, 7);  
 

CRemoteXY *remotexy;

void remotexy_connect()
{
  // Wifi point
  remotexy = new CRemoteXY (
    RemoteXY_CONF_PROGMEM, 
    &RemoteXY, 

    new CRemoteXYConnectionServer (
      new CRemoteXYComm_WiFiPoint (
        "The Round Table - 80mm",       // REMOTEXY_WIFI_SSID
        "obsession"),        // REMOTEXY_WIFI_PASSWORD
      6377                  // REMOTEXY_SERVER_PORT
    )
  );

  // Bluetooth Low Energy
  // remotexy = new CRemoteXY (
  //   RemoteXY_CONF_PROGMEM, 
  //   &RemoteXY, 
  //   new CRemoteXYStream_BLEDevice (
  //     "The Round Table - 80mm"      
  //   )
  //     );
  // remotexy->setPassword("obsession");

  // Bluetooth Classic
  // remotexy = new CRemoteXY (
  //   RemoteXY_CONF_PROGMEM, 
  //   &RemoteXY, 
  //   new CRemoteXYStream_BluetoothSerial (
  //     "The Round Table - 80mm"      
  //   )
  // ); 
  // remotexy->setPassword("obsession");
}

void setup()
{
  remotexy_connect();
}


void loop() 
{
  remotexy->handler ();

  // setting joystick deadzone
  if (RemoteXY.joystick_left_x < 20 && RemoteXY.joystick_left_x > -20)
  {
    x = 0;
  }
  else
  {
    x = RemoteXY.joystick_left_x;
  }
  if (RemoteXY.joystick_left_y < 20 && RemoteXY.joystick_left_y > -20)
  {
    y = 0;
  }
  else
  {
    y = RemoteXY.joystick_left_y;
  }
  if (RemoteXY.joystick_right_x < 5 && RemoteXY.joystick_right_x > -5)
  {
    rx = 0;
  }
  else
  {
    rx = RemoteXY.joystick_right_x;
  }

  // Setting speed
  if (RemoteXY.pushSwitch_1!=0)
  {
    max_speed = 255;
  }
  else
  {
    max_speed = 200;
  }

  motor1.set_motor_omnidirectional(x,y,rx,-100,100,min_speed,max_speed,1);
  motor2.set_motor_omnidirectional(x,y,rx,-100,100,min_speed,max_speed,2);
  motor3.set_motor_omnidirectional(x,y,rx,-100,100,min_speed,max_speed,3);
  motor4.set_motor_omnidirectional(x,y,rx,-100,100,min_speed,max_speed,4);
}