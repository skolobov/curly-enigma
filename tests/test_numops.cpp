#include <numops/numops.h>

#include <gtest/gtest.h>

#include <climits>

// --- add() tests ---

TEST(AddTest, PositiveNumbers) {
    EXPECT_EQ(numops::add(2, 3), 5);
    EXPECT_EQ(numops::add(100, 200), 300);
}

TEST(AddTest, NegativeNumbers) {
    EXPECT_EQ(numops::add(-1, -1), -2);
    EXPECT_EQ(numops::add(-10, -20), -30);
}

TEST(AddTest, MixedSigns) {
    EXPECT_EQ(numops::add(-1, 1), 0);
    EXPECT_EQ(numops::add(5, -3), 2);
}

TEST(AddTest, Zero) {
    EXPECT_EQ(numops::add(0, 0), 0);
    EXPECT_EQ(numops::add(42, 0), 42);
    EXPECT_EQ(numops::add(0, -7), -7);
}

TEST(AddTest, LargeValues) { EXPECT_EQ(numops::add(1000000, 2000000), 3000000); }

TEST(AddTest, Commutativity) {
    EXPECT_EQ(numops::add(3, 7), numops::add(7, 3));
    EXPECT_EQ(numops::add(-5, 12), numops::add(12, -5));
}

TEST(AddTest, BoundaryValues) {
    EXPECT_EQ(numops::add(INT_MAX, 0), INT_MAX);
    EXPECT_EQ(numops::add(INT_MIN, 0), INT_MIN);
}

// --- subtract() tests ---

TEST(SubtractTest, PositiveResult) {
    EXPECT_EQ(numops::subtract(5, 3), 2);
    EXPECT_EQ(numops::subtract(100, 1), 99);
}

TEST(SubtractTest, NegativeResult) {
    EXPECT_EQ(numops::subtract(3, 5), -2);
    EXPECT_EQ(numops::subtract(0, 10), -10);
}

TEST(SubtractTest, Zero) {
    EXPECT_EQ(numops::subtract(0, 0), 0);
    EXPECT_EQ(numops::subtract(7, 7), 0);
}

TEST(SubtractTest, NegativeNumbers) {
    EXPECT_EQ(numops::subtract(-5, -3), -2);
    EXPECT_EQ(numops::subtract(-3, -5), 2);
}

TEST(SubtractTest, BoundaryValues) {
    EXPECT_EQ(numops::subtract(INT_MAX, 0), INT_MAX);
    EXPECT_EQ(numops::subtract(INT_MIN, 0), INT_MIN);
    EXPECT_EQ(numops::subtract(INT_MAX, INT_MAX), 0);
}

// --- multiply() tests ---

TEST(MultiplyTest, PositiveNumbers) {
    EXPECT_EQ(numops::multiply(2, 3), 6);
    EXPECT_EQ(numops::multiply(7, 8), 56);
}

TEST(MultiplyTest, Zero) {
    EXPECT_EQ(numops::multiply(0, 100), 0);
    EXPECT_EQ(numops::multiply(42, 0), 0);
    EXPECT_EQ(numops::multiply(0, 0), 0);
}

TEST(MultiplyTest, NegativeNumbers) {
    EXPECT_EQ(numops::multiply(-2, -3), 6);
    EXPECT_EQ(numops::multiply(-4, 5), -20);
    EXPECT_EQ(numops::multiply(6, -7), -42);
}

TEST(MultiplyTest, Identity) {
    EXPECT_EQ(numops::multiply(1, 99), 99);
    EXPECT_EQ(numops::multiply(99, 1), 99);
    EXPECT_EQ(numops::multiply(-1, 42), -42);
}

TEST(MultiplyTest, Commutativity) {
    EXPECT_EQ(numops::multiply(3, 7), numops::multiply(7, 3));
    EXPECT_EQ(numops::multiply(-4, 5), numops::multiply(5, -4));
}

TEST(MultiplyTest, BoundaryValues) {
    EXPECT_EQ(numops::multiply(INT_MAX, 0), 0);
    EXPECT_EQ(numops::multiply(INT_MIN, 0), 0);
    EXPECT_EQ(numops::multiply(INT_MAX, 1), INT_MAX);
    EXPECT_EQ(numops::multiply(INT_MIN, 1), INT_MIN);
}

// --- divide() tests ---

TEST(DivideTest, ExactDivision) {
    EXPECT_EQ(numops::divide(10, 2), 5);
    EXPECT_EQ(numops::divide(100, 4), 25);
}

TEST(DivideTest, IntegerTruncation) {
    EXPECT_EQ(numops::divide(7, 2), 3);
    EXPECT_EQ(numops::divide(1, 3), 0);
}

TEST(DivideTest, NegativeNumbers) {
    EXPECT_EQ(numops::divide(-10, 2), -5);
    EXPECT_EQ(numops::divide(10, -2), -5);
    EXPECT_EQ(numops::divide(-10, -2), 5);
}

TEST(DivideTest, DivideByZero) { EXPECT_EQ(numops::divide(42, 0), 0); }

TEST(DivideTest, ZeroDividend) {
    EXPECT_EQ(numops::divide(0, 5), 0);
    EXPECT_EQ(numops::divide(0, -3), 0);
}

TEST(DivideTest, Identity) {
    EXPECT_EQ(numops::divide(99, 1), 99);
    EXPECT_EQ(numops::divide(-42, 1), -42);
}

TEST(DivideTest, BoundaryValues) {
    EXPECT_EQ(numops::divide(INT_MAX, 1), INT_MAX);
    EXPECT_EQ(numops::divide(INT_MIN, 1), INT_MIN);
    EXPECT_EQ(numops::divide(INT_MAX, INT_MAX), 1);
    EXPECT_EQ(numops::divide(INT_MIN, INT_MIN), 1);
}
