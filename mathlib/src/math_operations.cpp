#include "math_operations.h"

#include <cstdint>
#include <limits>
#include <stdexcept>

namespace Mathlib {
    int64_t add(int64_t a, int64_t b) {
        if (b > 0 && a > std::numeric_limits<int64_t>::max() - b)
            throw std::overflow_error("Overflow detected");
        if (b < 0 && a < std::numeric_limits<int64_t>::min() - b)
            throw std::overflow_error("Overflow detected");
        return a + b;
    }

    int64_t sub(int64_t a, int64_t b) {
        return add(a, -b);
    }

    int64_t mul(int64_t a, int64_t b) {
        if (a == 0 || b == 0) return 0;
        if (a > 0) {
            if (b > 0 && a > std::numeric_limits<int64_t>::max() / b)
                throw std::overflow_error("Overflow detected");
            if (b < 0 && b < std::numeric_limits<int64_t>::min() / a)
                throw std::overflow_error("Overflow detected");
        } else {
            if (b > 0 && a < std::numeric_limits<int64_t>::min() / b)
                throw std::overflow_error("Overflow detected");
            if (b < 0 && a < std::numeric_limits<int64_t>::max() / b)
                throw std::overflow_error("Overflow detected");
        }
        return a * b;
    }

    int64_t div(int64_t a, int64_t b) {
        if (b == 0)
            throw std::invalid_argument("Division by zero");
        if (a == std::numeric_limits<int64_t>::min() && b == -1)
            throw std::overflow_error("Overflow detected");
        return a / b;
    }

    int64_t pow(int64_t a, int64_t b) {
        if (b < 0)
            throw std::invalid_argument("Negative exponent not supported");

        int64_t result = 1;
        for (int64_t i = 0; i < b; ++i) {
            result = mul(result, a);
        }
        return result;
    }

    int64_t factorial(int64_t n) {
        if (n < 0)
            throw std::invalid_argument("Factorial is not defined for negative numbers");

        if (n == 0 || n == 1) return 1;
        return mul(n, factorial(n - 1));
    }
}
