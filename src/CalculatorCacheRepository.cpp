#include "CalculatorCacheRepository.h"
#include <algorithm>

CalculatorCacheRepository::CalculatorCacheRepository(
    ICalculatorRepository& repository
)
    : repository_(repository){};

void CalculatorCacheRepository::find(OperationData& data) {
    auto key = makeKey(data);

    if (auto it = cache_.find(key); it != cache_.end()) {
        data = it->second;
        return;
    }

    repository_.find(data);
    cache_[key] = data;
}

void CalculatorCacheRepository::save(const OperationData& data) {
    repository_.save(data);
    cache_[makeKey(data)] = data;
}

std::string CalculatorCacheRepository::makeKey(const OperationData& data) {
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
