#pragma once

#include "OperationData.h"

class Calculator {
public:
    virtual void calculate(OperationData&) const = 0;
    virtual ~Calculator() = default;
};