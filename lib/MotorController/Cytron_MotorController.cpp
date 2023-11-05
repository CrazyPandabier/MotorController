#include <Arduino.h>

#include "Cytron_MotorController.h"

Cytron::Cytron(uint8_t pwm_pin, uint8_t dir_pin, bool inverted, uint8_t channel_num) : pwm_pin(pwm_pin), dir_pin(dir_pin), inverted(inverted), channel_num(channel_num)
{
    if (pwm_pin == dir_pin)
    {
        throw std::invalid_argument("pwm_pin and dir_pin cannot be the same");
    }

    ledcSetup(channel_num, 20000, 8);
    ledcAttachPin(pwm_pin, channel_num);

    pinMode(dir_pin, OUTPUT);
}

void Cytron::Brake()
{

    digitalWrite(pwm_pin, LOW);
    digitalWrite(dir_pin, LOW);
}

void Cytron::SetDirection(EDirection direction)
{
    if (inverted)
    {
        direction = (direction == EDirection::Forward) ? EDirection::Backward : EDirection::Forward;
    }

    switch (direction)
    {
    case EDirection::Forward:
        digitalWrite(dir_pin, HIGH);
        break;
    case EDirection::Backward:
        digitalWrite(dir_pin, LOW);
        break;
    }
}

void Cytron::SetSpeed(uint8_t pwm)
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
        // sSerial.println(pwm);
        ledcWrite(channel_num, pwm);
    }
}