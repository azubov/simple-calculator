#include "StatementInitializer.h"

#include "Log.h"

void StatementInitializer::prepareCalculatorStatements(PGConnection& connection
) {
    Log::debug("Starting to prepare statements..");

    connection.exec(
        "PREPARE find_op AS "
        "SELECT result, status "
        "FROM calc.operations "
        "WHERE first_value = $1 AND operation = $2 AND "
        "(second_value = $3 OR ($3 IS NULL AND second_value IS NULL)) "
        "LIMIT 1"
    );

    Log::debug("find_op prepared successfully");

    connection.exec("PREPARE save_op AS "
                    "INSERT INTO calc.operations (first_value, operation, "
                    "second_value, result, status) "
                    "VALUES ($1, $2, $3, $4, $5)");

    Log::debug("save_op prepared successfully");
}