#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include "BlynkInterface.hpp"
#include "ConfigServer.hpp"
#include "EepromUtils.hpp"
#include "FactoryReset.hpp"
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
BlynkConfig blynkConfig;

RoboxState state = INIT;

void setup()
{
   Serial.begin(9600);

   Serial.println("*** Roboxes.com ***");
   Serial.println("");
}

void loop()
{
   FactoryReset::run();
   
   if (state == INIT)
   {
      Serial.println("Setting up wifi");
      state = SETUP_WIFI;
      
      EepromUtils::begin();
      EepromUtils::getWifiConfig(wifiConfig);
      EepromUtils::getDeviceConfig(deviceConfig);
      EepromUtils::getBlynkConfig(blynkConfig);

      Serial.println("Device config:"); 
      Serial.printf("   Device name: %s\n", deviceConfig.deviceName);
      Serial.printf("   SSID: %s\n", wifiConfig.ssid);
      Serial.printf("   Password: %s\n", wifiConfig.password);
      Serial.printf("   Blynk server: %s\n", blynkConfig.server);
      Serial.printf("   Authorization code: %s\n", blynkConfig.authCode);
      
      WifiUtils::setupWifi(wifiConfig.ssid, wifiConfig.password);
   }
   else if (state == SETUP_WIFI)
   {
      if (WifiUtils::isConnected() == true)
      {
         if (strlen(blynkConfig.server) == 0)
         {
            strncpy(blynkConfig.server, BLYNK_DEFAULT_DOMAIN, SERVER_NAME_SIZE); 
         }
      
         Serial.printf("Connecting to Blynk server. (server = \"%s\", auth code = \"%s\")\n", blynkConfig.server, blynkConfig.authCode);
         state = SETUP_BLYNK;
         Blynk.config(blynkConfig.authCode, blynkConfig.server, BLYNK_DEFAULT_PORT);
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

         BlynkInterface::lcdClear();
         BlynkInterface::lcdPrintf(0, 0, deviceConfig.deviceName);
         BlynkInterface::lcdPrintf(0, 1, WiFi.localIP().toString().c_str());

         Blynk.syncAll();
      }
   }
   else if (state == READY)
   {
      ConfigServer::run();
      Blynk.run();
      MyRobox.run();
   }
}
