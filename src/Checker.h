#pragma once

#include "OperationData.h"

class Checker {
public:
    void validate(const OperationData& data) const;

private:
    void validateOperation(char op) const;
    void validateArguments(const OperationData& data) const;
};