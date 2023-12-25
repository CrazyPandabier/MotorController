#include "CSerial.h"
#include <Arduino.h>

CSerial::CSerial(uint32_t baudRate)
{
    Serial2.begin(baudRate);
}

CSerial::~CSerial()
{
    Serial2.end();
}

void CSerial::Write(std::string data)
{
    Serial2.print(data.c_str());
}

void CSerial::Write(char data)
{
    Serial2.print(data);
}

void CSerial::WriteEndl(std::string data)
{
    Serial2.println(data.c_str());
}

void CSerial::WriteEndl(char data)
{
    Serial2.println(data);
}

bool CSerial::IsAvailable()
{
    return Serial2.available() > 0;
}

char CSerial::Read()
{
    return Serial2.read();
}

void CSerial::Flush()
{
    Serial2.flush();
}

void CSerial::Close()
{
    Serial2.end();
}
