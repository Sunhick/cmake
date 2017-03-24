#include "gtest/gtest.h"

extern int add(int, int);
extern int sub(int, int);

TEST(TestAddSub, PosNumbers) {
  EXPECT_EQ(5, add(0,5));
  EXPECT_EQ(10, sub(20, 10));
}

TEST(TestAddSub, NegNumbers) {
  EXPECT_EQ(-5, add(0,-5));
  EXPECT_EQ(-10, sub(-20, -10));
}
