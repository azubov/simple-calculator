#include "Runner.h"

#include "Log.h"

#include <string_view>

Runner::Runner(const Parser& parser, const Checker& checker, const Calculator& calculator,
               const Printer& printer) noexcept
    : parser_(parser)
    , checker_(checker)
    , calculator_(calculator)
    , printer_(printer) {}

int Runner::run(int argc, char* argv[]) const {
    Log::info("Runner started");

    if (handleHelpFlag(argc, argv)) {
        printer_.printHelp();

        Log::info("Runner finished successfully");
        return 0;
    }

    auto data = parser_.parse();
    checker_.validate(data);
    calculator_.calculate(data);
    printer_.printResult(data);

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