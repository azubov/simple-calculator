#include "Parser.h"

#include "Log.h"

#include <nlohmann/json.hpp>

Parser::Parser(std::istream& in) noexcept
    : in_(in) {}

OperationData Parser::parse() const {
    Log::info("Staring to parse input..");

    nlohmann::json json;
    in_ >> json;

    OperationData data;

    if (!json.contains("first") || !json["first"].is_number_integer()) {
        throw std::invalid_argument("Field 'first' must be an integer");
    }
    data.first = json["first"].get<std::int64_t>();

    if (!json.contains("operation") || !json["operation"].is_string()) {
        throw std::invalid_argument("Field 'operation' must be a string");
    }
    const auto& op = json["operation"].get_ref<const std::string&>();
    if (op.size() != 1) {
        throw std::invalid_argument("Field 'operation' must be a single character");
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