#include <Arduino.h>
#include <EEPROM.h>

#include "EepromUtils.hpp"

// **************************************************************************
//                                 Constants
// **************************************************************************
 
typedef char EepromStamp[12];
   
static const EepromStamp EEPROM_STAMP = "roboxes.com";
  
static const int EEPROM_BEGIN_ADDR = 0;
  
static const int EEPROM_STAMP_ADDR = EEPROM_BEGIN_ADDR;
  
static const int DEVICE_CONFIG_EEPROM_ADDR = EEPROM_STAMP_ADDR + sizeof(EepromStamp);
  
static const int WIFI_CONFIG_EEPROM_ADDR = DEVICE_CONFIG_EEPROM_ADDR + sizeof(DeviceConfig);

static const int BLYNK_CONFIG_EEPROM_ADDR = WIFI_CONFIG_EEPROM_ADDR + sizeof(WifiConfig);  

// **************************************************************************
//                                 Public
// **************************************************************************
 
 void EepromUtils::begin()
 {
   EEPROM.begin(512);

   initializeEeprom();
 }

void EepromUtils::getDeviceConfig(
   DeviceConfig& deviceConfig)
{ 
   EEPROM.get(DEVICE_CONFIG_EEPROM_ADDR, deviceConfig); 
}

void EepromUtils::setDeviceConfig(
   const DeviceConfig& deviceConfig)
{
   EEPROM.put(DEVICE_CONFIG_EEPROM_ADDR, deviceConfig);
   EEPROM.commit();
}

void EepromUtils::getBlynkConfig(
   BlynkConfig& blynkConfig)
{ 
   EEPROM.get(BLYNK_CONFIG_EEPROM_ADDR, blynkConfig); 
}

void EepromUtils::setBlynkConfig(
   const BlynkConfig& blynkConfig)
{
   EEPROM.put(BLYNK_CONFIG_EEPROM_ADDR, blynkConfig);
   EEPROM.commit();
}

void EepromUtils::getWifiConfig(
   WifiConfig& wifiConfig)
{
   EEPROM.get(WIFI_CONFIG_EEPROM_ADDR, wifiConfig);
}

void EepromUtils::setWifiConfig(
   const WifiConfig& wifiConfig)
 {
   EEPROM.put(WIFI_CONFIG_EEPROM_ADDR, wifiConfig);
   EEPROM.commit();  
 }

 void EepromUtils::clearEeprom()
 {
    for (int i = 0; i < 512; i++)
    {
       EEPROM.write(i, 0);
    }  
    
    EEPROM.commit();
 }

// **************************************************************************
//                                 Private
// **************************************************************************

 void EepromUtils::initializeEeprom()
 {
   EepromStamp eepromStamp;

   // Retrieve the current EEPROM stamp.
   EEPROM.get(EEPROM_BEGIN_ADDR, eepromStamp);

   // If it's not our expected stamp, then this is the first run of this device.
   if (strncmp(eepromStamp, EEPROM_STAMP, sizeof(EepromStamp)) != 0)
   {
      Serial.println("Initializing EEPROM");

      clearEeprom();
       
      EEPROM.put(EEPROM_BEGIN_ADDR, EEPROM_STAMP);

      EEPROM.commit();
   }    
 }
