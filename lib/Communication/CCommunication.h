#include "ICommunication.h"
#include "ISerial.h"
#include <map>

class CCommunication : public ICommunication
{
public:
    CCommunication(ISerial &serial, char prefix, char suffix);

    void AddCommand(char command, CallbackData) override;
    std::vector<char> GetCommands() override;
    void Receive() override;
    void Send(std::string message) override;

private:
    ISerial &mSerial;
    char mPrefix;
    char mSuffix;
    bool mComStarted = false;
    std::string mMessage = "";
    std::map<char, CallbackData> mCommands; // fixed the syntax error here
};
