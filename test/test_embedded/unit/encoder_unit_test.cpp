#include "../TestCase.h"
#include "CWheelEncoder.h"

class UnitTestEncoder : public CTestCase
{
public:
    void SetUp() override{};
    void TearDown() override{};
};

TEST_F(UnitTestEncoder, Construct_NormalParameters_NoThrow)
{
    EXPECT_NO_THROW(CWheelEncoder(26, 25));
}

TEST_F(UnitTestEncoder, Construct_SamePins_Throw)
{
    EXPECT_THROW(CWheelEncoder(26, 26), std::invalid_argument);
}