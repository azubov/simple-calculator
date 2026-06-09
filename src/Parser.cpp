#include "Parser.h"

#include "Log.h"

#include <exception>

#include <fmt/format.h>
#include <nlohmann/json.hpp>

OperationData Parser::parse(const std::string& msg) const {
    Log::info("Starting to parse input..");

    nlohmann::json json;
    try {
        json = nlohmann::json::parse(msg);
    } catch (const std::exception& ex) {
        throw std::invalid_argument(fmt::format("Invalid Json: {}", ex.what()));
    }

    OperationData data;

    if (!json.contains("first") || !json["first"].is_number_integer()) {
        throw std::invalid_argument("Field 'first' must be an integer");
    }
    data.first = json["first"].get<std::int64_t>();

    if (!json.contains("operation") || !json["operation"].is_string()) {
        throw std::invalid_argument("Field 'operation' must be a string");
    }
    std::string op = json["operation"].get<std::string>();
    if (op.size() != 1) {
        throw std::invalid_argument(
            "Field 'operation' must be a single character"
        );
    }
    data.operation = op[0];

    if (json.contains("second")) {
        if (!json["second"].is_number_integer()) {
            throw std::invalid_argument("Field 'second' must be an integer");
        }
        data.second = json["second"].get<std::int64_t>();
        data.hasSecond = true;
    }

    Log::info("Input parsed successfully");
    return data;
}