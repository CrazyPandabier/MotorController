#include "CSpeedController.h"

#include <Arduino.h>
#include <esp_task_wdt.h>

#define SAMPLE_TIME 10

CSpeedController::CSpeedController(IMotor& leftMotor, IMotor& rightMotor, IWheelEncoder& leftEncoder, IWheelEncoder& rightEncoder, PIDConstants leftConstants, PIDConstants rightConstants) :mLeftPID(&mLeftInput,&mLeftOutput, &mLeftSetpoint, leftConstants.Kp, leftConstants.Ki, leftConstants.Kd, DIRECT), mRightPID(&mRightInput, &mRightOutput, &mRightSetpoint, rightConstants.Kp, rightConstants.Ki, rightConstants.Kd, DIRECT)
{
    mLeftPID.SetSampleTime(SAMPLE_TIME);
    mRightPID.SetSampleTime(10);
    mLeftPID.SetOutputLimits(-255, 255);
    mRightPID.SetOutputLimits(-255, 255);
    mLeftPID.SetMode(AUTOMATIC);
    mRightPID.SetMode(AUTOMATIC);

    mLeftParams.pid = &mLeftPID;
    mLeftParams.input = &mLeftInput;
    mLeftParams.output = &mLeftOutput;
    mLeftParams.setpoint = &mLeftSetpoint;
    mLeftParams.motor = &leftMotor;
    mLeftParams.encoder = &leftEncoder;
    mLeftParams.CountsPerRev = leftConstants.CountsPerRev;
    
    mRightParams.pid = &mRightPID;
    mRightParams.input = &mRightInput;
    mRightParams.output = &mRightOutput;
    mRightParams.setpoint = &mRightSetpoint;
    mRightParams.motor = &rightMotor;
    mRightParams.encoder = &rightEncoder;
    mRightParams.CountsPerRev = rightConstants.CountsPerRev;

    xTaskCreate(PIDTask, "LeftPIDTask", 2048, &mLeftParams, 1, NULL);
    xTaskCreate(PIDTask, "RightPIDTask", 2048, &mRightParams, 1, NULL);
}

void CSpeedController::SetWheelSpeeds(double leftSpeed, double rightSpeed)
{
    *mLeftParams.setpoint = leftSpeed;
    *mRightParams.setpoint = rightSpeed;
}

void CSpeedController::Brake()
{
    SetWheelSpeeds(0, 0);  

    mLeftParams.motor->SetSpeed(0);
    mRightParams.motor->SetSpeed(0);
}

void CSpeedController::PIDTask(void* param)
{
    uint32_t previousCount = 0;
    double previousTime = 0;

    while(true)
    {
        PIDTaskParams* params = (PIDTaskParams*)param;
        uint32_t currentCount = params->encoder->GetCount();

        int deltaCount = currentCount - previousCount;

        previousCount = currentCount;
        double time = SAMPLE_TIME / 1000.0;
        *params->input =((double(deltaCount)/ double(params->CountsPerRev)) * 2*PI) / time;
        
        params->pid->Compute();
        if(*params->output < 0)
            params->motor->SetDirection(EDirection::Backward);
        else
            params->motor->SetDirection(EDirection::Forward);
        previousTime += time;
        
        params->motor->SetSpeed(abs(*params->output));

        vTaskDelay(SAMPLE_TIME / portTICK_PERIOD_MS);
    }
}