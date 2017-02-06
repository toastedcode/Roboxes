#include "ServoMotor.hpp"

const int ServoMotor::MIN_ANGLE;

const int ServoMotor::MAX_ANGLE;

const int ServoMotor::MIN_PWM;

const int ServoMotor::MAX_PWM;

ServoMotor::ServoMotor() :
   pin(0),
   angle(MIN_ANGLE),
   limitMin(MIN_ANGLE),
   limitMax(MAX_ANGLE)
{
   // Nothing to do here.
}

ServoMotor::ServoMotor(
   const int& pin) :
      pin(pin),
      angle(MIN_ANGLE)
{
   attach(pin);
}

ServoMotor::~ServoMotor()
{
   // Nothing to do here.
}

void ServoMotor::attach(
   const int& pin)
{
   this->pin = pin;

   pinMode(pin, OUTPUT);
   servo.attach(pin);
}

void ServoMotor::getLimits(
   int& limitMin,
   int& limitMax) const

{
   limitMin = this->limitMin;
   limitMax = this->limitMax;
}

void ServoMotor::setLimits(
   const int& limitMin,
   const int& limitMax)
{
   this->limitMin = limitMin;
   this->limitMax = limitMax;

   rotate(getAngle());
}


int ServoMotor::getAngle()
{
   return (servo.read());
}

void ServoMotor::rotate(
   int angle)
{
   servo.write(constrain(angle, limitMin, limitMax));
}

void ServoMotor::setPwm(
   const int& pwm)
{
   servo.writeMicroseconds(constrain(pwm, MIN_PWM, MAX_PWM));
}

int ServoMotor::angleToPwm(
   const int& angle)
{
   int pwm = 0;

   if ((angle >= MIN_ANGLE) && (angle >= MAX_ANGLE))
   {
      pwm = map(angle, MIN_ANGLE, MAX_ANGLE, MIN_PWM, MAX_PWM);
   }

   return (pwm);
}
