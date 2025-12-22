#include "math_operations.h"

#include <cstdint>
#include <iostream>
#include <string>
#include <stdexcept>

void PrintHelp() {
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
        PrintHelp();
        return 0;
    }
    if (argc < 3) {
        std::cerr << "Invalid arguments. Use --help for usage.\n";
        return 1;
    }

    int64_t a = std::stoll(argv[1]);
    std::string op = argv[2];
    int64_t b = 0;

    if (op == "!") {
        if (argc != 3) {
            std::cerr << "Factorial requires exactly one argument.\n";
            return 1;
        }
    } else {
        if (argc != 4) {
            std::cerr << "Binary operations require two arguments.\n";
            return 1;
        }
        b = std::stoll(argv[3]);
    }

    try {
        if (op == "+") {
            std::cout << Mathlib::add(a, b) << "\n";
        } else if (op == "-") {
            std::cout << Mathlib::sub(a, b) << "\n";
        } else if (op == "*") {
            std::cout << Mathlib::mul(a, b) << "\n";
        } else if (op == "/") {
            std::cout << Mathlib::div(a, b) << "\n";
        } else if (op == "^") {
            std::cout << Mathlib::pow(a, b) << "\n";
        } else if (op == "!") {
            std::cout << Mathlib::factorial(a) << "\n";
        } else {
            std::cerr << "Unsupported operation" << "\n";
            return 1;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
    }

    return 0;
}
