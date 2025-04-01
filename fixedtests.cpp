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
    EXPECT_EQ(c.to_string(), "12345.000000000");
    EXPECT_EQ(a.to_string(), "-12345.000000000");
}

TEST(FixedCreate, twoIntNumbers) {
    Fixed<NNN> a(1, 12345);
    EXPECT_EQ(a.to_string(), "1.000012345");

    Fixed<NNN> b(-1, 12345);
    EXPECT_EQ(b.to_string(), "-1.000012345");

    Fixed<NNN> c(12345, 1);
    EXPECT_EQ(c.to_string(), "12345.000000001");
}

TEST(FixedCreate, unsignedNumbers) {
    unsigned int x = 1U;
    unsigned int y = 12345U;
    EXPECT_EQ(Fixed<NNN>(x).to_string(), "1.000000000");
    EXPECT_EQ(Fixed<NNN>(y).to_string(), "12345.000000000");
}

TEST(FixedCreate, fromString){
    EXPECT_EQ(Fixed<NNN>("0").to_string(), "0.000000000");
    EXPECT_EQ(Fixed<NNN>("-0").to_string(), "0.000000000");
    EXPECT_EQ(Fixed<NNN>("10.123456789").to_string(), "10.123456789");
    EXPECT_EQ(Fixed<NNN>("-10.123456789").to_string(), "-10.123456789");
    EXPECT_EQ(Fixed<NNN>("123.12345678912345").to_string(), "123.123456789");
    EXPECT_EQ(Fixed<NNN>("123.12345").to_string(), "123.123450000");
    EXPECT_EQ(Fixed<NNN>("10.").to_string(), "10.000000000");
    EXPECT_EQ(Fixed<NNN>("0.5").to_string(), "0.500000000");
    EXPECT_ANY_THROW(Fixed<NNN>("5a.12345"));
    EXPECT_ANY_THROW(Fixed<NNN>("5.12a345"));
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

TEST(FixedAdd, plusEq) {
    Fixed<NNN> a(0);
    Fixed<NNN> e(0, 1);
    a += e;
    EXPECT_EQ(a, e);
    a += a;
    EXPECT_EQ(a, Fixed<NNN>(0,2));
    a += a;
    EXPECT_EQ(a, Fixed<NNN>(0, 4));
    a += a;
    EXPECT_EQ(a, Fixed<NNN>(0, 8));
    a += a;
    EXPECT_EQ(a, Fixed<NNN>(0, 16));
}

TEST(FixedAdd, plusEq2) {
    Fixed<NNN> b(0, 5);
    Fixed<NNN> c(0, 125);
    b += c;
    EXPECT_EQ(b, Fixed<NNN>(0, 130));
    c += b;
    EXPECT_EQ(b, Fixed<NNN>(0, 130));
    EXPECT_EQ(c, Fixed<NNN>(0, 255));

    Fixed<NNN> d("-2.000000125");
    b += d;
    EXPECT_EQ(b, Fixed<NNN>("-1.999999995"));
}

TEST(FixedAdd, plus) {
    Fixed<NNN> a("99.999000000");
    Fixed<NNN> b(" 1.0010000000");
    EXPECT_EQ(a+b, Fixed<NNN>("101.000000000"));
    EXPECT_EQ(b + a, Fixed<NNN>("101.000000000"));
    EXPECT_EQ(a + Fixed<NNN>(1), Fixed<NNN>("100.999000000"));
    EXPECT_EQ(Fixed<NNN>(1) + a, Fixed<NNN>("100.999000000"));
    EXPECT_EQ(a + Fixed<NNN>(-100), Fixed<NNN>("-0.001000000"));
}

TEST(FixedAdd, minus) {
    Fixed<NNN> a("99.999000000");
    Fixed<NNN> b(" 1.0010000000");
    EXPECT_EQ(a - b, Fixed<NNN>("98.998000000"));
    EXPECT_EQ(b - a, Fixed<NNN>("-98.998000000"));
    EXPECT_EQ(a - Fixed<NNN>(100), Fixed<NNN>("-0.001000000"));
    EXPECT_EQ(Fixed<NNN>(100) - a, Fixed<NNN>("0.001000000"));
    EXPECT_EQ(a - Fixed<NNN>(-100), Fixed<NNN>("199.999000000"));
}


TEST(FixedAdd, minusEq) {
    Fixed<NNN> b("0.000000001");
    Fixed<NNN> c("0.000000125");
    b-=c;
    EXPECT_EQ(b, Fixed<NNN>("-0.000000124"));
    Fixed<NNN> a("0.000000001");
    Fixed<NNN> z(0);
    z-=a;
    EXPECT_EQ(z, Fixed<NNN>("-0.000000001"));
    Fixed<NNN> e(1);
    e-=a;
    EXPECT_EQ(e, Fixed<NNN>("0.999999999"));
}