#include "CalculatorService.h"

#include "Log.h"
#include "OperationData.h"

#include <stdexcept>

CalculatorService::CalculatorService(
    const ICalculatorRepository& repository, const ICalculator& calculator
) noexcept
    : repository_(repository)
    , calculator_(calculator) {}

void CalculatorService::calculate(OperationData& data) const {
    repository_.find(data);

    if (data.status == OperationData::Status::success) {
        return;
    }
    if (data.status == OperationData::Status::invalid_argument) {
        throw std::invalid_argument(
            fmt::format("Operation has invalid_argument: {}", data)
        );
    }
    if (data.status == OperationData::Status::overflow_error) {
        throw std::overflow_error(
            fmt::format("Operation has overflow_error: {}", data)
        );
    }

    try {
        calculator_.calculate(data);
        saveWithStatus(data, OperationData::Status::success);
    } catch (const std::invalid_argument& e) {
        saveWithStatus(data, OperationData::Status::invalid_argument);
        throw;
    } catch (const std::overflow_error& e) {
        saveWithStatus(data, OperationData::Status::overflow_error);
        throw;
    }
}

void CalculatorService::saveWithStatus(
    OperationData& data, OperationData::Status status
) const {
    data.status = status;
    repository_.save(data);
}
