#include "Application.h"
#include "Log.h"
#include "SystemSignal.h"

#include <fmt/format.h>

#include <csignal>
#include <thread>

int main() {
    try {
        Log::setLogger(std::make_shared<SpdLogger>());
        Log::info("Starting application..");
        Application app;
        SystemSignal sys_signal{{SIGTERM, SIGINT}, [&app] {
                                    app.stop();
                                }};

        std::thread sig_thr(&SystemSignal::listen, &sys_signal);
        std::thread wrk_thr(&Application::run, &app);

        sys_signal.ready();
        Log::info("Application started");

        sig_thr.join();
        wrk_thr.join();

    } catch (const std::exception& e) {
        Log::error(fmt::format("Exception: {}", e.what()));
        return 1;
    }
    Log::info("Application stopped");
    return 0;
}