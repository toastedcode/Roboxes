#pragma once

#include "DistanceSensor.hpp"

DistanceSensor::DistanceSensor() :
   sensor(0)
{
}

DistanceSensor::DistanceSensor(
   const int& triggerPin,
   const int& echoPin,
   const int& maxCmDistance)
{
   attach(triggerPin, echoPin, maxCmDistance);
}

DistanceSensor::~DistanceSensor()
{
   delete (sensor);
}

 void DistanceSensor::attach(
    const int& triggerPin,
    const int& echoPin,
    const int& maxDistanceCm)
{
   sensor = new NewPing(triggerPin, echoPin, maxDistanceCm);
}

int DistanceSensor::read()
{
   int sensorValue = 0;

   if (sensor)
   {
      sensorValue = sensor->ping();
   }

   return (sensorValue);
}

int DistanceSensor::readCm()
{
   int sensorValue = 0;

   if (sensor)
   {
      sensorValue = sensor->ping_cm();
   }

   return (sensorValue);
}

int DistanceSensor::readIn()
{
   int sensorValue = 0;

   if (sensor)
   {
      sensorValue = sensor->ping_in();
   }

   return (sensorValue);
}


int DistanceSensor::toCentimeters(
   const int& microseconds)
{
   return (NewPing::convert_cm(microseconds));
}

int DistanceSensor::toInches(
   const int& microseconds)
{
   return (NewPing::convert_in(microseconds));
}
