#pragma once

#include "Calculator.h"
#include "ICalculatorRepository.h"
#include "OperationData.h"

class CalculatorService {
public:
    explicit CalculatorService(
        const ICalculatorRepository& repository, const Calculator& calculator
    ) noexcept;

    void calculate(OperationData& data) const;

private:
    const ICalculatorRepository& repository_;
    const Calculator& calculator_;

    void
    saveWithStatus(OperationData& data, OperationData::Status status) const;
};