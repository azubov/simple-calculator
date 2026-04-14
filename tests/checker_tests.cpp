#include "Checker.h"

#include "OperationData.h"
#include "TestHelper.h"

#include <gtest/gtest.h>

TEST(CheckerTests, ValidBinaryOperation) {
    Checker checker;
    OperationData data = testhelper::makeBinaryOp(1, '+', 2);
    EXPECT_NO_THROW(checker.validate(data));
}

TEST(CheckerTests, MissingSecondOperandForBinaryOp) {
    Checker checker;
    OperationData data = testhelper::makeUnaryOp(1, '+');
    EXPECT_THROW(checker.validate(data), std::invalid_argument);
}

TEST(CheckerTests, FactorialWithSecondOperandShouldFail) {
    Checker checker;
    OperationData data = testhelper::makeBinaryOp(1, '!', 2);
    EXPECT_THROW(checker.validate(data), std::invalid_argument);
}

TEST(CheckerTests, FactorialWithoutSecondOperandShouldPass) {
    Checker checker;
    OperationData data = testhelper::makeUnaryOp(1, '!');
    EXPECT_NO_THROW(checker.validate(data));
}

TEST(CheckerTests, UnsupportedOperationShouldFail) {
    Checker checker;
    OperationData data = testhelper::makeBinaryOp(1, '?', 2);
    EXPECT_THROW(checker.validate(data), std::invalid_argument);
}

TEST(CheckerTests, AllSupportedOperationsShouldPass) {
    Checker checker;
    for (char op : std::string("+-*/^")) {
        OperationData data = testhelper::makeBinaryOp(1, op, 2);
        EXPECT_NO_THROW(checker.validate(data));
    }
}