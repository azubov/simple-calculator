#pragma once

#include "OperationData.h"

#include "istream"

class Parser {
public:
    OperationData parse(std::istream& input) const;
};