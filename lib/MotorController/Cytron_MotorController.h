#ifndef MOTOR_CONTROL
#define MOTOR_CONTROL

#include <stdint.h>

#include "IMotor.h"

class Cytron : public IMotor
{

public:
    Cytron(uint8_t pwm_pin, uint8_t dir_pin, bool inverted, uint8_t channel_num);
    virtual void SetSpeed(uint8_t pwm) override;
    virtual void SetDirection(EDirection direction) override;

private:
    void Brake();

    uint8_t pwm_pin;
    uint8_t dir_pin;
    bool inverted;
    uint8_t channel_num;
};
#endif
