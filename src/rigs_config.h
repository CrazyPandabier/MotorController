#pragma once

#include <string>

namespace Config
{
    namespace General
    {
        constexpr double WheelRadius = 0.25;
        constexpr double WheelSeperation = 0.38;
        constexpr uint32_t CountsPerRev = 2190;
        constexpr int RemoteInterruptPin = 2;
        const std::string HeaderFrameId = "odom";
        const std::string ChildFrameId = "base_footprint";
    }

    namespace LeftMotor
    {
        constexpr int BusNum = 0;
        constexpr int SDAPin = 27;
        constexpr int SCLPin = 26;
        constexpr int DirPin = 23;
        constexpr uint32_t CountsPerRev = General::CountsPerRev;
        constexpr int Dir = 4;
        constexpr int Pwm = 5;
        constexpr bool DirInverted = false;
        constexpr int Enable = 15;
        constexpr double Kp = 0;
        constexpr double Ki = 0;
        constexpr double Kd = 0;
    }

    namespace RightMotor
    {
        constexpr int BusNum = 1;
        constexpr int SDAPin = 33;
        constexpr int SCLPin = 32;
        constexpr int DirPin = 22;
        constexpr uint32_t CountsPerRev = General::CountsPerRev;
        constexpr int Dir = 14;
        constexpr int Pwm = 25;
        constexpr bool DirInverted = true;
        constexpr int Enable = 13;
        constexpr double Kp = 0;
        constexpr double Ki = 0;
        constexpr double Kd = 0;
    }
}