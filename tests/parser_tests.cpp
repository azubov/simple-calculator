#include "OperationData.h"
#include "Parser.h"

#include <gtest/gtest.h>
#include <sstream>

TEST(ParserTests, ParsesValidBinaryOperation) {
    std::stringstream input(R"({
        "first": 3,
        "operation": "+",
        "second": 4
    })");

    Parser parser(input);
    OperationData data = parser.parse();

    EXPECT_EQ(data.first, 3);
    EXPECT_EQ(data.operation, '+');
    EXPECT_TRUE(data.hasSecond);
    EXPECT_EQ(data.second, 4);
}

TEST(ParserTests, ParsesUnaryOperationWithoutSecond) {
    std::stringstream input(R"({
        "first": 5,
        "operation": "!"
    })");

    Parser parser(input);
    OperationData data = parser.parse();

    EXPECT_EQ(data.first, 5);
    EXPECT_EQ(data.operation, '!');
    EXPECT_FALSE(data.hasSecond);
}

TEST(ParserTests, MissingFirstFieldThrows) {
    std::stringstream input(R"({
        "operation": "+",
        "second": 10
    })");

    Parser parser(input);

    EXPECT_THROW(parser.parse(), std::invalid_argument);
}

TEST(ParserTests, MissingOperationFieldThrows) {
    std::stringstream input(R"({
        "first": 10,
        "second": 20
    })");

    Parser parser(input);

    EXPECT_THROW(parser.parse(), std::invalid_argument);
}

TEST(ParserTests, OperationMustBeSingleCharacter) {
    std::stringstream input(R"({
        "first": 10,
        "operation": "add",
        "second": 20
    })");

    Parser parser(input);

    EXPECT_THROW(parser.parse(), std::invalid_argument);
}

TEST(ParserTests, FirstMustBeInteger) {
    std::stringstream input(R"({
        "first": "abc",
        "operation": "+",
        "second": 20
    })");

    Parser parser(input);

    EXPECT_THROW(parser.parse(), std::invalid_argument);
}

TEST(ParserTests, SecondMustBeIntegerIfPresent) {

    std::stringstream input(R"({
        "first": 10,
        "operation": "+",
        "second": "abc"
    })");

    Parser parser(input);

    EXPECT_THROW(parser.parse(), std::invalid_argument);
}