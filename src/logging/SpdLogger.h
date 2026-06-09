#pragma once

#include "logging/Logger.h"

#include <spdlog/logger.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <cstdlib>
#include <string>

class SpdLogger : public Logger {
public:
    explicit SpdLogger() {
        const char* env = std::getenv("CALC_LOG_PATH");
        const std::string path = (env != nullptr && env[0] != '\0')
                                     ? std::string(env)
                                     : "calculator.log";

        logger_ = spdlog::basic_logger_mt("calc_logger", path);
        logger_->set_level(spdlog::level::debug);
        logger_->flush_on(spdlog::level::info);
        logger_->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [Thread ID=%t] [%l] %v");
    }

    void info(std::string_view msg) override {
        logger_->info(msg);
    }

    void debug(std::string_view msg) override {
        logger_->debug(msg);
    }

    void error(std::string_view msg) override {
        logger_->error(msg);
    }

private:
    std::shared_ptr<spdlog::logger> logger_;
};