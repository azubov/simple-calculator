#pragma once

#include "CalculatorRepository.h"
#include "OperationData.h"

#include <string>
#include <unordered_map>
#include <vector>

class CachedCalculatorRepository : public CalculatorRepository {
public:
    explicit CachedCalculatorRepository(CalculatorRepository& repository);

    void find(OperationData& data) override;
    std::vector<OperationData> findAll() override;
    void save(const OperationData& data) override;

    void fillCacheFromRepository();

private:
    CalculatorRepository& repository_;
    std::unordered_map<std::string, OperationData> cache_;

    static std::string makeKey(const OperationData& data);
    void updateCache(const std::vector<OperationData>& operations_data);
};