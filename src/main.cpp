#include "Calculator.h"
#include "Checker.h"
#include "Log.h"
#include "Parser.h"
#include "Printer.h"
#include "Runner.h"

#include <fmt/format.h>

int main(int argc, char* argv[]) {
    Parser parser;
    Checker checker;
    Calculator calculator;
    Printer printer;
    Runner runner(parser, checker, calculator, printer);

    try {
        return runner.run(argc, argv);
    } catch (const std::exception& e) {
        printer.printException(e);
        Log::error("Runner finished with error");
        Log::error(fmt::format("Exception: {}", e.what()));

        return 1;
    }
}