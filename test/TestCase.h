#pragma once
#include <gtest/gtest.h>

class CTestCase : public ::testing::Test
{
protected:
    void SetUp() override{};
    void TearDown() override{};
};