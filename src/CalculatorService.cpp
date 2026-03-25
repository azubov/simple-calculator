#include "CalculatorService.h"
#include "OperationData.h"

#include <stdexcept>

CalculatorService::CalculatorService(
    const ICalculatorRepository& repository, const Calculator& calculator
) noexcept
    : repository_(repository)
    , calculator_(calculator) {}

void CalculatorService::calculate(OperationData& data) const {
    repository_.find(data);

    if (data.status == OperationData::Status::success) {
        return;
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
