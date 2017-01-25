#pragma once

//#include "BlynkLCD.hpp"
#include "DistanceSensor.hpp"
#include "FollowAI.hpp"
#include "Motor.hpp"
#include "MotorPair.hpp"
#include "RoverAI.hpp"
#include "ServoMotor.hpp"

enum ServoId
{
   SERVO_FIRST = 0,
   SERVO_1 = SERVO_FIRST,
   SERVO_2,
   SERVO_3,
   SERVO_4,
   SERVO_LAST,
   SERVO_COUNT = SERVO_LAST - SERVO_FIRST
};

class Robox
{

public:

   Robox();

   ~Robox();

   void begin();

   void run();

   MotorPair motors;

   ServoMotor servos[SERVO_COUNT];

   DistanceSensor distance;

   FollowAI follow;

   RoverAI rover;

private:

   bool connected;

};

static Robox MyRobox;
