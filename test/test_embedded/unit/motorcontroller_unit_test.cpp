#include "../TestCase.h"
#include "Cytron_MotorController.h"

class UnitTestMotorController : public CTestCase
{
public:
    void SetUp() override{};
    void TearDown() override{};
};

TEST_F(UnitTestMotorController, Construct_NormalParameters_NoThrow)
{
    EXPECT_NO_THROW(Cytron(26, 25, false, 0));
}

TEST_F(UnitTestMotorController, Construct_SamePins_Throw)
{
    EXPECT_THROW(Cytron(26, 26, false, 0), std::invalid_argument);
}