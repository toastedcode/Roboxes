#include "Arduino.h"
#include "EepromUtils.hpp"
#include "FactoryReset.hpp"

int FactoryReset::flashPressTime;

static const int FLASH_PIN = 0;  // GPIO 0

const int FLASH_PRESS_THRESHOLD = 5000;  // millis

void FactoryReset::run()
{
   pinMode(FLASH_PIN, INPUT);
 
   bool isPressed = (digitalRead(FLASH_PIN) == 0);

   pinMode(FLASH_PIN, OUTPUT);

   // Pressed.
   if (isPressed)
   {
      if (flashPressTime == 0)
      {
         // Start timing the press.
         flashPressTime = millis();
      }
      else if ((millis() - flashPressTime) > FLASH_PRESS_THRESHOLD)
      {
         factoryReset();  
      }
   }
   // Not pressed.
   else if (flashPressTime != 0)
   {
      flashPressTime = 0;
   }
}

void FactoryReset::factoryReset()
{
   Serial.println("Resetting to factory defaults ...");
  
   EepromUtils::clearEeprom();

   ESP.eraseConfig();

   ESP.reset();
}

