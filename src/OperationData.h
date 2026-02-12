#pragma once

#include <cstdint>

struct OperationData {
    std::int64_t first{};
    std::int64_t second{};
    std::int64_t result{};
    char operation{};
};