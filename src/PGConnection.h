#pragma once

#include <libpq-fe.h>

#include <memory>
#include <string>

class PGConnection {
public:
    PGConnection();

    PGconn* connect() const;

private:
    std::string host_ = "localhost";
    int port_ = 5432;
    std::string db_name_ = "calc-db";
    std::string login_ = "postgres";
    std::string pwd_ = "postgres";

    std::unique_ptr<PGconn, decltype(&PQfinish)> connection_{
        nullptr, &PQfinish
    };

    void prepareStatements() const;
    std::string connectionInfo() const;
};