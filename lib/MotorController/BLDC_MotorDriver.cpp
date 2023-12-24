#include "BLDC_MotorDriver.h"

#include <Arduino.h>

CBLDC_MotorDriver::CBLDC_MotorDriver(uint8_t EL, uint8_t ZF, uint8_t VR, bool inverted, uint8_t pwmChannel)
    : mEL(EL), mZF(ZF), mVR(VR), mInverted(inverted), mPwmChannel(pwmChannel)
{
    pinMode(EL, OUTPUT);
    pinMode(ZF, OUTPUT);
    ledcSetup(pwmChannel, 20000, 8);
    ledcAttachPin(VR, pwmChannel);

    digitalWrite(EL, LOW);
    digitalWrite(ZF, LOW);
}

void CBLDC_MotorDriver::SetSpeed(uint8_t pwm)
{
    if (pwm > 255)
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
        ledcWrite(mPwmChannel, pwm);
    }
}

void CBLDC_MotorDriver::SetDirection(EDirection direction)
{
    if (mInverted)
    {
        if (direction == EDirection::Forward)
        {
            direction = EDirection::Backward;
        }
        else
        {
            direction = EDirection::Forward;
        }
    }

    switch (direction)
    {
    case EDirection::Forward:
        digitalWrite(mZF, HIGH);
        break;
    case EDirection::Backward:
        digitalWrite(mZF, LOW);
        break;
    }
}

void CBLDC_MotorDriver::Brake()
{
    digitalWrite(mEL, LOW);
    digitalWrite(mVR, LOW);
}

