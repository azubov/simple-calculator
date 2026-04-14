#pragma once

#include "logging/Logger.h"

class NullLogger : public Logger {
public:
    void info(std::string_view) override {}
    void debug(std::string_view) override {}
    void error(std::string_view) override {}
};