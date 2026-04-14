#pragma once

#include "logging/Logger.h"
#include "logging/NullLogger.h"
#include "logging/OperationDataFormatter.h"
#include "logging/SpdLogger.h"

#include <memory>
#include <utility>

class Log {
public:
    static void setLogger(std::shared_ptr<Logger> logger) {
        instatnce() = std::move(logger);
    }

    static void info(std::string_view msg) {
        instatnce()->info(msg);
    };
    static void debug(std::string_view msg) {
        instatnce()->debug(msg);
    }
    static void error(std::string_view msg) {
        instatnce()->error(msg);
    }

private:
    static std::shared_ptr<Logger>& instatnce() {
        static std::shared_ptr<Logger> instatnce;
        return instatnce;
    }
};