#pragma once

#include "PGConnection.h"

#include <libpq-fe.h>

class StatementInitializer {
public:
    static void prepareCalculatorStatements(PGConnection& connection);
};