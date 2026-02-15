#include "Calculator.h"
#include "Checker.h"
#include "Parser.h"
#include "Printer.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    Parser parser;
    Checker checker;
    Calculator caclulator;
    Printer printer;

    try {
        if (argc > 1) {
            std::string arg = argv[1];
            if (arg == "--help") {
                printer.printHelp();
                return 0;
            }
            throw std::invalid_argument("Unknown argument. Use --help");
        }

        auto data = parser.parse(std::cin);
        checker.validate(data);
        caclulator.calculate(data);
        printer.printResult(data);
    } catch (const std::exception& e) {
        printer.printException(e);
        return 1;
    }
    return 0;
}