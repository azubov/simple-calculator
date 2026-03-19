#pragma once

#include "Calculator.h"
#include "Checker.h"
#include "Parser.h"
#include "Printer.h"

class Runner {
public:
    explicit Runner(const Parser& parser, const Checker& checker, const Calculator& calculator,
                    const Printer& printer) noexcept;

    int run(int argc, char* argv[]) const;

private:
    const Parser& parser_;
    const Checker& checker_;
    const Calculator& calculator_;
    const Printer& printer_;

    bool handleHelpFlag(int argc, char* argv[]) const;
};