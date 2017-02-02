#pragma once

class WifiUtils
{

public:

   static bool isConnected();
   
   static void setupWifi(
     const char* ssid,
     const char* password);

};
