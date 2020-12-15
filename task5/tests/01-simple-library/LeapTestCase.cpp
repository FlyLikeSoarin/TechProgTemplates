//
// Created by akhtyamovpavel on 5/1/20.
//

#include "LeapTestCase.h"

#include <Functions.h>

TEST(LeapTest, TestInvlidNegativeYear) {
  ASSERT_THROW(IsLeap(-1), std::invalid_argument);
}

TEST(LeapTest, TestNonLeapYear) {
  ASSERT_FALSE(IsLeap(1));
  ASSERT_FALSE(IsLeap(100));
}

TEST(LeapTest, TestLeapYear) {
  ASSERT_TRUE(IsLeap(4));
  ASSERT_TRUE(IsLeap(400));
}
