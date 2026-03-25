#include "CalculatorRepository.h"

#include <stdexcept>
#include <string>

CalculatorRepository::CalculatorRepository(const PGConnection& connection
) noexcept
    : connection_(connection) {}

void CalculatorRepository::find(OperationData& data) const {
    std::string first = std::to_string(data.first);
    std::string op(1, data.operation);
    std::string second = data.hasSecond ? std::to_string(data.second) : "";

    const char* params[3];
    params[0] = first.c_str();
    params[1] = op.c_str();
    params[2] = data.hasSecond ? second.c_str() : nullptr;

    PGconn* conn = connection_.connect();

    PGresult* res = PQexecPrepared(
        conn,
        "find_op",
        3,
        static_cast<const char* const*>(params),
        nullptr,
        nullptr,
        0
    );

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::string err = PQerrorMessage(conn);
        PQclear(res);
        throw std::runtime_error("find() failed: " + err);
    }

    if (PQntuples(res) == 1) {
        data.result = std::stoll(PQgetvalue(res, 0, 0));
        data.status =
            static_cast<OperationData::Status>(std::stoi(PQgetvalue(res, 0, 1))
            );
    }

    PQclear(res);
}

void CalculatorRepository::save(const OperationData& data) const {
    std::string first = std::to_string(data.first);
    std::string op(1, data.operation);
    std::string second = data.hasSecond ? std::to_string(data.second) : "";
    std::string result = std::to_string(data.result);
    std::string status = std::to_string(static_cast<int>(data.status));

    const char* params[5];
    params[0] = first.c_str();
    params[1] = op.c_str();
    params[2] = data.hasSecond ? second.c_str() : nullptr;
    params[3] = result.c_str();
    params[4] = status.c_str();

    PGconn* conn = connection_.connect();

    PGresult* res = PQexecPrepared(
        conn,
        "save_op",
        5,
        static_cast<const char* const*>(params),
        nullptr,
        nullptr,
        0
    );

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::string err = PQerrorMessage(conn);
        PQclear(res);
        throw std::runtime_error("save() failed: " + err);
    }

    PQclear(res);
}
