#include "CachedCalculatorRepository.h"

#include "Log.h"
#include "OperationData.h"

#include <algorithm>
#include <fmt/format.h>
#include <vector>

CachedCalculatorRepository::CachedCalculatorRepository(
    CalculatorRepository& repository
)
    : repository_(repository){};

void CachedCalculatorRepository::find(OperationData& data) {
    auto key = makeKey(data);

    if (auto it = cache_.find(key); it != cache_.end()) {
        Log::info(fmt::format("Cache hit for key '{}'", key));
        data = it->second;
        return;
    }

    Log::info(fmt::format("Cache miss for key '{}', querying repository..", key)
    );
    repository_.find(data);
    cache_[key] = data;
}

std::vector<OperationData> CachedCalculatorRepository::findAll() {
    Log::info("findAll(): fetching all operations from repository");

    std::vector<OperationData> operations_data = repository_.findAll();
    updateCache(operations_data);

    Log::info(fmt::format(
        "findAll(): cache updated with {} operations", operations_data.size()
    ));
    return operations_data;
}

void CachedCalculatorRepository::save(const OperationData& data) {
    auto key = makeKey(data);
    Log::info(fmt::format("save(): saving operation with key '{}'", key));

    repository_.save(data);
    cache_[makeKey(data)] = data;

    Log::debug(fmt::format("save(): cache updated for key '{}'", key));
}

void CachedCalculatorRepository::fillCacheFromRepository() {
    Log::info("Starting to cache warm-up..");

    std::vector<OperationData> operations_data = repository_.findAll();
    updateCache(operations_data);

    Log::info(fmt::format(
        "Cache warm-up completed: {} entries loaded", operations_data.size()
    ));
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
    Log::debug(fmt::format(
        "updateCache(): inserting {} operations", operations_data.size()
    ));

    for (const auto& data : operations_data) {
        cache_[makeKey(data)] = data;
    }
}