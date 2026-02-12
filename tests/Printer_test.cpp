#include "OperationData.h"
#include "Printer.h"

#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>

TEST(PrinterTest, PrintResultWritesToOutStream) {
    std::ostringstream out;
    std::ostringstream err;
    Printer printer(out, err);

    OperationData d;
    d.result = 66;

    printer.printResult(d);

    EXPECT_EQ(out.str(), "66\n");
    EXPECT_TRUE(err.str().empty());
}

TEST(PrinterTest, PrintExceptionWritesToErrStream) {
    std::ostringstream out;
    std::ostringstream err;
    Printer printer(out, err);

    std::runtime_error ex("error");
    printer.printException(ex);

    EXPECT_EQ(err.str(), "error\n");
    EXPECT_TRUE(out.str().empty());
}

TEST(PrinterTest, PrintHelpContainsUsage) {
    std::ostringstream out;
    std::ostringstream err;
    Printer printer(out, err);

    printer.printHelp();
    const auto s = out.str();

    EXPECT_NE(s.find("Usage: calc arg1 operation arg2"), std::string::npos);
    EXPECT_TRUE(err.str().empty());
}