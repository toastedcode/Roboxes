#pragma once

#include "NewPing.h"

class DistanceSensor
{

public:

   // Constructor.
   DistanceSensor();

   // Constructor.
   DistanceSensor(
      const int& triggerPin,
      const int& echoPin,
      const int& maxCmDistance);

   // Destructor.
   virtual ~DistanceSensor();

   void attach(
      const int& triggerPin,
      const int& echoPin,
      const int& maxCmDistance);

   // This operation takes a sensor reading and returns the new raw sensor value.
   virtual int read();

   // This operation takes a sensor reading and returns the new sensor value, converted to centimeters.
   virtual int readCm();

   // This operation takes a sensor reading and returns the new sensor value, converted to inches.
   virtual int readIn();

   static int toCentimeters(
      const int& microseconds);

   static int toInches(
      const int& microseconds);

private:

   NewPing* sensor;
};
