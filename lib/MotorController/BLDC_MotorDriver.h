#include "IMotor.h"

class CBLDC_MotorDriver : public IMotor
{
public:
    CBLDC_MotorDriver(uint8_t EL, uint8_t ZF, uint8_t VR, bool inverted, uint8_t pwmChannel);

    void SetSpeed(uint8_t pwm) override;
    void SetDirection(EDirection direction) override;   
private:
    void Brake();

    uint8_t mEL;
    uint8_t mZF;
    uint8_t mVR;
    bool mInverted;
    uint8_t mPwmChannel;
};