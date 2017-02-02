#pragma once

#include "Arduino.h"

enum JoystickDirection
{
   JOYSTICK_DIRECTION_FIRST = 0,
   RIGHT = JOYSTICK_DIRECTION_FIRST,
   UP_RIGHT,
   UP,
   UP_LEFT,
   LEFT,
   DOWN_LEFT,
   DOWN,
   DOWN_RIGHT,
   JOYSTICK_DIRECTION_LAST,
   JOYSTICK_DIRECTION_COUNT = (JOYSTICK_DIRECTION_LAST - JOYSTICK_DIRECTION_FIRST)
};

inline String toString(
   const JoystickDirection& direction)
{
   static const String NAMES[JOYSTICK_DIRECTION_COUNT] =
   {
      "RIGHT",
      "UP_RIGHT",
      "UP",
      "UP_LEFT",
      "LEFT",
      "DOWN_LEFT",
      "DOWN",
      "DOWN_RIGHT",
   };

   return (NAMES[direction]);
}

class JoystickUtils
{

public:

   static void interpretJoystick(
      const int& x,
      const int& y,
      JoystickDirection& direction,
      int& speed);

private:

   static double getAngle(
      const int& x,
      const int& y);
};
