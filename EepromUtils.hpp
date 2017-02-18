#pragma once

static const int SERVER_NAME_SIZE = 20 + 1;

static const int DEVICE_NAME_SIZE = 20 + 1;

static const int AUTH_CODE_SIZE = 32 + 1;

static const int SSID_SIZE = 20 + 1;

static const int PASSWORD_SIZE = 20 + 1;

struct DeviceConfig
{
   char deviceName[DEVICE_NAME_SIZE];

   inline DeviceConfig()
   {
      memset(deviceName, 0, DEVICE_NAME_SIZE);
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

struct BlynkConfig
{
   char server[SERVER_NAME_SIZE];

   char authCode[AUTH_CODE_SIZE];

   inline BlynkConfig()
   {
      memset(server, 0, SERVER_NAME_SIZE);
      memset(authCode, 0, AUTH_CODE_SIZE);
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

    static void getBlynkConfig(
       BlynkConfig& blynkConfig);

    static void setBlynkConfig(
       const BlynkConfig& blynkConfig);

   static void getWifiConfig(
    WifiConfig& wifiConfig);

   static void setWifiConfig(
      const WifiConfig& wifiConfig);

   static void clearEeprom();

private:    

  static void initializeEeprom();
};

