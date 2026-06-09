#include "OperationData.h"
#include "Runner.h"

#include "mocks/MockCalculator.h"
#include "mocks/MockRepository.h"
#include "mocks/MockServer.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::HasSubstr;
using ::testing::Invoke;
using ::testing::Not;
using ::testing::Return;
using ::testing::SaveArg;

class RunnerTests : public ::testing::Test {
protected:
    Parser parser;
    Checker checker;
    MockRepository calculator_repository;
    MockCalculator calculator;
    CalculatorService calculator_service{calculator_repository, calculator};

    std::ostringstream dummy_out;
    std::ostringstream dummy_err;
    Printer printer{dummy_out, dummy_err};

    MockServer server;
    Runner runner{parser, checker, calculator_service, printer, server};
};

TEST_F(RunnerTests, PrintsHelp) {
    std::string sent_msg;

    EXPECT_CALL(server, receive())
        .WillOnce(Return(std::make_pair(true, "--help")))
        .WillOnce(Invoke([this]() {
            runner.stop();
            return std::make_pair(false, std::string{});
        }));

    EXPECT_CALL(server, send(_)).WillOnce(SaveArg<0>(&sent_msg));

    runner.run();

    EXPECT_THAT(sent_msg, HasSubstr("This is a simple calculator!"));
    EXPECT_THAT(sent_msg, Not(HasSubstr("Error")));
}

TEST_F(RunnerTests, UnknownArgumentTriggersException) {
    std::string sent_msg;

    EXPECT_CALL(server, receive())
        .WillOnce(Return(std::make_pair(true, "--unknown")))
        .WillOnce(Invoke([this]() {
            runner.stop();
            return std::make_pair(false, std::string{});
        }));

    EXPECT_CALL(server, send(_)).WillOnce(SaveArg<0>(&sent_msg));

    runner.run();

    EXPECT_THAT(sent_msg, HasSubstr("Unknown argument. Use --help"));
}

TEST_F(RunnerTests, SuccessfulRun) {
    std::string sent_msg;
    std::string json_input = R"({ "first": 3, "operation": "+", "second": 4 })";

    EXPECT_CALL(server, receive())
        .WillOnce(Return(std::make_pair(true, json_input)))
        .WillOnce(Invoke([this]() {
            runner.stop();
            return std::make_pair(false, std::string{});
        }));

    EXPECT_CALL(calculator_repository, find(_)).Times(1);
    EXPECT_CALL(calculator, calculate(_)).WillOnce(Invoke([](OperationData& d) {
        d.result = 7;
    }));
    EXPECT_CALL(calculator_repository, save(_)).Times(1);

    EXPECT_CALL(server, send(_)).WillOnce(SaveArg<0>(&sent_msg));

    runner.run();

    EXPECT_THAT(sent_msg, HasSubstr("7"));
    EXPECT_THAT(sent_msg, Not(HasSubstr("Error")));
}