#include <gtest/gtest.h>
#include "../../src/utils/smoke.h"

TEST(TestUtils, TestSmokeGetHello)
{
    EXPECT_EQ("Hello ModernCpp!", Smoke::getHello());	
}