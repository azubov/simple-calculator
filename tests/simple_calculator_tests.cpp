#include "SimpleCalculator.h"

#include "TestHelper.h"

#include <gtest/gtest.h>

TEST(SimpleCalculatorTest, Addition) {
    SimpleCalculator calculator;
    OperationData op = testhelper::makeBinaryOp(3, '+', 5);
    calculator.calculate(op);
    EXPECT_EQ(op.result, 8);
}

TEST(SimpleCalculatorTest, Subtraction) {
    SimpleCalculator calculator;
    OperationData op = testhelper::makeBinaryOp(10, '-', 7);
    calculator.calculate(op);
    EXPECT_EQ(op.result, 3);
}

TEST(SimpleCalculatorTest, Multiplication) {
    SimpleCalculator calculator;
    OperationData op = testhelper::makeBinaryOp(2, '*', 3);
    calculator.calculate(op);
    EXPECT_EQ(op.result, 6);
}

TEST(SimpleCalculatorTest, Division) {
    SimpleCalculator calculator;
    OperationData op = testhelper::makeBinaryOp(10, '/', 2);
    calculator.calculate(op);
    EXPECT_EQ(op.result, 5);
}

TEST(SimpleCalculatorTest, Power) {
    SimpleCalculator calculator;
    OperationData op = testhelper::makeBinaryOp(2, '^', 3);
    calculator.calculate(op);
    EXPECT_EQ(op.result, 8);
}

TEST(SimpleCalculatorTest, Factorial) {
    SimpleCalculator calculator;
    OperationData op = testhelper::makeUnaryOp(4, '!');
    calculator.calculate(op);
    EXPECT_EQ(op.result, 24);
}