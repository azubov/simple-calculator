#include "Checker.h"

#include <stdexcept>
#include <string_view>

void Checker::validate(const OperationData& data) const {
    static constexpr std::string_view valid_operations = "+-*/^!";
    if (valid_operations.find(data.operation) == std::string::npos) {
        throw std::invalid_argument("Unsupported operation. Run with --help for usage.");
    }
}