#pragma once

#include "Calculator.h"

class CpuHeavyCalculator : public Calculator {
public:
    explicit CpuHeavyCalculator(const Calculator& calculator);

    void calculate(OperationData&) const override;

private:
    const Calculator& calculator_;
};