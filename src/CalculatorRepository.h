#pragma once

#include "OperationData.h"
#include "PGConnection.h"

class ICalculatorRepository {
public:
    virtual void find(OperationData&) = 0;
    virtual void save(const OperationData&) = 0;
    virtual ~ICalculatorRepository() = default;
};

class CalculatorRepository : public ICalculatorRepository {
public:
    explicit CalculatorRepository(const PGConnection& connection) noexcept;

    void find(OperationData& data) override;
    void save(const OperationData& data) override;

private:
    const PGConnection& connection_;
};