#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include "BlynkInterface.hpp"
#include "ConfigServer.hpp"
#include "EepromUtils.hpp"
#include "Roboxes.h"
#include "WifiUtils.hpp"

char* authCode = "0c5a1145fe3c4cb693c9ef09c9eaf8c8";

enum RoboxState
{
   INIT,
   SETUP_WIFI,
   WIFI_CONFIG,
   SETUP_BLYNK,
   READY
};

WifiConfig wifiConfig;
DeviceConfig deviceConfig;

RoboxState state = INIT;

void setup()
{
   Serial.begin(9600);

   Serial.println("*** Roboxes.com ***");
   Serial.println("");
}

void loop()
{
   if (state == INIT)
   {
      Serial.println("Setting up wifi");
      state = SETUP_WIFI;
      
      EepromUtils::begin();
      EepromUtils::getWifiConfig(wifiConfig);
      EepromUtils::getDeviceConfig(deviceConfig);

      Serial.println("Device config:"); 
      Serial.printf("   Device name: %s\n", deviceConfig.deviceName);
      Serial.printf("   Authorization code: %s\n", deviceConfig.authCode);
      Serial.printf("   SSID: %s\n", wifiConfig.ssid);
      Serial.printf("   Password: %s\n", wifiConfig.password);
      
      WifiUtils::setupWifi(wifiConfig.ssid, wifiConfig.password);
   }
   else if (state == SETUP_WIFI)
   {
      if (WifiUtils::isConnected() == true)
      {
         Serial.printf("Connecting to Blynk server. (auth code = \"%s\")\n", deviceConfig.authCode);
         state = SETUP_BLYNK;
         Blynk.config(deviceConfig.authCode);
      }
      else
      {
         Serial.println("Waiting for wifi config.");
         state = WIFI_CONFIG;
      }

      ConfigServer::begin();
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
         MyRobox.begin();
         
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
