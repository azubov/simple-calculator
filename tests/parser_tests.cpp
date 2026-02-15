#include "OperationData.h"
#include "Parser.h"

#include <gtest/gtest.h>
#include <sstream>

TEST(ParserTests, ParsesValidBinaryOperation) {
    Parser parser;
    std::stringstream input(R"({
        "first": 3,
        "operation": "+",
        "second": 4
    })");

    OperationData data = parser.parse(input);

    EXPECT_EQ(data.first, 3);
    EXPECT_EQ(data.operation, '+');
    EXPECT_TRUE(data.hasSecond);
    EXPECT_EQ(data.second, 4);
}

TEST(ParserTests, ParsesUnaryOperationWithoutSecond) {
    Parser parser;
    std::stringstream input(R"({
        "first": 5,
        "operation": "!"
    })");

    OperationData data = parser.parse(input);

    EXPECT_EQ(data.first, 5);
    EXPECT_EQ(data.operation, '!');
    EXPECT_FALSE(data.hasSecond);
}

TEST(ParserTests, MissingFirstFieldThrows) {
    Parser parser;
    std::stringstream input(R"({
        "operation": "+",
        "second": 10
    })");

    EXPECT_THROW(parser.parse(input), std::invalid_argument);
}

TEST(ParserTests, MissingOperationFieldThrows) {
    Parser parser;
    std::stringstream input(R"({
        "first": 10,
        "second": 20
    })");

    EXPECT_THROW(parser.parse(input), std::invalid_argument);
}

TEST(ParserTests, OperationMustBeSingleCharacter) {
    Parser parser;
    std::stringstream input(R"({
        "first": 10,
        "operation": "add",
        "second": 20
    })");

    EXPECT_THROW(parser.parse(input), std::invalid_argument);
}

TEST(ParserTests, FirstMustBeInteger) {
    Parser parser;
    std::stringstream input(R"({
        "first": "abc",
        "operation": "+",
        "second": 20
    })");

    EXPECT_THROW(parser.parse(input), std::invalid_argument);
}

TEST(ParserTests, SecondMustBeIntegerIfPresent) {
    Parser parser;
    std::stringstream input(R"({
        "first": 10,
        "operation": "+",
        "second": "abc"
    })");

    EXPECT_THROW(parser.parse(input), std::invalid_argument);
}