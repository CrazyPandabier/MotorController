#pragma once

#include <PID_v1.h>

#include "IMotor.h"
#include "IWheelEncoder.h"

struct PIDConstants
{
    double Kp;
    double Ki;
    double Kd;
    uint32_t CountsPerRev;
};

struct PIDTaskParams
{
    PID* pid;
    double* input;
    double* output;
    double* setpoint;
    uint32_t CountsPerRev;
    IMotor* motor;
    IWheelEncoder* encoder;
};

class CSpeedController
{
public:
    CSpeedController(IMotor& leftMotor, IMotor& rightMotor, IWheelEncoder& leftEncoder, IWheelEncoder& rightEncoder, PIDConstants leftConstants, PIDConstants rightConstants);
    void SetWheelSpeeds(double leftSpeed, double rightSpeed);
    void Brake();

private:
    static void PIDTask(void* param);

    double mLeftInput;
    double mRightInput;
    double mLeftOutput;
    double mRightOutput;
    double mLeftSetpoint;
    double mRightSetpoint;

    PIDTaskParams mLeftParams;
    PIDTaskParams mRightParams;

    PID mLeftPID;
    PID mRightPID;
};