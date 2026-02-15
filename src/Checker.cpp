#include "Checker.h"

#include "Logger.h"

#include <stdexcept>
#include <string_view>

void Checker::validate(const OperationData& data) const {
    auto log = Logger::instance().get();
    log->info("Staring to validate OperationData..");

    validateOperation(data.operation);
    validateArguments(data);

    log->info("OperationData validated successfully");
}

void Checker::validateOperation(char op) const {
    auto log = Logger::instance().get();
    log->debug("Validating operation..");

    static constexpr std::string_view valid = "+-*/^!";
    if (valid.find(op) == std::string::npos) {
        throw std::invalid_argument("Unsupported operation. Run with --help for usage.");
    }
}

void Checker::validateArguments(const OperationData& data) const {
    auto log = Logger::instance().get();
    log->debug("Validating arguments..");

    if (data.operation == '!') {
        if (data.hasSecond) {
            throw std::invalid_argument("Factorial requires exactly one operand (e.g., calc 5 !).");
        }
    } else {
        if (!data.hasSecond) {
            throw std::invalid_argument("Binary operations require two operands (e.g., calc 3 + 4).");
        }
    }
}