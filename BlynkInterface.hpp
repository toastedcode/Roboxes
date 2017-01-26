#pragma once

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space

#include "BlynkSimpleEsp8266.h"
#include "Motor.hpp"
#include "Robox.hpp"
#include "ServoMotor.hpp"

// V1:  LCD
// V2:  left motor slider
// V3:  right motor slider
// V4:  servo 1 button
// V5:  servo 2 button
// V6:  servo 3 button
// V7:  servo 4 button
// V8:  servo 1 slider
// V9:  servo 2 slider
// V10: servo 3 slider
// V11: servo 4 slider
// V12: joystick
// V13: d-pad up
// V14: d-pad down
// V15: d-pad left
// V16: d-pad right
// V17: distance sensor
// V18: follow mode button
// V19: rover mode button

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
   BLYNK_PRINT.printf("servos[%d].rotate[%d]\n", servoId, angle);
   MyRobox.servos[servoId].rotate(angle);
}

// V2:  left motor slider
BLYNK_WRITE(V2)
{
   BLYNK_PRINT.printf("motors.leftMotor.drive(%d)\n", param.asInt());
   MyRobox.motors.leftMotor.drive(param.asInt());
}

// V3:  right motor slider
BLYNK_WRITE(V3)
{
   BLYNK_PRINT.printf("motors.rightMotor.drive(%d)\n", param.asInt());
   MyRobox.motors.rightMotor.drive(param.asInt());
}

// V4:  servo 1 button
BLYNK_WRITE(V4)
{
   updateServo(
      SERVO_1,
      (param.asInt() ? ServoMotor::MIN_ANGLE : ServoMotor::MAX_ANGLE));
}

// V5:  servo 2 button
BLYNK_WRITE(V5)
{
   updateServo(
      SERVO_2,
      (param.asInt() ? ServoMotor::MIN_ANGLE : ServoMotor::MAX_ANGLE));
}

// V8:  servo 1 slider
BLYNK_WRITE(V8)
{
   updateServo(SERVO_1, param.asInt());
}

// V9:  servo 2 slider
BLYNK_WRITE(V9)
{
   updateServo(SERVO_2, param.asInt());
}

// V12: joystick
BLYNK_WRITE(V12)
{
   BLYNK_PRINT.printf("motors.drive(%d, %d)\n", param[1].asInt(), param[0].asInt());
   MyRobox.motors.drive(param[1].asInt(), param[0].asInt());
}

// V13: d-pad up
BLYNK_WRITE(V13)
{
   if (param.asInt())
   {
     BLYNK_PRINT.printf("motors.forward(%d)\n", Motor::MAX_SPEED);
     MyRobox.motors.forward(Motor::MAX_SPEED);
   }
   else
   {
     BLYNK_PRINT.printf("motors.stop()\n");
     MyRobox.motors.stop();
   }
}

// V14: d-pad down
BLYNK_WRITE(V14)
{
   if (param.asInt())
   {
     BLYNK_PRINT.printf("motors.reverse(%d)\n", Motor::MIN_SPEED);
     MyRobox.motors.reverse(Motor::MIN_SPEED);
   }
   else
   {
     BLYNK_PRINT.printf("motors.stop()\n");
     MyRobox.motors.stop();
   }
}

// V15: d-pad left
BLYNK_WRITE(V15)
{
   if (param.asInt())
   {
      BLYNK_PRINT.printf("motors.rotate(%d)\n", COUNTERCLOCKWISE);
      MyRobox.motors.rotate(COUNTERCLOCKWISE);
   }
   else
   {
     BLYNK_PRINT.printf("motors.stop()\n");
     MyRobox.motors.stop();
   }
}

// V16: d-pad right
BLYNK_WRITE(V16)
{
   if (param.asInt())
   {
      BLYNK_PRINT.printf("motors.rotate(%d)\n", CLOCKWISE);
      MyRobox.motors.rotate(CLOCKWISE);
   }
   else
   {
     BLYNK_PRINT.printf("motors.stop()\n");
     MyRobox.motors.stop();
   }
}

// V17: distance sensor
BLYNK_READ(V17)
{
   Blynk.virtualWrite(V17, MyRobox.distance.readCm());
}

// V18: follow mode button
BLYNK_WRITE(V18)
{
   BLYNK_PRINT.printf("follow.setEnabled(%d)\n", param.asInt());
   MyRobox.follow.setEnabled(param.asInt());
}

// V19: rover mode button
BLYNK_WRITE(V19)
{
   BLYNK_PRINT.printf("rover.setEnabled(%d)\n", param.asInt());
   MyRobox.rover.setEnabled(param.asInt());
}
