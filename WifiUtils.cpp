#include <>ESP8266WiFi.h>

#include "EepromUtils.hpp"

const String WIFI_AP_SSID = "ROBOXES_AP";

const int CONNECTION_TIMEOUT = 10;

void WifiUtils::setupWifi()
{
   WifiConfig wifiConfig = ConfigServer::getWifiConfig();

   Logger::logDebug("Connecting to Wifi network %s", wifiConfig.ssid);

   WiFi.mode(WIFI_STA);
   WiFi.begin(wifiConfig.ssid, wifiConfig.password);

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
      Serial.printf("success!  Connected to %s at %s\n", wifiConfig.ssid, WiFi.localIP().toString().c_str());
   }
   else
   {
      Serial.printf("failure!  Could not connect to %s\n", wifiConfig.ssid);

      WiFi.mode(WIFI_AP);
      WiFi.softAP(WIFI_AP_SSID.c_str(), "");
   }
}
