#include "CachedCalculatorRepository.h"

#include "TestHelper.h"
#include "mocks/MockRepository.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

TEST(
    CachedCalculatorRepositoryTests,
    Find_ReturnsCachedValue_WithoutCallingRepository
) {
    MockRepository repo;
    CachedCalculatorRepository cache_repo(repo);

    OperationData op = testhelper::makeBinaryOp(1, '+', 2);
    op.result = 3;
    op.status = OperationData::Status::success;

    EXPECT_CALL(repo, find(_)).Times(1);
    cache_repo.find(op);

    EXPECT_CALL(repo, find(_)).Times(0);

    OperationData op2 = testhelper::makeBinaryOp(1, '+', 2);
    cache_repo.find(op2);

    EXPECT_EQ(op2.result, 3);
    EXPECT_EQ(op2.status, OperationData::Status::success);
}

TEST(CachedCalculatorRepositoryTests, Find_CallsRepositoryOnCacheMiss) {
    MockRepository repo;
    CachedCalculatorRepository cache_repo(repo);

    OperationData op = testhelper::makeBinaryOp(10, '-', 3);

    EXPECT_CALL(repo, find(_)).Times(1).WillOnce(Invoke([](OperationData& d) {
        d.result = 7;
        d.status = OperationData::Status::success;
    }));

    cache_repo.find(op);

    EXPECT_EQ(op.result, 7);
}

TEST(CachedCalculatorRepositoryTests, Save_UpdatesCacheAndRepository) {
    MockRepository repo;
    CachedCalculatorRepository cache_repo(repo);

    OperationData op = testhelper::makeBinaryOp(4, '*', 5);
    op.result = 20;
    op.status = OperationData::Status::success;

    EXPECT_CALL(repo, save(op)).Times(1);

    cache_repo.save(op);

    EXPECT_CALL(repo, find(_)).Times(0);

    OperationData op2 = testhelper::makeBinaryOp(4, '*', 5);
    cache_repo.find(op2);

    EXPECT_EQ(op2.result, 20);
}

TEST(CachedCalculatorRepositoryTests, CommutativeOperations_UseSameCacheKey) {
    MockRepository repo;
    CachedCalculatorRepository cache_repo(repo);

    OperationData op1 = testhelper::makeBinaryOp(1, '+', 2);
    OperationData op2 = testhelper::makeBinaryOp(2, '+', 1);

    EXPECT_CALL(repo, find(_)).Times(1).WillOnce(Invoke([](OperationData& d) {
        d.result = 3;
        d.status = OperationData::Status::success;
    }));

    cache_repo.find(op1);

    EXPECT_CALL(repo, find(_)).Times(0);

    cache_repo.find(op2);

    EXPECT_EQ(op2.result, 3);
}

TEST(
    CachedCalculatorRepositoryTests, NonCommutativeOperations_UseDifferentKeys
) {
    MockRepository repo;
    CachedCalculatorRepository cache_repo(repo);

    OperationData op1 = testhelper::makeBinaryOp(5, '-', 2);
    OperationData op2 = testhelper::makeBinaryOp(2, '-', 5);

    EXPECT_CALL(repo, find(_))
        .Times(2)
        .WillRepeatedly(Invoke([](OperationData& d) {
            d.result = d.first - d.second;
            d.status = OperationData::Status::success;
        }));

    cache_repo.find(op1);
    cache_repo.find(op2);

    EXPECT_EQ(op1.result, 3);
    EXPECT_EQ(op2.result, -3);
}

TEST(CachedCalculatorRepositoryTests, UnaryOperation_UsesCorrectKey) {
    MockRepository repo;
    CachedCalculatorRepository cache_repo(repo);

    OperationData op = testhelper::makeUnaryOp(5, '!');

    EXPECT_CALL(repo, find(_)).Times(1).WillOnce(Invoke([](OperationData& d) {
        d.result = 120;
        d.status = OperationData::Status::success;
    }));

    cache_repo.find(op);

    EXPECT_CALL(repo, find(_)).Times(0);

    OperationData op2 = testhelper::makeUnaryOp(5, '!');
    cache_repo.find(op2);

    EXPECT_EQ(op2.result, 120);
}
