#pragma once

static const int DEVICE_NAME_SIZE = 20 + 1;

static const int AUTH_CODE_SIZE = 32 + 1;

static const int SSID_SIZE = 20 + 1;

static const int PASSWORD_SIZE = 20 + 1;

struct DeviceConfig
{
   char deviceName[DEVICE_NAME_SIZE];

   char authCode[AUTH_CODE_SIZE];

   inline DeviceConfig()
   {
      memset(deviceName, 0, DEVICE_NAME_SIZE);
      memset(authCode, 0, AUTH_CODE_SIZE);
   }
};

struct WifiConfig
{
   char ssid[SSID_SIZE];

   char password[PASSWORD_SIZE];

   inline WifiConfig()
   {
      memset(ssid, 0, SSID_SIZE);
      memset(password, 0, PASSWORD_SIZE);
   }
};

class EepromUtils
{

public:

   static void begin();

   static void getDeviceConfig(
      DeviceConfig& deviceConfig);

   static void setDeviceConfig(
    const DeviceConfig& deviceConfig);

   static void getWifiConfig(
    WifiConfig& wifiConfig);

   static void setWifiConfig(
      const WifiConfig& wifiConfig);

private:    

  static void initializeEeprom();
};

