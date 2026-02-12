#include "Calculator.h"
#include "OperationData.h"
#include "Printer.h"

#include <charconv>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <string>
#include <system_error>

std::int64_t parseInt64(const char* s) {
    if (s == nullptr) {
        throw std::invalid_argument(std::string("Invalid integer: nullptr"));
    }
    std::int64_t result = 0;
    const char* begin = s;
    const char* end = s + std::strlen(s);
    if (auto [ptr, ec] = std::from_chars(begin, end, result); ec != std::errc() || ptr != end) {
        throw std::invalid_argument(std::string("Invalid integer: ") + s);
    }
    return result;
}

char parseOperation(const char* s) {
    if (s == nullptr) {
        throw std::invalid_argument(std::string("Invalid operation: nullptr"));
    }
    if (std::strlen(s) != 1) {
        throw std::invalid_argument("Operation must be a single character. Run with --help for usage.");
    }
    return s[0];
}

OperationData parse(int argc, char* argv[]) {
    if (argc < 3) {
        throw std::invalid_argument("Invalid arguments. Run with --help for usage.");
    }

    OperationData data;
    data.first = parseInt64(argv[1]);
    data.operation = parseOperation(argv[2]);

    if (data.operation == '!') {
        if (argc != 3) {
            throw std::invalid_argument("Factorial requires exactly one operand (e.g.,: calc 5 !).");
        }
    } else {
        if (argc != 4) {
            throw std::invalid_argument("Binary operations require two operands (e.g.,: calc 3 + 4).");
        }
        data.second = parseInt64(argv[3]);
    }
    return data;
}

void validate(const OperationData& data) {
    static constexpr std::string_view valid_operations = "+-*/^!";
    if (valid_operations.find(data.operation) == std::string::npos) {
        throw std::invalid_argument("Unsupported operation. Run with --help for usage.");
    }
}

int main(int argc, char* argv[]) {
    Calculator caclulator;
    Printer printer;
    if (argc == 2 && std::string(argv[1]) == "--help") {
        printer.printHelp();
        return 0;
    }
    try {
        auto data = parse(argc, argv);
        validate(data);
        caclulator.calculate(data);
        printer.printResult(data);
    } catch (const std::exception& e) {
        printer.printException(e);
        return 1;
    }
    return 0;
}