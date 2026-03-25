#pragma once

#include "OperationData.h"

#include <fmt/format.h>

template <>
struct fmt::formatter<OperationData> {
    constexpr auto parse(fmt::format_parse_context& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const OperationData& d, FormatContext& ctx) {
        return fmt::format_to(
            ctx.out(),
            "{{ first={}, second={}, operation={}, result={}, hasSecond={}, "
            "status={} }}",
            d.first,
            d.hasSecond ? fmt::format_int(d.second).str() : "null",
            d.operation,
            d.result,
            d.hasSecond ? "true" : "false",
            statusToString(d.status)
        );
    }

private:
    static constexpr const char* statusToString(OperationData::Status s) {
        switch (s) {
        case OperationData::Status::success:
            return "success";
        case OperationData::Status::undefined:
            return "undefined";
        case OperationData::Status::invalid_argument:
            return "invalid_argument";
        case OperationData::Status::overflow_error:
            return "overflow_error";
        }
        return "unknown";
    }
};
