#pragma once

#include <Servo.h>

class ServoMotor
{

public:

   // Constructor.
   ServoMotor();

   // Constructor.
   ServoMotor(
      // The control pin for the servo.
      const int& pin);

   // Destructor.
   virtual ~ServoMotor();

   void attach(
      const int& pin);

   void getLimits(
      int& limitMin,
      int& limitMax) const;

   void setLimits(
      const int& limitMin,
      const int& limitMax);

   // Sets the speed of the two motors in the pair.
   void rotate(
      // The angle the servo should rotate to.
      int angle);

   // Retrieves the current angle of the servo.
   // Note: Non-const because it calls read() on the Servo object.
   int getAngle();

   // Sets the PWM of the servo in milliseconds.
   void setPwm(
      // The new PWM to write to the servo.
      const int& pwm);

   static int angleToPwm(
      const int& angle);

   static const int MIN_ANGLE = 0;

   static const int MAX_ANGLE = 180;

   static const int MIN_PWM = 1000;

   static const int MAX_PWM = 1500;

private:

   // The GPIO pin used for controlling the angle of the servo.
   int pin;

   // A servo object from the Arduino library.
   Servo servo;

   // The angle of the servo.
   int angle;

   int limitMin;

   int limitMax;
};
