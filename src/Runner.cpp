#include "Runner.h"
#include "Log.h"

Runner::Runner(
    const Parser& parser,
    const Checker& checker,
    CalculatorService& calculator_service,
    Printer& printer,
    Server& server
) noexcept
    : parser_(parser)
    , checker_(checker)
    , calculator_service_(calculator_service)
    , printer_(printer)
    , server_(server) {}

void Runner::run() {
    Log::info("Runner started");

    while (is_running_.load(std::memory_order_acquire)) {
        try {
            auto [has_data, msg] = server_.receive();
            if (!has_data) {
                continue;
            }
            if (msg[0] == '{') {
                auto data = parser_.parse(msg);
                checker_.validate(data);
                calculator_service_.calculate(data);
                printer_.printResult(data);
            } else if (msg == "--help") {
                printer_.printHelp();
            } else {
                printer_.printException(
                    std::invalid_argument("Unknown argument. Use --help")
                );
            }
        } catch (const std::invalid_argument& ia) {
            printer_.printException(ia);
        } catch (const std::overflow_error& oe) {
            printer_.printException(oe);
        }
        server_.send(printer_.flush());
    }
    Log::info("Runner finished successfully");
}

void Runner::stop() {
    Log::info("Stopping runner..");
    is_running_.store(false, std::memory_order_release);
}