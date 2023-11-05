#pragma once
#include <vector>
#include <string>

struct CallbackData
{
    std::vector<void *> args;
    void (*callback)(std::vector<void *> args, std::string message);
};

class ICommunication
{
public:
    /**
     * @brief           Add command to list of commands
     * @param command   Char of the command to add
     * @param callback  Callback function that is called when command is received
     */
    virtual void AddCommand(char command, CallbackData) = 0;
    /**
     * @brief           Get list of commands
     * @return          List of commands
     */
    virtual std::vector<char> GetCommands() = 0;
    /**
     * @brief           Receive data from serial port
     */
    virtual void Receive() = 0;
    /**
     * @brief           Send data to serial port
     * @param message   Message to send
     */
    virtual void Send(std::string message) = 0;
};