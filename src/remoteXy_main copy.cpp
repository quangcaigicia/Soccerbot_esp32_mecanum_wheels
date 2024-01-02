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
uint8_t RemoteXY_CONF[] =   // 531 bytes
  { 255,25,0,82,0,12,2,16,24,4,5,32,249,33,30,30,1,24,178,16,
  5,32,77,33,30,30,1,24,178,16,131,2,63,0,11,4,2,133,25,84,
  101,115,116,105,110,103,0,131,3,44,0,12,4,1,178,25,74,111,121,115,
  116,105,99,107,0,131,2,22,0,14,4,3,136,25,71,97,109,101,80,97,
  100,0,68,52,240,16,49,41,2,8,36,135,94,204,114,120,0,114,121,0,
  109,111,116,111,114,49,0,109,111,116,111,114,50,0,4,0,99,17,8,24,
  2,178,54,3,131,44,4,12,4,0,54,25,130,3,5,38,8,20,3,178,
  130,3,255,44,20,8,3,178,1,0,14,43,10,10,3,136,31,240,159,148,
  180,0,1,0,250,43,10,10,3,136,31,226,172,156,0,1,0,4,53,10,
  10,3,136,31,88,0,1,0,4,33,10,10,3,136,31,240,159,148,186,0,
  130,3,87,38,8,20,3,178,130,3,84,44,20,8,3,178,1,0,96,43,
  10,10,3,136,31,240,159,148,180,0,1,0,76,43,10,10,3,136,31,226,
  172,156,0,1,0,86,53,10,10,3,136,31,88,0,1,0,86,33,10,10,
  3,136,31,240,159,148,186,0,10,48,94,9,9,9,2,136,54,54,79,78,
  0,24,79,70,70,0,4,0,90,17,8,24,2,178,54,3,133,58,4,21,
  5,2,136,25,67,5,24,10,52,4,2,24,54,29,5,1,84,47,14,14,
  2,24,178,54,5,1,99,47,14,14,2,24,178,54,7,53,253,0,23,5,
  2,24,54,24,71,72,34,14,32,32,1,18,178,54,150,0,0,160,66,0,
  0,127,67,0,0,160,65,0,0,32,65,0,0,0,64,54,100,117,116,121,
  32,99,121,99,108,101,0,136,0,0,160,66,0,0,72,67,1,0,0,72,
  67,0,0,127,67,71,72,34,14,32,32,3,18,178,54,150,0,0,160,66,
  0,0,127,67,0,0,160,65,0,0,32,65,0,0,0,64,54,100,117,116,
  121,32,99,121,99,108,101,0,136,0,0,160,66,0,0,72,67,1,0,0,
  72,67,0,0,127,67,68,51,34,16,49,41,2,8,136,94,204,121,0,109,
  111,116,111,114,51,0,109,111,116,111,114,52,0,1,1,76,9,7,6,2,
  25,31,78,101,120,116,0,1,1,17,9,7,6,2,25,31,80,114,101,118,
  0,67,5,34,58,36,4,2,177,24,21 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  int8_t joystick_L_x; // from -100 to 100  
  int8_t joystick_L_y; // from -100 to 100  
  int8_t joystick_R_x; // from -100 to 100  
  int8_t joystick_R_y; // from -100 to 100  
  int8_t slider_test_1; // =0..100 slider position 
  uint8_t select_1; // =0 if select position A, =1 if position B, =2 if position C, ... 
  uint8_t button_L_circle; // =1 if button pressed, else =0 
  uint8_t button_L_square; // =1 if button pressed, else =0 
  uint8_t button_L_x; // =1 if button pressed, else =0 
  uint8_t button_L_triangle; // =1 if button pressed, else =0 
  uint8_t button_R_circle; // =1 if button pressed, else =0 
  uint8_t button_R_square; // =1 if button pressed, else =0 
  uint8_t button_R_x; // =1 if button pressed, else =0 
  uint8_t button_R_triangle; // =1 if button pressed, else =0 
  uint8_t pushSwitch_test_1; // =1 if state is ON, else =0 
  int8_t slider_test_2; // =0..100 slider position 
  uint8_t select_test_1; // =0 if select position A, =1 if position B, =2 if position C, ... 
  int8_t joystick_test_2_x; // from -100 to 100  
  int8_t joystick_test_2_y; // from -100 to 100  
  int8_t joystick_test_1_x; // from -100 to 100  
  int8_t joystick_test_1_y; // from -100 to 100  
  int16_t edit_test_1;  // 32767.. +32767 
  uint8_t button_next_test; // =1 if button pressed, else =0 
  uint8_t button_prev_test; // =1 if button pressed, else =0 

    // output variables
  float motorSpeedGraph_test_2_var1;
  float motorSpeedGraph_test_2_var2;
  float motorSpeedGraph_test_2_var3;
  float motorSpeedGraph_test_2_var4;
  char text_test_1[29];  // string UTF8 end zero 
  int16_t instrument_1;  // from 80 to 255 
  int16_t instrument_2;  // from 80 to 255 
  float motorSpeedGraph_test_1_var1;
  float motorSpeedGraph_test_1_var2;
  float motorSpeedGraph_test_1_var3;
  char text_test_2[21];  // string UTF8 end zero 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)


/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////


#include <motor.h>

int speed{0};
int x{0}, y{0}, rx{0};
Motor motor1(17, 5, 16, 1);  // Direction pin and pwm channel for motor A
Motor motor2(27, 26, 14, 2);  // Direction pin and pwm channel for motor B
Motor motor3(19, 18, 21, 3); // Direction pin and pwm channel for motor C
Motor motor4(23, 22, 25, 4); // Direction pin and pwm channel for motor C


#include <millisDelay.h>
bool move_mode{false};
int8_t move_mode_numb{0};
millisDelay move_modeDelay;

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
  Serial.begin(115200);
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

/////////////////////////////////////////////
//           END Motor Functions           //
/////////////////////////////////////////////

void reset_remotexy_indicators()
{
  RemoteXY.motorSpeedGraph_test_1_var1 = 0;
  RemoteXY.motorSpeedGraph_test_1_var2 = 0;
  RemoteXY.motorSpeedGraph_test_1_var3 = 0;
  RemoteXY.motorSpeedGraph_test_2_var1 = 0;
  RemoteXY.motorSpeedGraph_test_2_var2 = 0;
  RemoteXY.motorSpeedGraph_test_2_var3 = 0;
  RemoteXY.motorSpeedGraph_test_2_var4 = 0;
  sprintf (RemoteXY.text_test_2, "");
}

void loop() 
{
  remotexy->handler ();
  switch (RemoteXY.select_1)
  {
  //           GamePad           //
  case 0:
    break;
  //              Joystick              //
  case 1:
    break;
  //              Testing             //
  case 2:
    //        Reset graph       //
    if (RemoteXY.pushSwitch_test_1!=1)
    {
      reset_remotexy_indicators();
    }
    
    switch (RemoteXY.select_test_1)
    {
    //              Movement Test               //
    case 0:
      if(RemoteXY.pushSwitch_test_1!=1 && move_mode == false)
      {
        strcpy (RemoteXY.text_test_1, "Speed Test");
      }

      if (RemoteXY.pushSwitch_test_1!=1 && move_mode==true) 
        {
          strcpy (RemoteXY.text_test_1, "Stop Test");
          stopMovement();
          move_modeDelay.finish();
          move_mode_numb = 0;
          move_mode = false;
          remotexy->delay(1000);
        }
      
      speed = RemoteXY.slider_test_1 + RemoteXY.slider_test_2 + RemoteXY.joystick_test_1_y + RemoteXY.joystick_test_2_y;
      sprintf (RemoteXY.text_test_2, "Speed is %d", speed); 


      if(RemoteXY.pushSwitch_test_1!=0)
      {
        move_mode = true;
        if (move_modeDelay.remaining()==0)
        {
          move_modeDelay.start(3000);
          move_mode_numb += 1;
        }

        if (RemoteXY.edit_test_1!=0) // Using only one switch input
        {
          move_mode_numb = 0;
        }

        if (RemoteXY.button_next_test!=0)
        {
          move_mode_numb += 1;
          move_modeDelay.restart();
          remotexy->delay(200);
        }
        if (RemoteXY.button_prev_test!=0)
        {
          move_mode_numb -= 1;
          move_modeDelay.restart();
          remotexy->delay(200); 
        }

        switch (move_mode_numb | RemoteXY.edit_test_1)
        {
        case 1:
          strcpy (RemoteXY.text_test_1, "Forward");
          moveForward(speed);
          RemoteXY.motorSpeedGraph_test_2_var3 = speed;
          RemoteXY.motorSpeedGraph_test_2_var4 = speed;
          RemoteXY.motorSpeedGraph_test_1_var2 = speed;
          RemoteXY.motorSpeedGraph_test_1_var3 = speed;
          break;
        case 2:
          strcpy (RemoteXY.text_test_1, "Backward");
          moveBackward(speed);
          RemoteXY.motorSpeedGraph_test_2_var3 = -speed;
          RemoteXY.motorSpeedGraph_test_2_var4 = -speed;
          RemoteXY.motorSpeedGraph_test_1_var2 = -speed;
          RemoteXY.motorSpeedGraph_test_1_var3 = -speed;
          break;
        case 3:
          strcpy (RemoteXY.text_test_1, "Sideways Right");
          moveSidewaysRight(speed);
          RemoteXY.motorSpeedGraph_test_2_var3 = speed;
          RemoteXY.motorSpeedGraph_test_2_var4 = -speed;
          RemoteXY.motorSpeedGraph_test_1_var2 = -speed;
          RemoteXY.motorSpeedGraph_test_1_var3 = speed;
          break;
        case 4:
          strcpy (RemoteXY.text_test_1, "Sideways Left");
          moveSidewaysLeft(speed);
          RemoteXY.motorSpeedGraph_test_2_var3 = -speed;
          RemoteXY.motorSpeedGraph_test_2_var4 = speed;
          RemoteXY.motorSpeedGraph_test_1_var2 = speed;
          RemoteXY.motorSpeedGraph_test_1_var3 = -speed;
          break;
        case 5:
          strcpy (RemoteXY.text_test_1, "Forward Right 45°");
          moveDiagonalForwardRight(speed);
          RemoteXY.motorSpeedGraph_test_2_var3 = speed;
          RemoteXY.motorSpeedGraph_test_2_var4 = 0;
          RemoteXY.motorSpeedGraph_test_1_var2 = 0;
          RemoteXY.motorSpeedGraph_test_1_var3 = speed;
          break;
        case 6:
          strcpy (RemoteXY.text_test_1, "Forward Left 45°");
          moveDiagonalForwardLeft(speed);
          RemoteXY.motorSpeedGraph_test_2_var3 = 0;
          RemoteXY.motorSpeedGraph_test_2_var4 = speed;
          RemoteXY.motorSpeedGraph_test_1_var2 = speed;
          RemoteXY.motorSpeedGraph_test_1_var3 = 0;
          break;
        case 7:
          strcpy (RemoteXY.text_test_1, "Backward Right 45°");
          moveDiagonalBackwardRight(speed);
          RemoteXY.motorSpeedGraph_test_2_var3 = 0;
          RemoteXY.motorSpeedGraph_test_2_var4 = -speed;
          RemoteXY.motorSpeedGraph_test_1_var2 = -speed;
          RemoteXY.motorSpeedGraph_test_1_var3 = 0;
          break;
        case 8:
          strcpy (RemoteXY.text_test_1, "Backward Left 45°");
          moveDiagonalBackwardLeft(speed);
          RemoteXY.motorSpeedGraph_test_2_var3 = -speed;
          RemoteXY.motorSpeedGraph_test_2_var4 = 0;
          RemoteXY.motorSpeedGraph_test_1_var2 = 0;
          RemoteXY.motorSpeedGraph_test_1_var3 = -speed;
          break;
        case 9:
          strcpy (RemoteXY.text_test_1, "Pivot Forward Right");
          movePivotForwardRight(speed);
          RemoteXY.motorSpeedGraph_test_2_var3 = speed;
          RemoteXY.motorSpeedGraph_test_2_var4 = 0;
          RemoteXY.motorSpeedGraph_test_1_var2 = speed;
          RemoteXY.motorSpeedGraph_test_1_var3 = 0;
          break;
        case 10:
          strcpy (RemoteXY.text_test_1, "Pivot Forward Left");
          movePivotForwardLeft(speed);
          RemoteXY.motorSpeedGraph_test_2_var3 = 0;
          RemoteXY.motorSpeedGraph_test_2_var4 = speed;
          RemoteXY.motorSpeedGraph_test_1_var2 = 0;
          RemoteXY.motorSpeedGraph_test_1_var3 = speed;
          break;
        case 11:
          strcpy (RemoteXY.text_test_1, "Pivot Backward Right");
          movePivotBackwardRight(speed);
          RemoteXY.motorSpeedGraph_test_2_var3 = -speed;
          RemoteXY.motorSpeedGraph_test_2_var4 = 0;
          RemoteXY.motorSpeedGraph_test_1_var2 = -speed;
          RemoteXY.motorSpeedGraph_test_1_var3 = 0;
          break;
        case 12:
          strcpy (RemoteXY.text_test_1, "Pivot Backward Left");
          movePivotBackwardLeft(speed);
          RemoteXY.motorSpeedGraph_test_2_var3 = 0;
          RemoteXY.motorSpeedGraph_test_2_var4 = -speed;
          RemoteXY.motorSpeedGraph_test_1_var2 = 0;
          RemoteXY.motorSpeedGraph_test_1_var3 = -speed;
          break;
        case 13:
          strcpy (RemoteXY.text_test_1, "Rotate Right");
          moveRotateRight(speed);
          RemoteXY.motorSpeedGraph_test_2_var3 = speed;
          RemoteXY.motorSpeedGraph_test_2_var4 = -speed;
          RemoteXY.motorSpeedGraph_test_1_var2 = speed;
          RemoteXY.motorSpeedGraph_test_1_var3 = -speed;
          break;
        case 14:
          strcpy (RemoteXY.text_test_1, "Rotate Left");
          moveRotateLeft(speed);
          RemoteXY.motorSpeedGraph_test_2_var3 = -speed;
          RemoteXY.motorSpeedGraph_test_2_var4 = speed;
          RemoteXY.motorSpeedGraph_test_1_var2 = -speed;
          RemoteXY.motorSpeedGraph_test_1_var3 = speed;
          break;
        case 15:
          strcpy (RemoteXY.text_test_1, "Pivot Sideways Right");
          movePivotSidewaysRight(speed);
          RemoteXY.motorSpeedGraph_test_2_var3 = speed;
          RemoteXY.motorSpeedGraph_test_2_var4 = -speed;
          RemoteXY.motorSpeedGraph_test_1_var2 = 0;
          RemoteXY.motorSpeedGraph_test_1_var3 = 0;
          break;
        case 16:
          strcpy (RemoteXY.text_test_1, "Pivot Sideways Left");
          movePivotSidewaysLeft(speed);
          RemoteXY.motorSpeedGraph_test_2_var3 = -speed;
          RemoteXY.motorSpeedGraph_test_2_var4 = speed;
          RemoteXY.motorSpeedGraph_test_1_var2 = 0;
          RemoteXY.motorSpeedGraph_test_1_var3 = 0;
          break;
        case 17:
          strcpy (RemoteXY.text_test_1, "Pivot Sideways Right reverse");
          movePivotSidewaysRightReverse(speed);
          RemoteXY.motorSpeedGraph_test_2_var3 = 0;
          RemoteXY.motorSpeedGraph_test_2_var4 = 0;
          RemoteXY.motorSpeedGraph_test_1_var2 = -speed;
          RemoteXY.motorSpeedGraph_test_1_var3 = speed;
          break;
        case 18:
          strcpy (RemoteXY.text_test_1, "Pivot Sideways Left reverse");
          movePivotSidewaysLeftReverse(speed);
          RemoteXY.motorSpeedGraph_test_2_var3 = 0;
          RemoteXY.motorSpeedGraph_test_2_var4 = 0;
          RemoteXY.motorSpeedGraph_test_1_var2 = speed;
          RemoteXY.motorSpeedGraph_test_1_var3 = -speed;
          break;
        default:
          strcpy (RemoteXY.text_test_1, "Stop Test");
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
      strcpy (RemoteXY.text_test_1, "Joystick Test");
      x = RemoteXY.joystick_test_2_x;
      y = RemoteXY.joystick_test_2_y;
      rx = RemoteXY.joystick_test_1_x;
      RemoteXY.motorSpeedGraph_test_1_var1 = x;
      RemoteXY.motorSpeedGraph_test_1_var2 = y;
      RemoteXY.motorSpeedGraph_test_2_var1 = rx;
      if (RemoteXY.pushSwitch_test_1!=0)
      {
        RemoteXY.motorSpeedGraph_test_1_var2 = motor3.set_motor_omnidirectional(x, y, rx, 0, -100, 100, 85, -255, 255, 1);
        RemoteXY.motorSpeedGraph_test_1_var3 = motor4.set_motor_omnidirectional(x, y, rx, 0, -100, 100, 85, -255, 255, 2);
        RemoteXY.motorSpeedGraph_test_2_var3 = motor1.set_motor_omnidirectional(x, y, rx, 0, -100, 100, 85, -255, 255, 3);
        RemoteXY.motorSpeedGraph_test_2_var4 = motor2.set_motor_omnidirectional(x, y, rx, 0, -100, 100, 85, -255, 255, 4);
      }
      break;
    default:
      strcpy (RemoteXY.text_test_1, "Error!!!");
      break;
    }
  }
}