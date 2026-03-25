#pragma once

#include "Calculator.h"
#include "CalculatorRepository.h"
#include "OperationData.h"

class CalculatorService {
public:
    explicit CalculatorService(
        const ICalculatorRepository& repository, const ICalculator& calculator
    ) noexcept;

    void calculate(OperationData& data) const;

private:
    const ICalculatorRepository& repository_;
    const ICalculator& calculator_;

    void
    saveWithStatus(OperationData& data, OperationData::Status status) const;
};