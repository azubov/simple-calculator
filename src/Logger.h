#pragma once

#include "spdlog/common.h"
#include "spdlog/logger.h"
#include "spdlog/sinks/basic_file_sink.h"
#include <memory>
#include <spdlog/spdlog.h>

class Logger {
public:
    static Logger& instance() {
        static Logger instance;
        return instance;
    }

    std::shared_ptr<spdlog::logger> get() {
        return logger_;
    }

private:
    Logger() {
        logger_ = spdlog::basic_logger_mt("calc_logger", "calculator.log");
        logger_->set_level(spdlog::level::debug);
        logger_->flush_on(spdlog::level::info);
    }

    std::shared_ptr<spdlog::logger> logger_;
};