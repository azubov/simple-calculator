#include "Calculator.h"
#include "Checker.h"
#include "Parser.h"
#include "Printer.h"
#include "Runner.h"

int main(int argc, char* argv[]) {
    Parser parser;
    Checker checker;
    Calculator calculator;
    Printer printer;

    Runner runner(parser, checker, calculator, printer);
    return runner.run(argc, argv);
}