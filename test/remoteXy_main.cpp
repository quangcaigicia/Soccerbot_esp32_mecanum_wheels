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
uint8_t RemoteXY_CONF[] =   // 385 bytes
  { 255,23,0,47,0,122,1,16,24,4,5,32,249,33,30,30,1,24,178,16,
  5,32,77,33,30,30,1,24,178,16,71,72,34,14,32,32,0,18,178,54,
  150,0,0,160,66,0,0,127,67,0,0,160,65,0,0,32,65,0,0,0,
  64,54,100,117,116,121,32,99,121,99,108,101,0,136,0,0,160,66,0,0,
  72,67,1,0,0,72,67,0,0,127,67,131,2,63,0,11,4,2,133,25,
  84,101,115,116,105,110,103,0,131,3,44,0,12,4,1,178,25,74,111,121,
  115,116,105,99,107,0,131,2,22,0,14,4,3,136,25,71,97,109,101,80,
  97,100,0,68,20,241,5,49,57,2,8,36,135,94,204,4,0,99,17,8,
  24,2,178,54,3,131,44,4,12,4,0,54,25,130,3,5,38,8,20,3,
  178,130,3,255,44,20,8,3,178,1,0,14,43,10,10,3,136,31,240,159,
  148,180,0,1,0,250,43,10,10,3,136,31,226,172,156,0,1,0,4,53,
  10,10,3,136,31,88,0,1,0,4,33,10,10,3,136,31,240,159,148,186,
  0,130,3,87,38,8,20,3,178,130,3,84,44,20,8,3,178,1,0,96,
  43,10,10,3,136,31,240,159,148,180,0,1,0,76,43,10,10,3,136,31,
  226,172,156,0,1,0,86,53,10,10,3,136,31,88,0,1,0,86,33,10,
  10,3,136,31,240,159,148,186,0,10,48,94,9,9,9,2,136,54,54,79,
  78,0,24,79,70,70,0,4,0,90,17,8,24,2,178,54,3,133,37,56,
  25,6,2,136,25,67,5,36,47,38,9,0,24,54,29,5,3,99,44,19,
  19,2,24,178,54,5,3,79,44,19,19,2,24,178,54,7,52,86,0,23,
  5,2,24,54,24 };
  
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
  int8_t joystick_test_1_x; // from -100 to 100  
  int8_t joystick_test_1_y; // from -100 to 100  
  int8_t joystick_test_2_x; // from -100 to 100  
  int8_t joystick_test_2_y; // from -100 to 100  
  int16_t edit_test_1;  // 32767.. +32767 

  // output variables
  int16_t instrument_1;  // from 80 to 255 
  float onlineGraph_test_1_var1;
  float onlineGraph_test_1_var2;
  float onlineGraph_test_1_var3;
  float onlineGraph_test_1_var4;
  char text_test_1[29];  // string UTF8 end zero 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)


/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////


#include <motor.h>

int speed{0};

Motor motor1(17, 5, 16, 1);  // Direction pin and pwm channel for motor A
Motor motor2(27, 26, 14, 2);  // Direction pin and pwm channel for motor B
Motor motor3(19, 18, 21, 3); // Direction pin and pwm channel for motor C
Motor motor4(23, 22, 25, 4); // Direction pin and pwm channel for motor C


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
  // TODO you setup code
  
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

void display_speed(){
  speed = RemoteXY.slider_test_1 + RemoteXY.slider_test_2 + RemoteXY.joystick_test_1_x +RemoteXY.joystick_test_1_y + RemoteXY.joystick_test_2_x +  RemoteXY.joystick_test_2_y;
RemoteXY.instrument_1 = speed;
    RemoteXY.onlineGraph_test_1_var1 = speed;
}

void loop() 
{


  remotexy->handler ();
  switch (RemoteXY.select_1)
  {
  //           Gamepad               //
  case 0:
     RemoteXY.instrument_1 = RemoteXY.joystick_L_x + RemoteXY.joystick_L_y;
    break;
  //           Joystick              //
  case 1:
  break;
  //           Testing               //
  case 2:
  display_speed();
  switch (RemoteXY.select_test_1)
  {
  case 0:
    strcpy (RemoteXY.text_test_1, "Movement Test");
    if(RemoteXY.pushSwitch_test_1!=0){
      for (int8_t i = 1; i <= 19; i++)
      {
        remotexy->handler();
        display_speed();
        if (RemoteXY.pushSwitch_test_1!=1)
        {
          strcpy (RemoteXY.text_test_1, "Stop Test");
          stopMovement();
          remotexy->delay(3000);
          break;
        }
          
        if (RemoteXY.edit_test_1==0)
        {
            remotexy->delay(1000);
      strcpy (RemoteXY.text_test_1, "3");
      remotexy->delay(1000);
      strcpy (RemoteXY.text_test_1, "2");
      remotexy->delay(1000);
      strcpy (RemoteXY.text_test_1, "1");
      remotexy->delay(1000);
          stopMovement();
          goto for_loop;
        }
        
        
        if (RemoteXY.edit_test_1==1)
        {
          i = 1;
        }
        
    
    for_loop: 
    if(i == 1){
    strcpy (RemoteXY.text_test_1, "Forward");
    moveForward(speed);
    }
    else if (i == 2){
    strcpy (RemoteXY.text_test_1, "Backward");
    moveBackward(speed);
    }
    else if (i == 3){
    strcpy (RemoteXY.text_test_1, "Sideways Right");
     moveSidewaysRight(speed);
    }
    else if (i == 4){
     strcpy (RemoteXY.text_test_1, "Sideways Left");
    moveSidewaysLeft(speed);
    }
  else if (i==5){
    strcpy (RemoteXY.text_test_1, "Move Forward");
moveDiagonalForwardRight(speed);}
else if ( i == 6){
strcpy (RemoteXY.text_test_1, "Forward");
moveDiagonalForwardLeft(speed);}
else if ( i == 7){
strcpy (RemoteXY.text_test_1, "Forward");
moveDiagonalBackwardRight(speed);}
else if ( i == 8){
strcpy (RemoteXY.text_test_1, "Forward");
moveDiagonalBackwardLeft(speed);}
else if ( i == 9){
strcpy (RemoteXY.text_test_1, "Forward");
movePivotForwardRight(speed);}
else if ( i == 10){
strcpy (RemoteXY.text_test_1, "Forward");
movePivotForwardLeft(speed);}
else if ( i == 11){
strcpy (RemoteXY.text_test_1, "Forward");
moveDiagonalBackwardRight(speed);}
else if ( i == 12){
strcpy (RemoteXY.text_test_1, "Forward");
moveDiagonalBackwardLeft(speed);}
else if ( i == 13){
strcpy (RemoteXY.text_test_1, "Forward");
moveRotateRight(speed);}
else if ( i == 14){
strcpy (RemoteXY.text_test_1, "Forward");
moveRotateLeft(speed);}
else if ( i == 15){
strcpy (RemoteXY.text_test_1, "Forward");
movePivotSidewaysRight(speed);}
else if ( i == 16){
strcpy (RemoteXY.text_test_1, "Forward");
movePivotSidewaysLeft(speed);}
else if ( i == 17){
strcpy (RemoteXY.text_test_1, "Forward");
movePivotSidewaysRightReverse(speed);}
else if ( i == 18){
strcpy (RemoteXY.text_test_1, "Forward");
movePivotSidewaysLeftReverse(speed);}

      }}
    break;
  
  case 1:
  break;

  default:
  break;
  
  }
  }

   

 
  
 
  
  

  

  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay() 


}