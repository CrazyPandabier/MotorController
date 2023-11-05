#include "BLDC_MotorDriver.h"

#include <Arduino.h>

CBLDC_MotorDriver::CBLDC_MotorDriver(uint8_t EL, uint8_t ZF, uint8_t VR, bool inverted)
    : mEL(EL), mZF(ZF), mVR(VR), mInverted(inverted)
{
    pinMode(EL, OUTPUT);
    pinMode(ZF, OUTPUT);
    pinMode(VR, OUTPUT);

    digitalWrite(EL, HIGH);
    digitalWrite(ZF, LOW);
    digitalWrite(VR, LOW);
}

void CBLDC_MotorDriver::SetSpeed(uint8_t pwm)
{
    if (pwm < 0)
    {
        pwm = 0;
    }
    else if (pwm > 255)
    {
        pwm = 255;
    }

    if (pwm == 0)
    {
        Brake();
    }
    else
    {
        digitalWrite(mEL, HIGH);
        analogWrite(mVR, pwm);
    }
}

void CBLDC_MotorDriver::SetDirection(EDirection direction)
{
    if (mInverted)
    {
        direction = (direction == EDirection::Forward) ? EDirection::Backward : EDirection::Forward;
    }

    switch (direction)
    {
    case EDirection::Forward:
        digitalWrite(mZF, LOW);
        break;
    case EDirection::Backward:
        digitalWrite(mZF, HIGH);
        break;
    }
}

void CBLDC_MotorDriver::Brake()
{
    digitalWrite(mEL, LOW);
    digitalWrite(mVR, LOW);
}

