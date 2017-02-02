#include <FS.h>

#include "ConfigServer.hpp"
#include "EepromUtils.hpp"

// **************************************************************************
//                                Static members
// **************************************************************************

ESP8266WebServer ConfigServer::server(80);

// **************************************************************************
//                                 Public
// **************************************************************************

void ConfigServer::begin()
{
   SPIFFS.begin();
  
   // Setup  handlers.
   server.on("/", handleRoot);
   server.onNotFound(handleNotFound);
  
   server.begin();
  
   Serial.println("HTTP server started.");
}

void ConfigServer::run()
{
   server.handleClient();
}

// **************************************************************************
//                                 Private
// **************************************************************************

void ConfigServer::handleRoot()
{
   // Load config from EEPROM.
   DeviceConfig deviceConfig;
   WifiConfig wifiConfig;
   EepromUtils::getDeviceConfig(deviceConfig);
   EepromUtils::getWifiConfig(wifiConfig);

   Serial.println("Current config:");
   Serial.printf("   Device name: %s\n", deviceConfig.deviceName);
   Serial.printf("   Authorization code: %s\n", deviceConfig.authCode);
   Serial.printf("   SSID: %s\n", wifiConfig.ssid);
   Serial.printf("   Password: %s\n", wifiConfig.password);
  
   String newDeviceName = server.arg("id");
   String newAuthCode = server.arg("authcode");
   String newSsid = server.arg("ssid");
   String newPassword = server.arg("password");

   bool deviceConfigChanged = false;
   bool wifiConfigChanged = false;

   if (server.hasArg("id") && 
       (strncmp(newDeviceName.c_str(), deviceConfig.deviceName, DEVICE_NAME_SIZE) != 0))
   {
      strncpy(deviceConfig.deviceName, newDeviceName.c_str(), DEVICE_NAME_SIZE);   
      deviceConfigChanged = true;
   }

   if (server.hasArg("authcode") && 
       (strncmp(newAuthCode.c_str(), deviceConfig.authCode, AUTH_CODE_SIZE) != 0))
   {
      strncpy(deviceConfig.authCode, newAuthCode.c_str(), AUTH_CODE_SIZE);    
      deviceConfigChanged = true;
   }

   if (deviceConfigChanged == true)
   {
      Serial.printf("Updating device config [%s, %s].\n", deviceConfig.deviceName, deviceConfig.authCode);
      EepromUtils::setDeviceConfig(deviceConfig);
   }
   
   if (server.hasArg("ssid") && 
       (strncmp(newSsid.c_str(), wifiConfig.ssid, SSID_SIZE) != 0))
   {
      strncpy(wifiConfig.ssid, newSsid.c_str(), SSID_SIZE);
      wifiConfigChanged = true;
   }

   if (server.hasArg("password") && 
       (strncmp(newSsid.c_str(), wifiConfig.password, PASSWORD_SIZE) != 0))
   {
      strncpy(wifiConfig.password, newPassword.c_str(), PASSWORD_SIZE);   
      wifiConfigChanged = true;
   }
  
   if (wifiConfigChanged == true)
   {
      Serial.printf("Updating wifi config [%s, %s].\n", wifiConfig.ssid, wifiConfig.password);
      EepromUtils::setWifiConfig(wifiConfig);
   }
   
   File file = SPIFFS.open("/config.html", "r");
   if (!file)
   {
      Serial.println("file open failed");
      server.send(404, "text/plain", "File not found.");
   }
   else
   {
      Serial.println("Opened file.");

      //server.streamFile(file, "text/html");

      String content = file.readString();

      content.replace("%name", deviceConfig.deviceName);
      content.replace("%authcode", deviceConfig.authCode);
      content.replace("%ssid", wifiConfig.ssid);
      content.replace("%password", wifiConfig.password);

      if (deviceConfigChanged || wifiConfigChanged)
      {
         Serial.println("New config:"); 
         Serial.printf("   Device name: %s\n", deviceConfig.deviceName);
         Serial.printf("   Authorization code: %s\n", deviceConfig.authCode);
         Serial.printf("   SSID: %s\n", wifiConfig.ssid);
         Serial.printf("   Password: %s\n", wifiConfig.password);
   
         content.replace("%info", "All changes saved.  Resetting Robox to apply changes.");
      }
      else
      {
         content.replace("%info", "All changes saved.");
      }

      server.send(200, "text/html", content);

      file.close();
   }

   if (deviceConfigChanged || wifiConfigChanged)
   {
      ESP.restart();
   }
}

void ConfigServer::handleNotFound()
{
   server.send(404, "text/plain", "File not found.");
}
