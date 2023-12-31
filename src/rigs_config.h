#pragma once

#include <string>

namespace Config
{
    namespace General
    {
        constexpr double WheelRadius = 0.09;
        constexpr double WheelSeperation = 0.355;
    }

    namespace LeftMotor
    {
        constexpr int BusNum = 1;
        constexpr int SDAPin = 32;
        constexpr int SCLPin = 33;
        constexpr int DirPin = 22;
        constexpr uint32_t CountsPerRev = 3686544;
        constexpr int Dir = 14;
        constexpr int Pwm = 25;
        constexpr uint8_t PwmChannel = 0;
        constexpr bool DirInverted = true;
        constexpr int Enable = 13;
        constexpr double Kp = 50;
        constexpr double Ki = 0;
        constexpr double Kd = 0;
    }

    namespace RightMotor
    {
        constexpr int BusNum = 0;
        constexpr int SDAPin = 26;
        constexpr int SCLPin = 27;
        constexpr int DirPin = 23;
        constexpr uint32_t CountsPerRev = 3707787;
        constexpr int Dir = 4;
        constexpr int Pwm = 5;
        constexpr uint8_t PwmChannel = 1;
        constexpr bool DirInverted = false;
        constexpr int Enable = 15;
        constexpr double Kp = 50;
        constexpr double Ki = 0;
        constexpr double Kd = 0;
    }
}