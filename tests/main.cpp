#include <gtest/gtest.h>

#include "Log.h"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    Log::setLogger(std::make_shared<NullLogger>());

    return RUN_ALL_TESTS();
}