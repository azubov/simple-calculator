#include "Calculator.h"

#include "TestHelper.h"

#include <gtest/gtest.h>

TEST(CalculatorTest, Addition) {
    Calculator calculator;
    OperationData op = testhelper::makeBinaryOp(3, '+', 5);
    calculator.calculate(op);
    EXPECT_EQ(op.result, 8);
}

TEST(CalculatorTest, Subtraction) {
    Calculator calculator;
    OperationData op = testhelper::makeBinaryOp(10, '-', 7);
    calculator.calculate(op);
    EXPECT_EQ(op.result, 3);
}

TEST(CalculatorTest, Multiplication) {
    Calculator calculator;
    OperationData op = testhelper::makeBinaryOp(2, '*', 3);
    calculator.calculate(op);
    EXPECT_EQ(op.result, 6);
}

TEST(CalculatorTest, Division) {
    Calculator calculator;
    OperationData op = testhelper::makeBinaryOp(10, '/', 2);
    calculator.calculate(op);
    EXPECT_EQ(op.result, 5);
}

TEST(CalculatorTest, Power) {
    Calculator calculator;
    OperationData op = testhelper::makeBinaryOp(2, '^', 3);
    calculator.calculate(op);
    EXPECT_EQ(op.result, 8);
}

TEST(CalculatorTest, Factorial) {
    Calculator calculator;
    OperationData op = testhelper::makeUnaryOp(4, '!');
    calculator.calculate(op);
    EXPECT_EQ(op.result, 24);
}