#include "CWheelEncoder.h"

CWheelEncoder::CWheelEncoder(uint8_t pinA, uint8_t pinB) : mEncoder(pinA, pinB)
{
    if (pinA == pinB)
    {
        throw std::invalid_argument("pinA and pinB cannot be the same");
    }

    mEncoder.readAndReset();
}

uint32_t CWheelEncoder::GetCount()
{
    return mEncoder.read();
}