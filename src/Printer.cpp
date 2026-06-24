#include "Printer.h"

#include "Log.h"

#include <fmt/format.h>

Printer::Printer(std::ostringstream& out, std::ostringstream& err) noexcept
    : out_(out)
    , err_(err) {}

void Printer::printHelp() {
    Log::debug("Printing help..");
    out_ << "This is a simple calculator!\n"
         << "It only supports integers as arguments.\n"
         << "Usage: calc arg1 operation arg2\n"
         << "Supported operations:\n"
         << "+ [sum]\n"
         << "- [subtraction]\n"
         << "* [multiplication]\n"
         << "/ [division]\n"
         << "^ [exponentiation]\n"
         << "! [factorial]\n"
         << "Beware of an overflow!\n"
         << "The result should fit into a 64-bit integer.\n"
         << "Examples:\n"
         << "calc 3 + 5 -> 8\n"
         << "calc 10 - 7 -> 3\n"
         << "calc 2 * 3 -> 6\n"
         << "calc 10 / 2 -> 5\n"
         << "calc 2 ^ 3 -> 8\n"
         << "calc 4 ! -> 24\n";
}

void Printer::printResult(const OperationData& data) {
    Log::debug(fmt::format("Printing result: {}", data.result));
    out_ << data.result << '\n';
}

void Printer::printException(const std::exception& ex) {
    Log::error(fmt::format("Printing: {}", ex.what()));
    err_ << "Error: " << ex.what() << '\n';
}

std::string Printer::flush() {
    std::string result = out_.str() + err_.str();
    out_.str("");
    err_.str("");
    out_.clear();
    err_.clear();
    return result;
}