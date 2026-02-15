#include "Runner.h"

#include <gtest/gtest.h>
#include <sstream>

TEST(RunnerTests, PrintsHelpAndExits) {
    Runner runner;
    char* argv[] = {(char*)"calc", (char*)"--help"};

    std::istringstream in("");
    std::ostringstream out;

    int code = runner.run(2, argv, in, out);

    EXPECT_EQ(code, 0);
    EXPECT_NE(out.str().find("This is a simple calculator!"), std::string::npos);
}

TEST(RunnerTests, UnknownArgumentProducesError) {
    Runner runner;
    char* argv[] = {(char*)"calc", (char*)"--unknown"};

    std::istringstream in("");
    std::ostringstream out;

    int code = runner.run(2, argv, in, out);

    EXPECT_EQ(code, 1);
    EXPECT_NE(out.str().find("Unknown argument"), std::string::npos);
}

TEST(RunnerTests, SuccessfulRun) {
    Runner runner;
    char* argv[] = {(char*)"calc"};

    std::istringstream in(R"({ "first": 3, "operation": "+", "second": 4 })");
    std::ostringstream out;

    int code = runner.run(1, argv, in, out);

    EXPECT_EQ(code, 0);
    EXPECT_NE(out.str().find("7"), std::string::npos);
}
TEST(RunnerTests, InvalidJsonTriggersException) {
    Runner runner;
    char* argv[] = {(char*)"calc"};

    std::istringstream in("{ invalid json }");
    std::ostringstream out;

    int code = runner.run(1, argv, in, out);

    EXPECT_EQ(code, 1);
    EXPECT_NE(out.str().find("exception"), std::string::npos);
}