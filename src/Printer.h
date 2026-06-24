#pragma once

#include "OperationData.h"

#include <exception>
#include <sstream>
#include <string>

class Printer {
public:
    explicit Printer(std::ostringstream& out, std::ostringstream& err) noexcept;

    void printHelp();
    void printResult(const OperationData& data);
    void printException(const std::exception& ex);
    std::string flush();

private:
    std::ostringstream& out_;
    std::ostringstream& err_;
};