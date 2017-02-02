#pragma once

#include <ESP8266WebServer.h>

class ConfigServer
{
  
public:  

   static void begin();

   static void run();

private:

   static void handleRoot();

   static void handleNotFound();

   static ESP8266WebServer server;
};

