#include "Checker.h"
#include "OperationData.h"

#include <gtest/gtest.h>
#include <stdexcept>

TEST(CheckerTest, ValidOperationsDoNotThrow) {
    Checker checker;

    const char ops[] = {'+', '-', '*', '/', '^', '!'};

    for (char op : ops) {
        OperationData data{0, 0, 0, op};
        EXPECT_NO_THROW(checker.validate(data));
    }
}

TEST(CheckerTest, InvalidOperationThrows) {
    Checker checker;

    OperationData data{1, 1, 0, '?'};

    EXPECT_THROW(checker.validate(data), std::invalid_argument);
}