#include "Runner.h"

#include "mocks/MockCalculator.h"
#include "mocks/MockRepository.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>

using ::testing::_;
using ::testing::Invoke;
using ::testing::Throw;

TEST(RunnerTests, PrintsHelpAndExits) {
    std::istringstream in("");
    std::ostringstream out;

    Parser parser(in);
    Checker checker;
    MockRepository calculator_repository;
    MockCalculator calculator;
    CalculatorService calculator_service(calculator_repository, calculator);
    Printer printer(out, out);
    Runner runner(parser, checker, calculator_service, printer);

    char* argv[] = {(char*)"calc", (char*)"--help"};

    int code = runner.run(2, argv);

    EXPECT_EQ(code, 0);
    EXPECT_NE(
        out.str().find("This is a simple calculator!"), std::string::npos
    );
}

TEST(RunnerTests, UnknownArgumentProducesError) {
    std::istringstream in("");
    std::ostringstream out;

    Parser parser(in);
    Checker checker;
    MockRepository calculator_repository;
    MockCalculator calculator;
    CalculatorService calculator_service(calculator_repository, calculator);
    Printer printer(out, out);
    Runner runner(parser, checker, calculator_service, printer);

    char* argv[] = {(char*)"calc", (char*)"--unknown"};

    EXPECT_THROW(runner.run(2, argv), std::invalid_argument);
}

TEST(RunnerTests, SuccessfulRun) {
    std::istringstream in(R"({ "first": 3, "operation": "+", "second": 4 })");
    std::ostringstream out;

    Parser parser(in);
    Checker checker;
    MockRepository calculator_repository;
    MockCalculator calculator;
    CalculatorService calculator_service(calculator_repository, calculator);
    Printer printer(out, out);
    Runner runner(parser, checker, calculator_service, printer);

    EXPECT_CALL(calculator, calculate(_)).WillOnce(Invoke([](OperationData& d) {
        d.result = 7;
    }));

    char* argv[] = {(char*)"calc"};

    int code = runner.run(1, argv);

    EXPECT_EQ(code, 0);
    EXPECT_NE(out.str().find('7'), std::string::npos);
}

TEST(RunnerTests, InvalidJsonTriggersException) {
    std::istringstream in("{ invalid json }");
    std::ostringstream out;

    Parser parser(in);
    Checker checker;
    MockRepository calculator_repository;
    MockCalculator calculator;
    CalculatorService calculator_service(calculator_repository, calculator);
    Printer printer(out, out);
    Runner runner(parser, checker, calculator_service, printer);

    char* argv[] = {(char*)"calc"};

    EXPECT_THROW(runner.run(1, argv), std::exception);
}