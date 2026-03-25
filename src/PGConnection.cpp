#include "PGConnection.h"

#include <stdexcept>
#include <string>

PGConnection::PGConnection() {
    PGconn* conn = PQsetdbLogin(
        host_.c_str(),
        std::to_string(port_).c_str(),
        nullptr,
        nullptr,
        db_name_.c_str(),
        login_.c_str(),
        pwd_.c_str()
    );

    connection_.reset(conn);

    if (PQstatus(conn) != CONNECTION_OK) {
        throw std::runtime_error(
            "Connection failed: " + std::string(PQerrorMessage(conn))
        );
    }

    prepareStatements();
}

void PGConnection::prepareStatements() {
    PGresult* res{};

    // SELECT
    res = PQprepare(
        connection_.get(),
        "find_op",
        "SELECT result, status "
        "FROM calc.operations "
        "WHERE first_value = $1 AND operation = $2 AND "
        "(second_value = $3 OR ($3 IS NULL AND second_value IS NULL)) "
        "LIMIT 1",
        3,
        nullptr
    );

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::string err = PQerrorMessage(connection_.get());
        PQclear(res);
        throw std::runtime_error("Failed to prepare find_op: " + err);
    }
    PQclear(res);

    // INSERT
    res = PQprepare(
        connection_.get(),
        "save_op",
        "INSERT INTO calc.operations (first_value, operation, second_value, "
        "result, status) "
        "VALUES ($1, $2, $3, $4, $5)",
        5,
        nullptr
    );

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::string err = PQerrorMessage(connection_.get());
        PQclear(res);
        throw std::runtime_error("Failed to prepare save_op: " + err);
    }
    PQclear(res);
}

PGconn* PGConnection::connect() const {
    return connection_.get();
}
