#pragma once

#include "Calculator.h"

#include <gmock/gmock.h>

class MockCalculator : public Calculator {
public:
    MOCK_METHOD(void, calculate, (OperationData&), (const));
};
