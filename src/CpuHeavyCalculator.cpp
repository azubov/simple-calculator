#include "CpuHeavyCalculator.h"

#include "Log.h"

CpuHeavyCalculator::CpuHeavyCalculator(const Calculator& calculator)
    : calculator_(calculator){};

void CpuHeavyCalculator::calculate(OperationData& data) const {
    Log::info("CpuHeavyCalculator loadCPU");
    volatile long x = 0;
    for (long i = 0; i < 500000000; ++i) {
        x += i;
    }
    calculator_.calculate(data);
}