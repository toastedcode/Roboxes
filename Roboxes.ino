#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include "BlynkInterface.hpp"
#include "ConfigServer.hpp"
#include "EepromUtils.hpp"
#include "Roboxes.h"
#include "WifiUtils.hpp"

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "0c5a1145fe3c4cb693c9ef09c9eaf8c8";

enum RoboxState
{
   INIT,
   SETUP_WIFI,
   WIFI_CONFIG,
   SETUP_BLYNK,
   READY
};

RoboxState state = INIT;

void setup()
{
   Serial.begin(9600);

   Serial.println("*** Roboxes.com ***");
   Serial.println("");

   //Blynk.begin(auth, "TostNet", "t0stn3t5");
   //Blynk.begin(auth, "AndroidAP", "iamabug0929");

   EepromUtils::begin();

   MyRobox.begin();
}

void loop()
{
   if (state == INIT)
   {
      Serial.println("Setting up wifi");
      state = SETUP_WIFI;
      WifiUtils::setupWifi();
   }
   else if (state == SETUP_WIFI)
   {
       ConfigServer::run();
    
       if (WifiUtils::isConnected() == true)
       {
          Serial.println("Connecting to Blynk server.");
          state = SETUP_BLYNK;
           Blynk.config(ConfigServer::getDeviceConfig().authCode);
       }
       else
       {
          Serial.println("Waiting for wifi config.");
          state = WIFI_CONFIG;
          ConfigServer::begin();
       }
   }
   else if (state == WIFI_CONFIG)
   {
      ConfigServer::run();
   }
   else if (state == SETUP_BLYNK)
   {
      ConfigServer::run();
      Blynk.run();
      
      if (BlynkInterface::isConnected())
      {
        Serial.println("Robox is ready.");
         state = READY;
         
         BlynkInterface::lcdPrintf(0, 0, "Robox Online");
         BlynkInterface::lcdPrintf(0, 0, WiFi.localIP().toString().c_str());
      }
   }
   else if (state == READY)
   {
       ConfigServer::run();
       Blynk.run();
       MyRobox.run();
   }
}
