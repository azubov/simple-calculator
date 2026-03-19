#pragma once

#include "Logger.h"

#include <spdlog/logger.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <memory>

class SpdLogger : public Logger<SpdLogger> {
    friend struct Logger<SpdLogger>;

public:
    SpdLogger() {
        logger_ = spdlog::basic_logger_mt("calc_logger", "calculator.log");
        logger_->set_level(spdlog::level::debug);
        logger_->flush_on(spdlog::level::info);
    }

private:
    void infoImpl(std::string_view msg) {
        logger_->info(msg);
    }

    void debugImpl(std::string_view msg) {
        logger_->debug(msg);
    }

    void errorImpl(std::string_view msg) {
        logger_->error(msg);
    }

    std::shared_ptr<spdlog::logger> logger_;
};