#pragma once

#include "Printer.h"

class Runner {
public:
    int run(int argc, char* argv[]) const;

private:
    bool handleHelpFlag(int argc, char* argv[], const Printer& printer) const;
};