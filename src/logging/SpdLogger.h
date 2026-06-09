#pragma once

#include "logging/Logger.h"

#include <spdlog/logger.h>
#include <spdlog/sinks/basic_file_sink.h>

class SpdLogger : public Logger {
public:
    explicit SpdLogger() {
        logger_ = spdlog::basic_logger_mt("calc_logger", "calculator.log");
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