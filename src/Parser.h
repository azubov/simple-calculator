#pragma once

#include "OperationData.h"

#include "istream"
#include <iostream>

class Parser {
public:
    explicit Parser(std::istream& in = std::cin) noexcept;

    OperationData parse() const;

private:
    std::istream& in_;
};