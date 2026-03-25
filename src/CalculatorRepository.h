#pragma once

#include "OperationData.h"
#include "PGConnection.h"

class ICalculatorRepository {
public:
    virtual void find(OperationData&) const = 0;
    virtual void save(const OperationData&) const = 0;
    virtual ~ICalculatorRepository() = default;
};

class CalculatorRepository : public ICalculatorRepository {
public:
    explicit CalculatorRepository(const PGConnection& connection) noexcept;

    void find(OperationData& data) const override;
    void save(const OperationData& data) const override;

private:
    const PGConnection& connection_;
};