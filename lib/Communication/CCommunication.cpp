#include "CCommunication.h"
#include <ctype.h>

CCommunication::CCommunication(ISerial &serial, char prefix, char suffix) : mSerial(serial), mPrefix(prefix), mSuffix(suffix)
{
    if (mPrefix == mSuffix)
    {
        throw std::invalid_argument("Prefix and suffix cannot be the same");
    }

    if (isdigit(mPrefix))
    {
        throw std::invalid_argument("Prefix cannot be a digit");
    }

    if (isdigit(mSuffix))
    {
        throw std::invalid_argument("Suffix cannot be a digit");
    }
}

void CCommunication::AddCommand(char command, CallbackData callbackData)
{
    mCommands.emplace(command, callbackData);
}

std::vector<char> CCommunication::GetCommands()
{
    std::vector<char> commandList;

    for (auto const &command : mCommands)
    {
        commandList.push_back(command.first);
    }

    return commandList;
}

void CCommunication::Send(std::string message)
{
    mSerial.Write(mPrefix);
    mSerial.Write(message);
    mSerial.WriteEndl(mSuffix);
}

void CCommunication::Receive()
{
    if (mSerial.IsAvailable())
    {
        char character = mSerial.Read();

        if (character == mSuffix && mComStarted)
        {
            mSerial.Flush();
            mComStarted = false;
            char command = mMessage.at(0);

            try
            {
                mCommands.at(command).callback(mCommands.at(command).args, mMessage);
            }
            catch (std::out_of_range &e)
            {
                mSerial.Write("Command not found");
            }
        }

        if (mComStarted)
        {
            mMessage += character;
        }

        if (character == mPrefix && !mComStarted)
        {
            mComStarted = true;
            mMessage = "";
        }
    }
}