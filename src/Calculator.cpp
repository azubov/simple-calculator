#include "Calculator.h"

#include "Log.h"

#include <mathlib/math_operations.h>

void Calculator::calculate(OperationData& data) const {
    Log::info("Staring to calculate..");

    if (data.operation == '+') {
        data.result = mathlib::add(data.first, data.second);
    } else if (data.operation == '-') {
        data.result = mathlib::subtract(data.first, data.second);
    } else if (data.operation == '*') {
        data.result = mathlib::multiply(data.first, data.second);
    } else if (data.operation == '/') {
        data.result = mathlib::divide(data.first, data.second);
    } else if (data.operation == '^') {
        data.result = mathlib::power(data.first, data.second);
    } else if (data.operation == '!') {
        data.result = mathlib::factorial(data.first);
    }

    Log::info("Calculation finished successfully");
}