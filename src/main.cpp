#include <charconv>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <system_error>

#include <mathlib/math_operations.h>

void printHelp() {
    std::cout << "This is a simple calculator!\n"
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
              << "The result should fit into a 64‑bit integer.\n"
              << "Examples:\n"
              << "calc 3 + 5 -> 8\n"
              << "calc 10 - 7 -> 3\n"
              << "calc 2 * 3 -> 6\n"
              << "calc 10 / 2 -> 5\n"
              << "calc 2 ^ 3 -> 8\n"
              << "calc 4 ! -> 24\n";
}

struct OperationData {
    std::int64_t first{};
    std::int64_t second{};
    std::int64_t result{};
    char operation{};
};

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

void calculate(OperationData& data) {
    if (data.operation == '+') {
        data.result = mathlib::add(data.first, data.second);
    } else if (data.operation == '-') {
        data.result = mathlib::subtract(data.first, data.second);
    } else if (data.operation == '*') {
        data.result = mathlib::multiply(data.first, data.second);
    } else if (data.operation == '/') {
        data.result = mathlib::divide(data.first, data.second);
    } else if (data.operation == '^') {
        data.result = mathlib::power(data.first, data.second);
    } else if (data.operation == '!') {
        data.result = mathlib::factorial(data.first);
    }
}

void output(const OperationData& data) {
    std::cout << data.result << '\n';
}

int main(int argc, char* argv[]) {
    if (argc == 2 && std::string(argv[1]) == "--help") {
        printHelp();
        return 0;
    }
    try {
        auto data = parse(argc, argv);
        validate(data);
        calculate(data);
        output(data);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}