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
uint8_t RemoteXY_CONF[] =   // 158 bytes
  { 255,12,0,93,0,151,0,16,24,0,68,51,242,16,30,41,8,36,135,94,
  120,0,121,0,114,120,0,4,0,99,3,8,24,178,54,3,130,44,0,12,
  7,54,25,10,48,63,1,8,8,136,54,54,79,78,0,24,79,70,70,0,
  4,0,89,3,8,24,178,54,67,5,24,10,52,4,24,54,29,5,4,80,
  44,17,17,24,178,54,5,1,99,44,17,17,24,178,54,7,53,253,0,23,
  5,24,54,24,68,52,18,16,60,41,8,136,94,204,36,49,0,50,0,51,
  0,52,0,1,1,76,9,7,6,25,31,78,101,120,116,0,1,1,17,9,
  7,6,25,31,80,114,101,118,0,67,5,18,58,60,4,177,24,36 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  int8_t slider_1; // =0..100 slider position 
  uint8_t select_1; // =0 if select position A, =1 if position B, =2 if position C, ... 
  uint8_t pushSwitch_1; // =1 if state is ON, else =0 
  int8_t slider_2; // =0..100 slider position 
  int8_t joystick_2_x; // from -100 to 100  
  int8_t joystick_2_y; // from -100 to 100  
  int8_t joystick_1_x; // from -100 to 100  
  int8_t joystick_1_y; // from -100 to 100  
  int16_t edit_1;  // 32767.. +32767 
  uint8_t button_next; // =1 if button pressed, else =0 
  uint8_t button_prev; // =1 if button pressed, else =0 

    // output variables
  float controllerGraph_var1;
  float controllerGraph_var2;
  float controllerGraph_var3;
  char text_1[29];  // string UTF8 end zero 
  float motorSpeedGraph_var1;
  float motorSpeedGraph_var2;
  float motorSpeedGraph_var3;
  float motorSpeedGraph_var4;
  char text_2[36];  // string UTF8 end zero 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#include <motor.h>

int min_opperate_speed{0};
int max_speed{0};
float voltage{0};
float voltage_in{11.1};
int speed{0};
int speed_1{0};
int speed_2{0};
int speed_3{0};
int speed_4{0};
int x{0}, y{0}, rx{0};

Motor motor1(19, 18, 5, 1);  // Direction pin and pwm channel for motor A
Motor motor2(26, 27, 14, 2);  // Direction pin and pwm channel for motor B
Motor motor3(22, 21, 23, 3); // Direction pin and pwm channel for motor C
Motor motor4(25, 33, 32, 4); // Direction pin and pwm channel for motor C


#include <millisDelay.h>
bool move_mode{false};
int8_t move_mode_numb{0};
millisDelay move_modeDelay;
bool safety_speed{false};
millisDelay safety_speedDelay;



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
  // Serial.begin(115200);
  remotexy_connect();
}


/////////////////////////////////////////////
//           Motor Functions               //
/////////////////////////////////////////////
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

// Pivot ( on one side)
void movePivotForwardRight(int speed)
{
    motor1.forward(speed);
    motor2.stop();
    motor3.forward(speed);
    motor4.stop();
}

void movePivotForwardLeft(int speed)
{
    motor1.stop();
    motor2.forward(speed);
    motor3.stop();
    motor4.forward(speed);
}

void movePivotBackwardRight(int speed)
{
    motor1.backward(speed);
    motor2.stop();
    motor3.backward(speed);
    motor4.stop();
}

void movePivotBackwardLeft(int speed)
{
    motor1.stop();
    motor2.backward(speed);
    motor3.stop();
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
    motor3.stop();
    motor4.stop();
}

void movePivotSidewaysLeft(int speed)
{
    motor1.backward(speed);
    motor2.forward(speed);
    motor3.stop();
    motor4.stop();
}

void movePivotSidewaysRightReverse(int speed)
{ 
    motor1.stop();
    motor2.stop();
    motor3.backward(speed);
    motor4.forward(speed);
}

void movePivotSidewaysLeftReverse(int speed)
{
    motor1.stop();
    motor2.stop();
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

/////////////////////////////////////////////
//           END Motor Functions           //
/////////////////////////////////////////////

void calculate_voltage(int Speed)
{
  voltage = voltage_in * speed / 255;
}

void reset_remotexy_indicators()
{
  RemoteXY.motorSpeedGraph_var1 = 0;
  RemoteXY.motorSpeedGraph_var2 = 0;
  RemoteXY.motorSpeedGraph_var3 = 0;
  RemoteXY.motorSpeedGraph_var4 = 0;
  RemoteXY.controllerGraph_var1 = 0;
  RemoteXY.controllerGraph_var2 = 0;
  RemoteXY.controllerGraph_var3 = 0;
  sprintf (RemoteXY.text_2, "Speed: Volt:");
  sprintf (RemoteXY.text_1, "Speed: Volt:");
}

void loop() 
{
  remotexy->handler ();
  
 
  //              Testing             //
    //        Reset graph       //
    if (RemoteXY.pushSwitch_1!=1)
    {
      reset_remotexy_indicators();
    }
    
    switch (RemoteXY.select_1)
    {
    //              Movement Test               //
    case 0:
      if(RemoteXY.pushSwitch_1!=1 && move_mode == false)
      {
        strcpy (RemoteXY.text_1, "Speed Test");
      }

      if (RemoteXY.pushSwitch_1!=1 && move_mode==true) 
        {
          strcpy (RemoteXY.text_1, "Stop Test");
          stopMovement();
          move_modeDelay.finish();
          move_mode_numb = 0;
          move_mode = false;
          remotexy->delay(1000);
        }
      
      speed = RemoteXY.slider_1 + RemoteXY.slider_2 + RemoteXY.joystick_1_y + RemoteXY.joystick_2_y;
      voltage = voltage_in * speed / 255;
      sprintf (RemoteXY.text_2, "Speed: %i Volt: %f", speed, voltage); 


      if(RemoteXY.pushSwitch_1!=0)
      {
        move_mode = true;
        if (move_modeDelay.remaining()==0)
        {
          move_modeDelay.start(3000);
          move_mode_numb += 1;
        }

        if (RemoteXY.edit_1!=0) // Using only one switch input
        {
          move_mode_numb = 0;
        }

        if (RemoteXY.button_next!=0)
        {
          move_mode_numb += 1;
          move_modeDelay.restart();
          remotexy->delay(200);
        }
        if (RemoteXY.button_prev!=0)
        {
          move_mode_numb -= 1;
          move_modeDelay.restart();
          remotexy->delay(200); 
        }

        switch (move_mode_numb | RemoteXY.edit_1)
        {
        case 1:
          strcpy (RemoteXY.text_1, "Forward");
          moveForward(speed);
          RemoteXY.motorSpeedGraph_var1 = speed;
          RemoteXY.motorSpeedGraph_var2 = speed;
          RemoteXY.motorSpeedGraph_var3 = speed;
          RemoteXY.motorSpeedGraph_var4 = speed;
          break;
        case 2:
          strcpy (RemoteXY.text_1, "Backward");
          moveBackward(speed);
          RemoteXY.motorSpeedGraph_var1 = -speed;
          RemoteXY.motorSpeedGraph_var2 = -speed;
          RemoteXY.motorSpeedGraph_var3 = -speed;
          RemoteXY.motorSpeedGraph_var4 = -speed;
          break;
        case 3:
          strcpy (RemoteXY.text_1, "Sideways Right");
          moveSidewaysRight(speed);
          RemoteXY.motorSpeedGraph_var1 = speed;
          RemoteXY.motorSpeedGraph_var2 = -speed;
          RemoteXY.motorSpeedGraph_var3 = -speed;
          RemoteXY.motorSpeedGraph_var4 = speed;
          break;
        case 4:
          strcpy (RemoteXY.text_1, "Sideways Left");
          moveSidewaysLeft(speed);
          RemoteXY.motorSpeedGraph_var1 = -speed;
          RemoteXY.motorSpeedGraph_var2 = speed;
          RemoteXY.motorSpeedGraph_var3 = speed;
          RemoteXY.motorSpeedGraph_var4 = -speed;
          break;
        case 5:
          strcpy (RemoteXY.text_1, "Forward Right 45°");
          moveDiagonalForwardRight(speed);
          RemoteXY.motorSpeedGraph_var1 = speed;
          RemoteXY.motorSpeedGraph_var2 = 0;
          RemoteXY.motorSpeedGraph_var3 = 0;
          RemoteXY.motorSpeedGraph_var4 = speed;
          break;
        case 6:
          strcpy (RemoteXY.text_1, "Forward Left 45°");
          moveDiagonalForwardLeft(speed);
          RemoteXY.motorSpeedGraph_var1 = 0;
          RemoteXY.motorSpeedGraph_var2 = speed;
          RemoteXY.motorSpeedGraph_var3 = speed;
          RemoteXY.motorSpeedGraph_var4 = 0;
          break;
        case 7:
          strcpy (RemoteXY.text_1, "Backward Right 45°");
          moveDiagonalBackwardRight(speed);
          RemoteXY.motorSpeedGraph_var1 = 0;
          RemoteXY.motorSpeedGraph_var2 = -speed;
          RemoteXY.motorSpeedGraph_var3 = -speed;
          RemoteXY.motorSpeedGraph_var4 = 0;
          break;
        case 8:
          strcpy (RemoteXY.text_1, "Backward Left 45°");
          moveDiagonalBackwardLeft(speed);
          RemoteXY.motorSpeedGraph_var1 = -speed;
          RemoteXY.motorSpeedGraph_var2 = 0;
          RemoteXY.motorSpeedGraph_var3 = 0;
          RemoteXY.motorSpeedGraph_var4 = -speed;
          break;
        case 9:
          strcpy (RemoteXY.text_1, "Pivot Forward Right");
          movePivotForwardRight(speed);
          RemoteXY.motorSpeedGraph_var1 = speed;
          RemoteXY.motorSpeedGraph_var2 = 0;
          RemoteXY.motorSpeedGraph_var3 = speed;
          RemoteXY.motorSpeedGraph_var4 = 0;
          break;
        case 10:
          strcpy (RemoteXY.text_1, "Pivot Forward Left");
          movePivotForwardLeft(speed);
          RemoteXY.motorSpeedGraph_var1 = 0;
          RemoteXY.motorSpeedGraph_var2 = speed;
          RemoteXY.motorSpeedGraph_var3 = 0;
          RemoteXY.motorSpeedGraph_var4 = speed;
          break;
        case 11:
          strcpy (RemoteXY.text_1, "Pivot Backward Right");
          movePivotBackwardRight(speed);
          RemoteXY.motorSpeedGraph_var1 = -speed;
          RemoteXY.motorSpeedGraph_var2 = 0;
          RemoteXY.motorSpeedGraph_var3 = -speed;
          RemoteXY.motorSpeedGraph_var4 = 0;
          break;
        case 12:
          strcpy (RemoteXY.text_1, "Pivot Backward Left");
          movePivotBackwardLeft(speed);
          RemoteXY.motorSpeedGraph_var1 = 0;
          RemoteXY.motorSpeedGraph_var2 = -speed;
          RemoteXY.motorSpeedGraph_var3 = 0;
          RemoteXY.motorSpeedGraph_var4 = -speed;
          break;
        case 13:
          strcpy (RemoteXY.text_1, "Rotate Right");
          moveRotateRight(speed);
          RemoteXY.motorSpeedGraph_var1 = speed;
          RemoteXY.motorSpeedGraph_var2 = -speed;
          RemoteXY.motorSpeedGraph_var3 = speed;
          RemoteXY.motorSpeedGraph_var4 = -speed;
          break;
        case 14:
          strcpy (RemoteXY.text_1, "Rotate Left");
          moveRotateLeft(speed);
          RemoteXY.motorSpeedGraph_var1 = -speed;
          RemoteXY.motorSpeedGraph_var2 = speed;
          RemoteXY.motorSpeedGraph_var3 = -speed;
          RemoteXY.motorSpeedGraph_var4 = speed;
          break;
        case 15:
          strcpy (RemoteXY.text_1, "Pivot Sideways Right");
          movePivotSidewaysRight(speed);
          RemoteXY.motorSpeedGraph_var1 = speed;
          RemoteXY.motorSpeedGraph_var2 = -speed;
          RemoteXY.motorSpeedGraph_var3 = 0;
          RemoteXY.motorSpeedGraph_var4 = 0;
          break;
        case 16:
          strcpy (RemoteXY.text_1, "Pivot Sideways Left");
          movePivotSidewaysLeft(speed);
          RemoteXY.motorSpeedGraph_var1 = -speed;
          RemoteXY.motorSpeedGraph_var2 = speed;
          RemoteXY.motorSpeedGraph_var3 = 0;
          RemoteXY.motorSpeedGraph_var4 = 0;
          break;
        case 17:
          strcpy (RemoteXY.text_1, "Pivot Sideways Right reverse");
          movePivotSidewaysRightReverse(speed);
          RemoteXY.motorSpeedGraph_var1 = 0;
          RemoteXY.motorSpeedGraph_var2 = 0;
          RemoteXY.motorSpeedGraph_var3 = -speed;
          RemoteXY.motorSpeedGraph_var4 = speed;
          break;
        case 18:
          strcpy (RemoteXY.text_1, "Pivot Sideways Left reverse");
          movePivotSidewaysLeftReverse(speed);
          RemoteXY.motorSpeedGraph_var1 = 0;
          RemoteXY.motorSpeedGraph_var2 = 0;
          RemoteXY.motorSpeedGraph_var3 = speed;
          RemoteXY.motorSpeedGraph_var4 = -speed;
          break;
        default:
          strcpy (RemoteXY.text_1, "Stop Test");
          stopMovement();
          move_modeDelay.finish();
          move_mode_numb = 0;
          move_mode = false;
          remotexy->delay(1000);
          stopMovement();
          break;
        }
      }
      break;
    //        Joystick Test      //
    case 1:
      x = RemoteXY.joystick_2_x;
      y = RemoteXY.joystick_2_y;
      rx = RemoteXY.joystick_1_x;
      RemoteXY.controllerGraph_var1 = x;
      RemoteXY.controllerGraph_var2 = y;
      RemoteXY.controllerGraph_var3 = rx;
      min_opperate_speed = 80 + RemoteXY.slider_2;
      max_speed = 155 + RemoteXY.slider_1;
      calculate_voltage(speed);
      sprintf (RemoteXY.text_2, "Min Speed: %i Max Speed: %i Volt: %f",min_opperate_speed, max_speed, voltage); 
      strcpy (RemoteXY.text_1, "Joystick Test");

      // activate joystick mode if swith on //
      if (RemoteXY.pushSwitch_1!=0)
      {
        RemoteXY.motorSpeedGraph_var1 = motor1.set_motor_omnidirectional(x, y, rx, -100, 100, min_opperate_speed, max_speed, 1);
        RemoteXY.motorSpeedGraph_var2 = motor2.set_motor_omnidirectional(x, y, rx, -100, 100, min_opperate_speed, max_speed, 2);
        RemoteXY.motorSpeedGraph_var3 = motor3.set_motor_omnidirectional(x, y, rx, -100, 100, min_opperate_speed, max_speed, 3);
        RemoteXY.motorSpeedGraph_var4 = motor4.set_motor_omnidirectional(x, y, rx, -100, 100, min_opperate_speed, max_speed, 4);
      }
      break;
  }
}