#pragma once

#include "OperationData.h"

class ICalculator {
public:
    virtual ~ICalculator() = default;
    virtual void calculate(OperationData& data) const = 0;
};

class Calculator : public ICalculator {
public:
    void calculate(OperationData& data) const override;
};