#include "Checker.h"

#include <stdexcept>
#include <string_view>

void Checker::validate(const OperationData& data) const {
    validateOperation(data.operation);
    validateArguments(data);
}

void Checker::validateOperation(char op) const {
    static constexpr std::string_view valid = "+-*/^!";
    if (valid.find(op) == std::string::npos) {
        throw std::invalid_argument("Unsupported operation. Run with --help for usage.");
    }
}

void Checker::validateArguments(const OperationData& data) const {
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