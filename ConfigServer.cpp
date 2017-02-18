#include <FS.h>

#include "ConfigServer.hpp"
#include "EepromUtils.hpp"
#include "WifiUtils.hpp"

// **************************************************************************
//                                Constants
// **************************************************************************

const byte DNS_PORT = 53;

const byte HTTP_PORT = 80;

// **************************************************************************
//                                Static members
// **************************************************************************

ESP8266WebServer ConfigServer::server(HTTP_PORT);

DNSServer ConfigServer::dnsServer;

// **************************************************************************
//                                 Public
// **************************************************************************

void ConfigServer::begin()
{
   SPIFFS.begin();

   dnsServer.start(DNS_PORT, "*", WifiUtils::getIpAddress());

   Serial.printf("DNS server started.  Directing all traffic to %s\n", WifiUtils::getIpAddress().toString().c_str());
  
   // Setup  handlers.
   //server.on("/", ConfigServer::handleRoot);  // TODO: What about this?
   //server.onNotFound(ConfigServer::handleNotFound);  // TODO: What about this?
   server.onNotFound(ConfigServer::handleRoot);
  
   server.begin();

   Serial.println("HTTP server started.");
}

void ConfigServer::run()
{
   dnsServer.processNextRequest();
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
   BlynkConfig blynkConfig;
   EepromUtils::getDeviceConfig(deviceConfig);
   EepromUtils::getWifiConfig(wifiConfig);
   EepromUtils::getBlynkConfig(blynkConfig);

   Serial.println("Current config:");
   Serial.printf("   Device name: %s\n", deviceConfig.deviceName);
   Serial.printf("   SSID: %s\n", wifiConfig.ssid);
   Serial.printf("   Password: %s\n", wifiConfig.password);
   Serial.printf("   Blynk server: %s\n", blynkConfig.server);
   Serial.printf("   Authorization code: %s\n", blynkConfig.authCode);
  
   String newDeviceName = server.arg("id");
   String newSsid = server.arg("ssid");
   String newPassword = server.arg("password");
   String newServer = server.arg("server");
   String newAuthCode = server.arg("authcode");

   bool deviceConfigChanged = false;
   bool wifiConfigChanged = false;
   bool blynkConfigChanged = false;

   if (server.hasArg("id") && 
       (strncmp(newDeviceName.c_str(), deviceConfig.deviceName, DEVICE_NAME_SIZE) != 0))
   {
      strncpy(deviceConfig.deviceName, newDeviceName.c_str(), DEVICE_NAME_SIZE);   
      deviceConfigChanged = true;
   }

   if (deviceConfigChanged == true)
   {
      Serial.printf("Updating device config [%s].\n", deviceConfig.deviceName);
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

   if ((server.hasArg("server") && 
       (strncmp(newServer.c_str(), blynkConfig.server, SERVER_NAME_SIZE) != 0)))
   {
      strncpy(blynkConfig.server, newServer.c_str(), SERVER_NAME_SIZE);    
      blynkConfigChanged = true;
   }

   if (server.hasArg("authcode") && 
       (strncmp(newAuthCode.c_str(), blynkConfig.authCode, AUTH_CODE_SIZE) != 0))
   {
      strncpy(blynkConfig.authCode, newAuthCode.c_str(), AUTH_CODE_SIZE);    
      blynkConfigChanged = true;
   }

   if (blynkConfigChanged == true)
   {
      Serial.printf("Updating blynk config [%s, %s].\n", blynkConfig.server, blynkConfig.authCode);
      EepromUtils::setBlynkConfig(blynkConfig);
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
      content.replace("%ssid", wifiConfig.ssid);
      content.replace("%password", wifiConfig.password);
      content.replace("%server", blynkConfig.server);
      content.replace("%authcode", blynkConfig.authCode);

      if (deviceConfigChanged || wifiConfigChanged || blynkConfigChanged)
      {
         Serial.println("New config:"); 
         Serial.printf("   Device name: %s\n", deviceConfig.deviceName);
         Serial.printf("   SSID: %s\n", wifiConfig.ssid);
         Serial.printf("   Password: %s\n", wifiConfig.password);
         Serial.printf("   Blynk server: %s\n", blynkConfig.server);
         Serial.printf("   Authorization code: %s\n", blynkConfig.authCode);
   
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
