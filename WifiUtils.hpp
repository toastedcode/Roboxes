#pragma once

#include "IPAddress.h"

class WifiUtils
{

public:

   static bool isConnected();
   
   static void setupWifi(
     const char* ssid,
     const char* password);

   static IPAddress getIpAddress();

};
