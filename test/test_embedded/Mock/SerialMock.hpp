#include "ISerial.h"
#include "gmock/gmock.h"

class SerialMock : public ISerial
{
public:
    SerialMock() = default;
    MOCK_METHOD(void, Write, (std::string data), (override));
    MOCK_METHOD(void, Write, (char data), (override));
    MOCK_METHOD(void, WriteEndl, (std::string data), (override));
    MOCK_METHOD(void, WriteEndl, (char data), (override));
    MOCK_METHOD(bool, IsAvailable, (), (override));
    MOCK_METHOD(char, Read, (), (override));
    MOCK_METHOD(void, Flush, (), (override));
    MOCK_METHOD(void, Close, (), (override));
};
