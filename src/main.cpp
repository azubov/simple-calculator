#include "mathlib/math_operations.h"

#include <cstdint>
#include <iostream>
#include <string>
#include <stdexcept>

void print_help() {
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
    std::string_view operation;
    std::string result;
};

OperationData parse(int argc, char *argv[]) {
    if (argc == 2 && std::string(argv[1]) == "--help") {
        print_help();
        std::exit(0);
    }
    if (argc < 3) {
        throw std::invalid_argument("Invalid arguments. Run with --help for usage.");
    }

    OperationData data;
    data.first = std::stoll(argv[1]);
    data.operation = argv[2];

    if (data.operation == "!") {
        if (argc != 3) {
            throw std::invalid_argument("Factorial requires exactly one argument.");
        }
    } else {
        if (argc != 4) {
            throw std::invalid_argument("Binary operations require two arguments.");
        }
        data.second = std::stoll(argv[3]);
    }
    return data;
}

void validate(const OperationData &data) {
    static constexpr std::string_view kValidOperations = "+-*/^!";
    if (kValidOperations.find(data.operation) == std::string::npos) {
        throw std::invalid_argument("Unsupported operation. Run with --help for usage.");
    }
}

void calculate(OperationData &data) {
    if (data.operation == "+") {
        data.result = std::to_string(mathlib::add(data.first, data.second));
    } else if (data.operation == "-") {
        data.result = std::to_string(mathlib::subtract(data.first, data.second));
    } else if (data.operation == "*") {
        data.result = std::to_string(mathlib::multiply(data.first, data.second));
    } else if (data.operation == "/") {
        data.result = std::to_string(mathlib::divide(data.first, data.second));
    } else if (data.operation == "^") {
        data.result = std::to_string(mathlib::power(data.first, data.second));
    } else if (data.operation == "!") {
        data.result = std::to_string(mathlib::factorial(data.first));
    }
}

void output(const OperationData &data) {
    std::cout << data.result << "\n";
}

int main(int argc, char *argv[]) {
    try {
        auto data = parse(argc, argv);
        validate(data);
        calculate(data);
        output(data);
    } catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
