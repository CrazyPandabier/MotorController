#pragma once
#include <string>

class ISerial
{
public:
    /**
     * @brief       Write data to serial port
     * @param data  Data to write
     */
    virtual void Write(std::string data) = 0;
    /**
     * @brief       Write data to serial port
     * @param data  Data to write
     */
    virtual void Write(char data) = 0;
    /**
     * @brief       Write data to serial port with endline
     * @param data  Data to write
     */
    virtual void WriteEndl(std::string data) = 0;
    /**
     * @brief       Write data to serial port with endline
     * @param data  Data to write
     */
    virtual void WriteEndl(char data) = 0;
    /**
     * @brief Check if data is available
     */
    virtual bool IsAvailable() = 0;
    /**
     * @brief Read data from serial port
     */
    virtual char Read() = 0;
    /**
     * @brief Flush serial port
     */
    virtual void Flush() = 0;
    /**
     * @brief Close serial port
     */
    virtual void Close() = 0;
};