#include "IWheelEncoder.h"

#include "AS5600.h"
#include "Wire.h"


class CAS5600 : public IWheelEncoder
{
public:
    CAS5600(uint8_t busNum, uint8_t SDAPin, uint8_t SCLPin, uint8_t dirPin);
   uint32_t GetCount() override;
private:
    uint8_t mPin;
    TwoWire mWire;
    AS5600 mEncoder;
    int mCount;
};