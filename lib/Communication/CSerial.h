#include "ISerial.h"

class CSerial : public ISerial
{
public:
    CSerial(uint32_t baudRate);
    ~CSerial();

    void Write(std::string data) override;
    void Write(char data) override;
    void WriteEndl(std::string data) override;
    void WriteEndl(char data) override;
    bool IsAvailable() override;
    char Read() override;
    void Flush() override;
    void Close() override;
};