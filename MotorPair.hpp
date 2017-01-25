#pragma once

#include "Motor.hpp"

class MotorPair
{

public:
   
   // Constructor.
   MotorPair();

   // Constructor.
   MotorPair(
      // The left motor in a motor pair.
      const Motor& leftMotor,
      // The right motor in a motor pair.
      const Motor& rightMotor);

   // Destructor.
   virtual ~MotorPair();

   void attach(
      // The left motor in a motor pair.
      const Motor& leftMotor,
      // The right motor in a motor pair.
      const Motor& rightMotor);

   // Sets the speed of the two motors in the pair.
   void drive(
      // The combined speed of the left and right motors.
      // Positive values indicate the motors are running forward; negative values reverse.
      const int& speed,
      // The speed ratio between the left and right motors.
      // Positive values indicate the motor pair will be turning to the right; negative values left.
      const int& yaw);

   void forward(
      const int& speed);

   void reverse(
      const int& speed);

   void rotate(
      // The speed of the left and right motors.
      // Negative values will cause the right motor to rotate forward, and the left the rotate backwards (rotate left).
      // Positive values will cause the left motor to rotate forward, and the right to rotate backwards (rotate right).
      const int& speed);

   // Stops both motors in the pair by setting their speed to zero.
   void stop();

   // Retrieves the speed of the motor pair.
   int getSpeed() const;

   // Retrieves the yaw of the motor pair.
   int getYaw() const;

   static const int MIN_YAW = -100;

   static const int MAX_YAW = 100;

   static const int NO_YAW = 0;

   // The left motor in a motor pair.
   Motor leftMotor;

   // The right motor in a motor pair.
   Motor rightMotor;

private:

   // Updates the two motors to reflect the current speed.
   void updateMotors();

   // The speed of the motor pair.
   // Positive values indicate the motors are running forward; negative values reverse.
   int speed;

   // The speed ratio between the left and right motors.
   // Positive values indicate the motor pair will be turning to the right; negative values left.
   int yaw;
};
