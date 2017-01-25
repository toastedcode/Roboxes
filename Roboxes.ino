#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include "BlynkInterface.hpp"
#include "Roboxes.h"

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "0c5a1145fe3c4cb693c9ef09c9eaf8c8";

bool connected = false;

void setup()
{
   Serial.begin(9600);

   Serial.println("*** Roboxes.com ***");
   Serial.println("");

   //Blynk.begin(auth, "TostNet", "t0stn3t5");
   Blynk.begin(auth, "AndroidAP", "iamabug0929");

   MyRobox.begin();
}

void loop()
{
   if (!connected && BlynkInterface::isConnected())
   {
      BlynkInterface::lcdPrintf(0, 0, "Connected!");
      connected = true;  
   }
   
   Blynk.run();

   MyRobox.run();
}
