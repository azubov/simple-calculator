#include "Checker.h"
#include "OperationData.h"

#include <gtest/gtest.h>

TEST(CheckerTests, ValidBinaryOperation) {
    OperationData data;
    data.first = 1;
    data.operation = '+';
    data.second = 2;
    data.hasSecond = true;

    Checker checker;
    EXPECT_NO_THROW(checker.validate(data));
}

TEST(CheckerTests, MissingSecondOperandForBinaryOp) {
    OperationData data;
    data.first = 1;
    data.operation = '+';

    Checker checker;
    EXPECT_THROW(checker.validate(data), std::invalid_argument);
}

TEST(CheckerTests, FactorialWithSecondOperandShouldFail) {
    OperationData data;
    data.first = 1;
    data.operation = '!';
    data.second = 2;
    data.hasSecond = true;

    Checker checker;
    EXPECT_THROW(checker.validate(data), std::invalid_argument);
}

TEST(CheckerTests, FactorialWithoutSecondOperandShouldPass) {
    OperationData data;
    data.first = 1;
    data.operation = '!';

    Checker checker;
    EXPECT_NO_THROW(checker.validate(data));
}

TEST(CheckerTests, UnsupportedOperationShouldFail) {
    OperationData data;
    data.first = 1;
    data.operation = '?';
    data.second = 2;
    data.hasSecond = true;

    Checker checker;
    EXPECT_THROW(checker.validate(data), std::invalid_argument);
}

TEST(CheckerTests, AllSupportedOperationsShouldPass) {
    Checker checker;
    for (char op : std::string("+-*/^")) {
        OperationData data;
        data.first = 1;
        data.operation = op;
        data.second = 2;
        data.hasSecond = true;
        EXPECT_NO_THROW(checker.validate(data));
    }
}