#include "CSerial.h"
#include <Arduino.h>

CSerial::CSerial(uint32_t baudRate)
{
    Serial.begin(baudRate);
}

CSerial::~CSerial()
{
    Serial.end();
}

void CSerial::Write(std::string data)
{
    Serial.print(data.c_str());
}

void CSerial::Write(char data)
{
    Serial.print(data);
}

void CSerial::WriteEndl(std::string data)
{
    Serial.println(data.c_str());
}

void CSerial::WriteEndl(char data)
{
    Serial.println(data);
}

bool CSerial::IsAvailable()
{
    return Serial.available() > 0;
}

char CSerial::Read()
{
    return Serial.read();
}

void CSerial::Flush()
{
    Serial.flush();
}

void CSerial::Close()
{
    Serial.end();
}
