#pragma once

#include "CalculatorRepository.h"

#include <gmock/gmock.h>

class MockRepository : public CalculatorRepository {
public:
    MOCK_METHOD(void, find, (OperationData&), (override));
    MOCK_METHOD(std::vector<OperationData>, findAll, (), (override));
    MOCK_METHOD(void, save, (const OperationData&), (override));
};