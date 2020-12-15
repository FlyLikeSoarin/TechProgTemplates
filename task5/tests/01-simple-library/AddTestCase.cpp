//
// Created by akhtyamovpavel on 5/1/20.
//

#include "AddTestCase.h"
#include "Functions.h"

TEST(AddTest, TestCorrectness) {
    ASSERT_EQ(4, Add(2, 2));
    ASSERT_EQ(0, Add(1, -1));
}
