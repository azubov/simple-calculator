#pragma once

#include "Printer.h"

#include <istream>
#include <ostream>

class Runner {
public:
    int run(int argc, char* argv[]) const;
    int run(int argc, char* argv[], std::istream& in, std::ostream& out) const;

private:
    bool handleHelpFlag(int argc, char* argv[], const Printer& printer) const;
};