#pragma once

#include "OperationData.h"

#include <vector>

class CalculatorRepository {
public:
    virtual void find(OperationData&) = 0;
    virtual std::vector<OperationData> findAll() = 0;
    virtual void save(const OperationData&) = 0;
    virtual ~CalculatorRepository() = default;
};