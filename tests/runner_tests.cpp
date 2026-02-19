#include "Runner.h"

#include <gtest/gtest.h>
#include <sstream>

TEST(RunnerTests, PrintsHelpAndExits) {
    std::istringstream in("");
    std::ostringstream out;

    Parser parser(in);
    Checker checker;
    Calculator calculator;
    Printer printer(out, out);
    Runner runner(parser, checker, calculator, printer);

    char* argv[] = {(char*)"calc", (char*)"--help"};

    int code = runner.run(2, argv);

    EXPECT_EQ(code, 0);
    EXPECT_NE(out.str().find("This is a simple calculator!"), std::string::npos);
}

TEST(RunnerTests, UnknownArgumentProducesError) {
    std::istringstream in("");
    std::ostringstream out;

    Parser parser(in);
    Checker checker;
    Calculator calculator;
    Printer printer(out, out);
    Runner runner(parser, checker, calculator, printer);

    char* argv[] = {(char*)"calc", (char*)"--unknown"};

    int code = runner.run(2, argv);

    EXPECT_EQ(code, 1);
    EXPECT_NE(out.str().find("Unknown argument"), std::string::npos);
}

TEST(RunnerTests, SuccessfulRun) {
    std::istringstream in(R"({ "first": 3, "operation": "+", "second": 4 })");
    std::ostringstream out;

    Parser parser(in);
    Checker checker;
    Calculator calculator;
    Printer printer(out, out);
    Runner runner(parser, checker, calculator, printer);

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
    Calculator calculator;
    Printer printer(out, out);
    Runner runner(parser, checker, calculator, printer);

    char* argv[] = {(char*)"calc"};

    int code = runner.run(1, argv);

    EXPECT_EQ(code, 1);
    EXPECT_NE(out.str().find("exception"), std::string::npos);
}