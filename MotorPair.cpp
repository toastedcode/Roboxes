#include <Arduino.h>

#include "MotorPair.hpp"

const int MotorPair::MIN_YAW;

const int MotorPair::MAX_YAW;

MotorPair::MotorPair() :
   speed(Motor::NO_SPEED),
   yaw(NO_YAW)
{

}

MotorPair::MotorPair(
   const Motor& leftMotor,
   const Motor& rightMotor) :
      leftMotor(leftMotor),
      rightMotor(rightMotor),
      speed(Motor::NO_SPEED),
      yaw(NO_YAW)
{
   updateMotors();
}

MotorPair::~MotorPair()
{
   // Nothing to do here.
}

void MotorPair::attach(
   const Motor& leftMotor,
   const Motor& rightMotor)
{
   this->leftMotor = leftMotor;
   this->rightMotor = rightMotor;

   updateMotors();
}

void MotorPair::drive(
   const int& speed,
   const int& yaw)
{
   this->speed = constrain(speed, Motor::MIN_SPEED, Motor::MAX_SPEED);
   this->yaw = constrain(yaw, MIN_YAW, MAX_YAW);

   updateMotors();
}

void MotorPair::forward(
   const int& speed)
{
   this->speed = constrain(speed, Motor::NO_SPEED, Motor::MAX_SPEED);
   yaw = NO_YAW;

   updateMotors();
}

void MotorPair::reverse(
   const int& speed)
{
   this->speed = constrain(speed, Motor::MIN_SPEED, Motor::NO_SPEED);
   yaw = NO_YAW;

   updateMotors();
}

void MotorPair::rotate(
   const int& speed)
{
   this->speed = abs(speed);
   this->yaw = 0;

   if (speed == 0)
   {
      leftMotor.drive(this->speed);
      rightMotor.drive(this->speed);
   }
   else if (speed < 0)
   {
      leftMotor.drive(this->speed * -1);
      rightMotor.drive(this->speed);
   }
   else
   {
      leftMotor.drive(this->speed);
      rightMotor.drive(speed * -1);
   }
}

void MotorPair::stop()
{
   speed = Motor::NO_SPEED;
   yaw = NO_YAW;

   updateMotors();
}

inline int MotorPair::getSpeed() const
{
   return (speed);
}

inline int MotorPair::getYaw() const
{
   return (yaw);
}

void MotorPair::updateMotors()
{
   int leftMotorSpeed = speed;
   int rightMotorSpeed = speed;

   if (yaw < 0)
   {
      // Cause the motor pair to yaw to the left by decreasing the speed of the left motor.
      leftMotorSpeed = ((speed * (MAX_YAW - abs(yaw))) / 100);
   }
   else if (yaw > 0)
   {
      // Cause the motor pair to yaw to the right by decreasing the speed of the right motor.
      rightMotorSpeed = ((speed * (MAX_YAW - yaw)) / 100);
   }

   leftMotor.drive(leftMotorSpeed);
   rightMotor.drive(rightMotorSpeed);
}
