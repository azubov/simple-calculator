#include "Application.h"
#include "StatementInitializer.h"

Application::Application()
    : printer_(out_buf_, err_buf_)
    , pg_repository_(db_connection_)
    , cached_repository_(pg_repository_)
#ifdef ENABLE_CPU_LOAD
    , heavy_calculator_(simple_calculator_)
    , calculator_service_(cached_repository_, heavy_calculator_)
#else
    , calculator_service_(cached_repository_, simple_calculator_)
#endif
    , server_("tcp://*:5555")
    , runner_(parser_, checker_, calculator_service_, printer_, server_) {

    StatementInitializer::prepareCalculatorStatements(db_connection_);
    cached_repository_.fillCacheFromRepository();
}

void Application::run() {
    runner_.run();
}

void Application::stop() {
    runner_.stop();
}