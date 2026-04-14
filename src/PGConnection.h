#pragma once

#include "PGResult.h"

#include <libpq-fe.h>
#include <memory>
#include <string>
#include <vector>

class PGConnection {
public:
    PGConnection();

    PGResult exec(const std::string& sql);
    PGResult execPrepared(
        const std::string& stmt_name, const std::vector<std::string>& params
    );

private:
    std::string host_ = "localhost";
    int port_ = 5432;
    std::string db_name_ = "calc-db";
    std::string login_ = "postgres";
    std::string pwd_ = "postgres";

    std::unique_ptr<PGconn, decltype(&PQfinish)> connection_{
        nullptr, &PQfinish
    };

    std::string connectionInfo() const;
};