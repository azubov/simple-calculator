#include "PGConnection.h"

#include "Log.h"

#include <fmt/format.h>
#include <libpq-fe.h>
#include <stdexcept>

PGConnection::PGConnection() {
    Log::info("Connecting with: " + connectionInfo());

    connection_.reset(PQsetdbLogin(
        host_.c_str(),
        std::to_string(port_).c_str(),
        nullptr,
        nullptr,
        db_name_.c_str(),
        login_.c_str(),
        pwd_.c_str()
    ));

    if (PQstatus(connection_.get()) != CONNECTION_OK) {
        std::string err = PQerrorMessage(connection_.get());
        throw std::runtime_error("Connection failed: " + err);
    }

    Log::info("Connection acquired successfully");
}

std::string PGConnection::connectionInfo() const {
    return "host=" + host_ + " port=" + std::to_string(port_) +
           " dbname=" + db_name_ + " user=" + login_;
}

PGResult PGConnection::exec(const std::string& sql) {
    PGResult res(
        PGResult::PGResultPtr(PQexec(connection_.get(), sql.c_str()), &PQclear)
    );

    if (!res.isOk()) {
        std::string err = PQerrorMessage(connection_.get());
        throw std::runtime_error(
            fmt::format("Failed to execute SQL {}: {}", sql, err)
        );
    }

    return res;
}

PGResult PGConnection::execPrepared(
    const std::string& stmt_name, const std::vector<std::string>& params
) {
    std::vector<const char*> c_params;
    c_params.reserve(params.size());

    for (const auto& p : params) {
        c_params.push_back(p.empty() ? nullptr : p.c_str());
    }

    PGResult res(PGResult::PGResultPtr(
        PQexecPrepared(
            connection_.get(),
            stmt_name.c_str(),
            static_cast<int>(c_params.size()),
            c_params.data(),
            nullptr,
            nullptr,
            0
        ),
        &PQclear
    ));

    if (!res.isOk()) {
        std::string err = PQerrorMessage(connection_.get());
        throw std::runtime_error(
            fmt::format("Failed to execute prepared SQL {}: {}", stmt_name, err)
        );
    }

    return res;
}
