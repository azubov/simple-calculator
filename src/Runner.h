#pragma once

#include "CalculatorService.h"
#include "Checker.h"
#include "Parser.h"
#include "Printer.h"
#include "Server.h"

#include <atomic>

class Runner {
public:
    explicit Runner(
        const Parser& parser,
        const Checker& checker,
        CalculatorService& calculator_service,
        Printer& printer,
        Server& server
    ) noexcept;

    void run();
    void stop();

private:
    const Parser& parser_;
    const Checker& checker_;
    CalculatorService& calculator_service_;
    Printer& printer_;
    Server& server_;

    std::atomic<bool> is_running_{true};
};