#include "JoystickUtils.hpp"

#define PI 3.14159265

static const int HIGH_SPEED_THRESHOLD = 50;
static const int LOW_SPEED_THRESHOLD = 33;

static const int NO_SPEED = 0;      // 0%
static const int HIGH_SPEED = 100;  // 100%
static const int LOW_SPEED = 80;    // 80%

void JoystickUtils::interpretJoystick(
   const int& x,
   const int& y,
   JoystickDirection& direction,
   int& speed)
{
   // The function getAngle() returns the angle between 0 and 359, representing the angle between the
   // supplied vector and the vector (1, 0).
   // This constant allows us to transform that angle such that 0 corresponds to the min-angle for the UP direction.
   static const int ANGLE_OFFSET = 22;

   static const int JOYSTICK_DIRECTION_RANGE = (360 / JOYSTICK_DIRECTION_COUNT);

   direction = UP;
   speed = NO_SPEED;

   int angle = (int)getAngle(x, y);

   // Transform the angle so that 0 corresponds to the min-angle for the UP direction.
   angle = (angle + ANGLE_OFFSET);
   if (angle > 359)
   {
      angle = (angle - 360);
   }

   // Convert the angle into a joystick direction.
   direction = static_cast<JoystickDirection>(angle /  JOYSTICK_DIRECTION_RANGE);

   // You guys like the Pythagorean theorem, right?
   int magnitude = (int)(sqrt((x*x) + (y*y)));

   if (magnitude >= HIGH_SPEED_THRESHOLD)
   {
      speed = HIGH_SPEED;
   }
   else if (magnitude >= LOW_SPEED_THRESHOLD)
   {
      speed = LOW_SPEED;
   }
   else
   {
      speed = NO_SPEED;
   }
}

double JoystickUtils::getAngle(const int& x, const int& y)
{
   double angle = 0;

   if (x == 0)
   {
      angle = (y < 0) ? 270 : 90;
   }
   else
   {
      double arctan = atan(y/x) / PI * 180;

      if (x < 0 || y < 0)
         arctan += 180;

      if (x > 0 && y < 0)
         arctan -= 180;

      if (arctan < 0)
         arctan += 360;

      angle = (int)arctan % 360;
   }

   return (angle);
}
