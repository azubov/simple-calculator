#include "math_operations.h"

#include <gtest/gtest.h>
#include <cstdint>
#include <limits>
#include <stdexcept>

TEST(MathlibTest, sum) {
    EXPECT_EQ(Mathlib::add(3, 5), 8);
    EXPECT_THROW(Mathlib::add(std::numeric_limits<int64_t>::max(), 1), std::overflow_error);
}

TEST(MathlibTest, subtraction) {
    EXPECT_EQ(Mathlib::sub(10, 7), 3);
    EXPECT_THROW(Mathlib::sub(std::numeric_limits<int64_t>::min(), 1), std::overflow_error);
}

TEST(MathlibTest, multiplication) {
    EXPECT_EQ(Mathlib::mul(2, 3), 6);
    EXPECT_THROW(Mathlib::mul(std::numeric_limits<int64_t>::max(), 2), std::overflow_error);
}

TEST(MathlibTest, division) {
    EXPECT_EQ(Mathlib::div(10, 2), 5);
    EXPECT_THROW(Mathlib::div(1, 0), std::invalid_argument);
    EXPECT_THROW(Mathlib::div(std::numeric_limits<int64_t>::min(), -1), std::overflow_error);
}

TEST(MathlibTest, exponentiation) {
    EXPECT_EQ(Mathlib::pow(2, 3), 8);
    EXPECT_THROW(Mathlib::pow(2, 63), std::overflow_error);
}

TEST(MathlibTest, factorial) {
    EXPECT_EQ(Mathlib::factorial(4), 24);
    EXPECT_THROW(Mathlib::factorial(-1), std::invalid_argument);
    EXPECT_THROW(Mathlib::factorial(21), std::overflow_error);
}
