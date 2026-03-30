#pragma once

#include "CalculatorRepository.h"
#include "OperationData.h"

#include <string>
#include <unordered_map>

class CalculatorCacheRepository : public ICalculatorRepository {
public:
    explicit CalculatorCacheRepository(ICalculatorRepository& repository);

    void find(OperationData& data) override;
    void save(const OperationData& data) override;

private:
    ICalculatorRepository& repository_;
    std::unordered_map<std::string, OperationData> cache_;

    static std::string makeKey(const OperationData& data);
};