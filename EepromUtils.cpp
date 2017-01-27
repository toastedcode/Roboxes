#include <Arduino.h>
#include <EEPROM.h>

#include "EepromUtils.hpp"

// **************************************************************************
//                                 Constants
// **************************0************************************************
 
typedef char EepromStamp[12];
   
static const EepromStamp EEPROM_STAMP = "roboxes.cot";
  
static const int EEPROM_BEGIN_ADDR = 0;
  
static const int EEPROM_STAMP_ADDR = EEPROM_BEGIN_ADDR;
  
static const int DEVICE_CONFIG_EEPROM_ADDR = EEPROM_STAMP_ADDR + sizeof(EepromStamp);
  
static const int WIFI_CONFIG_EEPROM_ADDR = DEVICE_CONFIG_EEPROM_ADDR + sizeof(DeviceConfig);  

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

      for (int i = 0; i < 512; i++)
      {
         EEPROM.write(i, 0);
      }
       
      EEPROM.put(EEPROM_BEGIN_ADDR, EEPROM_STAMP);

      EEPROM.commit();
   }    
 }
