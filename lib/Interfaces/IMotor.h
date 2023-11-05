#pragma once
#include <cstdint>

enum class EDirection : uint32_t
{
    Forward = 0,
    Backward
};

class IMotor
{
public:
    virtual ~IMotor() = default;
    /**
     * @brief           Set speed of motor
     * @param pwm       Speed of motor
     */
    virtual void SetSpeed(uint8_t pwm) = 0;
    /**
     * @brief           Set direction of motor
     * @param direction Direction of motor
     */
    virtual void SetDirection(EDirection direction) = 0;
};