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
        constexpr int Encoder1 = 26;
        constexpr int Encoder2 = 25;
        constexpr uint32_t CountsPerRev = General::CountsPerRev;
        constexpr int Dir = 14;
        constexpr int Pwm = 27;
        constexpr bool DirInverted = false;
        constexpr int Channel = 1;
        constexpr double Kp = 0.16365535849189533;
        constexpr double Ki = 23.75620975449702;
        constexpr double Kd = 0;
    }

    namespace RightMotor
    {
        constexpr int Encoder1 = 33;
        constexpr int Encoder2 = 32;
        constexpr uint32_t CountsPerRev = General::CountsPerRev;
        constexpr int Dir = 12;
        constexpr int Pwm = 13;
        constexpr bool DirInverted = true;
        constexpr int Channel = 0;
        constexpr double Kp = 0.16365535849189533;
        constexpr double Ki = 23.75620975449702;
        constexpr double Kd = 0;
    }
}