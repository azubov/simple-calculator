#include "OperationData.h"

#include <exception>
#include <iostream>
#include <ostream>

class Printer {
public:
    explicit Printer(std::ostream& out = std::cout, std::ostream& err = std::cerr) noexcept;

    void printHelp() const;
    void printResult(const OperationData& data) const;
    void printException(const std::exception& ex) const;

private:
    std::ostream& out_;
    std::ostream& err_;
};