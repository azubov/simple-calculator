#pragma once

#include <string_view>

struct Logger {
    virtual ~Logger() = default;
    virtual void info(std::string_view msg) = 0;
    virtual void debug(std::string_view msg) = 0;
    virtual void error(std::string_view msg) = 0;
};