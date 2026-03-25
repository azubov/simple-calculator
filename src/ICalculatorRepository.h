#pragma once

#include "OperationData.h"

class ICalculatorRepository {
public:
    virtual void find(OperationData&) const = 0;
    virtual void save(const OperationData&) const = 0;
    virtual ~ICalculatorRepository() = default;
};
