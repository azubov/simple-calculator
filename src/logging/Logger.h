#pragma once

#include <string_view>

template <typename T>
struct Logger {
    static T& instance() {
        static T impl;
        return impl;
    }

    static void info(std::string_view msg) {
        instance().infoImpl(msg);
    }
    static void debug(std::string_view msg) {
        instance().debugImpl(msg);
    }
    static void error(std::string_view msg) {
        instance().errorImpl(msg);
    }
};

template <typename T>
using LoggerSelector = T;