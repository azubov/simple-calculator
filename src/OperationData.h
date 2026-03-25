#pragma once

#include <cstdint>

struct OperationData {
    enum class Status { success, undefined, invalid_argument, overflow_error };

    std::int64_t first{};
    std::int64_t second{};
    std::int64_t result{};
    char operation{};
    bool hasSecond{false};
    Status status{Status::undefined};
};