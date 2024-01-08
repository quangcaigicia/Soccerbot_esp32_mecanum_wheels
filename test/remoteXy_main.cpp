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


#include "BLEDevice.h"  
#include <RemoteXY.h>





// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 260 bytes
  { 255,15,0,65,0,253,0,16,24,4,5,32,250,19,26,26,1,24,178,16,
  5,32,80,19,26,26,1,24,178,16,131,3,32,1,12,4,1,178,25,74,
  111,121,115,116,105,99,107,0,131,2,55,1,14,4,3,136,25,83,101,116,
  116,105,110,103,115,0,3,130,45,1,9,5,0,54,25,1,0,77,9,10,
  10,1,136,31,226,134,169,0,71,72,34,14,32,32,3,19,178,54,150,0,
  0,2,67,0,0,127,67,0,0,160,65,0,0,32,65,0,0,0,64,54,
  77,105,110,32,83,112,101,101,100,0,136,0,0,2,67,0,0,27,67,93,
  0,0,27,67,0,0,72,67,36,0,0,72,67,0,0,127,67,4,0,91,
  12,8,24,3,178,54,4,0,80,12,8,24,3,178,54,1,0,99,9,10,
  10,1,136,31,226,134,170,0,4,0,1,12,8,24,3,178,54,4,0,12,
  12,8,24,3,178,54,67,5,27,50,44,4,3,2,26,31,67,5,27,55,
  22,4,3,2,26,16,67,5,49,55,22,4,3,2,26,16,7,45,80,2,
  21,4,3,17,24,2,2,129,0,75,2,7,4,3,17,86,111,108,116,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  int8_t joystick_L_x; // from -100 to 100  
  int8_t joystick_L_y; // from -100 to 100  
  int8_t joystick_R_x; // from -100 to 100  
  int8_t joystick_R_y; // from -100 to 100  
  uint8_t select_1; // =0 if select position A, =1 if position B, =2 if position C, ... 
  uint8_t button_Left; // =1 if button pressed, else =0 
  int8_t settings_slider_max_2; // =0..100 slider position 
  int8_t settings_slider_max_1; // =0..100 slider position 
  uint8_t button_Right; // =1 if button pressed, else =0 
  int8_t settings_slider_min_1; // =0..100 slider position 
  int8_t settings_slider_min_2; // =0..100 slider position 
  float testings_edit_1;

    // output variables
  int16_t settings_instrument_1;  // from 130 to 255 
  char text_speed_1[31];  // string UTF8 end zero 
  char text_volt_1[16];  // string UTF8 end zero 
  char text_volt_2[16];  // string UTF8 end zero 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#include <motor.h>

int min_speed{0};
int max_speed{0};
float voltage{0};
int speed{0};
int x{0}, y{0}, rx{0};

Motor motor1(19, 18, 5, 1);  // Direction pin and pwm channel for motor A
Motor motor2(26, 27, 14, 2);  // Direction pin and pwm channel for motor B
Motor motor3(22, 21, 23, 3); // Direction pin and pwm channel for motor C
Motor motor4(25, 33, 32, 4); // Direction pin and pwm channel for motor C

CRemoteXY *remotexy;

void remotexy_connect()
{
  remotexy = new CRemoteXY (
    RemoteXY_CONF_PROGMEM, 
    &RemoteXY, 
    new CRemoteXYStream_BLEDevice (
      "Mẹc Xe Đẹc"       // REMOTEXY_BLUETOOTH_NAME
    )
      );
  remotexy->setPassword("123");
}

void setup() 
{
  remotexy_connect();
}

void loop() 
{
  remotexy->handler ();
  switch (RemoteXY.select_1)
  {
  //           Joystick           //
  case 0:
    x = RemoteXY.joystick_L_x;
    y = RemoteXY.joystick_L_y;
    rx = RemoteXY.joystick_R_x;
    if (RemoteXY.button_Right != 0)
    {
        
    }
    motor1.set_motor_omnidirectional(x, y, rx, -100, 100, min_speed, max_speed, 1);
    motor2.set_motor_omnidirectional(x, y, rx, -100, 100, min_speed, max_speed, 2);
    motor3.set_motor_omnidirectional(x, y, rx, -100, 100, min_speed, max_speed, 3);
    motor4.set_motor_omnidirectional(x, y, rx, -100, 100, min_speed, max_speed, 4);
    break;
  //              Settings              //
  case 1:
    min_speed = 55 + RemoteXY.settings_slider_min_1 + RemoteXY.settings_slider_min_2;
    max_speed = 55 + RemoteXY.settings_slider_max_1 + RemoteXY.settings_slider_max_2;
    voltage = RemoteXY.testings_edit_1;
    RemoteXY.settings_instrument_1 = min_speed;
    sprintf (RemoteXY.text_speed_1, "Min Speed: %i Max Speed: %i",min_speed, max_speed);
    sprintf (RemoteXY.text_volt_1, "Min Volt: %f", round(voltage*min_speed/255*1000)/1000);
    sprintf (RemoteXY.text_volt_2, "Max Volt: %f", round(voltage*max_speed/255*1000)/1000);
  }
}