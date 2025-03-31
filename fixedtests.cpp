#include <gtest/gtest.h>
#include "fixed.h"

const int NNN = 9;

TEST(FixedCreate, defaultConstructor) {
    Fixed<NNN> a;
    EXPECT_EQ(a.to_string(), "0.000000000");
}

TEST(FixedCreate, intNumbers) {
    Fixed<NNN> b(0);
    Fixed<NNN> c(12345);
    Fixed<NNN> a(-12345);

    EXPECT_EQ(b.to_string(), "0.000000000");
    EXPECT_EQ(b.to_string(), "12345.000000000");
    EXPECT_EQ(b.to_string(), "-12345.000000000");
}

TEST(FixedCreate, twoIntNumbers) {
    Fixed<NNN> a(1, 12345);
    EXPECT_EQ(a.to_string(), "1.000012345");

    Fixed<NNN> b(-1, 12345);
    EXPECT_EQ(a.to_string(), "-1.000012345");

    Fixed<NNN> c(12345, 1);
    EXPECT_EQ(a.to_string(), "12345.000000001");
}

TEST(FixedCreate, unsignedNumbers) {
    unsigned int x = 1U;
    unsigned int y = 12345U;
    EXPECT_EQ(Fixed<NNN>(x).to_string(), "1.000000000");
    EXPECT_EQ(Fixed<NNN>(y).to_string(), "12345.000000000");
}

TEST(FixedCreate, doubleNumbers) {
    EXPECT_EQ(Fixed<NNN>(1.00390625).to_string(), "1.003906250");
    EXPECT_EQ(Fixed<NNN>(0.001953125).to_string(), "0.001953125");
}
 TEST(FixedCopy, copyFromShortFixed){
    Fixed<3> a(123, 456);
    EXPECT_EQ(a.to_string(), "123.456");

    Fixed<NNN> b(a);
    EXPECT_EQ(b.to_string(), "123.456000000");
 }

 TEST(FixedCompare, ComparePositive){
    Fixed<NNN> a(1,2);
    Fixed<NNN> b(0,99);
    EXPECT_FALSE(a<b);
    EXPECT_FALSE(a<=b);
    EXPECT_FALSE(a==b);
    EXPECT_TRUE(a!=b);
    EXPECT_TRUE(a>=b);
    EXPECT_TRUE(a>b);

    EXPECT_TRUE(b<a);
    EXPECT_TRUE(b<=a);
    EXPECT_FALSE(b==a);
    EXPECT_TRUE(b!=a);
    EXPECT_FALSE(b>=a);
    EXPECT_FALSE(b>a);

    Fixed<NNN> c(a);
    EXPECT_FALSE(c<a);
    EXPECT_TRUE(c<=a);
    EXPECT_TRUE(c==a);
    EXPECT_FALSE(c!=a);
    EXPECT_TRUE(c>=a);
    EXPECT_FALSE(c>a);
 }

 TEST(FixedCompare, CompareNegative){
    Fixed<NNN> a(-1, 2);
    Fixed<NNN> b(-1, 99);

    EXPECT_FALSE(a<b);
    EXPECT_FALSE(a<=b);
    EXPECT_FALSE(a==b);
    EXPECT_TRUE(a!=b);
    EXPECT_TRUE(a>=b);
    EXPECT_TRUE(a>b);

    EXPECT_TRUE(b<a);
    EXPECT_TRUE(b<=a);
    EXPECT_FALSE(b==a);
    EXPECT_TRUE(b!=a);
    EXPECT_FALSE(b>=a);
    EXPECT_FALSE(b>a);

    Fixed<NNN> c(a);
    EXPECT_FALSE(c<a);
    EXPECT_TRUE(c<=a);
    EXPECT_TRUE(c==a);
    EXPECT_FALSE(c!=a);
    EXPECT_TRUE(c>=a);
    EXPECT_FALSE(c>a);
 }

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}