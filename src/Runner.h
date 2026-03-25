#pragma once

#include "CalculatorService.h"
#include "Checker.h"
#include "Parser.h"
#include "Printer.h"

class Runner {
public:
    explicit Runner(
        const Parser& parser,
        const Checker& checker,
        const CalculatorService& calculator_service,
        const Printer& printer
    ) noexcept;

    int run(int argc, char* argv[]) const;

private:
    const Parser& parser_;
    const Checker& checker_;
    const CalculatorService& calculator_service_;
    const Printer& printer_;

    bool handleHelpFlag(int argc, char* argv[]) const;
};