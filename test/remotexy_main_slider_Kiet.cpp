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
  { 255,6,0,0,0,48,0,16,19,0,5,32,236,11,41,41,2,26,31,1,
  0,75,2,18,18,2,31,0,1,0,55,19,24,24,2,31,0,1,0,88,
  19,24,24,2,31,0,1,0,76,44,17,17,2,31,0 };
  
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

int min_speed{100};
int max_speed{200};
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
        "Bé Thảo Tóc Vàng Đáng Yêu",       // REMOTEXY_WIFI_SSID
        "emdilaychong"),        // REMOTEXY_WIFI_PASSWORD
      6377                  // REMOTEXY_SERVER_PORT
    )
  );

  // Bluetooth Low Energy
  // remotexy = new CRemoteXY (
  //   RemoteXY_CONF_PROGMEM, 
  //   &RemoteXY, 
  //   new CRemoteXYStream_BLEDevice (
  //     "Bé Thảo Tóc Vàng Đáng Yêu"      
  //   )
  //     );
  // remotexy->setPassword("emdilaychong");

  // Bluetooth Classic
  // remotexy = new CRemoteXY (
  //   RemoteXY_CONF_PROGMEM, 
  //   &RemoteXY, 
  //   new CRemoteXYStream_BluetoothSerial (
  //     "Bé Thảo Tóc Vàng Đáng Yêu"      
  //   )
  // ); 
  // remotexy->setPassword("emdilaychong");
}

void setup()
{
  remotexy_connect();
  pinMode(solanoid,OUTPUT);
  digitalWrite(solanoid,LOW);
}

/////////////////////////////////////////////
//           Motor Functions               //
/////////////////////////////////////////////

// Move Diagonal
void moveDiagonalForwardRight(int speed)
{
    motor1.forward(speed);
    motor2.stop();
    motor3.stop();
    motor4.forward(speed);
}

void moveDiagonalForwardLeft(int speed)
{
    motor1.stop();
    motor2.forward(speed);
    motor3.forward(speed);
    motor4.stop();
}

void moveDiagonalBackwardRight(int speed)
{
    motor1.stop();
    motor2.backward(speed);
    motor3.backward(speed);
    motor4.stop();
}

void moveDiagonalBackwardLeft(int speed)
{
    motor1.backward(speed);
    motor2.stop();
    motor3.stop();
    motor4.backward(speed);
}

/////////////////////////////////////////////
//           END Motor Functions           //
/////////////////////////////////////////////

void loop() 
{
  remotexy->handler ();

  if (RemoteXY.pushSwitch_1!=0)
  {
    min_speed = 155;
    max_speed = 255;
  }
  else
  {
    min_speed = 100;
    max_speed = 200;
  }

  if (RemoteXY.button_upleft!=0)
  {
    moveDiagonalForwardLeft(max_speed);
  }
  else if(RemoteXY.button_upright!=0)
  {
    moveDiagonalForwardRight(max_speed);
  }
  else if (RemoteXY.button_downleft!=0)
  {
    moveDiagonalBackwardLeft(max_speed);
  }
  else if (RemoteXY.button_downright!=0)
  {
    moveDiagonalBackwardRight(max_speed);
  }
  else
  {
    if (RemoteXY.button_left!=0)
  {
    x = -100;
  }
  else if (RemoteXY.button_right!=0)
  {
    x = 100;
  }
  else
  {
    x = 0;
  }

  if (RemoteXY.slider_left <= 10 && RemoteXY.slider_left >= -10)
  {
    y = 0;
  }
  else
  {
    y = RemoteXY.slider_left;
  }
  if (RemoteXY.slider_right <= -10 && RemoteXY.slider_right >= 10)
  {
    rx = 0;
  }
  else
  {
    rx = RemoteXY.slider_right;
  }
  
  motor1.set_motor_omnidirectional(x,y,rx,-100,100,min_speed,max_speed,1);
  motor2.set_motor_omnidirectional(x,y,rx,-100,100,min_speed,max_speed,2);
  motor3.set_motor_omnidirectional(x,y,rx,-100,100,min_speed,max_speed,3);
  motor4.set_motor_omnidirectional(x,y,rx,-100,100,min_speed,max_speed,4);
  }



  
}