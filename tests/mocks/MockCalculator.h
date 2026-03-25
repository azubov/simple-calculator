#pragma once

#include "Calculator.h"

#include <gmock/gmock.h>

class MockCalculator : public ICalculator {
public:
    MOCK_METHOD(void, calculate, (OperationData&), (const));
};
