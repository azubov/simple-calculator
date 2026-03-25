#pragma once

#include "ICalculatorRepository.h"
#include "PGConnection.h"

class CalculatorRepository : public ICalculatorRepository {
public:
    explicit CalculatorRepository(const PGConnection& connection) noexcept;

    void find(OperationData& data) const override;
    void save(const OperationData& data) const override;

private:
    const PGConnection& connection_;
};