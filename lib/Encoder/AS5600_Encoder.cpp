#include "AS5600_Encoder.h"

CAS5600::CAS5600(uint8_t busNum, uint8_t SDAPin, uint8_t SCLPin, uint8_t dirPin)
    : mWire(busNum), mEncoder(&mWire)
{
    mWire.begin(SDAPin, SCLPin, 100000);
    mEncoder.begin(dirPin);
    mEncoder.setDirection(AS5600_CLOCK_WISE);
}

uint32_t CAS5600::GetCount()
{
    if (!mEncoder.isConnected())
    {
        throw std::runtime_error("Encoder not connected");
    }

    return mEncoder.getCumulativePosition();
}
