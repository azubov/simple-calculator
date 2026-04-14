#include "PostgresCalculatorRepository.h"

#include "Log.h"

#include <cstddef>
#include <string>
#include <vector>

PostgresCalculatorRepository::PostgresCalculatorRepository(
    PGConnection& connection
) noexcept
    : connection_(connection) {}

void PostgresCalculatorRepository::find(OperationData& data) {
    Log::info("Starting to find data..");

    std::string first = std::to_string(data.first);
    std::string op(1, data.operation);
    std::string second = data.hasSecond ? std::to_string(data.second) : "";

    auto result = connection_.execPrepared("find_op", {first, op, second});

    if (result.rows() == 1) {

        if (!result.isNull(0, 0)) {
            data.result = result.getLong(0, 0);
        }
        data.status = static_cast<OperationData::Status>(result.getInt(0, 1));

        Log::info(fmt::format("Data found successfully: {}", data));
    } else {
        Log::info("Data not found");
    }
}

std::vector<OperationData> PostgresCalculatorRepository::findAll() {
    Log::info("Starting to find all data..");

    auto result =
        connection_.exec("SELECT first_value, operation, second_value, result, "
                         "status FROM calc.operations;");

    int rows = result.rows();

    std::vector<OperationData> operations_data;
    operations_data.reserve((static_cast<size_t>(rows)));

    for (int i = 0; i < rows; ++i) {
        OperationData data{};

        data.first = result.getLong(i, 0);
        data.operation = result.getChar(i, 1);
        data.hasSecond = !result.isNull(i, 2);
        if (!result.isNull(i, 2)) {
            data.second = result.getLong(i, 2);
        }
        if (!result.isNull(i, 3)) {
            data.result = result.getLong(i, 3);
        }
        data.status = static_cast<OperationData::Status>(result.getInt(i, 4));

        operations_data.push_back(data);
    }

    return operations_data;
}

void PostgresCalculatorRepository::save(const OperationData& data) {
    Log::info(fmt::format("Starting to save data: {}", data));

    std::string first = std::to_string(data.first);
    std::string op(1, data.operation);
    std::string second = data.hasSecond ? std::to_string(data.second) : "";
    std::string result = std::to_string(data.result);
    std::string status = std::to_string(static_cast<int>(data.status));

    connection_.execPrepared("save_op", {first, op, second, result, status});

    Log::info("Data saved successfully");
}