#pragma once

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space

#include "BlynkSimpleEsp8266.h"
#include "JoystickUtils.hpp"
#include "Motor.hpp"
#include "Robox.hpp"
#include "ServoMotor.hpp"

// TAB 1
// V1:  LCD
// V2: joystick
// V3:  servo 1 button
// V4:  servo 2 button
// TAB 2
// V5:  servo 1 min slider
// V6:  servo 1 max slider
// V7:  servo 1 slider
// V8:  servo 2 min slider
// V9:  servo 2 max slider
// V10:  servo 2 slider
// TAB 3
// V11: joystick
// TAB 4
// V12: distance sensor
// V13: follow mode button
// V14: rover mode button

static const int FORWARD = Motor::MAX_SPEED;
static const int REVERSE = Motor::MIN_SPEED;

static const int CLOCKWISE = Motor::MAX_SPEED;
static const int COUNTERCLOCKWISE = Motor::MIN_SPEED;

class BlynkInterface
{

public:
  
   static bool isConnected();
  
   static void lcdPrintf(
      const int& col,
      const int& row,
      const char* format);

   static void lcdClear();

private:

   static WidgetLCD lcd;
};

WidgetLCD BlynkInterface::lcd(V1);

inline bool BlynkInterface::isConnected()
{
  return (Blynk.connected());
}

inline void BlynkInterface::lcdPrintf(
  const int& col,
  const int& row,
  const char* format)
{
   lcd.print(col, row, format);
}

inline void BlynkInterface::lcdClear()
{
   lcd.clear();
}

inline void updateServo(
   ServoId servoId,
   int angle)
{
   int limitMin = 0;
   int limitMax = 0;
   MyRobox.servos[servoId].getLimits(limitMin, limitMax);

   int mappedAngle = map(angle, ServoMotor::MIN_ANGLE, ServoMotor::MAX_ANGLE, limitMin, limitMax);

   BLYNK_PRINT.printf("servos[%d].rotate[%d]\n", servoId, mappedAngle);
   MyRobox.servos[servoId].rotate(angle);
}

inline void updateMotors(
   const JoystickDirection& direction,
   const int& speed)
{
   static const int TURN_SPEED_MODIFIER = 20;

   int leftMotorSpeed = 0;
   int rightMotorSpeed = 0;

   switch (direction)
   {
      case RIGHT:
      {
         leftMotorSpeed = speed;
         rightMotorSpeed = (speed * -1);
         break;
      }

      case UP_RIGHT:
      {
         leftMotorSpeed = speed;
         rightMotorSpeed = (speed - TURN_SPEED_MODIFIER);
         break;
      }

      case UP:
      {
         leftMotorSpeed = speed;
         rightMotorSpeed = speed;
         break;
      }

      case UP_LEFT:
      {
         leftMotorSpeed = (speed - TURN_SPEED_MODIFIER);
         rightMotorSpeed = speed;
         break;
      }

      case LEFT:
      {
         leftMotorSpeed = (speed * -1);
         rightMotorSpeed = speed;
         break;
      }

      case DOWN_LEFT:
      {
         leftMotorSpeed = ((speed - TURN_SPEED_MODIFIER) * -1);
         rightMotorSpeed = (speed * -1);
         break;
      }

      case DOWN:
      {
         leftMotorSpeed = (speed * -1);
         rightMotorSpeed = (speed * -1);
         break;
      }

      case DOWN_RIGHT:
      {
         leftMotorSpeed = (speed * -1);
         rightMotorSpeed = ((speed - TURN_SPEED_MODIFIER) * -1);
         break;
      }
   }

   MyRobox.motors.leftMotor.drive(leftMotorSpeed);
   MyRobox.motors.rightMotor.drive(rightMotorSpeed);
}

// V2: joystick
BLYNK_WRITE(V2)
{
   JoystickDirection direction = UP;
   int speed = 0;

   JoystickUtils::interpretJoystick(
      param[0].asInt(),
      param[1].asInt(),
      direction,
      speed);

   BLYNK_PRINT.printf("interpretJoystick(%d, %d) => %s, %d\n",
                      param[0].asInt(),
                      param[1].asInt(),
                      toString(direction).c_str(),
                      speed);

   updateMotors(direction, speed);
}

// V3:  servo 1 button
BLYNK_WRITE(V3)
{
   updateServo(
      SERVO_1,
      (param.asInt() ? ServoMotor::MIN_ANGLE : ServoMotor::MAX_ANGLE));
}

// V4:  servo 2 button
BLYNK_WRITE(V4)
{
   updateServo(
      SERVO_2,
      (param.asInt() ? ServoMotor::MIN_ANGLE : ServoMotor::MAX_ANGLE));
}

// V5:  servo 1 min slider
BLYNK_WRITE(V5)
{
   int limitMin = 0;
   int limitMax = 0;
   MyRobox.servos[SERVO_1].getLimits(limitMin, limitMax);

   MyRobox.servos[SERVO_1].setLimits(param.asInt(), limitMax);
}

// V6:  servo 1 max slider
BLYNK_WRITE(V6)
{
   int limitMin = 0;
   int limitMax = 0;
   MyRobox.servos[SERVO_1].getLimits(limitMin, limitMax);

   MyRobox.servos[SERVO_1].setLimits(limitMin, param.asInt());
}

// V7:  servo 1 slider
BLYNK_WRITE(V7)
{
   updateServo(SERVO_1, param.asInt());
}

// V8:  servo 2 min slider
BLYNK_WRITE(V8)
{
   int limitMin = 0;
   int limitMax = 0;
   MyRobox.servos[SERVO_2].getLimits(limitMin, limitMax);

   MyRobox.servos[SERVO_2].setLimits(param.asInt(), limitMax);
}

// V9:  servo 2 max slider
BLYNK_WRITE(V9)
{
   int limitMin = 0;
   int limitMax = 0;
   MyRobox.servos[SERVO_2].getLimits(limitMin, limitMax);

   MyRobox.servos[SERVO_2].setLimits(limitMin, param.asInt());
}

// V10:  servo 2 slider
BLYNK_WRITE(V10)
{
   updateServo(SERVO_2, param.asInt());
}

// V11: joystick
BLYNK_WRITE(V11)
{
   JoystickDirection direction = UP;
   int speed = 0;

   JoystickUtils::interpretJoystick(
      param[0].asInt(),
      param[1].asInt(),
      direction,
      speed);

   updateMotors(direction, speed);
}

// V12: distance sensor
BLYNK_READ(V12)
{
   Blynk.virtualWrite(V17, MyRobox.distance.readCm());
}

// V13: follow mode button
BLYNK_WRITE(V13)
{
   BLYNK_PRINT.printf("follow.setEnabled(%d)\n", param.asInt());
   MyRobox.follow.setEnabled(param.asInt());
}

// V14: rover mode button
BLYNK_WRITE(V14)
{
   BLYNK_PRINT.printf("rover.setEnabled(%d)\n", param.asInt());
   MyRobox.rover.setEnabled(param.asInt());
}
