#pragma once

#include "Calculator.h"
#include "CalculatorRepository.h"
#include "OperationData.h"

class CalculatorService {
public:
    explicit CalculatorService(
        CalculatorRepository& repository, const Calculator& calculator
    ) noexcept;

    void calculate(OperationData& data);

private:
    CalculatorRepository& repository_;
    const Calculator& calculator_;

    void
    saveWithStatus(OperationData& data, OperationData::Status status) const;
};