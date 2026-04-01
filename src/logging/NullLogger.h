#pragma once

#include "logging/Logger.h"

class NullLogger : public Logger<NullLogger> {
    friend struct Logger<NullLogger>;

private:
    void infoImpl(std::string_view) {}
    void debugImpl(std::string_view) {}
    void errorImpl(std::string_view) {}
};