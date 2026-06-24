#pragma once

#include "OperationData.h"

#include <string>

class Parser {
public:
    OperationData parse(const std::string& msg) const;
};