

#include <WiFi.h>  
#include "BLEDevice.h"

#include <RemoteXY.h>


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,1,0,1,0,27,0,10,13,2,
  1,0,9,9,46,46,6,7,50,50,
  2,31,88,0,65,4,62,16,31,31,
  14,62,35,35 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t button_1; // =1 if button pressed, else =0 

    // output variables
  uint8_t led_1_r; // =0..255 LED Red brightness 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)



/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////


CRemoteXY *remotexy;

void setup() 
{
 
  CRemoteXYComm_WiFi * wifi =  new CRemoteXYComm_WiFi (
    "Ichrich",                            // REMOTEXY_WIFI_SSID
    "12345678qQ@"                                 // REMOTEXY_WIFI_PASSWORD
  );
  
  remotexy = new CRemoteXY (RemoteXY_CONF_PROGMEM, &RemoteXY);
  
  remotexy->addConnection (new CRemoteXYStream_BLEDevice (
    "REMOTEXY"                               // REMOTEXY_BLUETOOTH_NAME 
  ));
  
  remotexy->addConnection (new CRemoteXYConnectionCloud ( wifi, 
    "cloud.remotexy.com",                     // REMOTEXY_CLOUD_SERVER 
    6376,                                     // REMOTEXY_CLOUD_PORT
    "6961fdaa88d48419dfb1cf9c5f3401eb"                // REMOTEXY_CLOUD_TOKEN
  ));
  
  
  
  // TODO you setup code
  
}

void loop() 
{ 
  remotexy->handler ();
  
  if (RemoteXY.button_1)  RemoteXY.led_1_r = 255;
  else RemoteXY.led_1_r = 0;
  
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay() 


}