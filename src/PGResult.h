#pragma once

#include <libpq-fe.h>
#include <memory>
#include <stdexcept>
#include <string>

class PGResult {
public:
    using PGResultPtr = std::unique_ptr<PGresult, decltype(&PQclear)>;

    explicit PGResult(PGResultPtr result)
        : result_(std::move(result)) {
        if (!result_) {
            throw std::runtime_error(
                "PGResult constructed with nullptr PGresult"
            );
        }
    }

    bool hasRows() const {
        return PQresultStatus(result_.get()) == PGRES_TUPLES_OK;
    }

    int rows() const {
        return PQntuples(result_.get());
    }

    bool isNull(int row, int col) const {
        checkBounds(row, col);
        return PQgetisnull(result_.get(), row, col);
    }

    char getChar(int row, int col) const {
        checkBounds(row, col);
        if (isNull(row, col)) {
            throw std::runtime_error("NULL value in getChar");
        }
        auto* v = PQgetvalue(result_.get(), row, col);
        return v ? v[0] : '\0';
    }

    std::string getString(int row, int col) const {
        checkBounds(row, col);
        if (isNull(row, col)) {
            throw std::runtime_error("NULL value in getString");
        }
        return PQgetvalue(result_.get(), row, col);
    }

    long long getLong(int row, int col) const {
        checkBounds(row, col);
        if (isNull(row, col)) {
            throw std::runtime_error("NULL value in getLong");
        }
        return std::stoll(PQgetvalue(result_.get(), row, col));
    }

    int getInt(int row, int col) const {
        checkBounds(row, col);
        if (isNull(row, col)) {
            throw std::runtime_error("NULL value in getInt");
        }
        return std::stoi(PQgetvalue(result_.get(), row, col));
    }

    bool isOk() const {
        auto status = PQresultStatus(result_.get());
        return status == PGRES_TUPLES_OK || status == PGRES_COMMAND_OK;
    }

private:
    PGResultPtr result_;

    void checkBounds(int row, int col) const {
        int r = PQntuples(result_.get());
        int c = PQnfields(result_.get());
        if (row < 0 || row >= r || col < 0 || col >= c) {
            throw std::out_of_range("PGResult index out of range");
        }
    }
};
