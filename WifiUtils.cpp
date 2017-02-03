#include <ESP8266WiFi.h>

#include "WifiUtils.hpp"

const String WIFI_AP_SSID = "ROBOXES_AP";

const IPAddress AP_IP_ADDRESS(192, 168, 1, 1);

const IPAddress AP_GATEWAY(192, 168, 1, 1);

const IPAddress AP_SUBNET(255, 255, 255, 0);

const int CONNECTION_TIMEOUT = 10;

bool WifiUtils::isConnected()
{
   return (WiFi.status() == WL_CONNECTED);
}

void WifiUtils::setupWifi(
  const char* ssid,
  const char* password)
{
   Serial.printf("Connecting to Wifi network %s", ssid);

   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, password);

   int secondsToConnect = 0;

   // Wait until the connection is made, or until we timeout.
   while ((WiFi.status() != WL_CONNECTED)&&
          (secondsToConnect < CONNECTION_TIMEOUT))
   {
      delay(1000);
      secondsToConnect++;
      Serial.print(" .");
   }

   if (WiFi.status() == WL_CONNECTED)
   {
      Serial.println("success!");
      Serial.printf("Connected to %s at %s\n", ssid, WiFi.localIP().toString().c_str());
   }
   else
   {
      Serial.printf("failure!  Could not connect to %s\n", ssid);

      Serial.printf("Starting access point %s\n", WIFI_AP_SSID.c_str());

      WiFi.mode(WIFI_AP);
      WiFi.softAPConfig(AP_IP_ADDRESS, AP_GATEWAY, AP_SUBNET);
      WiFi.softAP(WIFI_AP_SSID.c_str(), "");

      Serial.printf("Hosting AP at %s\n", WiFi.softAPIP().toString().c_str());
   }
}

IPAddress WifiUtils::getIpAddress()
{
   IPAddress ipAddress;
   
   if (WiFi.getMode() == WIFI_AP)
   {
      ipAddress = WiFi.softAPIP();
   }
   else
   {
      ipAddress = WiFi.localIP();
   }

   return (ipAddress);
}

