#pragma once

class Motor
{

public:
   
   enum Orientation
   {
      LEFT,
      RIGHT
   };

   // Constructor.
   Motor();

   // Constructor.
   Motor(
      const int& directionPin,
      const int& speedPin,
      const Orientation& orientation);

   // Destructor.
   virtual ~Motor();

   void attach(
      const int& directionPin,
      const int& speedPin);

   void setOrientation(
      const Orientation& orientation);

   Orientation getOrientation() const;

   void drive(
      const int& speed);

   void stop();

   static const int NO_SPEED = 0;

   static const int MIN_SPEED = -100;

   static const int MAX_SPEED = 100;

private:

   // Updates the speed and direction GPIO pins to reflect the current motor speed.
   void updatePins();

   static const int NO_PWM = 0;

   static const int MIN_PWM = 300;

   static const int MAX_PWM = 1023;

   // The GPIO pin attached to the direction pin of the motor.
   int directionPin;

   // The GPIO pin attached to the speed pin of the motor.
   int speedPin;

   // The configured orientation (left, right) of the motor.
   Orientation orientation;

   // The speed of the motor.
   // Positive values indicate the motor is running forward; negative values reverse.
   int speed;
};
