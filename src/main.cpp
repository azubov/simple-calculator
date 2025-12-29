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

int main(int argc, char *argv[]) {
    if (argc == 2 && std::string(argv[1]) == "--help") {
        print_help();
        return 0;
    }
    if (argc < 3) {
        std::cerr << "Invalid arguments. Use --help for usage.\n";
        return 1;
    }

    std::int64_t lhs = std::stoll(argv[1]);
    std::string operation = argv[2];
    std::int64_t rhs = 0;

    if (operation == "!") {
        if (argc != 3) {
            std::cerr << "Factorial requires exactly one argument.\n";
            return 1;
        }
    } else {
        if (argc != 4) {
            std::cerr << "Binary operations require two arguments.\n";
            return 1;
        }
        rhs = std::stoll(argv[3]);
    }

    try {
        if (operation == "+") {
            std::cout << mathlib::add(lhs, rhs) << "\n";
        } else if (operation == "-") {
            std::cout << mathlib::subtract(lhs, rhs) << "\n";
        } else if (operation == "*") {
            std::cout << mathlib::multiply(lhs, rhs) << "\n";
        } else if (operation == "/") {
            std::cout << mathlib::divide(lhs, rhs) << "\n";
        } else if (operation == "^") {
            std::cout << mathlib::power(lhs, rhs) << "\n";
        } else if (operation == "!") {
            std::cout << mathlib::factorial(lhs) << "\n";
        } else {
            std::cerr << "Unsupported operation" << "\n";
            return 1;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
    }

    return 0;
}
