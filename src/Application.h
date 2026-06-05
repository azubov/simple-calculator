#pragma once

#include "CachedCalculatorRepository.h"
#include "CalculatorService.h"
#include "Checker.h"
#include "PGConnection.h"
#include "Parser.h"
#include "PostgresCalculatorRepository.h"
#include "Printer.h"
#include "Runner.h"
#include "SimpleCalculator.h"

#ifdef ENABLE_CPU_LOAD
#    include "CpuHeavyCalculator.h"
#endif

class Application {

public:
    Application();
    int run(int argc, char* argv[]);

private:
    Parser parser_;
    Checker checker_;
    Printer printer_;
    PGConnection db_connection_;
    PostgresCalculatorRepository pg_repository_;
    CachedCalculatorRepository cached_repository_;
    SimpleCalculator simple_calculator_;
#ifdef ENABLE_CPU_LOAD
    CpuHeavyCalculator heavy_calculator_;
#endif
    CalculatorService calculator_service_;
    Runner runner_;
};