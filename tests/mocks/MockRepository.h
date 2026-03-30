#pragma once

#include "CalculatorRepository.h"

#include <gmock/gmock.h>

class MockRepository : public ICalculatorRepository {
public:
    MOCK_METHOD(void, find, (OperationData&), (override));
    MOCK_METHOD(void, save, (const OperationData&), (override));
};
