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

int Application::run(int argc, char* argv[]) {
    return runner_.run(argc, argv);
}