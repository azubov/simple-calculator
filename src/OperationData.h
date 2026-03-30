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

    bool operator==(const OperationData& other) const noexcept {
        return first == other.first && second == other.second &&
               operation == other.operation && hasSecond == other.hasSecond &&
               result == other.result && status == other.status;
    }
};