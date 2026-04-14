#pragma once

#include "CalculatorRepository.h"
#include "PGConnection.h"

class PostgresCalculatorRepository : public CalculatorRepository {
public:
    explicit PostgresCalculatorRepository(PGConnection& connection) noexcept;

    void find(OperationData& data) override;
    std::vector<OperationData> findAll() override;
    void save(const OperationData& data) override;

private:
    PGConnection& connection_;
};