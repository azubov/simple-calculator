#include "Calculator.h"
#include "OperationData.h"

#include <gtest/gtest.h>

TEST(CalculatorTest, Addition) {
    Calculator calculator;
    OperationData data{3, 5, 0, '+'};
    calculator.calculate(data);
    EXPECT_EQ(data.result, 8);
}

TEST(CalculatorTest, Subtraction) {
    Calculator calculator;
    OperationData data{10, 7, 0, '-'};
    calculator.calculate(data);
    EXPECT_EQ(data.result, 3);
}

TEST(CalculatorTest, Multiplication) {
    Calculator calculator;
    OperationData data{2, 3, 0, '*'};
    calculator.calculate(data);
    EXPECT_EQ(data.result, 6);
}

TEST(CalculatorTest, Division) {
    Calculator calculator;
    OperationData data{10, 2, 0, '/'};
    calculator.calculate(data);
    EXPECT_EQ(data.result, 5);
}

TEST(CalculatorTest, Power) {
    Calculator calculator;
    OperationData data{2, 3, 0, '^'};
    calculator.calculate(data);
    EXPECT_EQ(data.result, 8);
}

TEST(CalculatorTest, Factorial) {
    Calculator calculator;
    OperationData data{4, 0, 0, '!'};
    calculator.calculate(data);
    EXPECT_EQ(data.result, 24);
}