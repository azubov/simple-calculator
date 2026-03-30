#include "Calculator.h"
#include "CalculatorCacheRepository.h"
#include "CalculatorRepository.h"
#include "CalculatorService.h"
#include "Checker.h"
#include "Log.h"
#include "PGConnection.h"
#include "Parser.h"
#include "Printer.h"
#include "Runner.h"

#include <fmt/format.h>

int main(int argc, char* argv[]) {
    Parser parser;
    Checker checker;
    Printer printer;

    try {
        PGConnection db_connection;
        CalculatorRepository repository(db_connection);
        CalculatorCacheRepository cache_repository(repository);
        Calculator calculator;
        CalculatorService calculator_service(cache_repository, calculator);
        Runner runner(parser, checker, calculator_service, printer);

        return runner.run(argc, argv);
    } catch (const std::exception& e) {
        printer.printException(e);
        Log::error("Runner finished with error");
        Log::error(fmt::format("Exception: {}", e.what()));

        return 1;
    }
}