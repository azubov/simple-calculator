#include "Application.h"
#include "Log.h"
#include <fmt/format.h>

int main(int argc, char* argv[]) {
    try {
        Log::setLogger(std::make_shared<SpdLogger>());
        Application app;
        return app.run(argc, argv);
    } catch (const std::exception& e) {
        Log::error(fmt::format("Exception: {}", e.what()));
        return 1;
    }
}