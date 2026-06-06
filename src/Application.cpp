#include "Application.h"
#include "StatementInitializer.h"

Application::Application()
    : pg_repository_(db_connection_)
    , cached_repository_(pg_repository_)
#ifdef ENABLE_CPU_LOAD
    , heavy_calculator_(simple_calculator_)
    , calculator_service_(cached_repository_, heavy_calculator_)
#else
    , calculator_service_(cached_repository_, simple_calculator_)
#endif
    , runner_(parser_, checker_, calculator_service_, printer_) {

    StatementInitializer::prepareCalculatorStatements(db_connection_);
    cached_repository_.fillCacheFromRepository();
}

void Application::run(int argc, char* argv[]) {
    while (is_running_.load(std::memory_order_acquire)) {
        runner_.run(argc, argv);
    }
}

void Application::stop() {
    is_running_.store(false, std::memory_order_release);
}