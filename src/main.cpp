#include "Application.h"
#include "Log.h"
#include "SystemSignal.h"

#include <fmt/format.h>

#include <csignal>
#include <thread>

int main(int argc, char* argv[]) {
    try {
        Log::setLogger(std::make_shared<SpdLogger>());
        Application app;
        SystemSignal sys_signal{{SIGTERM, SIGINT}, [&app] {
                                    app.stop();
                                }};

        std::thread sig_thr(&SystemSignal::listen, &sys_signal);
        std::thread wrk_thr(&Application::run, &app, argc, argv);

        sys_signal.ready();

        sig_thr.join();
        wrk_thr.join();

    } catch (const std::exception& e) {
        Log::error(fmt::format("Exception: {}", e.what()));
        return 1;
    }
}