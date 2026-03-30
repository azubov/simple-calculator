#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "CalculatorCacheRepository.h"
#include "mocks/MockRepository.h"

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

static OperationData
makeOp(long long a, char op, long long b = 0, bool hasSecond = false) {
    OperationData d{};
    d.first = a;
    d.operation = op;
    d.hasSecond = hasSecond;
    d.second = b;
    return d;
}

TEST(
    CalculatorCacheRepositoryTests,
    Find_ReturnsCachedValue_WithoutCallingRepository
) {
    MockRepository repo;
    CalculatorCacheRepository cacheRepo(repo);

    OperationData op = makeOp(1, '+', 2, true);
    op.result = 3;
    op.status = OperationData::Status::success;

    EXPECT_CALL(repo, find(_)).Times(1);
    cacheRepo.find(op);

    EXPECT_CALL(repo, find(_)).Times(0);

    OperationData op2 = makeOp(1, '+', 2, true);
    cacheRepo.find(op2);

    EXPECT_EQ(op2.result, 3);
    EXPECT_EQ(op2.status, OperationData::Status::success);
}

TEST(CalculatorCacheRepositoryTests, Find_CallsRepositoryOnCacheMiss) {
    MockRepository repo;
    CalculatorCacheRepository cacheRepo(repo);

    OperationData op = makeOp(10, '-', 3, true);

    EXPECT_CALL(repo, find(_)).Times(1).WillOnce(Invoke([](OperationData& d) {
        d.result = 7;
        d.status = OperationData::Status::success;
    }));

    cacheRepo.find(op);

    EXPECT_EQ(op.result, 7);
}

TEST(CalculatorCacheRepositoryTests, Save_UpdatesCacheAndRepository) {
    MockRepository repo;
    CalculatorCacheRepository cacheRepo(repo);

    OperationData op = makeOp(4, '*', 5, true);
    op.result = 20;
    op.status = OperationData::Status::success;

    EXPECT_CALL(repo, save(op)).Times(1);

    cacheRepo.save(op);

    EXPECT_CALL(repo, find(_)).Times(0);

    OperationData op2 = makeOp(4, '*', 5, true);
    cacheRepo.find(op2);

    EXPECT_EQ(op2.result, 20);
}

TEST(CalculatorCacheRepositoryTests, CommutativeOperations_UseSameCacheKey) {
    MockRepository repo;
    CalculatorCacheRepository cacheRepo(repo);

    OperationData op1 = makeOp(1, '+', 2, true);
    OperationData op2 = makeOp(2, '+', 1, true);

    EXPECT_CALL(repo, find(_)).Times(1).WillOnce(Invoke([](OperationData& d) {
        d.result = 3;
        d.status = OperationData::Status::success;
    }));

    cacheRepo.find(op1);

    EXPECT_CALL(repo, find(_)).Times(0);

    cacheRepo.find(op2);

    EXPECT_EQ(op2.result, 3);
}

TEST(
    CalculatorCacheRepositoryTests, NonCommutativeOperations_UseDifferentKeys
) {
    MockRepository repo;
    CalculatorCacheRepository cacheRepo(repo);

    OperationData op1 = makeOp(5, '-', 2, true);
    OperationData op2 = makeOp(2, '-', 5, true);

    EXPECT_CALL(repo, find(_))
        .Times(2)
        .WillRepeatedly(Invoke([](OperationData& d) {
            d.result = d.first - d.second;
            d.status = OperationData::Status::success;
        }));

    cacheRepo.find(op1);
    cacheRepo.find(op2);

    EXPECT_EQ(op1.result, 3);
    EXPECT_EQ(op2.result, -3);
}

TEST(CalculatorCacheRepositoryTests, UnaryOperation_UsesCorrectKey) {
    MockRepository repo;
    CalculatorCacheRepository cacheRepo(repo);

    OperationData op = makeOp(5, '!', 0, false);

    EXPECT_CALL(repo, find(_)).Times(1).WillOnce(Invoke([](OperationData& d) {
        d.result = 120;
        d.status = OperationData::Status::success;
    }));

    cacheRepo.find(op);

    EXPECT_CALL(repo, find(_)).Times(0);

    OperationData op2 = makeOp(5, '!', 0, false);
    cacheRepo.find(op2);

    EXPECT_EQ(op2.result, 120);
}
