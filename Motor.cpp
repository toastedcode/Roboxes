#include <Arduino.h>

#include "Motor.hpp"

const int Motor::NO_SPEED;

const int Motor::MIN_SPEED;

const int Motor::MAX_SPEED;

const int Motor::NO_PWM;

const int Motor::MIN_PWM;

const int Motor::MAX_PWM;

Motor::Motor() :
      directionPin(0),
      speedPin(0),
      orientation(LEFT),
      speed(NO_SPEED)
{
   //  Nothing to do here.
}

Motor::Motor(
   const int& directionPin,
   const int& speedPin,
   const Orientation& orientation) :
      directionPin(directionPin),
      speedPin(speedPin),
      orientation(orientation),
      speed(NO_SPEED)
{
   attach(directionPin, speedPin);
}

Motor::~Motor()
{
   //  Nothing to do here.
}

void Motor::attach(
   const int& directionPin,
   const int& speedPin)
{
   this->directionPin = directionPin;
   this->speedPin = speedPin;

   pinMode(directionPin, OUTPUT);
   pinMode(speedPin, OUTPUT);

   updatePins();
}

void Motor::setOrientation(
   const Orientation& orientation)
{
   this->orientation = orientation;
}

Motor::Orientation Motor::getOrientation() const
{
   return (orientation);
}

void Motor::drive(
   const int& speed)
{
   this->speed = constrain(speed, MIN_SPEED, MAX_SPEED);

   updatePins();
}

void Motor::stop()
{
   speed = NO_SPEED;

   updatePins();
}

void Motor::updatePins()
{
   if (speed == 0)
   {
      digitalWrite(directionPin, LOW);
      analogWrite(speedPin, NO_PWM);
   }
   else if (speed > 0)
   {
      digitalWrite(directionPin, HIGH);
      analogWrite(speedPin, ((speed * (MAX_PWM - MIN_PWM)) / 100));
   }
   else // if (speed < 0)
   {
      digitalWrite(directionPin, LOW);
      analogWrite(speedPin, ((abs(speed) * (MAX_PWM - MIN_PWM)) / 100));
   }
}
