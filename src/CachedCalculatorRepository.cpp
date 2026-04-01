#include "CachedCalculatorRepository.h"

#include "OperationData.h"

#include <algorithm>
#include <vector>

CachedCalculatorRepository::CachedCalculatorRepository(
    CalculatorRepository& repository
)
    : repository_(repository){};

void CachedCalculatorRepository::find(OperationData& data) {
    auto key = makeKey(data);

    if (auto it = cache_.find(key); it != cache_.end()) {
        data = it->second;
        return;
    }

    repository_.find(data);
    cache_[key] = data;
}

std::vector<OperationData> CachedCalculatorRepository::findAll() {
    std::vector<OperationData> operations_data = repository_.findAll();
    updateCache(operations_data);
    return operations_data;
}

void CachedCalculatorRepository::save(const OperationData& data) {
    repository_.save(data);
    cache_[makeKey(data)] = data;
}

void CachedCalculatorRepository::fillCacheFromRepository() {
    std::vector<OperationData> operations_data = repository_.findAll();
    updateCache(operations_data);
}

std::string CachedCalculatorRepository::makeKey(const OperationData& data) {
    if (!data.hasSecond) {
        return std::to_string(data.first) + data.operation;
    }

    if (data.operation == '+' || data.operation == '*') {
        auto a = std::min(data.first, data.second);
        auto b = std::max(data.first, data.second);
        return std::to_string(a) + data.operation + std::to_string(b);
    }

    return std::to_string(data.first) + data.operation +
           std::to_string(data.second);
}

void CachedCalculatorRepository::updateCache(
    const std::vector<OperationData>& operations_data
) {
    for (const auto& data : operations_data) {
        cache_[makeKey(data)] = data;
    }
}