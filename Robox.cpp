#include "Robox.hpp"

static const int LEFT_MOTOR_SPEED_PIN = 0;
static const int LEFT_MOTOR_DIRECTION_PIN = 5;
static const int RIGHT_MOTOR_SPEED_PIN = 2;
static const int RIGHT_MOTOR_DIRECTION_PIN = 4;
static const int SERVO_1_PIN = 14;
static const int SERVO_2_PIN = 14;
static const int SERVO_3_PIN = 14;
static const int SERVO_4_PIN = 14;
static const int DISTANCE_TRIGGER_PIN = 13;
static const int DISTANCE_ECHO_PIN = 15;
static const int MAX_DISTANCE_CM = 200;

void Robox::begin()
{
   //
   // Setup components.
   //

   Motor leftMotor(LEFT_MOTOR_SPEED_PIN, LEFT_MOTOR_DIRECTION_PIN, Motor::LEFT);

   Motor rightMotor(RIGHT_MOTOR_SPEED_PIN, RIGHT_MOTOR_DIRECTION_PIN, Motor::RIGHT);

   motors.attach(leftMotor, rightMotor);

   servos[SERVO_1].attach(SERVO_1_PIN);
   servos[SERVO_2].attach(SERVO_2_PIN);
   servos[SERVO_3].attach(SERVO_3_PIN);
   servos[SERVO_4].attach(SERVO_4_PIN);

   distance.attach(DISTANCE_TRIGGER_PIN, DISTANCE_ECHO_PIN, MAX_DISTANCE_CM);

   //
   // Initialize components.
   //

   motors.drive(0, 0);

   for (int i = SERVO_FIRST; i < SERVO_LAST; i++)
   {
      servos[i].rotate(0);
   }

   follow.setEnabled(false);

   rover.setEnabled(false);
}

void Robox::run()
{
   follow.run();
   rover.run();
}
