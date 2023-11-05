#pragma once
#include "IWheelEncoder.h"
#include <Encoder.h>

class CWheelEncoder : public IWheelEncoder
{
public:
    CWheelEncoder(uint8_t pinA, uint8_t pinB);
    virtual uint32_t GetCount() override;

private:
    Encoder mEncoder;
};