#pragma once

#include "Calculator.h"

class SimpleCalculator : public Calculator {
public:
    void calculate(OperationData&) const override;
};