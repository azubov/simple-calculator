#pragma once

#include "OperationData.h"

#include <cstdint>

namespace testhelper {
    inline OperationData makeBinaryOp(std::int64_t a, char op, std::int64_t b) {
        OperationData d{};
        d.first = a;
        d.operation = op;
        d.hasSecond = true;
        d.second = b;
        return d;
    }

    inline OperationData makeUnaryOp(std::int64_t a, char op) {
        OperationData d{};
        d.first = a;
        d.operation = op;
        d.hasSecond = false;
        return d;
    }
} // namespace testhelper