#include "CachedCalculatorRepository.h"
#include "Calculator.h"
#include "CalculatorService.h"
#include "Checker.h"
#include "CpuHeavyCalculator.h"
#include "Log.h"
#include "PGConnection.h"
#include "Parser.h"
#include "PostgresCalculatorRepository.h"
#include "Printer.h"
#include "Runner.h"
#include "SimpleCalculator.h"
#include "StatementInitializer.h"

#include <fmt/format.h>

int main(int argc, char* argv[]) {
    Log::setLogger(std::make_shared<SpdLogger>());

    Parser parser;
    Checker checker;
    Printer printer;

    try {
        PGConnection db_connection;
        StatementInitializer::prepareCalculatorStatements(db_connection);

        PostgresCalculatorRepository pg_repository(db_connection);
        CachedCalculatorRepository cached_repository(pg_repository);
        cached_repository.fillCacheFromRepository();

#ifdef ENABLE_CPU_LOAD
        SimpleCalculator simple_calculator;
        CpuHeavyCalculator calculator(simple_calculator);
#else
        SimpleCalculator calculator;
#endif

        CalculatorService calculator_service(cached_repository, calculator);
        Runner runner(parser, checker, calculator_service, printer);

        return runner.run(argc, argv);
    } catch (const std::exception& e) {
        printer.printException(e);
        Log::error("Runner finished with error");
        Log::error(fmt::format("Exception: {}", e.what()));

        return 1;
    }
}