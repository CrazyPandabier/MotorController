#include "../TestCase.h"
#include "CCommunication.h"
#include "../Mock/SerialMock.hpp"

class UnitTestCommunication : public CTestCase
{
public:
    void SetUp() override{};
    void TearDown() override{};
};

TEST_F(UnitTestCommunication, Construct_NormalParameters_NoThrow)
{
    auto serial = std::unique_ptr<SerialMock>(new SerialMock());
    EXPECT_NO_THROW(CCommunication(*serial, '#', ';'));
}

TEST_F(UnitTestCommunication, Construct_InvalidStartDelimiter_Throw)
{
    auto serial = std::unique_ptr<SerialMock>(new SerialMock());
    EXPECT_THROW(CCommunication(*serial, '1', ';'), std::invalid_argument);
}

TEST_F(UnitTestCommunication, Construct_InvalidEndDelimiter_Throw)
{
    auto serial = std::unique_ptr<SerialMock>(new SerialMock());
    EXPECT_THROW(CCommunication(*serial, '#', '1'), std::invalid_argument);
}

TEST_F(UnitTestCommunication, Construct_StartAndEndDelimiterSame_Throw)
{
    auto serial = std::unique_ptr<SerialMock>(new SerialMock());
    EXPECT_THROW(CCommunication(*serial, '#', '#'), std::invalid_argument);
}

TEST_F(UnitTestCommunication, AddCommand_NormalParameters_NoThrow)
{
    auto serial = std::unique_ptr<SerialMock>(new SerialMock());
    CCommunication communication(*serial, '#', ';');
    EXPECT_NO_THROW(communication.AddCommand('a', {std::vector<void *>{}, [](std::vector<void *> args, std::string message) {}}));
}

TEST_F(UnitTestCommunication, GetCommands_NoCommands_EmptyVector)
{
    auto serial = std::unique_ptr<SerialMock>(new SerialMock());
    CCommunication communication(*serial, '#', ';');
    EXPECT_EQ(0, communication.GetCommands().size());
}

TEST_F(UnitTestCommunication, GetCommands_OneCommand_VectorWithOneElement)
{
    auto serial = std::unique_ptr<SerialMock>(new SerialMock());
    CCommunication communication(*serial, '#', ';');
    communication.AddCommand('a', {std::vector<void *>{}, [](std::vector<void *> args, std::string message) {}});
    EXPECT_EQ(1, communication.GetCommands().size());
}

TEST_F(UnitTestCommunication, GetCommands_MultipleCommands_VectorWithMultipleElements)
{
    auto serial = std::unique_ptr<SerialMock>(new SerialMock());
    CCommunication communication(*serial, '#', ';');
    communication.AddCommand('a', {std::vector<void *>{}, [](std::vector<void *> args, std::string message) {}});
    communication.AddCommand('b', {std::vector<void *>{}, [](std::vector<void *> args, std::string message) {}});
    communication.AddCommand('c', {std::vector<void *>{}, [](std::vector<void *> args, std::string message) {}});
    communication.AddCommand('d', {std::vector<void *>{}, [](std::vector<void *> args, std::string message) {}});
    communication.AddCommand('e', {std::vector<void *>{}, [](std::vector<void *> args, std::string message) {}});
    EXPECT_EQ(5, communication.GetCommands().size());
}

TEST_F(UnitTestCommunication, AddCommand_CommandAlreadyExists_Throw)
{
    auto serial = std::unique_ptr<SerialMock>(new SerialMock());
    CCommunication communication(*serial, '#', ';');
    communication.AddCommand('a', {std::vector<void *>{}, [](std::vector<void *> args, std::string message) {}});
    EXPECT_NO_THROW(communication.AddCommand('a', {std::vector<void *>{}, [](std::vector<void *> args, std::string message) {}}));
    EXPECT_EQ(1, communication.GetCommands().size());
}

TEST_F(UnitTestCommunication, Send_NormalParameters_WriteCalled)
{
    auto serial = std::unique_ptr<SerialMock>(new SerialMock());
    EXPECT_CALL(*serial, Write('#')).Times(1);
    EXPECT_CALL(*serial, Write(';')).Times(1);
    EXPECT_CALL(*serial, Write("a")).Times(1);

    CCommunication communication(*serial, '#', ';');
    communication.AddCommand('a', {std::vector<void *>{}, [](std::vector<void *> args, std::string message) {}});
    EXPECT_NO_THROW(communication.Send("a"));
}

TEST_F(UnitTestCommunication, Receive_ExistingCommand_NoThrow)
{
    auto serial = std::unique_ptr<SerialMock>(new SerialMock());
    EXPECT_CALL(*serial, IsAvailable()).Times(1).WillOnce(testing::Return(true));
    EXPECT_CALL(*serial, Read()).Times(1).WillOnce(testing::Return('a'));

    CCommunication communication(*serial, '#', ';');
    communication.AddCommand('a', {std::vector<void *>{}, [](std::vector<void *> args, std::string message) {}});
    EXPECT_NO_THROW(communication.Receive());
}