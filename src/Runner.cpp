#include "Runner.h"

#include "Calculator.h"
#include "Checker.h"
#include "Log.h"
#include "Parser.h"
#include "Printer.h"
#include <fmt/format.h>

#include <iostream>
#include <string_view>

int Runner::run(int argc, char* argv[]) const {
    return run(argc, argv, std::cin, std::cout);
}

int Runner::run(int argc, char* argv[], std::istream& in, std::ostream& out) const {
    Log::info("Runner started");

    Parser parser;
    Checker checker;
    Calculator calculator;
    Printer printer(out, out);

    try {
        if (handleHelpFlag(argc, argv)) {
            printer.printHelp();

            Log::info("Runner finished successfully");
            return 0;
        }

        auto data = parser.parse(in);
        checker.validate(data);
        calculator.calculate(data);
        printer.printResult(data);
    } catch (const std::exception& e) {
        Log::error(fmt::format("Exception: {}", e.what()));
        printer.printException(e);

        Log::error("Runner finished with error");
        return 1;
    }

    Log::info("Runner finished successfully");
    return 0;
}

bool Runner::handleHelpFlag(int argc, char* argv[]) const {
    if (argc > 1) {
        if (std::string_view(argv[1]) == "--help") {
            return true;
        }
        throw std::invalid_argument("Unknown argument. Use --help");
    }
    return false;
}