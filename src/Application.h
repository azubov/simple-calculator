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

#include <atomic>

class Application {

public:
    Application();
    void run(int argc, char* argv[]);
    void stop();

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

    std::atomic<bool> is_running_{true};
};