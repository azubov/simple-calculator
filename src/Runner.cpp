#include "Runner.h"

#include "Calculator.h"
#include "Checker.h"
#include "Parser.h"
#include "Printer.h"

#include <iostream>
#include <string>

int Runner::run(int argc, char* argv[]) const {
    return run(argc, argv, std::cin, std::cout);
}

int Runner::run(int argc, char* argv[], std::istream& in, std::ostream& out) const {
    Parser parser;
    Checker checker;
    Calculator calculator;
    Printer printer(out, out);

    try {
        if (handleHelpFlag(argc, argv, printer)) {
            return 0;
        }

        auto data = parser.parse(in);
        checker.validate(data);
        calculator.calculate(data);
        printer.printResult(data);
    } catch (const std::exception& e) {
        printer.printException(e);
        return 1;
    }
    return 0;
}

bool Runner::handleHelpFlag(int argc, char* argv[], const Printer& printer) const {
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "--help") {
            printer.printHelp();
            return true;
        }
        throw std::invalid_argument("Unknown argument. Use --help");
    }
    return false;
}